#pragma once

#include <functional>
#include <list>

namespace peak::interpreter {

class Sentence;
class SentenceExpression;

class ParseTool {
public:
	static std::list<std::shared_ptr<Sentence>> Load(const std::string& src);

public:
	static std::size_t JumpTextSpace(const std::string& src, std::size_t size, std::size_t pos);
	static std::size_t JumpComment(const std::string& src, std::size_t size, std::size_t pos);
	static std::size_t JumpCommentBlock(const std::string& src, std::size_t size, std::size_t pos);
	static std::shared_ptr<Sentence> ParseSentence(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

public:
	static std::shared_ptr<Sentence> _ParseVariableDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseString(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private:
	static std::list<std::function<std::shared_ptr<Sentence>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceParseList;
	static std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>> _sentenceExpressionParseList;
};
} // namespace peak::interpreter