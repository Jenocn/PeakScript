#include "Value.h"

using namespace peak::interpreter;

int TypeValueCount::_count{0};

TypeValueCount::TypeValueCount() {
	_index = _count;
	++_count;
}

int TypeValueCount::GetIndex() const {
	return _index;
}
