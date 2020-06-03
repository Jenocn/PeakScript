/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"

namespace peak {
namespace interpreter {

struct ParseData;
class Space;
class Variable;

class Executer {
public:
	static std::shared_ptr<Executer> Create(const std::string& src);
	~Executer();
	
	bool Execute();

	std::shared_ptr<Space> GetSpace() const;

	std::shared_ptr<Variable> FindVariable(const std::string& name);
	bool AddVariable(std::shared_ptr<Variable> variable);

private:
	Executer(std::shared_ptr<ParseData> data);

private:
	std::shared_ptr<ParseData> _parseData{nullptr};
	std::shared_ptr<Space> _space{nullptr};
};

} // namespace interpreter
} // namespace peak