#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>

class NodeEditor {
	inline static unsigned int id = 0;
	static unsigned int getNextId();
public:
	static void init();

	static void destroy();

	static void spawnMain();
	static void spawnNewLinearRegression();
};