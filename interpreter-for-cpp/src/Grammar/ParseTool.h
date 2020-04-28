#pragma once

#include <functional>
#include <list>

namespace peak::interpreter {

class Sentence;
class SentenceExpression;
class SentenceExpressionMath;

class ParseTool {
public:
	static std::list<std::shared_ptr<Sentence>> Load(const std::string& src);

public:
	static bool Jump(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

	static bool JumpTextSpace(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpComment(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpCommentBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

public:
	// [0:success] [-1:jump but not end] [1:not jump, not end] [2:pos >= size]
	static int CheckAndJumpEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

public:
	static std::shared_ptr<Sentence> ParseSentence(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

public:
	static std::shared_ptr<Sentence> _ParseVariableDefineOrAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

public:
	static std::shared_ptr<SentenceExpression> _ParseString(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseVariable(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

	static std::shared_ptr<SentenceExpression> _ParseArithmetic(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private:
	static std::shared_ptr<SentenceExpressionMath> _CreateSentenceExpressionArithmetic(std::shared_ptr<SentenceExpression> left, std::shared_ptr<SentenceExpression> right, char symbol);

private:
	static std::list<std::function<std::shared_ptr<Sentence>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceParseList;
	static std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceExpressionParseList;
	static std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceValueParseList;
};
} // namespace peak::interpreter