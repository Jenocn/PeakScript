#include "value.h"

using namespace peak;

int TypeValueCount::_count{0};

TypeValueCount::TypeValueCount() {
	_index = _count;
	++_count;
}

int TypeValueCount::GetIndex() const {
	return _index;
}
