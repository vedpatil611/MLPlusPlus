#include <ImGui/imgui.h>
#include <imfilebrowser.h>
#include <rapidcsv.h>
#include <stdio.h>
#include <vector>

#include "Window.h"
#include "Algorithms/LinearRegression.h"
#include "UI/DockableWindow.h"

static ImGui::FileBrowser fileDialog;

void PropertyPanel();

int main()
{
	Window window;

	DockableWindow::init(&window);

	fileDialog.SetTitle("Select File");
	fileDialog.SetTypeFilters({ ".csv" });

	while (!window.shouldClose())
	{
		window.pollInput();
		window.clearBuffer();

		DockableWindow::begin();
		PropertyPanel();
		DockableWindow::end();

		window.swapBuffer();
	}

	DockableWindow::destroy();
	return 0;
}

void PropertyPanel()
{
	static char selectedFile[256] = "null";
	static bool fileSelection = false;
	
	ImGui::Begin("Property");

	ImGui::Text("Train dataset");

	//ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
	//ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	//ImGui::Text(selectedFile);
	ImGui::InputText("", selectedFile, 256, ImGuiInputTextFlags_ReadOnly);
	//ImGui::PopStyleColor();
	//ImGui::PopStyleVar();

	if (ImGui::Button("Select File"))
	{
		fileSelection = true;
		fileDialog.Open();
	}

	if (fileSelection)
	{
		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			strcpy(selectedFile, fileDialog.GetSelected().string().c_str());

			rapidcsv::Document doc(selectedFile);
			std::vector<double>& x = doc.GetColumn<double>("x");
			std::vector<double>& y = doc.GetColumn<double>("y");

			LinearRegression lr(0.0001f, 1000);
			lr.train(x, y);

			rapidcsv::Document testDoc("dataset/test.csv");
			auto& td = testDoc.GetColumn<double>("x");
			auto r = lr.predict(td);
			for (unsigned int i = 0; i < r.size() ; ++i)
			{
				printf("%f\n", r[i]);
			}

			fileSelection = false;
		}
	}

	ImGui::End();
}
