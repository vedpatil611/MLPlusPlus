#include "NodeEditor.h"

#include <string>
#include <Window.h>

NodeEditor::NodeEditor(Window* window)
	:window(window)
{
	ImNodes::CreateContext();
}

NodeEditor::~NodeEditor()
{
	for (auto* x : nodes)
		delete x;
	for (auto* x : links)
		delete x;

	ImNodes::DestroyContext();
}

NodeEditor::Iterator NodeEditor::begin()
{
	return nodes.begin();
}

NodeEditor::Iterator NodeEditor::end()
{
	return nodes.end();
}

void NodeEditor::renderEditor()
{
	ImGui::Begin("Node Editor");
	ImNodes::BeginNodeEditor();

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::BeginMenu("Linear Regression"))
		{
			if (ImGui::MenuItem("New"))
			{
				spawnNewLinearRegression();
			}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Set"))
		{
			spawnSet();
		}
		ImGui::EndPopup();
	}

	for (auto x : nodes)
		x->show();
	for (auto l : links)
		ImNodes::Link(l->id, l->start_id, l->end_id);

	ImNodes::EndNodeEditor();

	{
		static int id = 0;
		int start_id, end_id;
		if (ImNodes::IsLinkCreated(&start_id, &end_id))
			addLink(new Nodes::Link(++id, start_id, end_id));
	}

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

	if (window->getKeys()[261])
	{
		int ns[128] = { 0 };
		ImNodes::GetSelectedNodes(ns);

		for (auto& x = nodes.begin(); x != nodes.end();)
		{
			auto it = std::find(ns, ns + 128, (*x)->start_id);
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

		for (auto x = links.begin(); x < links.end();)
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

void NodeEditor::renderVariablesPanel()
{
	ImGui::Begin("Variables");

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::MenuItem("Add Variable"))
		{
			objects.emplace_back(new Nodes::Object(Nodes::DataType::FLOAT, nullptr));
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

		ImGui::TableNextColumn();
		ImGui::Text("Float");
	}
	ImGui::EndTable();

	ImGui::End();
}

void NodeEditor::spawnMain()
{
	nodes.emplace_back(new Nodes::Main(id));
	id += Nodes::Main::getIdIncreament();
}

void NodeEditor::spawnSet()
{
	nodes.emplace_back(new Nodes::Set(id));
	id += Nodes::Set::getIdIncreament();
}

void NodeEditor::spawnNewLinearRegression()
{
	nodes.emplace_back(new Nodes::LinearRegression(id));
	id += Nodes::LinearRegression::getIdIncreament();
}

void NodeEditor::addLink(Nodes::Link* link)
{
	links.emplace_back(link);
}
