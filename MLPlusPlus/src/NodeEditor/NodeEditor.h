#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/Nodes.h>
#include <NodeEditor/NodeLink.h>
#include <vector>

class NodeEditor {
public:
	using Iterator = std::vector<Nodes::Node*>::iterator;
private:
	unsigned int id = 1;
	std::vector<Nodes::Node*> nodes;
	std::vector<Nodes::Link*> links;
public:
	NodeEditor();
	~NodeEditor();

	Iterator begin();
	Iterator end();

	void spawnMain();
	void spawnNewLinearRegression();
	void spawnSetLinearRegressionObject();

	void addLink(Nodes::Link* link);
	inline std::vector<Nodes::Link*>& getLinks() { return links; }
	inline std::vector<Nodes::Node*>& getNodes() { return nodes; }
};