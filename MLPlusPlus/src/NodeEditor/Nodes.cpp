#include "Nodes.h"

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

		ImNodes::BeginOutputAttribute(id++);
		ImGui::Text("Start");
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}

	int Main::lastIdOffset() const
	{
		return 2;
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

	int LinearRegression::lastIdOffset() const
	{
		return 4;
	}

	LR_SetLearningRate::LR_SetLearningRate(int id)
		:Node(id) {}

	void LR_SetLearningRate::show()
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
	int LR_SetLearningRate::lastIdOffset() const
	{
		return 5;
	}
}