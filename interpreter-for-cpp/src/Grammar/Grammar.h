#pragma once

#include <string>

namespace peak::interpreter {
class Grammar {
public:
	static bool IsTextSpace(char ch);
	static bool IsTextNewLine(char ch);
	static bool IsTextSpecialChar(char ch);
	static bool IsTextNumber(char ch);
	static bool IsGrammarStringSign(char ch);
	static bool IsGrammarEndSign(char ch);
	static bool IsSpecialSign(const std::string& value);

public:
	static bool MatchNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, bool* value);
	static bool MatchNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, double* number);
	static bool MatchName(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* name);
	static bool MatchEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchComment(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchCommentBlockBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchCommentBlockEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchVariableDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchSign(const std::string& sign, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchSign(char sign, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos);
	static bool MatchPair(const std::string& signLeft, const std::string& signRight, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* result);
	static bool MatchPair(char signLeft, char signRight, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* result);

public:
};
} // namespace peak::interpreter