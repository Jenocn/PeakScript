/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "value.h"

namespace peak {

class Space;

class ValueObject : public TypeValue<ValueObject> {
public:
	ValueObject(std::shared_ptr<Space> indexSpace = nullptr, std::shared_ptr<ValueObject> parent = nullptr);
	virtual std::shared_ptr<Value> Clone() const;
	std::shared_ptr<Space> GetSpace() const;
	virtual std::string ToString() const;

private:
	std::shared_ptr<Space> _space{nullptr};
};

} // namespace peak