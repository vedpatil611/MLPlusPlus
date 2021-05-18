#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/Nodes.h>
#include <NodeEditor/NodeLink.h>
#include <NodeEditor/Object.h>
#include <vector>

class NodeEditor {
private:
	static inline unsigned int id = 1;
	class Window* window;
	std::vector<Nodes::Node*> nodes;
	std::vector<Nodes::Link*> links;
	std::vector<Nodes::Object*> objects;
	Nodes::Node* mainRef;
public:
	NodeEditor(class Window* window);
	~NodeEditor();

	void renderEditor();
	void renderGraph();
	void renderVariablesPanel();

	void spawnSet(const char* varName);
	void spawnGet(const char* varName);

	inline std::vector<Nodes::Link*>& getLinks() { return links; }
	inline std::vector<Nodes::Node*>& getNodes() { return nodes; }

#ifdef DEBUG
private:
	std::vector<double> x = { 1.0, 2.0, 3.0 };
	std::vector<double> y = { 2.0, 4.5, 6.0 };
#endif // DEBUG
};