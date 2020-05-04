/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <memory>
#include <string>

namespace peak::interpreter {
class Value {
public:
	virtual ~Value() {}
	virtual int GetType() const = 0;
	virtual std::string ToString() const { return ""; }
};

class TypeValueCount {
public:
	TypeValueCount();

	int GetIndex() const;

private:
	static int _count;
	int _index{0};
};

template <typename T>
class TypeValue : public Value {
public:
	static int Type() {
		return _count.GetIndex();
	}
	virtual int GetType() const final {
		return TypeValue<T>::Type();
	}

private:
	static TypeValueCount _count;
};

template <typename T>
TypeValueCount TypeValue<T>::_count;

} // namespace peak::interpreter