#include "ValueFunction.h"
#include "../Space.h"
#include "../Variable.h"
#include "ValueTool.h"

using namespace peak::interpreter;

ValueFunction::ValueFunction(std::size_t paramSize, FunctionType func) {
	AddFunction(paramSize, func);
}
ValueFunction::ValueFunction(const std::vector<std::string>& params, FunctionType func) {
	AddFunction(params, func);
}

bool ValueFunction::AddFunction(std::size_t paramSize, FunctionType func) {
	auto ite = _functionMap.find(paramSize);
	if (ite == _functionMap.end()) {
		_functionMap.emplace(paramSize, std::make_pair(std::vector<std::string>(), func));
		return true;
	}
	return false;
}

bool ValueFunction::AddFunction(const std::vector<std::string>& params, FunctionType func) {
	auto size = params.size();
	auto ite = _functionMap.find(size);
	if (ite == _functionMap.end()) {
		_functionMap.emplace(size, std::make_pair(params, func));
		return true;
	}
	return false;
}

std::shared_ptr<Value> ValueFunction::Call(const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space) {
	auto ite = _functionMap.find(args.size());
	if (ite == _functionMap.end()) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::FunctionCall, "The function (" + std::to_string(args.size()) + " params) not found!");
		return nullptr;
	}
	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Function, space));
	const auto& params = ite->second.first;
	auto func = ite->second.second;
	auto paramSize = params.size();
	for (std::size_t i = 0; i < args.size(); ++i) {
		if (i >= paramSize) {
			break;
		}
		auto tempVariable = std::shared_ptr<Variable>(new Variable(params[i], VariableAttribute::None));
		if (!tempSpace->AddVariable(tempVariable)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::FunctionCall, "The function params name is exist!");
			return nullptr;
		}
		tempVariable->SetValue(args[i]);
	}
	return func(args, tempSpace);
}

std::string ValueFunction::ToString() const {
	return "function";
}
