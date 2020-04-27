#include "ParseTool.h"
#include "../Runtime/Sentence/SentenceBlock.h"
#include "../Runtime/Sentence/SentenceExpressionValue.h"
#include "../Runtime/Sentence/SentenceVar.h"
#include "../Runtime/Value/ValueTool.h"
#include "../Runtime/Variable.h"
#include "Grammar.h"

using namespace peak::interpreter;

std::list<std::function<std::shared_ptr<Sentence>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceParseList = {
	_ParseVariableDefine,
};
std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> ParseTool::_sentenceExpressionParseList = {
	_ParseString,
	_ParseNumber,
	_ParseBool,
	_ParseNull,
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

std::shared_ptr<Sentence> ParseTool::_ParseVariableDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (!Grammar::MatchVariableDefine(src, size, pos, &pos)) {
		return nullptr;
	}
	if (pos >= size) {
		return nullptr;
	}
	if (!Grammar::IsTextSpace(src[pos])) {
		return nullptr;
	}
	Jump(src, size, pos, &pos);
	std::string name;
	if (!Grammar::MatchName(src, size, pos, &pos, &name)) {
		return nullptr;
	}
	bool bCheckTail = Jump(src, size, pos, &pos);
	std::shared_ptr<SentenceExpression> expression{nullptr};
	if (Grammar::MatchAssign(src, size, pos, &pos)) {
		Jump(src, size, pos, &pos);
		expression = _ParseExpression(src, size, pos, &pos);
		if (!expression) {
			return nullptr;
		}
		bCheckTail = Jump(src, size, pos, &pos);
	}

	if (bCheckTail) {
		if (!Grammar::IsGrammarEndSign(src[pos - 1])) {
			return nullptr;
		}
	} else {
		if (!Grammar::MatchEnd(src, size, pos, &pos)) {
			return nullptr;
		}
	}

	*nextPos = pos;
	return std::shared_ptr<Sentence>(new SentenceVar(name, expression));
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
