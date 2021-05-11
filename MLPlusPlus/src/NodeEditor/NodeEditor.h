#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/Nodes.h>
#include <vector>

class NodeEditor {
public:
	using Iterator = std::vector<Nodes::Node*>::iterator;
private:
	unsigned int id = 0;
public:
	std::vector<Nodes::Node*> nodes;
	NodeEditor();
	~NodeEditor();

	Iterator begin();
	Iterator end();

	void spawnMain();
	void spawnNewLinearRegression();
};