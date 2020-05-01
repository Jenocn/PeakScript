/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "IValueCalculate.h"

namespace peak::interpreter {

class Value;

class ValueCalculateAdd : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateSub : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateMul : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateDiv : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateMod : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
class ValueCalculateSame : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateNotSame : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateMore : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateSameOrMore : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateLess : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateSameOrLess : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
class ValueCalculateLogicAnd : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateLogicOr : public IValueCalculate {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
} // namespace peak::interpreter