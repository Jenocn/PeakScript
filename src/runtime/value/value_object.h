/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "value.h"

namespace peak {

class Space;
class Module;

class ValueObject: public TypeValue<ValueObject> {
public:
	ValueObject(std::shared_ptr<Module> module);
	ValueObject(std::shared_ptr<Space> indexSpace = nullptr, std::shared_ptr<ValueObject> parent = nullptr);
	virtual std::shared_ptr<Value> Clone() const override;
	std::shared_ptr<Space> GetSpace() const;
	virtual std::string ToString() const override;
	virtual std::string ToRawString() const override;

private:
	std::shared_ptr<Space> _space { nullptr };
};

} // namespace peak