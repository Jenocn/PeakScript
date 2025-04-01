/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "value.h"

namespace peak { 

class ValueNumber : public TypeValue<ValueNumber> {
public:
	ValueNumber(double value);
	double GetValue() const;
	virtual std::string ToString() const;
	virtual std::shared_ptr<Value> Clone() const;

private:
	double _value{0};
};

} // namespace peak