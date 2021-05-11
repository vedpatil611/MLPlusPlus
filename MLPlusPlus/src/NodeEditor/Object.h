#pragma once

namespace Nodes
{
	enum class DataType
	{
		INT,
		FLOAT,
		STRING,
		BOOL,
		LINEAR_REGRESSION_MODEL
	};

	class Object 
	{
	public:
		DataType type;
		void* object;

		Object();
		Object(DataType type, void* object);
		~Object();
	};
}