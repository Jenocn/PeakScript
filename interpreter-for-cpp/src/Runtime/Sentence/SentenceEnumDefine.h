/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak {
namespace interpreter {

class ValueNumber;
	
class SentenceEnumDefine : public Sentence {
public:
	SentenceEnumDefine(const std::string& name, const std::list<std::pair<std::string, std::shared_ptr<ValueNumber>>>& valueList);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::list<std::pair<std::string, std::shared_ptr<ValueNumber>>> _valueList;
};
} // namespace interpreter
} // namespace peak