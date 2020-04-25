#pragma once

#include <string>

namespace peak {
namespace interpreter {
class Method {
public:
	const std::string& GetName() const;

private:
	std::string _name;
};
} // namespace interpreter
} // namespace peak