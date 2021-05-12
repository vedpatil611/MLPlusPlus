#include "Nodes.h"

#include <stdio.h>

namespace Nodes
{
	Main::Main(int id)
		:Node(id) {}

	void Main::show()
	{
		int id = start_id;
		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted("Main");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginOutputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImGui::Text("Start");
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}

	LinearRegression::LinearRegression(int id)
		:Node(id) {}

	void LinearRegression::show()
	{
		int id = start_id;
		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted("LinearRegression");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Indent(90);
		ImGui::Text("object");
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}

	Set::Set(int id, Object* obj)
		:Node(id), object(obj)
	{
		count = ++s_count;
	}
	
	void Set::show()
	{
		int id = start_id;
		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		char t[64];
		sprintf(t, "Set %s", object->name);
		ImGui::TextUnformatted(t);
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();

		char s[8];
		sprintf(s, "name%d", count);
		switch (object->type)
		{
		case DataType::INT:
		case DataType::FLOAT:
		case DataType::STRING:
		{
			ImNodes::BeginInputAttribute(id++);
			ImGui::PushItemWidth(50);
			ImGui::PushID(ImGui::GetID(s));
			ImGui::InputText("value", name, 16);
			ImGui::PopID();
			ImGui::PopItemWidth();
			ImNodes::EndInputAttribute();
			break;
		}
		default:
			ImNodes::BeginInputAttribute(id++);
			ImGui::Text("value");
			ImNodes::EndInputAttribute();
			break;
		}

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Indent(100);
		ImGui::Text("lr object");
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}
	
	LR_SetIterations::LR_SetIterations(int id)
		:Node(id) 
	{
		count = ++s_count;
	}
	
	void LR_SetIterations::show()
	{
		int id = start_id;
		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted("Set Iterations");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		ImGui::Text("lr object");
		ImNodes::EndInputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		char t[4] = "";
		sprintf(t, "t%d", count);
		ImGui::PushItemWidth(30);
		ImGui::PushID(ImGui::GetID(t));
		ImGui::InputText("value", value, 16);
		ImGui::PopID();
		ImGui::PopItemWidth();
		ImNodes::EndInputAttribute();

		ImNodes::EndNode();
	}
	
	Get::Get(int id, Object* obj)
		:Node(id), object(obj) {}

	void Get::show()
	{
		int id = start_id;

		ImNodes::BeginNode(id++);

		char title[64] = "";
		sprintf(title, "Get %s", object->name);
		ImNodes::BeginNodeTitleBar();
		ImGui::Text(title);
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginOutputAttribute(id++);
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}
	
	FileReader::FileReader(int id)
		:Node(id) 
	{
		count = ++s_count;
		fileDialog.SetTitle("Select File");
		fileDialog.SetTypeFilters({ ".csv" });
	}

	void FileReader::show()
	{
		int id = start_id;
		ImNodes::BeginNode(id++);
		
		ImNodes::BeginNodeTitleBar();
		ImGui::Text("File Reader");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginStaticAttribute(id++);
		ImGui::PushItemWidth(50);
		ImGui::InputText("Filename", filename, 64, ImGuiInputTextFlags_ReadOnly);
		ImGui::PopItemWidth();
		ImGui::Indent(100);
		ImNodes::EndStaticAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Text("obj");
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginStaticAttribute(id++);
		if (ImGui::Button("Select File"))
		{
			fileSelection = true;
			fileDialog.Open();
		}
		ImNodes::EndStaticAttribute();

		if (fileSelection)
		{
			fileDialog.Display();
			if (fileDialog.HasSelected())
			{
				strcpy(filename, fileDialog.GetSelected().filename().string().c_str());
				//doc = rapidcsv::Document(fileDialog.GetSelected().string().c_str());
				fileSelection = false;
			}
		}

		ImNodes::EndNode();
	}
	
	FR_ReadColumn::FR_ReadColumn(int id)
		:Node(id)
	{
		count = ++s_count;
	}

	void FR_ReadColumn::show()
	{
		int id = start_id;

		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		ImGui::Text("Read Column");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		ImGui::Text("self");
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Indent(90);
		ImGui::Text("Array");
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginStaticAttribute(id++);
		char colName[4] = "";
		sprintf(colName, "c%d", count);
		ImGui::PushItemWidth(50);
		ImGui::PushID(ImGui::GetID(colName));
		ImGui::InputText("Column Name", columnName, 32);
		ImGui::PopID();
		ImGui::PopItemWidth();
		ImNodes::EndStaticAttribute();

		ImNodes::EndNode();
	}

	LR_Train::LR_Train(int id)
		:Node(id) 
	{
		count = ++s_count;
	}

	void LR_Train::show()
	{
		int id = start_id;
		
		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		ImGui::Text("Train");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++, ImNodesPinShape_TriangleFilled);
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		ImGui::Text("self");
		ImNodes::EndInputAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Text("self");
		ImNodes::EndOutputAttribute();

		char colName[8] = "";
		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		sprintf(colName, "tr%d", count);
		ImGui::PushItemWidth(50);
		ImGui::PushID(ImGui::GetID(colName));
		ImGui::InputText("Rate", rate, 8);
		ImGui::PopID();
		ImGui::PopItemWidth();
		ImNodes::EndInputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		sprintf(colName, "tr%d", count);
		ImGui::PushItemWidth(50);
		ImGui::PushID(ImGui::GetID(colName));
		ImGui::InputText("Iterations", iter, 8);
		ImGui::PopID();
		ImGui::PopItemWidth();
		ImNodes::EndInputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		ImGui::Text("x");
		ImNodes::EndInputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		ImGui::Text("y");
		ImNodes::EndInputAttribute();

		ImNodes::EndNode();
	}
}