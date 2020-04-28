#include "Grammar.h"
#include <set>

using namespace peak::interpreter;

// text
static const std::set<char> SET_TEXT_SPACE = {' ', '\n', '\t'};
static const std::set<char> SET_TEXT_NEW_LINE = {'\n'};

// grammar
static const std::set<char> SET_STRING_SIGN = {'\"', '\'', '`'};
static const std::set<char> SET_END_SIGN = {'\n', ';'};
static const std::set<std::string> SET_VARIABLE_DEFINE_SIGN = {"var", "auto", "set", "the"};
static const std::set<std::string> SET_ASSIGN_SIGN = {"=", ":", ":=", "is", "as"};
static const std::set<std::string> SET_BOOL_TRUE_SIGN = {"true", "yes"};
static const std::set<std::string> SET_BOOL_FALSE_SIGN = {"false", "no"};
static const std::set<std::string> SET_CONDITION_IF_SIGN = {"if"};
static const std::set<std::string> SET_CONDITION_ELSE_SIGN = {"else"};
static const std::set<std::string> SET_BLOCK_BEGIN = {"{", "begin"};
static const std::set<std::string> SET_BLOCK_END = {"}", "end"};
static const std::set<std::string> SET_COMMENT_SIGN = {"//", "#"};
static const std::set<char> SET_ARITHMETIC_SYMBOL_LEVEL_2 = {'*', '/', '%'};
static const std::set<char> SET_ARITHMETIC_SYMBOL_LEVEL_1 = {'+', '-'};
static const std::string STRING_COMMENT_BLOCK_BEGIN_SIGN = "/*";
static const std::string STRING_COMMENT_BLOCK_END_SIGN = "*/";
static const std::string STRING_NULL_SIGN = "null";
static const std::string STRING_ECHO_SIGN = "echo";
static const char CHAR_LEFT_BRACKET = '(';
static const char CHAR_RIGHT_BRACKET = ')';

bool Grammar::IsTextSpace(char ch) {
	return (SET_TEXT_SPACE.find(ch) != SET_TEXT_SPACE.end());
}
bool Grammar::IsTextNewLine(char ch) {
	return (SET_TEXT_NEW_LINE.find(ch) != SET_TEXT_NEW_LINE.end());
}
bool Grammar::IsTextSpecialChar(char ch) {
	return (ch >= 0 && ch <= 47) || (ch >= 58 && ch <= 94) || (ch == 96) || (ch >= 123 && ch <= 126);
}
bool Grammar::IsTextNumber(char ch) {
	return ch >= '0' && ch <= '9';
}
bool Grammar::IsGrammarStringSign(char ch) {
	return (SET_STRING_SIGN.find(ch) != SET_STRING_SIGN.end());
}

bool Grammar::IsGrammarEndSign(char ch) {
	return (SET_END_SIGN.find(ch) != SET_END_SIGN.end());
}

bool Grammar::IsSpecialSign(const std::string& value) {
	std::size_t pos = 0;
	std::size_t size = value.size();
	if (MatchVariableDefine(value, size, 0, &pos)) {
		return true;
	}
	if (MatchAssign(value, size, 0, &pos)) {
		return true;
	}
	if (MatchNull(value, size, 0, &pos)) {
		return true;
	}
	bool bBoolValue = false;
	if (MatchBool(value, size, 0, &pos, &bBoolValue)) {
		return true;
	}
	if (MatchEcho(value, size, 0, &pos)) {
		return true;
	}

	// temp todo...
	return false;
}
int Grammar::GetArithmeticSymbolLevel(char ch) {
	if (SET_ARITHMETIC_SYMBOL_LEVEL_1.find(ch) != SET_ARITHMETIC_SYMBOL_LEVEL_1.end()) {
		return 1;
	}
	if (SET_ARITHMETIC_SYMBOL_LEVEL_2.find(ch) != SET_ARITHMETIC_SYMBOL_LEVEL_2.end()) {
		return 2;
	}
	return 0;
}

bool Grammar::IsArithmeticLeftBrcket(char ch) {
	return ch == CHAR_LEFT_BRACKET;
}
bool Grammar::IsArithmeticRightBrcket(char ch) {
	return ch == CHAR_RIGHT_BRACKET;
}
bool Grammar::IsArithmeticSymbolAdd(char ch) {
	return ch == '+';
}
bool Grammar::IsArithmeticSymbolSub(char ch) {
	return ch == '-';
}
bool Grammar::IsArithmeticSymbolMul(char ch) {
	return ch == '*';
}
bool Grammar::IsArithmeticSymbolDiv(char ch) {
	return ch == '/';
}
bool Grammar::IsArithmeticSymbolMod(char ch) {
	return ch == '%';
}

bool Grammar::MatchEcho(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_ECHO_SIGN, src, size, pos, nextPos);
}

bool Grammar::MatchBlockBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_BLOCK_BEGIN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Grammar::MatchBlockEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_BLOCK_END) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}

bool Grammar::MatchConditionIf(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_CONDITION_IF_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Grammar::MatchConditionElse(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_CONDITION_ELSE_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}

bool Grammar::MatchArithmeticLeftBrcket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_LEFT_BRACKET, src, size, pos, nextPos);
}
bool Grammar::MatchArithmeticRightBrcket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_RIGHT_BRACKET, src, size, pos, nextPos);
}

bool Grammar::MatchArithmeticSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, char* symbol) {
	for (auto sign : SET_ARITHMETIC_SYMBOL_LEVEL_2) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			*symbol = sign;
			return true;
		}
	}
	for (auto sign : SET_ARITHMETIC_SYMBOL_LEVEL_1) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			*symbol = sign;
			return true;
		}
	}
	return false;
}

bool Grammar::MatchNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_NULL_SIGN, src, size, pos, nextPos);
}

bool Grammar::MatchBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, bool* value) {
	for (const auto& sign : SET_BOOL_TRUE_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			*value = true;
			return true;
		}
	}
	for (const auto& sign : SET_BOOL_FALSE_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			*value = false;
			return true;
		}
	}
	return false;
}

bool Grammar::MatchNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, double* number) {
	if (pos >= size) {
		return false;
	}
	char ch = src[pos];
	bool bSub = (ch == '-');
	bool bPoint = (ch == '.');

	if (!IsTextNumber(ch) && !bSub && !bPoint) {
		return false;
	}
	auto beginPos = pos;
	++pos;
	while (pos < size) {
		ch = src[pos];
		if (!IsTextNumber(ch)) {
			if (ch == '.') {
				if (bPoint) {
					return false;
				}
				bPoint = true;
			} else {
				break;
			}
		}
		++pos;
	}

	if (pos == beginPos) {
		return false;
	}

	auto checkSize = 1;
	std::size_t p = 0;
	if (bPoint) {
		if (src[pos - 1] == '.') {
			return false;
		}
		++checkSize;
	}
	if (bSub) {
		++checkSize;
		p = 1;
	}
	auto tempSize = pos - beginPos;
	if (tempSize < checkSize) {
		return false;
	}
	auto tempStr = std::move(src.substr(beginPos, tempSize));
	if (bPoint) {
		tempStr.insert(p, 1, '0');
	}
	*number = atof(tempStr.c_str());
	*nextPos = pos;
	return true;
}

bool Grammar::MatchName(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* name) {
	if (pos >= size) {
		return false;
	}
	char ch = src[pos];
	if (IsTextNumber(ch) || IsTextSpecialChar(ch) || IsTextSpace(ch)) {
		return false;
	}
	auto beginPos = pos;
	while (pos < size) {
		ch = src[pos];
		if (IsTextSpecialChar(ch) || IsTextSpace(ch)) {
			break;
		}
		++pos;
	}

	if (pos == beginPos) {
		return false;
	}
	auto tempSize = pos - beginPos;
	auto tempName = std::move(src.substr(beginPos, tempSize));
	if (IsSpecialSign(tempName)) {
		return false;
	}
	*name = std::move(tempName);
	*nextPos = pos;
	return true;
}

bool Grammar::MatchAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_ASSIGN_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}

bool Grammar::MatchComment(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_COMMENT_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Grammar::MatchCommentBlockBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_COMMENT_BLOCK_BEGIN_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchCommentBlockEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_COMMENT_BLOCK_END_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchVariableDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_VARIABLE_DEFINE_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Grammar::MatchSign(const std::string& sign, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	auto signSize = sign.size();
	if (pos + signSize > size) {
		return false;
	}
	for (std::size_t i = 0; i < signSize; ++i) {
		if (sign[i] != src[pos + i]) {
			return false;
		}
	}
	*nextPos = pos + signSize;
	return true;
}
bool Grammar::MatchSign(char sign, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (pos >= size) {
		return false;
	}
	if (src[pos] == sign) {
		*nextPos = pos + 1;
		return true;
	}
	return false;
}

bool Grammar::MatchPair(const std::string& signLeft, const std::string& signRight, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* result) {
	if (!MatchSign(signLeft, src, size, pos, &pos)) {
		return false;
	}
	bool bSame = signLeft == signRight;
	auto beginPos = pos;
	int count = 0;
	while (pos < size) {
		if (!bSame && MatchSign(signLeft, src, size, pos, &pos)) {
			++count;
			continue;
		}
		if (MatchSign(signRight, src, size, pos, &pos)) {
			if (count > 0) {
				--count;
				continue;
			}
			auto tempSize = pos - signRight.size() - beginPos;
			*result = std::move(src.substr(beginPos, tempSize));
			*nextPos = pos;
			return true;
		}
		++pos;
	}
	return false;
}
bool Grammar::MatchPair(char signLeft, char signRight, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* result) {
	if (src[pos] != signLeft) {
		return false;
	}
	++pos;
	bool bSame = signLeft == signRight;
	auto beginPos = pos;
	int count = 0;
	bool bIgnore = false;
	while (pos < size) {
		char ch = src[pos];
		do {
			if (bIgnore) {
				break;
			}
			if (!bSame && (ch == signLeft)) {
				++count;
				break;
			}
			if (ch == signRight) {
				if (count > 0) {
					--count;
					break;
				}
				auto tempSize = pos - beginPos;
				*result = std::move(src.substr(beginPos, tempSize));
				*nextPos = pos + 1;
				return true;
			}
		} while (false);

		bIgnore = (ch == '\\' ? !bIgnore : false);
		++pos;
	}
	return false;
}
