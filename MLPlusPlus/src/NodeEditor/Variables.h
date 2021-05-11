#pragma once

#include <vector>

namespace Nodes
{
	enum class DataType;
	class Object;

	class Variables
	{
	private:
		std::vector<Object*> vars;
	public:
		void addVariable();
		void addVariable(DataType type);
	};
}