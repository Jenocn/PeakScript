/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/ErrorLogger.h"
#include "Grammar.h"

namespace peak {
namespace interpreter {

class Sentence;
class SentenceExpression;
class IValueCalculate;

struct ParseData {
	bool bSuccess{false};
	std::list<std::shared_ptr<Sentence>> sentenceList;
};

class ParseTool {
public:
	static std::shared_ptr<ParseData> Load(const std::string& src);

private:
	static bool Jump(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

	static bool JumpTextSpace(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpTextSpaceAndEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpComment(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool JumpCommentBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

	static std::shared_ptr<Sentence> ParseSentence(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private:
	static std::shared_ptr<SentenceExpression> _ParseExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseExpressionMath(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseExpressionMathBracket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, bool bBracket);
	static std::shared_ptr<SentenceExpression> _ParseExpressionValue(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseVariable(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

	static std::shared_ptr<SentenceExpression> __ParseExpressionValueForArrayValue(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private: // Sentence
	static std::shared_ptr<Sentence> _ParseReturn(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseFunctionDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseVariableDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseVariableAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseVariableSet(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseExpressionToEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseCondition(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseLoop(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseFor(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseForeach(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseWhile(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseDoWhile(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseBlock(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseEcho(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseTryCatchFinally(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<Sentence> _ParseLoopControl(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private: // Expression Value
	static std::shared_ptr<SentenceExpression> _ParseString(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseArray(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseArrayItem(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseVariableName(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseFunctioCall(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseDoubleExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static std::shared_ptr<SentenceExpression> _ParseNotExpression(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);

private:
	static IValueCalculate* _GetCalculate(MathSymbol symbol);
	static IValueCalculate* _GetCalculate(DoubleSymbol symbol);

private:
	using SentenceParseList = std::list<std::function<std::shared_ptr<Sentence>(const std::string&, std::size_t, std::size_t, std::size_t*)>>;
	using ExpressionParseList = std::list<std::function<std::shared_ptr<SentenceExpression>(const std::string&, std::size_t, std::size_t, std::size_t*)>>;

	static SentenceParseList _sentenceParseList;
	static ExpressionParseList _sentenceValueParseList;
	static ExpressionParseList _sentenceVariableParseList;

	static ExpressionParseList __sentenceArrayItemParseList;

private:
	static std::string _GetErrorLine(const std::string& src, std::size_t size, std::size_t pos);
	static void _SetErrorMessage(ErrorCode code, const std::string& src, std::size_t size, std::size_t pos);
	static void _ClearErrorMessage();
	static void _ShowErrorMessage();
	static std::pair<ErrorCode, std::string> _errorMessage;
};
} // namespace interpreter
} // namespace peak