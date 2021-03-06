#include "ParseTool.h"
#include "../Runtime/Sentence/Analysis/ExpressionVariableAnalysisInstance.h"
#include "../Runtime/Sentence/SentenceBlock.h"
#include "../Runtime/Sentence/SentenceCondition.h"
#include "../Runtime/Sentence/SentenceDoWhile.h"
#include "../Runtime/Sentence/SentenceEcho.h"
#include "../Runtime/Sentence/SentenceEnumDefine.h"
#include "../Runtime/Sentence/SentenceExport.h"
#include "../Runtime/Sentence/SentenceExpressionDouble.h"
#include "../Runtime/Sentence/SentenceExpressionFunctionCall.h"
#include "../Runtime/Sentence/SentenceExpressionInside.h"
#include "../Runtime/Sentence/SentenceExpressionMath.h"
#include "../Runtime/Sentence/SentenceExpressionNew.h"
#include "../Runtime/Sentence/SentenceExpressionNot.h"
#include "../Runtime/Sentence/SentenceExpressionSelfAssign.h"
#include "../Runtime/Sentence/SentenceExpressionValueArray.h"
#include "../Runtime/Sentence/SentenceExpressionVariable.h"
#include "../Runtime/Sentence/SentenceFor.h"
#include "../Runtime/Sentence/SentenceForeach.h"
#include "../Runtime/Sentence/SentenceFunctionDefine.h"
#include "../Runtime/Sentence/SentenceImport.h"
#include "../Runtime/Sentence/SentenceLoop.h"
#include "../Runtime/Sentence/SentenceLoopControl.h"
#include "../Runtime/Sentence/SentenceObjectDefine.h"
#include "../Runtime/Sentence/SentenceReturn.h"
#include "../Runtime/Sentence/SentenceTryCatchFinally.h"
#include "../Runtime/Sentence/SentenceVariableAssign.h"
#include "../Runtime/Sentence/SentenceVariableDefine.h"
#include "../Runtime/Sentence/SentenceVariableSet.h"
#include "../Runtime/Sentence/SentenceWhile.h"
#include "../Runtime/Value/ValueCalculateInstance.h"
#include "../Runtime/Value/ValueTool.h"
#include "../Runtime/Variable.h"

using namespace peak::interpreter;

ParseTool::SentenceParseList ParseTool::_sentenceParseList = {
	_ParseVariableAssign,
	_ParseVariableDefine,
	_ParseVariableSet,
	_ParseFunctionDefine,
	_ParseObjectDefine,
	_ParseEnumDefine,
	_ParseCondition,
	_ParseLoop,
	_ParseForeach,
	_ParseFor,
	_ParseWhile,
	_ParseDoWhile,
	_ParseBlock,
	_ParseEcho,
	_ParseLoopControl,
	_ParseReturn,
	_ParseImport,
	_ParseExport,
	_ParseTryCatchFinally,
	_ParseExpressionToEnd,
};
ParseTool::ExpressionParseList ParseTool::_sentenceValueParseList = {
	_ParseString,
	_ParseNumber,
	_ParseBool,
	_ParseNull,
	_ParseInside,
	_ParseArrayItem,
	_ParseArray,
	_ParseNew,
	_ParseFunctioCall,
	_ParseDoubleExpression,
	_ParseNotExpression,
	_ParseVariableName,
};

// target = value;
ParseTool::ExpressionParseList ParseTool::_sentenceVariableParseList = {
	_ParseInside,
	_ParseArrayItem,
	_ParseVariableName,
};

// target[]
ParseTool::ExpressionParseList ParseTool::__sentenceArrayItemParseList = {
	_ParseArray,
	_ParseFunctioCall,
	_ParseVariableName,
};

// target.
ParseTool::ExpressionParseList ParseTool::__sentenceInsideHeaderParseList = {
	_ParseNew,
	_ParseFunctioCall,
	_ParseArrayItem,
	_ParseVariableName,
};

// .target
ParseTool::ExpressionParseList ParseTool::__sentenceInsideAppendParseList = {
	_ParseArrayItem,
	_ParseFunctioCall,
	_ParseVariableName,
};

std::shared_ptr<ParseData> ParseTool::Load(const std::string& src) {
	auto retData = std::shared_ptr<ParseData>(new ParseData());
	retData->bSuccess = true;
	std::size_t pos = 0;
	auto size = src.size();
	while (pos < size) {
		JumpEnd(src, size, pos, &pos);
		if (pos >= size) {
			break;
		}
		auto parseSentence = ParseSentence(src, size, pos, &pos);
		if (!parseSentence) {
			retData->bSuccess = false;
			ErrorLogger::LogParseError(src, size, pos);
			break;
		}
		retData->sentenceList.emplace_back(parseSentence);
	}
	return retData;
}

bool ParseTool::Jump(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool bJump = false;
	bool bRet = false;
	do {
		bJump = false;
		bJump |= JumpTextSpace(src, size, pos, &pos);
		bJump |= JumpComment(src, size, pos, &pos);
		bJump |= JumpCommentBlock(src, size, pos, &pos);
		bRet |= bJump;
	} while (bJump);
	*nextPos = pos;
	return bRet;
}

bool ParseTool::JumpEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool bJump = false;
	bool bRet = false;
	do {
		bJump = false;
		bool bEnd = JumpTextSpaceAndEnd(src, size, pos, &pos);
		bJump |= bEnd;
		bJump |= JumpComment(src, size, pos, &pos);
		bJump |= JumpCommentBlock(src, size, pos, &pos);
		bRet |= bEnd;
	} while (bJump);
	*nextPos = pos;
	if (Grammar::IsGrammarEndSign('\n')) {
		bRet |= (pos >= size);
	}
	return bRet;
}

bool ParseTool::JumpTextSpace(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	auto beginPos = pos;
	while (pos < size) {
		if (!Grammar::IsTextSpace(src[pos])) {
			break;
		}
		++pos;
	}
	*nextPos = pos;
	return pos != beginPos;
}
bool ParseTool::JumpTextSpaceAndEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool bRet = false;
	while (pos < size) {
		char ch = src[pos];
		bool bEnd = Grammar::IsGrammarEndSign(ch);
		if (!bEnd && !Grammar::IsTextSpace(ch)) {
			break;
		}
		bRet |= bEnd;
		++pos;
	}
	*nextPos = pos;
	return bRet;
}
bool ParseTool::JumpComment(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (Grammar::MatchComment(src, size, pos, &pos)) {
		while (pos <= size) {
			if ((pos == size) || Grammar::IsTextNewLine(src[pos])) {
				*nextPos = pos;
				return true;
			}
			++pos;
		}
	}
	return false;
}

bool ParseTool::JumpCommentBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	int findBegin = 0;
	if (Grammar::MatchCommentBlockBegin(src, size, pos, &pos)) {
		while (pos < size) {
			if (Grammar::MatchCommentBlockBegin(src, size, pos, &pos)) {
				++findBegin;
				continue;
			}
			if (Grammar::MatchCommentBlockEnd(src, size, pos, &pos)) {
				if (findBegin == 0) {
					*nextPos = pos;
					return true;
				}
				--findBegin;
				continue;
			}
			++pos;
		}
	}
	return false;
}

std::shared_ptr<Sentence> ParseTool::ParseSentence(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto func : _sentenceParseList) {
		auto parseData = func(src, size, pos, nextPos);
		if (parseData) {
			return parseData;
		}
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return _ParseExpressionMath(src, size, pos, nextPos);
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseExpressionValue(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto func : _sentenceValueParseList) {
		auto value = func(src, size, pos, nextPos);
		if (value) {
			return value;
		}
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseVariable(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto func : _sentenceVariableParseList) {
		auto value = func(src, size, pos, nextPos);
		if (value) {
			return value;
		}
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::__ParseExpressionValueForArrayValue(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto func : __sentenceArrayItemParseList) {
		auto value = func(src, size, pos, nextPos);
		if (value) {
			return value;
		}
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::__ParseExpressionInsideHeader(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto func : __sentenceInsideHeaderParseList) {
		auto value = func(src, size, pos, nextPos);
		if (value) {
			return value;
		}
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::__ParseExpressionInsideAppend(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto func : __sentenceInsideAppendParseList) {
		auto value = func(src, size, pos, nextPos);
		if (value) {
			return value;
		}
	}
	return nullptr;
}

std::shared_ptr<Sentence> ParseTool::_ParseImport(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchImport(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);

	if (pos >= size) {
		return nullptr;
	}
	char sign = src[pos];
	if (!Grammar::IsGrammarStringSign(sign)) {
		return nullptr;
	}
	std::string moduleName;
	if (!Grammar::MatchPair(sign, sign, src, size, pos, &pos, &moduleName)) {
		return nullptr;
	}

	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceImport(moduleName));
}
std::shared_ptr<Sentence> ParseTool::_ParseExport(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchExport(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);

	if (pos >= size) {
		return nullptr;
	}
	char sign = src[pos];
	if (!Grammar::IsGrammarStringSign(sign)) {
		return nullptr;
	}
	std::string moduleName;
	if (!Grammar::MatchPair(sign, sign, src, size, pos, &pos, &moduleName)) {
		return nullptr;
	}

	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceExport(moduleName));
}

std::shared_ptr<Sentence> ParseTool::_ParseReturn(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchReturn(src, size, pos, &pos)) {
		return nullptr;
	}
	if (!Jump(src, size, pos, &pos)) {
		return nullptr;
	}

	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}

	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceReturn(expression));
}
std::shared_ptr<Sentence> ParseTool::_ParseFunctionDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (Grammar::MatchFunction(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
	}
	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	if (!Grammar::MatchLeftBrcket(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	std::vector<std::string> params;
	std::string paramName;
	while (Grammar::MatchName(src, size, pos, &pos, &paramName)) {
		params.emplace_back(paramName);
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchSplitSymbol(src, size, pos, &pos)) {
			break;
		}
		Jump(src, size, pos, &pos);
	}
	if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	auto contentSentence = _ParseBlock(src, size, pos, &pos);
	if (!contentSentence) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceFunctionDefine(name, params, contentSentence));
}

std::shared_ptr<Sentence> ParseTool::_ParseEnumDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchEnum(src, size, pos, &pos)) {
		return nullptr;
	}
	if (!Jump(src, size, pos, &pos)) {
		return nullptr;
	}
	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	if (!Grammar::MatchObjectBegin(src, size, pos, &pos)) {
		return nullptr;
	}
	std::set<std::string> checkNameSet;
	std::set<double> checkValueSet;
	std::list<std::pair<std::string, std::shared_ptr<ValueNumber>>> valueList;
	double indexValue = 0;
	while (true) {
		if (pos >= size) {
			return nullptr;
		}
		Jump(src, size, pos, &pos);
		if (Grammar::MatchObjectEnd(src, size, pos, &pos)) {
			break;
		}
		std::string valueName = "";
		if (!Grammar::MatchName(src, size, pos, &pos, &valueName)) {
			return nullptr;
		}
		Jump(src, size, pos, &pos);
		if (Grammar::MatchAssign(src, size, pos, &pos)) {
			Jump(src, size, pos, &pos);
			if (!Grammar::MatchNumber(src, size, pos, &pos, &indexValue)) {
				return nullptr;
			}
			Jump(src, size, pos, &pos);
		}

		auto valueNumber = std::shared_ptr<ValueNumber>(new ValueNumber(indexValue));
		if (!ValueTool::IsInteger(valueNumber)) {
			return nullptr;
		}

		if (checkNameSet.find(valueName) != checkNameSet.end()) {
			return nullptr;
		}
		if (checkValueSet.find(indexValue) != checkValueSet.end()) {
			return nullptr;
		}
		checkNameSet.emplace(valueName);
		checkValueSet.emplace(indexValue);
		valueList.emplace_back(valueName, valueNumber);

		Jump(src, size, pos, &pos);
		if (!Grammar::MatchSplitSymbol(src, size, pos, &pos)) {
			if (Grammar::MatchObjectEnd(src, size, pos, &pos)) {
				break;
			}
			return nullptr;
		}

		indexValue += 1;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceEnumDefine(name, valueList));
}

std::shared_ptr<Sentence> ParseTool::_ParseObjectDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (Grammar::MatchObject(src, size, pos, &pos)) {
		if (!Jump(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	std::string parentName = "";
	if (Grammar::MatchExtends(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchName(src, size, pos, &pos, &parentName)) {
			return nullptr;
		}
		Jump(src, size, pos, &pos);
	}

	if (!Grammar::MatchObjectBegin(src, size, pos, &pos)) {
		return nullptr;
	}

	std::list<std::shared_ptr<Sentence>> sentenceList;
	while (true) {
		if (pos >= size) {
			return nullptr;
		}
		Jump(src, size, pos, &pos);
		if (Grammar::MatchObjectEnd(src, size, pos, &pos)) {
			break;
		}
		auto sentence = ParseSentence(src, size, pos, &pos);
		if (!sentence) {
			return nullptr;
		}
		sentenceList.emplace_back(sentence);
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceObjectDefine(name, parentName, sentenceList));
}

std::shared_ptr<Sentence> ParseTool::_ParseVariableDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool bConst = Grammar::MatchConst(src, size, pos, &pos);
	if (bConst && !Jump(src, size, pos, &pos)) {
		return nullptr;
	}
	if (Grammar::MatchVariableDefine(src, size, pos, &pos)) {
		if (!Jump(src, size, pos, &pos)) {
			return nullptr;
		}
	} else {
		if (!bConst) {
			return nullptr;
		}
	}

	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}

	auto beginPos = pos;
	Jump(src, size, pos, &pos);

	auto attribute = bConst ? VariableAttribute::Const : VariableAttribute::None;

	if (!Grammar::MatchAssign(src, size, pos, &pos)) {
		pos = beginPos;
		if (bConst) {
			return nullptr;
		}
		if (JumpEnd(src, size, pos, &pos)) {
			*nextPos = pos;
			return std::shared_ptr<Sentence>(new SentenceVariableDefine(name, attribute, nullptr));
		}
		return nullptr;
	}

	Jump(src, size, pos, &pos);
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceVariableDefine(name, attribute, expression));
}

std::shared_ptr<Sentence> ParseTool::_ParseVariableAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	auto variableExpression = _ParseVariable(src, size, pos, &pos);
	if (!variableExpression) {
		return nullptr;
	}

	Jump(src, size, pos, &pos);
	if (!Grammar::MatchAssign(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceVariableAssign(variableExpression, expression));
}

std::shared_ptr<Sentence> ParseTool::_ParseVariableSet(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchVariableSet(src, size, pos, &pos)) {
		return nullptr;
	}
	if (!Jump(src, size, pos, &pos)) {
		return nullptr;
	}

	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}

	auto beginPos = pos;
	Jump(src, size, pos, &pos);

	if (!Grammar::MatchAssign(src, size, pos, &pos)) {
		pos = beginPos;
		if (!JumpEnd(src, size, pos, &pos)) {
			return nullptr;
		}
		*nextPos = pos;
		return std::shared_ptr<Sentence>(new SentenceVariableSet(name, nullptr));
	}

	Jump(src, size, pos, &pos);
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceVariableSet(name, expression));
}

std::shared_ptr<Sentence> ParseTool::_ParseExpressionToEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return expression;
}

std::shared_ptr<Sentence> ParseTool::_ParseCondition(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchConditionIf(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	bool bBracket = Grammar::MatchLeftBrcket(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
	}
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (bBracket) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	Jump(src, size, pos, &pos);
	auto sentence = ParseSentence(src, size, pos, &pos);
	if (!sentence) {
		return nullptr;
	}

	std::shared_ptr<Sentence> sentenceElse{nullptr};

	Jump(src, size, pos, &pos);
	if (Grammar::MatchConditionElse(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
		sentenceElse = _ParseCondition(src, size, pos, &pos);
		if (!sentenceElse) {
			sentenceElse = ParseSentence(src, size, pos, &pos);
			if (!sentenceElse) {
				return nullptr;
			}
		}
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceCondition(expression, sentence, sentenceElse));
}

std::shared_ptr<Sentence> ParseTool::_ParseLoop(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchLoop(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);

	bool bBracket = Grammar::MatchLeftBrcket(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
	}

	std::string name;
	auto savePos = pos;
	bool bMatchName = Grammar::MatchName(src, size, pos, &pos, &name);
	if (bMatchName) {
		Jump(src, size, pos, &pos);
	}

	if (Grammar::MatchForeachIn(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
	} else {
		if (bMatchName) {
			pos = savePos;
			name = "";
		}
	}

	auto condition = _ParseExpression(src, size, pos, &pos);
	if (!condition) {
		return nullptr;
	}

	if (bBracket) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}

	Jump(src, size, pos, &pos);
	auto sentence = ParseSentence(src, size, pos, &pos);
	if (!sentence) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceLoop(name, condition, sentence));
}

std::shared_ptr<Sentence> ParseTool::_ParseFor(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchFor(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	bool bBracket = Grammar::MatchLeftBrcket(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
	}

	auto sentence0 = ParseSentence(src, size, pos, &pos);
	if (!sentence0) {
		sentence0 = _ParseExpression(src, size, pos, &pos);
		Jump(src, size, pos, &pos);
		if ((pos >= size) || !Grammar::IsGrammarEndSign(src[pos])) {
			return nullptr;
		}
		++pos;
	}
	auto expression0 = _ParseExpression(src, size, pos, &pos);
	{
		Jump(src, size, pos, &pos);
		if ((pos >= size) || !Grammar::IsGrammarEndSign(src[pos])) {
			return nullptr;
		}
		++pos;
	}
	auto expression1 = _ParseExpression(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	Jump(src, size, pos, &pos);
	auto content = ParseSentence(src, size, pos, &pos);
	if (!content && !JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceFor(sentence0, expression0, expression1, content));
}

std::shared_ptr<Sentence> ParseTool::_ParseForeach(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchForeach(src, size, pos, &pos)) {
		if (!Grammar::MatchFor(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	Jump(src, size, pos, &pos);

	bool bBracket = Grammar::MatchLeftBrcket(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
	}

	if (Grammar::MatchVariableDefine(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
	}
	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	if (!Grammar::MatchForeachIn(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}

	if (bBracket) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	Jump(src, size, pos, &pos);
	auto sentence = ParseSentence(src, size, pos, &pos);
	if (!sentence) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceForeach(name, expression, sentence));
}

std::shared_ptr<Sentence> ParseTool::_ParseWhile(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchWhile(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	bool bBracket = Grammar::MatchLeftBrcket(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
	}
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (bBracket) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	Jump(src, size, pos, &pos);
	auto sentence = ParseSentence(src, size, pos, &pos);
	if (!sentence && !JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceWhile(expression, sentence));
}

std::shared_ptr<Sentence> ParseTool::_ParseDoWhile(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchDo(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	auto sentence = ParseSentence(src, size, pos, &pos);
	if (!sentence) {
		return nullptr;
	}

	Jump(src, size, pos, &pos);
	if (!Grammar::MatchWhile(src, size, pos, &pos)) {
		return nullptr;
	}

	Jump(src, size, pos, &pos);
	bool bBracket = Grammar::MatchLeftBrcket(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
	}

	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (bBracket) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceDoWhile(expression, sentence));
}

std::shared_ptr<Sentence> ParseTool::_ParseBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchBlockBegin(src, size, pos, &pos)) {
		return nullptr;
	}

	auto sentenceBlock = std::shared_ptr<SentenceBlock>(new SentenceBlock());
	while (true) {
		if (pos >= size) {
			return nullptr;
		}
		JumpEnd(src, size, pos, &pos);
		if (Grammar::MatchBlockEnd(src, size, pos, &pos)) {
			break;
		}

		auto parseSentence = ParseSentence(src, size, pos, &pos);
		if (!parseSentence) {
			return nullptr;
		}
		sentenceBlock->Push(parseSentence);
	}

	*nextPos = pos;
	return sentenceBlock;
}

std::shared_ptr<Sentence> ParseTool::_ParseEcho(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchEcho(src, size, pos, &pos)) {
		return nullptr;
	}
	if (!Jump(src, size, pos, &pos)) {
		return nullptr;
	}

	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}

	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceEcho(expression));
}

std::shared_ptr<Sentence> ParseTool::_ParseTryCatchFinally(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchTry(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	auto sentence = ParseSentence(src, size, pos, &pos);
	if (!sentence) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);

	decltype(sentence) catchSentence = nullptr;
	if (Grammar::MatchCatch(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
		catchSentence = ParseSentence(src, size, pos, &pos);
		if (!catchSentence) {
			return nullptr;
		}
		Jump(src, size, pos, &pos);
	}
	decltype(sentence) finallySentence = nullptr;
	if (Grammar::MatchFinally(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
		finallySentence = ParseSentence(src, size, pos, &pos);
		if (!finallySentence) {
			return nullptr;
		}
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceTryCatchFinally(sentence, catchSentence, finallySentence));
}

std::shared_ptr<Sentence> ParseTool::_ParseLoopControl(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	std::shared_ptr<Sentence> sentence = nullptr;
	do {
		if (Grammar::MatchContinue(src, size, pos, &pos)) {
			sentence = std::shared_ptr<Sentence>(new SentenceLoopControlContinue());
			break;
		}
		if (Grammar::MatchBreak(src, size, pos, &pos)) {
			sentence = std::shared_ptr<Sentence>(new SentenceLoopControlBreak());
			break;
		}
		return nullptr;
	} while (false);
	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return sentence;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseString(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	char sign = src[pos];
	if (!Grammar::IsGrammarStringSign(sign)) {
		return nullptr;
	}
	std::string temp;
	if (Grammar::MatchPair(sign, sign, src, size, pos, &pos, &temp)) {
		*nextPos = pos;
		return std::shared_ptr<SentenceExpression>(new SentenceExpression(std::shared_ptr<Value>(new ValueString(temp))));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	double temp{0};
	if (Grammar::MatchNumber(src, size, pos, nextPos, &temp)) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpression(std::shared_ptr<Value>(new ValueNumber(temp))));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool temp{false};
	if (Grammar::MatchBool(src, size, pos, nextPos, &temp)) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpression(std::shared_ptr<Value>(new ValueBool(temp))));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (Grammar::MatchNull(src, size, pos, nextPos)) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpression(std::shared_ptr<Value>(new ValueNull())));
	}
	return nullptr;
}
std::shared_ptr<SentenceExpression> ParseTool::_ParseArray(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchArrayBegin(src, size, pos, &pos)) {
		return nullptr;
	}
	std::vector<std::shared_ptr<SentenceExpression>> temp;
	while (true) {
		Jump(src, size, pos, &pos);
		auto expression = _ParseExpression(src, size, pos, &pos);
		if (!expression) {
			break;
		}
		temp.emplace_back(expression);
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchSplitSymbol(src, size, pos, &pos)) {
			break;
		}
	}
	if (!Grammar::MatchArrayEnd(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<SentenceExpression>(new SentenceExpressionValueArray(temp));
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseArrayItem(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::SearchNextArray(src, size, pos)) {
		return nullptr;
	}
	auto valueExpression = __ParseExpressionValueForArrayValue(src, size, pos, &pos);
	if (!valueExpression) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	if (!Grammar::MatchArrayBegin(src, size, pos, &pos)) {
		return nullptr;
	}
	std::vector<std::shared_ptr<SentenceExpression>> indexExpressionVec;
	while (true) {
		Jump(src, size, pos, &pos);
		auto indexExpression = _ParseExpression(src, size, pos, &pos);
		if (!indexExpression) {
			return nullptr;
		}
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchArrayEnd(src, size, pos, &pos)) {
			return nullptr;
		}
		indexExpressionVec.emplace_back(indexExpression);

		auto savePos = pos;
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchArrayBegin(src, size, pos, &pos)) {
			pos = savePos;
			break;
		}
	}
	if (indexExpressionVec.empty()) {
		return nullptr;
	}
	*nextPos = pos;

	auto analysis = std::shared_ptr<IExpressionVariableAnalysis>(new ExpressionVariableAnalysisArrayItem(valueExpression, indexExpressionVec));
	return std::shared_ptr<SentenceExpression>(new SentenceExpressionVariable(analysis));
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseVariableName(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	std::string name;
	if (Grammar::MatchName(src, size, pos, nextPos, &name)) {
		auto analysis = std::shared_ptr<IExpressionVariableAnalysis>(new ExpressionVariableAnalysisName(name));
		return std::shared_ptr<SentenceExpression>(new SentenceExpressionVariable(analysis));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseFunctioCall(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	if (!Grammar::MatchLeftBrcket(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	std::vector<std::shared_ptr<SentenceExpression>> args;
	while (true) {
		auto argExpression = _ParseExpression(src, size, pos, &pos);
		if (!argExpression) {
			break;
		}
		args.emplace_back(argExpression);
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchSplitSymbol(src, size, pos, &pos)) {
			break;
		}
		Jump(src, size, pos, &pos);
	}
	if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<SentenceExpression>(new SentenceExpressionFunctionCall(name, args));
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseDoubleExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	DoubleSymbol symbol;
	bool bDouble = Grammar::MatchDoubleSymbol(src, size, pos, &pos, &symbol);
	bool bLast = !bDouble;
	auto variableSentence = _ParseVariable(src, size, pos, &pos);
	if (!variableSentence) {
		return nullptr;
	}
	if (!bDouble && !Grammar::MatchDoubleSymbol(src, size, pos, &pos, &symbol)) {
		return nullptr;
	}
	auto calculate = _GetCalculate(symbol);
	if (!calculate) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<SentenceExpression>(new SentenceExpressionDouble(variableSentence, calculate, bLast));
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseNotExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchNotSymbol(src, size, pos, &pos)) {
		return nullptr;
	}
	auto expression = _ParseExpressionValue(src, size, pos, &pos);
	if (!expression) {
		if (!Grammar::MatchLeftBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
		expression = _ParseExpressionMathBracket(src, size, pos, &pos, true);
		if (!expression) {
			return nullptr;
		}
	}
	*nextPos = pos;
	return std::shared_ptr<SentenceExpression>(new SentenceExpressionNot(expression));
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseNew(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchNew(src, size, pos, &pos)) {
		return nullptr;
	}
	if (!Jump(src, size, pos, &pos)) {
		return nullptr;
	}
	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	if (Grammar::MatchLeftBrcket(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	*nextPos = pos;
	return std::shared_ptr<SentenceExpression>(new SentenceExpressionNew(name));
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseInside(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::SearchNextInside(src, size, pos)) {
		return nullptr;
	}
	auto header = __ParseExpressionInsideHeader(src, size, pos, &pos);
	if (!header) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	if (!Grammar::MatchInsideSymbol(src, size, pos, &pos)) {
		return nullptr;
	}
	std::vector<std::shared_ptr<SentenceExpression>> insides;
	bool bTailCall = false;
	while (true) {
		Jump(src, size, pos, &pos);
		auto append = __ParseExpressionInsideAppend(src, size, pos, &pos);
		if (!append) {
			return nullptr;
		}
		insides.emplace_back(append);

		auto savePos = pos;
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchInsideSymbol(src, size, pos, &pos)) {
			bTailCall = (append->GetExpressionType() == ExpressionType::Function);
			pos = savePos;
			break;
		}
	}
	if (insides.empty()) {
		return nullptr;
	}
	*nextPos = pos;
	if (bTailCall) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpressionInside(header, insides));
	}
	auto analysis = std::shared_ptr<ExpressionVariableAnalysisInside>(new ExpressionVariableAnalysisInside(header, insides));
	return std::shared_ptr<SentenceExpression>(new SentenceExpressionVariable(analysis));
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseExpressionMath(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return _ParseExpressionMathBracket(src, size, pos, nextPos, false);
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseExpressionMathBracket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, bool bBracket) {
	std::stack<std::shared_ptr<SentenceExpression>> expressionStack;
	std::stack<MathSymbol> symbolStack;

	static const auto calcLoopFunc = [](MathSymbol symbol, decltype(expressionStack)* stack0, decltype(symbolStack)* stack1) {
		int level = Grammar::GetMathSymbolLevel(symbol);
		while (!stack1->empty()) {
			int preLevel = Grammar::GetMathSymbolLevel(stack1->top());
			if (preLevel < level) {
				break;
			}
			if (stack0->size() < 2) {
				return false;
			}
			auto topSymbol = stack1->top();
			stack1->pop();
			auto vr = stack0->top();
			stack0->pop();
			auto vl = stack0->top();
			stack0->pop();
			auto calculate = _GetCalculate(topSymbol);
			if (!calculate) {
				return false;
			}
			std::shared_ptr<SentenceExpressionMath> expression{nullptr};
			if (Grammar::IsVariableSelfAssignSymbol(topSymbol)) {
				expression = std::shared_ptr<SentenceExpressionSelfAssign>(new SentenceExpressionSelfAssign(vl, vr, calculate));
			} else {
				expression = std::shared_ptr<SentenceExpressionMath>(new SentenceExpressionMath(vl, vr, calculate));
			}
			stack0->emplace(expression);
		}
		return true;
	};

	while (true) {
		bool bRet = false;
		Jump(src, size, pos, &pos);
		if (Grammar::MatchLeftBrcket(src, size, pos, &pos)) {
			Jump(src, size, pos, &pos);
			auto priorityExpression = _ParseExpressionMathBracket(src, size, pos, &pos, true);
			if (!priorityExpression) {
				return nullptr;
			}
			expressionStack.emplace(priorityExpression);
			bRet = true;
		} else {
			auto value = _ParseExpressionValue(src, size, pos, &pos);
			if (value) {
				expressionStack.emplace(value);
				bRet = true;
			}
		}

		if (!bRet) {
			break;
		}

		auto saveJumpBeginPos = pos;
		Jump(src, size, pos, &pos);

		if (pos >= size) {
			break;
		}

		if (bBracket && Grammar::MatchRightBrcket(src, size, pos, &pos)) {
			break;
		}

		auto symbol = MathSymbol::None;
		if (Grammar::MatchMathSymbol(src, size, pos, &pos, &symbol)) {
			bRet = false;
			if (!calcLoopFunc(symbol, &expressionStack, &symbolStack)) {
				return nullptr;
			}
			symbolStack.emplace(symbol);
		} else {
			pos = saveJumpBeginPos;
			break;
		}
		if (bRet) {
			break;
		}
	}

	if (!calcLoopFunc(MathSymbol::None, &expressionStack, &symbolStack)) {
		return nullptr;
	}

	if (expressionStack.size() != 1) {
		return nullptr;
	}

	*nextPos = pos;

	return expressionStack.top();
}

IValueCalculate* ParseTool::_GetCalculate(MathSymbol symbol) {
	switch (symbol) {
	case MathSymbol::Mul:
		return ValueCalculateMul::GetInstance();
	case MathSymbol::Div:
		return ValueCalculateDiv::GetInstance();
	case MathSymbol::Mod:
		return ValueCalculateMod::GetInstance();
	case MathSymbol::Add:
		return ValueCalculateAdd::GetInstance();
	case MathSymbol::Sub:
		return ValueCalculateSub::GetInstance();
	case MathSymbol::Less:
		return ValueCalculateLess::GetInstance();
	case MathSymbol::LessEqual:
		return ValueCalculateSameOrLess::GetInstance();
	case MathSymbol::Equal:
		return ValueCalculateSame::GetInstance();
	case MathSymbol::NotEqual:
		return ValueCalculateNotSame::GetInstance();
	case MathSymbol::More:
		return ValueCalculateMore::GetInstance();
	case MathSymbol::MoreEqual:
		return ValueCalculateSameOrMore::GetInstance();
	case MathSymbol::LogicAnd:
		return ValueCalculateLogicAnd::GetInstance();
	case MathSymbol::LogicOr:
		return ValueCalculateLogicOr::GetInstance();
	case MathSymbol::AssignAdd:
		return ValueCalculateAdd::GetInstance();
	case MathSymbol::AssignSub:
		return ValueCalculateSub::GetInstance();
	case MathSymbol::AssignMul:
		return ValueCalculateMul::GetInstance();
	case MathSymbol::AssignDiv:
		return ValueCalculateDiv::GetInstance();
	case MathSymbol::AssignMod:
		return ValueCalculateMod::GetInstance();
	default:
		break;
	}

	return nullptr;
}

IValueCalculate* ParseTool::_GetCalculate(DoubleSymbol symbol) {
	switch (symbol) {
	case DoubleSymbol::AddAdd:
		return ValueCalculateAdd::GetInstance();
	case DoubleSymbol::SubSub:
		return ValueCalculateSub::GetInstance();
	default:
		break;
	}
	return nullptr;
}
