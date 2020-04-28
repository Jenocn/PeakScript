#include "ParseTool.h"
#include "../Runtime/Sentence/SentenceBlock.h"
#include "../Runtime/Sentence/SentenceCondition.h"
#include "../Runtime/Sentence/SentenceEcho.h"
#include "../Runtime/Sentence/SentenceExpressionArithmeticInstance.h"
#include "../Runtime/Sentence/SentenceExpressionValue.h"
#include "../Runtime/Sentence/SentenceExpressionVariable.h"
#include "../Runtime/Sentence/SentenceVariableAssign.h"
#include "../Runtime/Sentence/SentenceVariableDefine.h"
#include "../Runtime/Value/ValueTool.h"
#include "../Runtime/Variable.h"
#include "Grammar.h"
#include <stack>

using namespace peak::interpreter;

std::list<std::function<std::shared_ptr<Sentence>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceParseList = {
	_ParseVariableDefineOrAssign,
	_ParseCondition,
	_ParseBlock,
	_ParseEcho,
};
std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceExpressionParseList = {
	_ParseArithmetic,
	_ParseString,
	_ParseNumber,
	_ParseBool,
	_ParseNull,
	_ParseVariable,
};
std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceValueParseList = {
	_ParseString,
	_ParseNumber,
	_ParseBool,
	_ParseNull,
	_ParseVariable,
};

std::list<std::shared_ptr<Sentence>> ParseTool::Load(const std::string& src) {

	std::list<std::shared_ptr<Sentence>> ret;

	std::size_t pos = 0;
	auto size = src.size();
	while (pos < size) {
		Jump(src, size, pos, &pos);
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
				*nextPos = pos + 1;
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

std::shared_ptr<Sentence> ParseTool::_ParseVariableDefineOrAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	bool bDefine = Grammar::MatchVariableDefine(src, size, pos, &pos);
	if (bDefine && !Jump(src, size, pos, &pos)) {
		return nullptr;
	}

	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	if (JumpEnd(src, size, pos, &pos) && !bDefine) {
		return nullptr;
	}

	Jump(src, size, pos, &pos);
	if (!Grammar::MatchAssign(src, size, pos, &pos)) {
		return nullptr;
	}

	Jump(src, size, pos, &pos);
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression && !bDefine) {
		return nullptr;
	}
	if (!JumpEnd(src, size, pos, &pos)) {
		return nullptr;
	}

	*nextPos = pos;
	if (bDefine) {
		return std::shared_ptr<Sentence>(new SentenceVariableDefine(name, expression));
	}
	return std::shared_ptr<Sentence>(new SentenceVariableAssign(name, expression));
}

std::shared_ptr<Sentence> ParseTool::_ParseCondition(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchConditionIf(src, size, pos, &pos)) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	bool bBracket = Grammar::MatchArithmeticLeftBrcket(src, size, pos, &pos);
	if (bBracket) {
		Jump(src, size, pos, &pos);
	}
	auto expression = _ParseExpression(src, size, pos, &pos);
	if (!expression) {
		return nullptr;
	}
	if (bBracket) {
		Jump(src, size, pos, &pos);
		if (!Grammar::MatchArithmeticRightBrcket(src, size, pos, &pos)) {
			return nullptr;
		}
	}
	Jump(src, size, pos, &pos);
	auto sentenceBlock = _ParseBlock(src, size, pos, &pos);
	if (!sentenceBlock) {
		return nullptr;
	}

	std::shared_ptr<Sentence> sentenceElse{nullptr};

	Jump(src, size, pos, &pos);
	if (Grammar::MatchConditionElse(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
		sentenceElse = _ParseCondition(src, size, pos, &pos);
		if (!sentenceElse) {
			sentenceElse = _ParseBlock(src, size, pos, &pos);
		}
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceCondition(expression, sentenceBlock, sentenceElse));
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
		Jump(src, size, pos, &pos);
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

std::shared_ptr<SentenceExpression> ParseTool::_ParseArithmetic(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return _ParseArithmeticCheckBracket(src, size, pos, nextPos, false);
}

std::shared_ptr<SentenceExpression> ParseTool::_ParseArithmeticCheckBracket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, bool bBracket) {
	std::stack<std::shared_ptr<SentenceExpression>> expressionStack;
	std::stack<char> symbolStack;

	static const auto calcLoopFunc = [](char symbol, decltype(expressionStack)* stack0, decltype(symbolStack)* stack1) {
		int level = symbol == 0 ? 0 : Grammar::GetArithmeticSymbolLevel(symbol);
		while (!stack1->empty()) {
			int preLevel = Grammar::GetArithmeticSymbolLevel(stack1->top());
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
			auto expression = _CreateSentenceExpressionArithmetic(vl, vr, topSymbol);
			if (!expression) {
				return false;
			}
			stack0->emplace(expression);
		}
		return true;
	};

	while (true) {
		bool bRet = false;
		Jump(src, size, pos, &pos);
		if (Grammar::MatchArithmeticLeftBrcket(src, size, pos, &pos)) {
			Jump(src, size, pos, &pos);
			auto priorityExpression = _ParseArithmeticCheckBracket(src, size, pos, &pos, true);
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

		auto savePos = pos;
		if (JumpEnd(src, size, pos, &pos)) {
			pos = savePos;
			break;
		}
		Jump(src, size, pos, &pos);
		if (pos >= size) {
			break;
		}
		if (bBracket && Grammar::MatchArithmeticRightBrcket(src, size, pos, &pos)) {
			break;
		}

		char symbol = 0;
		if (Grammar::MatchArithmeticSymbol(src, size, pos, &pos, &symbol)) {
			bRet = false;
			if (!calcLoopFunc(symbol, &expressionStack, &symbolStack)) {
				return nullptr;
			}
			symbolStack.emplace(symbol);
		}
		if (bRet) {
			break;
		}
	}

	if (!calcLoopFunc(0, &expressionStack, &symbolStack)) {
		return nullptr;
	}

	if (expressionStack.size() != 1) {
		return nullptr;
	}

	*nextPos = pos;

	return expressionStack.top();
}

std::shared_ptr<SentenceExpressionMath> ParseTool::_CreateSentenceExpressionArithmetic(std::shared_ptr<SentenceExpression> v0, std::shared_ptr<SentenceExpression> v1, char symbol) {
	if (Grammar::IsArithmeticSymbolAdd(symbol)) {
		return std::shared_ptr<SentenceExpressionMath>(new SentenceExpressionArithmeticAdd(v0, v1));
	} else if (Grammar::IsArithmeticSymbolSub(symbol)) {
		return std::shared_ptr<SentenceExpressionMath>(new SentenceExpressionArithmeticSub(v0, v1));
	} else if (Grammar::IsArithmeticSymbolMul(symbol)) {
		return std::shared_ptr<SentenceExpressionMath>(new SentenceExpressionArithmeticMul(v0, v1));
	} else if (Grammar::IsArithmeticSymbolDiv(symbol)) {
		return std::shared_ptr<SentenceExpressionMath>(new SentenceExpressionArithmeticDiv(v0, v1));
	} else if (Grammar::IsArithmeticSymbolMod(symbol)) {
		return std::shared_ptr<SentenceExpressionMath>(new SentenceExpressionArithmeticMod(v0, v1));
	}
	return nullptr;
}