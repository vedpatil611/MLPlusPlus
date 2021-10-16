#include "Object.h"

#include <stdexcept>
#include <DataTypes/Array.h>
#include <DataTypes/Bool.h>
#include <DataTypes/FileReader.h>
#include <DataTypes/Float.h>
#include <DataTypes/Integer.h>
#include <DataTypes/String.h>
#include <Algorithms/LinearRegression.h>

#define DELETE_CASE(e_type, type)			\
	case e_type:							\
		delete static_cast<type*>(object);	\
		break;

#define CLEAR_CASE(e_type, type)			\
	case e_type:							\
		delete static_cast<type*>(object);	\
		object = nullptr;					\
		break;

namespace Nodes
{
	Object::Object()
		: type(DataType::FLOAT), object(nullptr) {}

	Object::Object(DataType type, void* object, bool selected /* = false*/)
		: type(type), object(object) {}

	Object::~Object()
	{
		switch (type)
		{
			DELETE_CASE(DataType::ARRAY, Array)
			DELETE_CASE(DataType::FILE_READER_OBJECT, FileReader)
			DELETE_CASE(DataType::BOOL, Bool)
			DELETE_CASE(DataType::FLOAT, Float)
			DELETE_CASE(DataType::INT, Integer)
			DELETE_CASE(DataType::LINEAR_REGRESSION_MODEL, ::LinearRegression)
			DELETE_CASE(DataType::STRING, String)
		default:
			throw std::runtime_error("Invalid data type");
		}
	}
	
	void Object::clear()
	{
		switch (type)
		{
			CLEAR_CASE(DataType::ARRAY, Array)
			CLEAR_CASE(DataType::FILE_READER_OBJECT, FileReader)
			CLEAR_CASE(DataType::BOOL, Bool)
			CLEAR_CASE(DataType::FLOAT, Float)
			CLEAR_CASE(DataType::INT, Integer)
			CLEAR_CASE(DataType::LINEAR_REGRESSION_MODEL, ::LinearRegression)
			CLEAR_CASE(DataType::STRING, String)
		default:
			throw std::runtime_error("Invalid data type");
		}
	}
}