#include "NodeEditor.h"

NodeEditor::NodeEditor()
{
	ImNodes::CreateContext();
}

NodeEditor::~NodeEditor()
{
	for (auto* x : nodes)
		delete x;
	for (auto* x : links)
		delete x;

	ImNodes::DestroyContext();
}

NodeEditor::Iterator NodeEditor::begin()
{
	return nodes.begin();
}

NodeEditor::Iterator NodeEditor::end()
{
	return nodes.end();
}

void NodeEditor::spawnMain()
{
	nodes.emplace_back(new Nodes::Main(id));
	id += Nodes::Main::getIdIncreament();
}

void NodeEditor::spawnNewLinearRegression()
{
	nodes.emplace_back(new Nodes::LinearRegression(id));
	id += Nodes::LinearRegression::getIdIncreament();
}

void NodeEditor::addLink(Nodes::Link* link)
{
	links.emplace_back(link);
}
