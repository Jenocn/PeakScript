#include "ValueObject.h"
#include "../Space.h"

using namespace peak::interpreter;

ValueObject::ValueObject(std::shared_ptr<Space> space)
	: _space(space) {
}

std::shared_ptr<Value> ValueObject::Clone() const {
	return std::shared_ptr<Value>(new ValueObject(_space->CopySpace()));
}

std::shared_ptr<Space> ValueObject::GetSpace() const {
	return _space;
}

std::string ValueObject::ToString() const {
	return "object";
}
