#include "Nodes.h"

#include <stdio.h>

namespace Nodes
{
	Main::Main(int id)
		:Node(id, -1, id + 1) {}

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
		:Node(id, id + 1, id + 2) 
	{
		outputs.emplace_back(id + 4, DataType::LINEAR_REGRESSION_MODEL);
	}

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
		:Node(id, id + 1, id + 2), object(obj)
	{
		count = ++s_count;
		inputs.emplace_back(id + 4, object->type);
		outputs.emplace_back(id + 5, object->type);
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
		ImGui::Text(object->name);
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}
	
	Get::Get(int id, Object* obj)
		:Node(id), object(obj) 
	{
		outputs.emplace_back(id + 2, object->type);
	}

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
		ImGui::Text(object->name);
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}
	
	FileReader::FileReader(int id)
		:Node(id, id + 1, id + 2) 
	{
		count = ++s_count;
		fileDialog.SetTitle("Select File");
		fileDialog.SetTypeFilters({ ".csv" });

		outputs.emplace_back(id + 5, DataType::FILE_READER_OBJECT);
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
		ImNodes::EndStaticAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Indent(100);
		ImGui::Text("self");
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
		:Node(id, id + 1, id + 2)
	{
		count = ++s_count;

		inputs.emplace_back(id + 4, DataType::FILE_READER_OBJECT);
		outputs.emplace_back(id + 5, DataType::ARRAY);
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
		:Node(id, id + 1, id + 2) 
	{
		count = ++s_count;

		inputs.emplace_back(id + 4, DataType::LINEAR_REGRESSION_MODEL);
		inputs.emplace_back(id + 6, DataType::FLOAT);
		inputs.emplace_back(id + 7, DataType::INT);
		inputs.emplace_back(id + 8, DataType::ARRAY);
		inputs.emplace_back(id + 9, DataType::ARRAY);
		outputs.emplace_back(id + 5, DataType::LINEAR_REGRESSION_MODEL);
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
		ImGui::Indent(90);
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

	LR_Predict::LR_Predict(int id)
		:Node(id, id + 1, id + 2)
	{
		inputs.emplace_back(id + 4, DataType::LINEAR_REGRESSION_MODEL);
		inputs.emplace_back(id + 6, DataType::ARRAY);

		outputs.emplace_back(id + 5, DataType::LINEAR_REGRESSION_MODEL);
	}

	void LR_Predict::show()
	{
		int id = start_id;

		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		ImGui::Text("Predict");
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
		ImGui::Text("y array");
		ImNodes::EndOutputAttribute();

		ImGui::NewLine();
		ImNodes::BeginInputAttribute(id++);
		ImGui::Text("x array");
		ImNodes::EndInputAttribute();

		ImNodes::EndNode();
	}
}