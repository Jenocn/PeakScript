#pragma once

#include <string>

namespace peak::interpreter {
class Method {
public:
	const std::string& GetName() const;

private:
	std::string _name;
};
} // namespace peak::interpreter