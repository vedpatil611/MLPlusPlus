#pragma once

namespace Nodes
{
	enum class DataType
	{
		INT,
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
		void* object;
		DataType type;
		char name[64] = "";
		bool isSelected;

		Object();
		Object(DataType type, void* object, bool selected = false);
		~Object();
	};
}