#pragma once

#include <memory>

namespace peak::interpreter {

class Value;
	
class IValueCalculate {
	public:
	virtual ~IValueCalculate() {}
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const = 0;
};
} // namespace peak::interpreter