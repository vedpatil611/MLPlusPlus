#pragma once

namespace Nodes
{
	enum class DataType
	{
		INT,
		FLOAT,
		STRING,
		LINEAR_REGRESSION_MODEL
	};

	class Object 
	{
	public:
		DataType type;
		void* object;
	};
}