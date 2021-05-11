#include "Object.h"

namespace Nodes
{
	Object::Object()
		: type(DataType::FLOAT), object(nullptr) {}

	Object::Object(DataType type, void* object)
		: type(type), object(object) {}

	Object::~Object()
	{
		delete object;
	}
}