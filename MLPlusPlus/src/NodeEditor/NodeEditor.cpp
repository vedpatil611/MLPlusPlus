#include "NodeEditor.h"

unsigned int NodeEditor::getNextId()
{
	return ++id;
}

void NodeEditor::init()
{
	ImNodes::CreateContext();
	//ImNodes::SetNodeGridSpacePos(1, ImVec2(200.0f, 200.0f));
}

void NodeEditor::destroy()
{
	ImNodes::DestroyContext();
}

void NodeEditor::spawnMain()
{
	ImNodes::BeginNode(1);

	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("Main");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginOutputAttribute(2);
	ImGui::Text("Start");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}

void NodeEditor::spawnNewLinearRegression()
{
	static char rate[10];
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

	ImNodes::EndNode();
}
