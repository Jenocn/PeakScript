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
	ValueFunction(std::function<std::shared_ptr<Value>(const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space)> func);
	ValueFunction(const std::vector<std::string>& params, std::function<std::shared_ptr<Value>(const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space)> func);
	std::shared_ptr<Value> Call(const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space);
	virtual std::string ToString() const;

private:
	std::vector<std::string> _params;
	std::function<std::shared_ptr<Value>(const std::vector<std::shared_ptr<Value>>&, std::shared_ptr<Space>)> _func{nullptr};
};
} // namespace interpreter
} // namespace peak