#include "NodeEditor.h"

#include <string>
#include <Window.h>
#include <implot/implot.h>

#ifdef DEBUG
#include <Algorithms/LinearRegression.h>
#endif

#define SPAWN_NODE(x) {												\
	ImNodes::SetNodeScreenSpacePos(id, ImGui::GetIO().MousePos);	\
	nodes.emplace_back(new x(id));									\
	id += x::getIdIncreament();										\
}

NodeEditor::NodeEditor(Window* window)
	:window(window)
{
	ImNodes::CreateContext();
	ImPlot::CreateContext();

	auto* m = new Nodes::Main(id);
	nodes.emplace_back(m);
	id += Nodes::Main::getIdIncreament();
	mainRef = m;

#ifdef DEBUG
	::LinearRegression* lr = new ::LinearRegression();
	lr->train(0.0001, 1000, x, y);

	auto* o1 = new Nodes::Object(Nodes::DataType::ARRAY, (void*)&x);
	strcpy(o1->name, "x");
	strcpy(o1->typeSelected, "Array");

	auto* o2 = new Nodes::Object(Nodes::DataType::ARRAY, (void*)&y);
	strcpy(o2->name, "y");
	strcpy(o2->typeSelected, "Array");
	
	auto* o3 = new Nodes::Object(Nodes::DataType::LINEAR_REGRESSION_MODEL, (void*)lr);
	strcpy(o3->name, "lr");
	strcpy(o3->typeSelected, "Linear Regression Object");

	std::vector<double> a;

	objects.emplace_back(o1);
	objects.emplace_back(o2);
	objects.emplace_back(o3);
#endif // DEBUG

}

NodeEditor::~NodeEditor()
{
	for (auto* x : nodes)
		delete x;
	for (auto* x : links)
		delete x;
	for (auto* x : objects)
		delete x;

	ImPlot::DestroyContext();
	ImNodes::DestroyContext();
}

void NodeEditor::renderEditor()
{
	ImGui::Begin("Node Editor");
	ImNodes::BeginNodeEditor();

	// Right click editor to open menu to spawn nodes
	if (ImGui::BeginPopupContextWindow())
	{
		// Set functions
		if (ImGui::BeginMenu("Set"))
		{
			for (int i = 0; i < objects.size(); ++i)
			{
				if (ImGui::MenuItem(objects[i]->name))
					spawnSet(objects[i]->name);
			}
			ImGui::EndMenu();
		}
		// Get functions
		if (ImGui::BeginMenu("Get"))
		{
			for (int i = 0; i < objects.size(); ++i)
			{
				if (ImGui::MenuItem(objects[i]->name))
					spawnGet(objects[i]->name);
			}
			ImGui::EndMenu();
		}
		// Linear regression functions
		if (ImGui::BeginMenu("Linear Regression"))
		{
			if (ImGui::MenuItem("New"))
				SPAWN_NODE(Nodes::LinearRegression);
			if (ImGui::MenuItem("Train"))
				SPAWN_NODE(Nodes::LR_Train);
			if (ImGui::MenuItem("Predict"))
				SPAWN_NODE(Nodes::LR_Predict);

			ImGui::EndMenu();
		}
		// File reader functions
		if (ImGui::BeginMenu("File Reader"))
		{
			if (ImGui::MenuItem("new"))
				SPAWN_NODE(Nodes::FileReader);
			if (ImGui::MenuItem("Read Column"))
				SPAWN_NODE(Nodes::FR_ReadColumn);
			
			ImGui::EndMenu();
		}
		// Plot graph node
		if (ImGui::MenuItem("Plot Graph"))
			SPAWN_NODE(Nodes::PlotGraph);

		ImGui::EndPopup();
	}

	for (auto x : nodes)
		x->show();
	for (auto l : links)
		ImNodes::Link(l->id, l->start_id, l->end_id);

	ImNodes::EndNodeEditor();

	// link creation check
	{
		static int id = 0;
		int start_id, end_id;
		if (ImNodes::IsLinkCreated(&start_id, &end_id))
		{
			links.emplace_back(new Nodes::Link(++id, start_id, end_id));

			for (int i = 0; i < nodes.size(); ++i)
			{
				if (nodes[i]->n == start_id)
				{
					for (int j = 0; j < nodes.size(); ++j)
					{
						if (nodes[j]->p == end_id)
						{
							nodes[i]->next = nodes[j];
							nodes[j]->prev = nodes[i];
							break;
						}
					}
				}
			}
		}
	}

	// link break check
	{
		int link_id;
		if (ImNodes::IsLinkDestroyed(&link_id))
		{
			auto iter = std::find_if(links.begin(), links.end(), [link_id](const Nodes::Link* link) -> bool
				{
					return link->id == link_id;
				});
			assert(iter != links.end());
			links.erase(iter);
		}
	}

	// 294 is code for F5
	// start executing code
	if (window->getKeys()[294])
	{
		auto* t = mainRef;
		while (t != nullptr)
		{
			t->execute(nodes, links);
			if (t->hasError)
			{
				printf("%s\n", t->error);
				t->hasError = false;
				break;
			}
			t = t->next;
		}

		// Garabage collection
		/*t = mainRef;
		while (t != nullptr)
		{
			t->clean();
			t = t->next;
		}*/

		for (auto obj : objects)
			delete obj->object;
	}

	// delete nodes and link
	// 261 is code for delete key
	if (window->getKeys()[261])
	{
		int ns[128] = { 0 };
		ImNodes::GetSelectedNodes(ns);

		for (auto x = nodes.begin(); x != nodes.end();)
		{
			auto it = std::find(ns, ns + 128, (*x)->start_id);
			//if ((*x)->start_id == 1) continue; // avoid deleting main function
				
			if (it < ns + 128)
			{
				if (x == nodes.end() - 1)
				{
					x = nodes.erase(x);
					break;
				}
				x = nodes.erase(x);
				if (nodes.empty()) break;
			}
			else ++x;
		}

		int ls[128] = { 0 };
		ImNodes::GetSelectedLinks(ls);

		// delete selected links
#ifdef OS_LINUX
		for (auto x = links.begin(); x < links.end();)
#elif OS_WINDOWS
        for (auto& x = links.begin(); x < links.end();)
#endif
		{
			auto it = std::find(ls, ls + 128, (*x)->id);
			if (it < ls + 128)
			{
				if (x == links.end() - 1)
				{
					x = links.erase(x);
					break;
				}
				x = links.erase(x);
				if (links.empty()) break;
			}
			else ++x;
		}
	}

	ImGui::End();
}

void NodeEditor::renderGraph()
{
	if (Graphs::plotter != nullptr)
	{
		Graphs::plotter->plot();
	}
}

void NodeEditor::renderVariablesPanel()
{
	ImGui::Begin("Variables");

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::MenuItem("Add Variable"))
		{
			objects.emplace_back(new Nodes::Object(Nodes::DataType::FLOAT));
		}
		ImGui::EndPopup();
	}

	ImGui::BeginTable("Var table", 2);
	ImGui::TableNextColumn();
	ImGui::TableHeader("Variable Name");
	ImGui::TableNextColumn();
	ImGui::TableHeader("Data Type");

	char s[8] = "var";
	for (int i = 0; i < objects.size(); ++i)
	{
		sprintf(s, "var%d", i);
		ImGui::TableNextRow();

		ImGui::TableNextColumn();
		ImGui::PushItemWidth(-1);
		ImGui::InputText(s, objects[i]->name, 64);
		ImGui::PopItemWidth();

		ImGui::TableNextColumn();
		ImGui::PushItemWidth(-1);
		if (ImGui::BeginCombo(objects[i]->name, objects[i]->typeSelected))
		{
			if (ImGui::Selectable("Integer"))					{ objects[i]->type = Nodes::DataType::INT;						strcpy(objects[i]->typeSelected, "Integer");					}
			if (ImGui::Selectable("Float"))						{ objects[i]->type = Nodes::DataType::FLOAT;					strcpy(objects[i]->typeSelected, "Float");						}
			if (ImGui::Selectable("String"))					{ objects[i]->type = Nodes::DataType::STRING;					strcpy(objects[i]->typeSelected, "String");						}
			if (ImGui::Selectable("Bool"))						{ objects[i]->type = Nodes::DataType::BOOL;						strcpy(objects[i]->typeSelected, "Bool");						}
			if (ImGui::Selectable("Array"))						{ objects[i]->type = Nodes::DataType::ARRAY;					strcpy(objects[i]->typeSelected, "Array");						}
			if (ImGui::Selectable("Linear Regression Object"))	{ objects[i]->type = Nodes::DataType::LINEAR_REGRESSION_MODEL;	strcpy(objects[i]->typeSelected, "Linear Regression Object");	}
			if (ImGui::Selectable("File Reader Object"))		{ objects[i]->type = Nodes::DataType::FILE_READER_OBJECT;		strcpy(objects[i]->typeSelected, "File Reader Object");			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}
	ImGui::EndTable();

	ImGui::End();
}

void NodeEditor::spawnSet(const char* varName)
{
	ImNodes::SetNodeScreenSpacePos(id, ImGui::GetIO().MousePos);
	Nodes::Object* obj = nullptr;
	for (int i = 0; i < objects.size(); ++i)
	{
		if (strcmp(varName, objects[i]->name) == 0)
		{
			obj = objects[i];
			break;
		}
	}
	nodes.emplace_back(new Nodes::Set(id, obj));
	id += Nodes::Set::getIdIncreament();
}

void NodeEditor::spawnGet(const char* varName)
{
	ImNodes::SetNodeScreenSpacePos(id, ImGui::GetIO().MousePos);
	Nodes::Object* obj = nullptr;
	for (int i = 0; i < objects.size(); ++i)
	{
		if (strcmp(varName, objects[i]->name) == 0)
		{
			obj = objects[i];
			break;
		}
	}
	nodes.emplace_back(new Nodes::Get(id, obj));
	id += Nodes::Get::getIdIncreament();
}
