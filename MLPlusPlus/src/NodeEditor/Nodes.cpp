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

		ImNodes::BeginOutputAttribute(id++);
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

	Set::Set(int id)
		:Node(id) 
	{
		count = ++s_count;
	}
	
	void Set::show()
	{
		int id = start_id;
		ImNodes::BeginNode(id++);

		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted("Set");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(id++);
		ImNodes::EndInputAttribute();

		ImNodes::BeginOutputAttribute(id++);
		ImNodes::EndOutputAttribute();

		char s[8];
		sprintf(s, "name%d", count);
		ImGui::NewLine();
		ImNodes::BeginStaticAttribute(id++);
		ImGui::PushItemWidth(50);
		ImGui::PushID(ImGui::GetID(s));
		ImGui::InputText("", name, 16);
		ImGui::PopID();
		ImGui::PopItemWidth();
		ImNodes::EndStaticAttribute();

		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Indent(100);
		ImGui::Text("lr object");
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
	}
}