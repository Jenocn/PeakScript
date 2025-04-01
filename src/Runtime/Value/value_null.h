/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "value.h"

namespace peak { 

class ValueNull : public TypeValue<ValueNull> {
public:
	static const std::shared_ptr<ValueNull> DEFAULT_VALUE;
	virtual std::string ToString() const;
	virtual std::shared_ptr<Value> Clone() const;
};

} // namespace peak