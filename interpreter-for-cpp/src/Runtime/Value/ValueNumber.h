/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak::interpreter {
class ValueNumber : public TypeValue<ValueNumber> {
public:
	ValueNumber(double value);
	double GetValue() const;
	virtual std::string ToString() const;

private:
	double _value{0};
};
} // namespace peak::interpreter