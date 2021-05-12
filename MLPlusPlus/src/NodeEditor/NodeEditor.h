#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/Nodes.h>
#include <NodeEditor/NodeLink.h>
#include <NodeEditor/Object.h>
#include <vector>

class NodeEditor {
public:
	using Iterator = std::vector<Nodes::Node*>::iterator;
private:
	static inline unsigned int id = 1;
	class Window* window;
	std::vector<Nodes::Node*> nodes;
	std::vector<Nodes::Link*> links;
	std::vector<Nodes::Object*> objects;
public:
	NodeEditor(class Window* window);
	~NodeEditor();

	Iterator begin();
	Iterator end();

	void renderEditor();
	void renderVariablesPanel();

	void spawnMain();
	void spawnSet(const char* varName);
	void spawnNewLinearRegression();

	void addLink(Nodes::Link* link);
	inline std::vector<Nodes::Link*>& getLinks() { return links; }
	inline std::vector<Nodes::Node*>& getNodes() { return nodes; }
};