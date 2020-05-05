/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak::interpreter {
class ValueNull : public TypeValue<ValueNull> {
public:
	static const std::shared_ptr<ValueNull> DEFAULT_VALUE;
	virtual std::string ToString() const;
};
} // namespace peak::interpreter