/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "value.h"

namespace peak { 

class ValueString : public TypeValue<ValueString> {
public:
	ValueString(const std::string& value);
	const std::string& GetValue() const;
	virtual std::string ToString() const override;
	virtual std::string ToRawString() const override;
	virtual std::shared_ptr<Value> Clone() const override;

private:
	std::string _value;
};

} // namespace peak