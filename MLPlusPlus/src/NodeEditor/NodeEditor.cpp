#include "NodeEditor.h"

NodeEditor::NodeEditor()
{
	ImNodes::CreateContext();
}

NodeEditor::~NodeEditor()
{
	for (auto* x : nodes)
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

void NodeEditor::spawnMain()
{
	nodes.emplace_back(new Nodes::Main(id));
	id += Nodes::Main::getIdIncreament();
}

void NodeEditor::spawnNewLinearRegression()
{
	/*static char rate[10];
	static char iter[10];
	ImNodes::BeginNode(getNextId());

	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("Linear Regression");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginInputAttribute(getNextId());
	ImGui::InputText("Learning rate", rate, 10);
	ImNodes::EndInputAttribute();

	ImGui::SameLine();
	ImNodes::BeginOutputAttribute(getNextId());
	ImGui::Text("lr object");
	ImNodes::EndOutputAttribute();

	ImNodes::BeginInputAttribute(getNextId());
	ImGui::InputText("Iterrations", iter, 10);
	ImNodes::EndInputAttribute();

	ImNodes::BeginOutputAttribute(getNextId());
	ImGui::Text("Start");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();*/
}
