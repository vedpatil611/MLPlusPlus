#pragma once

namespace Nodes
{
	enum class DataType
	{
		INT = 1,
		FLOAT,
		STRING,
		BOOL,
		ARRAY,
		LINEAR_REGRESSION_MODEL,
		FILE_READER_OBJECT
	};

	class Object 
	{
	public:
		void* object = nullptr;
		DataType type;
		char name[64] = "";
		char typeSelected[32] = "Float";

		Object();
		Object(DataType type, void* object, bool selected = false);
		~Object();
	};
}