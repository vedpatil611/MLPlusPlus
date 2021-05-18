#include "Nodes.h"

#include <stdio.h>
#include <algorithm>
#include <Algorithms/LinearRegression.h>

#define NODE_ERROR(message)		\
	hasError = true;			\
	strcpy(error, message);		\
	return;

#define DEL(x) try { delete x; } catch(std::exception& e) { }

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

	void Main::execute(std::vector<Node*>& nodes, std::vector<Link*>& links) { }

	void Main::clean() { }

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

	void LinearRegression::execute(std::vector<Node*>& nodes, std::vector<Link*>& links)
	{
		::LinearRegression* lr = new ::LinearRegression();
		output = new Object();
		output->type = DataType::LINEAR_REGRESSION_MODEL;
		output->object = (void*) lr;
	}

	void LinearRegression::clean()
	{
		delete output;
		output = nullptr;
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

	void Set::execute(std::vector<Node*>& nodes, std::vector<Link*>& links)
	{
		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 4 - 1 == links[i]->start_id || start_id + 4 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j) 
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->start_id))
					{
						object->object = nodes[j]->output->object;
						output = object;
						pinParsed = true;
						return;
					}
				}
			}
		}

		if (!pinParsed)
		{
			switch (object->type)
			{
			case DataType::FLOAT:
			{
				double* v = new double;
				*v = atof(name);
				object->object = (void *) v;
				output = object;
				pinParsed = true;
				break;
			}
			case DataType::INT:
			{
				int* v = new int;
				*v = atoi(name);
				object->object = (void*) v;
				output = object;
				pinParsed = true;
				break;
			}
			case DataType::STRING:
			{
				char* v = new char[20];
				strcpy(v, name);
				object->object = (void*) v;
				output = object;
				pinParsed = true;
				break;
			}
			default:
				break;
			}
		}

		if (!pinParsed)
		{
			NODE_ERROR("Input pin not found at set");
		}
	}

	void Set::clean() { }
	
	Get::Get(int id, Object* obj)
		:Node(id), object(obj) 
	{
		outputs.emplace_back(id + 2, object->type);
		output = object;
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

	void Get::execute(std::vector<Node*>& nodes, std::vector<Link*>& links) { }

	void Get::clean() { }
	
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
				strcpy(filepath, fileDialog.GetSelected().string().c_str());
				strcpy(filename, fileDialog.GetSelected().filename().string().c_str());
				//doc = rapidcsv::Document(fileDialog.GetSelected().string().c_str());
				fileSelection = false;
			}
		}

		ImNodes::EndNode();
	}

	void FileReader::execute(std::vector<Node*>& nodes, std::vector<Link*>& links)
	{
		try 
		{
			doc = rapidcsv::Document(filepath);
			output = new Object();
			output->type = DataType::FILE_READER_OBJECT;
			output->object = (void*) &doc;
		}
		catch (std::exception& e)
		{
			NODE_ERROR("file not selected for file reader constructor");
		}
	}

	void FileReader::clean() 
	{
		output = nullptr;
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

	void FR_ReadColumn::execute(std::vector<Node*>& nodes, std::vector<Link*>& links)
	{
		bool pinParsed = false;
		Object* in;
		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 4 - 1 == links[i]->start_id || start_id + 4 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id -1 == links[i]->end_id || nodes[j]->outputs[0].id -1 == links[i]->start_id))
					{
						pinParsed = true;
						in = nodes[j]->output;
						if (in->object == nullptr)
						{
							NODE_ERROR("Filereader object reference is null");
						}
						try 
						{
							auto* doc = static_cast<rapidcsv::Document*>(in->object);
							arr = doc->GetColumn<double>(columnName);
							output = new Object();
							output->type = DataType::ARRAY;
							output->object = (void*)&arr;
							return;
						}
						catch (std::exception e)
						{
							NODE_ERROR("Column name not found");
						}
					}
				}
			}
		}

		if (!pinParsed)
		{
			NODE_ERROR("File reader reference pin not connected");
		}
	}

	void FR_ReadColumn::clean()
	{
		output = nullptr;
		arr.clear();
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

	void LR_Train::execute(std::vector<Node*>& nodes, std::vector<Link*>& links)
	{
		bool lrParsed, rateParsed, iterParsed, xParsed, yParsed;
		lrParsed = rateParsed = iterParsed = xParsed = yParsed = false;

		::LinearRegression* lr;
		double rate;
		int iter;
		std::vector<double> x, y;

		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 4 - 1 == links[i]->start_id || start_id + 4 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->start_id))
					{
						lr = static_cast<::LinearRegression*>(nodes[j]->output->object);
						if (lr == nullptr)
						{
							NODE_ERROR("lr object is null");
						}
						lrParsed = true;
						break;
					}
				}
			}
		}
		if (!lrParsed)
		{
			NODE_ERROR("Lr pin reference not connected");
		}

		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 6 - 1 == links[i]->start_id || start_id + 6 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->start_id))
					{
						rate = *static_cast<double*>(nodes[j]->output->object);
						rateParsed = true;
						if (nodes[j]->output->object == nullptr)
						{
							rateParsed = false;
						}
						break;
					}
				}
			}
		}

		if (!rateParsed)
		{
			try
			{
				rate = atof(this->rate);
			}
			catch (std::exception& e)
			{
				NODE_ERROR("Couldn't parse rate at Linear regression train");
			}
		}

		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 7 - 1 == links[i]->start_id || start_id + 7 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->start_id))
					{
						iter = *static_cast<double*>(nodes[j]->output->object);
						iterParsed = true;
						if (nodes[j]->output->object == nullptr)
						{
							iterParsed = false;
						}
						break;
					}
				}
			}
		}

		if (!iterParsed)
		{
			try
			{
				iter = atoi(this->iter);
			}
			catch (std::exception& e)
			{
				NODE_ERROR("Couldn't parse iterations");
			}
		}

		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 8 - 1 == links[i]->start_id || start_id + 8 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->start_id))
					{
						if (nodes[j]->output->object == nullptr)
						{
							NODE_ERROR("X array reference is null");
						}
						x = *static_cast<std::vector<double>*>(nodes[j]->output->object);
						xParsed = true;
						break;
					}
				}
			}
		}

		if (!xParsed)
		{
			NODE_ERROR("X array reference pin is not connected");
		}

		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 9 - 1 == links[i]->start_id || start_id + 9 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->start_id))
					{
						if (nodes[j]->output->object == nullptr)
						{
							NODE_ERROR("Y array reference is null");
						}
						y = *static_cast<std::vector<double>*>(nodes[j]->output->object);
						yParsed = true;
						break;
					}
				}
			}
		}

		if (!yParsed)
		{
			NODE_ERROR("Y array reference is not connected");
		}

		lr->train(rate, iter, x, y);
		output = new Object();
		output->type = DataType::LINEAR_REGRESSION_MODEL;
		output->object = (void*) lr;
	}

	void LR_Train::clean()
	{
		delete output;
		output = nullptr;
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
	
	void LR_Predict::execute(std::vector<Node*>& nodes, std::vector<Link*>& links)
	{
		bool lrParsed, xParsed;
		lrParsed = xParsed = true;
		::LinearRegression* lr;
		std::vector<double> x;
		
		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 4 - 1 == links[i]->start_id || start_id + 4 - 1 == links[i]->end_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->start_id))
					{
						if (nodes[j]->output->object == nullptr)
						{
							NODE_ERROR("LR object ref is null");
						}
						lr = static_cast<::LinearRegression*>(nodes[j]->output->object);
						break;
					}
				}
			}
		}

		if (!lrParsed)
		{
			NODE_ERROR("LR self reference pin not connected to linear regression train function");
		}

		for (int i = 0; i < links.size(); ++i)
		{
			if (start_id + 6 - 1 == links[i]->start_id || start_id + 6 - 1 == links[i]->start_id)
			{
				for (int j = 0; j < nodes.size(); ++j)
				{
					if (!nodes[j]->outputs.empty() && (nodes[j]->outputs[0].id - 1 == links[i]->end_id || nodes[j]->outputs[0].id - 1 == links[i]->end_id))
					{
						if (nodes[j]->output->object == nullptr)
						{
							NODE_ERROR("X array reference is null")
						}
						x = *static_cast<std::vector<double>*>(nodes[j]->output->object);
						break;
					}
				}
			}
		}

		y = lr->predict(x);
		output = new Object();
		output->type = DataType::ARRAY;
		output->object = (void*) &y;

		#ifdef DEBUG
			for (auto i : y)
				printf("%f\n", i);
		#endif // DEBUG
	}

	void LR_Predict::clean() 
	{ 
		output = nullptr;
		y.clear();
	}
}