#include "Nodes.h"

Nodes::Main::Main(int id)
	:Node(id) {}

void Nodes::Main::show()
{
	ImNodes::BeginNode(start_id);

	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("Main");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginOutputAttribute(start_id + 1);
	ImGui::Text("Start");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}

Nodes::LinearRegression::LinearRegression(int id)
	:Node(id) {}

void Nodes::LinearRegression::show()
{
	int id = start_id;
	ImNodes::BeginNode(id++);

	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("LinearRegression");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginInputAttribute(id++);
	ImNodes::EndInputAttribute();

	ImGui::SameLine();
	ImNodes::BeginOutputAttribute(id++);
	ImGui::Indent(50);
	ImNodes::EndOutputAttribute();

	ImGui::NewLine();
	ImNodes::BeginOutputAttribute(id++);
	ImGui::Indent(90);
	ImGui::Text("object");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}

Nodes::LR_SetLearningRate::LR_SetLearningRate(int id)
	:Node(id) {}

void Nodes::LR_SetLearningRate::show()
{
	int id = start_id;
	ImNodes::BeginNode(id++);

	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("Set");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginInputAttribute(id++);
	ImNodes::EndOutputAttribute();

	ImNodes::BeginOutputAttribute(id++);
	ImNodes::EndOutputAttribute();

	ImGui::NewLine();

	ImNodes::BeginInputAttribute(id++);
	ImGui::Text("lr object");
	ImNodes::EndInputAttribute();

	ImGui::SameLine();
	ImNodes::BeginOutputAttribute(id++);
	ImGui::Indent(100);
	ImGui::Text("lr object");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}
