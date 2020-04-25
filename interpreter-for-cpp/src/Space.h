#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace peak {
namespace interpreter {

class Variable;
class Method;

class Space {
public:
	Space();
	Space(std::shared_ptr<Space> parent);

	void Clear();

	bool AddVariable(std::shared_ptr<Variable> value);
	bool AddMethod(std::shared_ptr<Method> value);

	std::shared_ptr<Variable> FindVariable(const std::string& name) const;
	std::shared_ptr<Method> FindMethod(const std::string& name) const;

private:
	std::shared_ptr<Space> _parent{nullptr};

	std::unordered_map<std::string, std::shared_ptr<Method>> _methods;
	std::unordered_map<std::string, std::shared_ptr<Variable>> _variables;
};
} // namespace interpreter
} // namespace peak