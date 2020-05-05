/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "IValueCalculate.h"

namespace peak::interpreter {

class Value;

class ValueCalculateAdd : public ValueCalculateSingleton<ValueCalculateAdd> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateSub : public ValueCalculateSingleton<ValueCalculateSub> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateMul : public ValueCalculateSingleton<ValueCalculateMul> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateDiv : public ValueCalculateSingleton<ValueCalculateDiv> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateMod : public ValueCalculateSingleton<ValueCalculateMod> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};

class ValueCalculateSame : public ValueCalculateSingleton<ValueCalculateSame> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateNotSame : public ValueCalculateSingleton<ValueCalculateNotSame> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateMore : public ValueCalculateSingleton<ValueCalculateMore> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateSameOrMore : public ValueCalculateSingleton<ValueCalculateSameOrMore> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateLess : public ValueCalculateSingleton<ValueCalculateLess> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateSameOrLess : public ValueCalculateSingleton<ValueCalculateSameOrLess> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};

class ValueCalculateLogicAnd : public ValueCalculateSingleton<ValueCalculateLogicAnd> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
class ValueCalculateLogicOr : public ValueCalculateSingleton<ValueCalculateLogicOr> {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const;
};
} // namespace peak::interpreter