/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <memory>

namespace peak::interpreter {

class Value;

class IValueCalculate {
public:
	virtual ~IValueCalculate() {}
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const = 0;
};

template <typename T>
class ValueCalculateSingleton : public IValueCalculate {
public:
	static T* GetInstance() {
		static T _instance;
		return &_instance;
	}
};
} // namespace peak::interpreter