#include <algorithm>
#include <imgui.h>
#include <imfilebrowser.h>
#include <rapidcsv.h>
#include <stdio.h>
#include <vector>

#include <Algorithms/LinearRegression.h>
#include <NodeEditor/NodeEditor.h>
#include <NodeEditor/NodeLink.h>
#include <UI/DockableWindow.h>
#include <vendors/imnodes/imnodes.h>
#include <Window.h>

Window* window;
NodeEditor* nodeEditor;

int main()
{
	window = new Window();

	DockableWindow::init(window);
	nodeEditor = new NodeEditor(window);
	
	while (!window->shouldClose())
	{
		window->pollInput();
		window->clearBuffer();
		
		DockableWindow::begin();
		nodeEditor->renderEditor();
		nodeEditor->renderVariablesPanel();
		nodeEditor->renderGraph();
		DockableWindow::end();

		window->swapBuffer();	
	}

	delete nodeEditor;
	DockableWindow::destroy();
	delete window;
	return 0;
}
