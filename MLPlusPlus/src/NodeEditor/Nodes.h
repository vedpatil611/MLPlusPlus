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
}