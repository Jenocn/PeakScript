#include "ValueNull.h"

using namespace peak::interpreter;

const std::shared_ptr<ValueNull> ValueNull::DEFAULT_VALUE = std::shared_ptr<ValueNull>(new ValueNull());

std::string ValueNull::ToString() const {
	return "null";
}