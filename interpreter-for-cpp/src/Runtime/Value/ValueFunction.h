/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak {
namespace interpreter {

class Variable;
class Space;

class ValueFunction : public TypeValue<ValueFunction> {
public:
	using FunctionType = std::function<std::shared_ptr<Value>(const std::vector<std::shared_ptr<Value>>&, std::shared_ptr<Space>)>;

public:
	ValueFunction(std::size_t paramSize, FunctionType func);
	ValueFunction(const std::vector<std::string>& params, FunctionType func);
	std::shared_ptr<Value> Call(const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space);
	virtual std::string ToString() const;

	bool AddFunction(std::size_t paramSize, FunctionType func);
	bool AddFunction(const std::vector<std::string>& params, FunctionType func);

private:
	std::map<std::size_t, std::pair<std::vector<std::string>, FunctionType>> _functionMap;
};
} // namespace interpreter
} // namespace peak