#include "Object.h"

namespace Nodes
{
	Object::Object()
		: type(DataType::FLOAT), object(nullptr) {}

	Object::Object(DataType type, void* object, bool selected /* = false*/)
		: type(type), object(object) {}

	Object::~Object()
	{
		if(!object) delete object;
	}
}