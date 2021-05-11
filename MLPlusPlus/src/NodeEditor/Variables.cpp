#include "Variables.h"

#include <NodeEditor/Object.h>

namespace Nodes
{
	void Variables::addVariable()
	{
		vars.emplace_back(new Nodes::Object());
	}

	void Variables::addVariable(Nodes::DataType type)
	{
		vars.emplace_back(new Object(type, nullptr));
	}
}