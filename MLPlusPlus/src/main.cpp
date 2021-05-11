#include <Core.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imfilebrowser.h>
#include <rapidcsv.h>
#include <stdio.h>
#include <vector>

#include <Algorithms/LinearRegression.h>
#include <NodeEditor/NodeEditor.h>
#include <NodeEditor/NodeLink.h>
#include <Plotter/Shader.h>
#include <Plotter/LineRenderer.h>
#include <Plotter/PointRenderer.h>
#include <UI/DockableWindow.h>
#include <vendors/imnodes/imnodes.h>
#include <Window.h>

Window* window;
static ImGui::FileBrowser fileDialog;
LinearRegression* lr;
NodeEditor* nodeEditor;
PointRenderer* pointRenderer;
LineRenderer* lineRenderer;

void PropertyPanel();
void ShowNodeEditor();

int main()
{
	window = new Window();

	DockableWindow::init(window);
	nodeEditor = new NodeEditor();
	nodeEditor->spawnMain();

	fileDialog.SetTitle("Select File");
	fileDialog.SetTypeFilters({ ".csv" });

	Shader pointShader("Shaders/Point.vert.glsl", "Shaders/Point.frag.glsl");
	pointRenderer = new PointRenderer(&pointShader);
	lineRenderer = new LineRenderer(&pointShader);

	while (!window->shouldClose())
	{
		window->pollInput();
		window->clearBuffer();

		lineRenderer->draw(window, 0.0f);
		pointRenderer->draw(window, 0.0f);
		
		DockableWindow::begin();
		PropertyPanel();
		ShowNodeEditor();
		DockableWindow::end();

		window->swapBuffer();
	}

	delete pointRenderer;
	delete lr;
	delete nodeEditor;
	DockableWindow::destroy();
	delete window;
	return 0;
}

void PropertyPanel()
{
	static char selectedFile[256] = "null";
	static char selectedFileTest[256] = "null";
	static char xLabel[64] = "";
	static char xLabelTest[64] = "";
	static char yLabel[64] = "";
	static char learningRateC[16] = "0.01";
	static double learningRate = 0.01;
	static char epochC[16] = "1000";
	static unsigned int epoch = 1000;
	static bool fileSelection = false;
	static bool testFileSelection = false;
	static std::vector<double> x, y;
	static std::vector<double> xp, res;
	static rapidcsv::Document doc; 

	ImGui::Begin("Property");

	ImGui::Text("Train dataset");
	ImGui::PushItemWidth(-1);
	ImGui::InputText("TrainFile", selectedFile, 256, ImGuiInputTextFlags_ReadOnly);
	ImGui::PopItemWidth();

	if (ImGui::Button("Select File"))
	{
		fileSelection = true;
		fileDialog.Open();
	}

	ImGui::Text("X Label");
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	ImGui::InputText("X Label", xLabel, 64);
	ImGui::PopItemWidth();

	ImGui::Text("Y Label");
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	ImGui::InputText("Y Label", yLabel, 64);
	ImGui::PopItemWidth();

	ImGui::Text("Learning Rate");
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	ImGui::InputText("LearningRate", learningRateC, 16, ImGuiInputTextFlags_CharsDecimal);
	ImGui::PopItemWidth();

	ImGui::Text("Iterations   ");
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	ImGui::InputText("Iterations", epochC, 16, ImGuiInputTextFlags_CharsDecimal);
	ImGui::PopItemWidth();


	if (ImGui::Button("Train"))
	{
		x = doc.GetColumn<double>(xLabel);
		y = doc.GetColumn<double>(yLabel);
		
		learningRate = atof(learningRateC);
		epoch = atoi(epochC);

		delete lr;
		lr = new LinearRegression(learningRate, epoch);
		lr->train(x, y);
	}

	ImGui::Text("Prediction dataset");
	ImGui::PushItemWidth(-1);
	ImGui::InputText("SelectFileP", selectedFileTest, 256, ImGuiInputTextFlags_ReadOnly);
	ImGui::PopItemWidth();

	if (ImGui::Button("Select Prediction File"))
	{
		testFileSelection = true;
		fileDialog.Open();
	}
	
	ImGui::Text("X Label");
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	ImGui::InputText("PredictLabel", xLabelTest, 64);
	ImGui::PopItemWidth();
	
	if (ImGui::Button("Predict"))
	{
		xp = doc.GetColumn<double>(xLabelTest);
		res = lr->predict(xp);
		for (int i = 0; i < xp.size(); ++i)
			printf("%f\t%f\n", xp[i], res[i]);
	}

	if (ImGui::Button("Plot Graph"))
	{
		pointRenderer->begin();

		double xMin, yMin, xMax, yMax;
		xMin = xMax = xp[0];
		yMin = yMax = res[0];
		for (int i = 0; i < 300; ++i)
		{
			pointRenderer->submit(xp[i], res[i], { 0.0f, 1.0f, 0.0f, 1.0f });

			if (xMin > xp[i])	xMin = xp[i];
			if (yMin > res[i])	yMin = res[i];
			if (xMax < xp[i])	xMax = xp[i];
			if (yMax < res[i])	yMax = res[i];
		}
		pointRenderer->end();
		
		lineRenderer->begin();
		lineRenderer->submit(xMin - 30.0, 0.0, xMax + 30.0, 0.0, { 1.0f, 0.0f, 0.0f, 1.0f });
		lineRenderer->submit(0.0, yMin - 30.0, 0.0, yMax + 30.0, { 0.0f, 0.0f, 1.0f, 1.0f });
		lineRenderer->submit(xMin - 30.0, lr->getY(xMin - 30.0), xMax + 30.0, lr->getY(xMax + 30.0), { 0.8f, 0.0f, 0.8f, 1.0f });
		lineRenderer->end();

		window->setProjCoords(xMin - 20, xMax + 20, yMin - 20, yMax + 20);
	}

	// file browser 
	if (fileSelection)
	{
		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			strcpy(selectedFile, fileDialog.GetSelected().filename().string().c_str());
			doc = rapidcsv::Document(fileDialog.GetSelected().string().c_str());
			fileSelection = false;
		}
	}
	if (testFileSelection)
	{
		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			strcpy(selectedFileTest, fileDialog.GetSelected().filename().string().c_str());
			doc = rapidcsv::Document(fileDialog.GetSelected().string().c_str());
			testFileSelection = false;
		}
	}

	ImGui::End();
}

void ShowNodeEditor()
{
	static int c_id = 0;
	ImGui::Begin("Node Editor");
	ImNodes::BeginNodeEditor();

	if (ImGui::BeginPopupContextWindow())
	{
		if(ImGui::BeginMenu("Linear Regression"))
		{
			if (ImGui::MenuItem("New"))
			{
				nodeEditor->spawnNewLinearRegression();
			}
			if (ImGui::MenuItem("Set"))
			{
				nodeEditor->spawnSetLinearRegressionObject();
			}
			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}

	for (auto x : *nodeEditor)
		x->show();
	for (auto l : nodeEditor->getLinks())
		ImNodes::Link(l->id, l->start_id, l->end_id);

	ImNodes::EndNodeEditor();

	{
		int start_id, end_id;
		if (ImNodes::IsLinkCreated(&start_id, &end_id))
			nodeEditor->addLink(new Nodes::Link(++c_id, start_id, end_id));
	}

	{
		int link_id;
		if (ImNodes::IsLinkDestroyed(&link_id))
		{
			auto& links = nodeEditor->getLinks();
			auto iter = std::find_if(links.begin(), links.end(), [link_id](const Nodes::Link* link) -> bool 
			{
				return link->id == link_id;
			});
			assert(iter != links.end());
			links.erase(iter);
		}
	}

	ImGui::End();
}
