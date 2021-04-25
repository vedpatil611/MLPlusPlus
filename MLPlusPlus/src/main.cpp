#include <ImGui/imgui.h>
#include <imfilebrowser.h>
#include <rapidcsv.h>
#include <stdio.h>
#include <vector>

#include "Algorithms/LinearRegression.h"
#include "Plotter/Shader.h"
#include "UI/DockableWindow.h"
#include "Window.h"

static ImGui::FileBrowser fileDialog;
LinearRegression* lr;

void PropertyPanel();

int main()
{
	Window window;

	DockableWindow::init(&window);

	fileDialog.SetTitle("Select File");
	fileDialog.SetTypeFilters({ ".csv" });

	Shader pointShader("Shaders/Point.vert.glsl", "Shaders/Point.frag.glsl");

	while (!window.shouldClose())
	{
		window.pollInput();
		window.clearBuffer();

		DockableWindow::begin();
		PropertyPanel();
		DockableWindow::end();

		window.swapBuffer();
	}

	delete lr;
	DockableWindow::destroy();
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

	if (ImGui::Button("Plot Graph"))
	{

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
		auto xp = doc.GetColumn<double>(xLabelTest);
		auto res = lr->predict(xp);
		for (int i = 0; i < xp.size(); ++i)
			printf("%f\t%f\n", xp[i], res[i]);
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
