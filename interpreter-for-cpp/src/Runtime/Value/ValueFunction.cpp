#include "ValueFunction.h"
#include "../Space.h"
#include "../Variable.h"
#include "ValueTool.h"
#include <vector>

using namespace peak::interpreter;

ValueFunction::ValueFunction(const std::vector<std::string>& params, std::function<std::shared_ptr<Value>(std::shared_ptr<Space> space)> func)
	: _params(params), _func(func) {
}

std::shared_ptr<Value> ValueFunction::Call(const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space) {
	if (_func) {
		auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Function, space));
		auto paramSize = _params.size();
		for (std::size_t i = 0; i < args.size(); ++i) {
			if (i >= paramSize) {
				break;
			}
			auto tempVariable = std::shared_ptr<Variable>(new Variable(_params[i]));
			tempVariable->SetValue(args[i]);
			if (!tempSpace->AddVariable(tempVariable)) {
				return nullptr;
			}
		}
		return _func(tempSpace);
	}
	return nullptr;
}