#include "ParseTool.h"
#include "../Runtime/Sentence/SentenceBlock.h"
#include "../Runtime/Sentence/SentenceCondition.h"
#include "../Runtime/Sentence/SentenceDoWhile.h"
#include "../Runtime/Sentence/SentenceEcho.h"
#include "../Runtime/Sentence/SentenceExpressionDouble.h"
#include "../Runtime/Sentence/SentenceExpressionFunctionCall.h"
#include "../Runtime/Sentence/SentenceExpressionMath.h"
#include "../Runtime/Sentence/SentenceExpressionSelfAssign.h"
#include "../Runtime/Sentence/SentenceExpressionValue.h"
#include "../Runtime/Sentence/SentenceExpressionVariable.h"
#include "../Runtime/Sentence/SentenceFor.h"
#include "../Runtime/Sentence/SentenceFunctionDefine.h"
#include "../Runtime/Sentence/SentenceLoop.h"
#include "../Runtime/Sentence/SentenceLoopControl.h"
#include "../Runtime/Sentence/SentenceReturn.h"
#include "../Runtime/Sentence/SentenceTryCatchFinally.h"
#include "../Runtime/Sentence/SentenceVariableAssign.h"
#include "../Runtime/Sentence/SentenceVariableDefine.h"
#include "../Runtime/Sentence/SentenceVariableSet.h"
#include "../Runtime/Sentence/SentenceWhile.h"
#include "../Runtime/Value/ValueCalculateInstance.h"
#include "../Runtime/Value/ValueTool.h"
#include "../Runtime/Variable.h"
#include <stack>
#include <vector>

using namespace peak::interpreter;

std::list<std::function<std::shared_ptr<Sentence>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceParseList = {
	_ParseVariableDefineOrAssign,
	_ParseVariableSet,
	_ParseFunctionDefine,
	_ParseCondition,
	_ParseLoop,
	_ParseFor,
	_ParseWhile,
	_ParseDoWhile,
	_ParseBlock,
	_ParseEcho,
	_ParseLoopControl,
	_ParseReturn,
	_ParseTryCatchFinally,
	_ParseExpressionToEnd,
};
std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceExpressionParseList = {
	_ParseExpressionMath,
};
std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceValueParseList = {
	_ParseString,
	_ParseNumber,
	_ParseBool,
	_ParseNull,
	_ParseFunctioCall,
	_ParseDoubleExpression,
	_ParseVariable,
};

std::list<std::shared_ptr<Sentence>> ParseTool::Load(const std::string& src) {

	std::list<std::shared_ptr<Sentence>> ret;

	std::size_t pos = 0;
	auto size = src.size();
	while (pos < size) {
		JumpEnd(src, size, pos, &pos);
		if (pos >= size) {
			break;
		}
		auto parseSentence = ParseSentence(src, size, pos, &pos);
		if (!parseSentence) {
			break;
		}
		ret.emplace_back(parseSentence);
	}

	return ret;
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
		while (pos < size) {
			if (Grammar::IsTextNewLine(src[pos])) {
				*nextPos = pos;
				return true;
			}
			++pos;
		}
	}
	return false;
}

bool ParseTool::JumpCommentBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (Grammar::MatchCommentBlockBegin(src, size, pos, &pos)) {
		while (pos < size) {
			if (Grammar::MatchCommentBlockEnd(src, size, pos, &pos)) {
				*nextPos = pos;
				return true;
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
	for (auto func : _sentenceExpressionParseList) {
		auto parseData = func(src, size, pos, nextPos);
		if (parseData) {
			return parseData;
		}
	}
	return nullptr;
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
	auto contentSentence = ParseSentence(src, size, pos, &pos);
	if (!contentSentence) {
		return nullptr;
	}
	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceFunctionDefine(name, params, contentSentence));
}

std::shared_ptr<Sentence> ParseTool::_ParseVariableDefineOrAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool bConst = Grammar::MatchConst(src, size, pos, &pos);
	if (bConst && !Jump(src, size, pos, &pos)) {
		return nullptr;
	}
	bool bDefine = Grammar::MatchVariableDefine(src, size, pos, &pos);
	if (bDefine && !Jump(src, size, pos, &pos)) {
		return nullptr;
	}
	bDefine |= bConst;

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
		if (bDefine && JumpEnd(src, size, pos, &pos)) {
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
	if (bDefine) {
		return std::shared_ptr<Sentence>(new SentenceVariableDefine(name, attribute, expression));
	}
	return std::shared_ptr<Sentence>(new SentenceVariableAssign(name, expression));
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
	auto expression = _ParseExpressionMath(src, size, pos, &pos);
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

	auto condition = _ParseExpressionMath(src, size, pos, &pos);
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
	if (!Grammar::IsGrammarStringSign(src[pos])) {
		return nullptr;
	}
	char sign = src[pos];
	std::string temp;
	if (Grammar::MatchPair(sign, sign, src, size, pos, &pos, &temp)) {
		*nextPos = pos;
		return std::shared_ptr<SentenceExpression>(new SentenceExpressionValue(std::shared_ptr<Value>(new ValueString(temp))));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	double temp{0};
	if (Grammar::MatchNumber(src, size, pos, nextPos, &temp)) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpressionValue(std::shared_ptr<Value>(new ValueNumber(temp))));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool temp{false};
	if (Grammar::MatchBool(src, size, pos, nextPos, &temp)) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpressionValue(std::shared_ptr<Value>(new ValueBool(temp))));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (Grammar::MatchNull(src, size, pos, nextPos)) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpressionValue(std::shared_ptr<Value>(new ValueNull())));
	}
	return nullptr;
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseVariable(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	std::string name;
	if (Grammar::MatchName(src, size, pos, nextPos, &name)) {
		return std::shared_ptr<SentenceExpression>(new SentenceExpressionVariable(name));
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
			for (auto func : _sentenceValueParseList) {
				auto value = func(src, size, pos, &pos);
				if (value) {
					expressionStack.emplace(value);
					bRet = true;
					break;
				}
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
