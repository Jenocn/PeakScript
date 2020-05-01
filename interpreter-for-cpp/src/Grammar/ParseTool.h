/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <functional>
#include <list>
#include "Grammar.h"

namespace peak::interpreter {

class Sentence;
class SentenceExpression;
class IValueCalculate;

class ParseTool {
public:
	static std::list<std::shared_ptr<Sentence>> Load(const std::string& src);

private:
	static bool Jump(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

	static bool JumpTextSpace(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpTextSpaceAndEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpComment(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpCommentBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private:
	static std::shared_ptr<Sentence> ParseSentence(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private:
	static std::shared_ptr<Sentence> _ParseVariableDefineOrAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseExpressionToEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseCondition(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseLoop(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseFor(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseWhile(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseEcho(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private:
	static std::shared_ptr<SentenceExpression> _ParseString(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseVariable(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

	static std::shared_ptr<SentenceExpression> _ParseExpressionMath(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseExpressionMathBracket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, bool bBracket);

private:
	static std::shared_ptr<IValueCalculate> _CreateCalculate(MathSymbol symbol);

private:
	static std::list<std::function<std::shared_ptr<Sentence>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceParseList;
	static std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceExpressionParseList;
	static std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceValueParseList;
};
} // namespace peak::interpreter