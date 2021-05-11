#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>

namespace Nodes
{
	class Node {
	protected:
		int start_id;
		Node(int id) : start_id(id) {}
	public:
		virtual void show() = 0;
	};

	class Main: public Node {
	public:
		Main(int id) : Node(id) {};

		void show() override {
			ImNodes::BeginNode(start_id);

			ImNodes::BeginNodeTitleBar();
			ImGui::TextUnformatted("Main");
			ImNodes::EndNodeTitleBar();

			ImNodes::BeginOutputAttribute(start_id + 1);
			ImGui::Text("Start");
			ImNodes::EndOutputAttribute();

			ImNodes::EndNode();
		}

		static inline constexpr int getIdIncreament() { return 2; }
	};

	class LinearRegression : public Node
	{
	public:
		LinearRegression(int id) : Node(id) {}

		void show() override {
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

		static inline constexpr int getIdIncreament() { return 4; }
	};
}