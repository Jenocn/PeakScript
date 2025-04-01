#include "syntax.h"
#include <unordered_set>
#include <unordered_map>

using namespace peak;

// text
static const std::unordered_set<char> SET_TEXT_SPACE = {' ', '\n', '\r', '\t'};
static const std::unordered_set<char> SET_TEXT_NEW_LINE = {'\n', '\r'};

// grammar
static const std::unordered_set<char> SET_STRING_SIGN = {'\"', '\'', '`'};
static const std::unordered_set<char> SET_END_SIGN = {'\n', '\r', ';', '\0'};
static const std::unordered_set<std::string> SET_VARIABLE_DEFINE_SIGN = {"var", "the"};
static const std::unordered_set<std::string> SET_ASSIGN_SIGN = {"=", "is", "as"};
static const std::unordered_set<std::string> SET_BOOL_TRUE_SIGN = {"true", "yes"};
static const std::unordered_set<std::string> SET_BOOL_FALSE_SIGN = {"false", "no"};
static const std::unordered_set<std::string> SET_CONDITION_IF_SIGN = {"if"};
static const std::unordered_set<std::string> SET_CONDITION_ELSE_SIGN = {"else"};
static const std::unordered_set<std::string> SET_BLOCK_BEGIN = {"{", "begin"};
static const std::unordered_set<std::string> SET_BLOCK_END = {"}", "end"};
static const std::unordered_set<std::string> SET_COMMENT_SIGN = {"//", "#"};
static const std::unordered_set<std::string> SET_EXTENDS_SIGN = {":", "extends"};
static const std::unordered_map<MathSymbol, std::pair<int, std::unordered_set<std::string>>> MAP_SET_MATH_SYMBOL = {
	{MathSymbol::AssignMul, {110, {"*="}}},
	{MathSymbol::AssignDiv, {110, {"/="}}},
	{MathSymbol::AssignMod, {110, {"%="}}},
	{MathSymbol::AssignAdd, {110, {"+="}}},
	{MathSymbol::AssignSub, {110, {"-="}}},
	{MathSymbol::Mul, {100, {"*"}}},
	{MathSymbol::Div, {100, {"/"}}},
	{MathSymbol::Mod, {100, {"%"}}},
	{MathSymbol::Add, {90, {"+"}}},
	{MathSymbol::Sub, {90, {"-"}}},
	{MathSymbol::Less, {80, {"<"}}},
	{MathSymbol::LessEqual, {80, {"<="}}},
	{MathSymbol::More, {80, {">"}}},
	{MathSymbol::MoreEqual, {80, {">="}}},
	{MathSymbol::Equal, {70, {"=="}}},
	{MathSymbol::NotEqual, {70, {"!="}}},
	{MathSymbol::LogicAnd, {60, {"&&", "and"}}},
	{MathSymbol::LogicOr, {60, {"||", "or"}}},
};
static const std::unordered_map<DoubleSymbol, std::string> MAP_DOUBLE_SYMBOL = {
	{DoubleSymbol::AddAdd, "++"},
	{DoubleSymbol::SubSub, "--"},
};
static const std::string STRING_COMMENT_BLOCK_BEGIN_SIGN = "/*";
static const std::string STRING_COMMENT_BLOCK_END_SIGN = "*/";
static const std::string STRING_NULL_SIGN = "null";
static const std::string STRING_ECHO_SIGN = "echo";
static const std::string STRING_FOR_SIGN = "for";
static const std::string STRING_FOREACH_SIGN = "foreach";
static const std::string STRING_FOREACH_IN_SIGN = "in";
static const std::string STRING_WHILE_SIGN = "while";
static const std::string STRING_DO_SIGN = "do";
static const std::string STRING_LOOP_SIGN = "loop";
static const std::string STRING_TRY_SIGN = "try";
static const std::string STRING_CATCH_SIGN = "catch";
static const std::string STRING_FINALLY_SIGN = "finally";
static const std::string STRING_BREAK_SIGN = "break";
static const std::string STRING_CONTINUE_SIGN = "continue";
static const std::string STRING_FUNCTION_SIGN = "function";
static const std::string STRING_RETURN_SIGN = "return";
static const std::string STRING_SET_SIGN = "set";
static const std::string STRING_CONST_SIGN = "const";
static const std::string STRING_NEW_SIGN = "new";
static const std::string STRING_OBJECT_SIGN = "object";
static const std::string STRING_ENUM_SIGN = "enum";
static const std::string STRING_IMPORT_SIGN = "import";
static const std::string STRING_EXPORT_SIGN = "export";

static const char CHAR_NOT_SYMBOL = '!';
static const char CHAR_LEFT_BRACKET = '(';
static const char CHAR_RIGHT_BRACKET = ')';
static const char CHAR_SPLIT_SYMBOL = ',';
static const char CHAR_ARRAY_BEGIN = '[';
static const char CHAR_ARRAY_END = ']';
static const char CHAR_INSIDE_SYMBOL = '.';

bool Syntax::IsTextSpace(char ch) {
	return (SET_TEXT_SPACE.find(ch) != SET_TEXT_SPACE.end());
}
bool Syntax::IsTextNewLine(char ch) {
	return (SET_TEXT_NEW_LINE.find(ch) != SET_TEXT_NEW_LINE.end());
}
bool Syntax::IsTextSpecialChar(char ch) {
	return (ch >= 0 && ch <= 47) || (ch >= 58 && ch <= 64) || (ch >= 91 && ch <= 94) || (ch == 96) || (ch >= 123 && ch <= 127);
}
bool Syntax::IsTextNumber(char ch) {
	return ch >= '0' && ch <= '9';
}
bool Syntax::IsGrammarStringSign(char ch) {
	return (SET_STRING_SIGN.find(ch) != SET_STRING_SIGN.end());
}

bool Syntax::IsGrammarEndSign(char ch) {
	return (SET_END_SIGN.find(ch) != SET_END_SIGN.end());
}

bool Syntax::IsSpecialSign(const std::string& value) {
	std::size_t pos = 0;
	std::size_t size = value.size();
	do {
		if (MatchVariableDefine(value, size, 0, &pos)) {
			break;
		}
		if (MatchNull(value, size, 0, &pos)) {
			break;
		}
		bool bBoolValue = false;
		if (MatchBool(value, size, 0, &pos, &bBoolValue)) {
			break;
		}
		if (MatchEcho(value, size, 0, &pos)) {
			break;
		}
		if (MatchForeach(value, size, 0, &pos)) {
			break;
		}
		if (MatchFor(value, size, 0, &pos)) {
			break;
		}
		if (MatchWhile(value, size, 0, &pos)) {
			break;
		}
		if (MatchLoop(value, size, 0, &pos)) {
			break;
		}
		if (MatchBlockBegin(value, size, 0, &pos)) {
			break;
		}
		if (MatchBlockEnd(value, size, 0, &pos)) {
			break;
		}
		if (MatchTry(value, size, 0, &pos)) {
			break;
		}
		if (MatchCatch(value, size, 0, &pos)) {
			break;
		}
		if (MatchFinally(value, size, 0, &pos)) {
			break;
		}
		if (MatchBreak(value, size, 0, &pos)) {
			break;
		}
		if (MatchContinue(value, size, 0, &pos)) {
			break;
		}
		if (MatchDo(value, size, 0, &pos)) {
			break;
		}
		if (MatchConditionIf(value, size, 0, &pos)) {
			break;
		}
		if (MatchConditionElse(value, size, 0, &pos)) {
			break;
		}
		if (MatchReturn(value, size, 0, &pos)) {
			break;
		}
		if (MatchNew(value, size, 0, &pos)) {
			break;
		}
		if (MatchAssign(value, size, 0, &pos)) {
			break;
		}
		if (MatchExtends(value, size, 0, &pos)) {
			break;
		}
		if (MatchObject(value, size, 0, &pos)) {
			break;
		}
		if (MatchEnum(value, size, 0, &pos)) {
			break;
		}
		if (MatchImport(value, size, 0, &pos)) {
			break;
		}
		if (MatchExport(value, size, 0, &pos)) {
			break;
		}
		// temp todo...

		return false;
	} while (false);

	return pos >= size || IsTextSpecialChar(value[pos]);
}
int Syntax::GetMathSymbolLevel(MathSymbol value) {
	auto ite = MAP_SET_MATH_SYMBOL.find(value);
	if (ite != MAP_SET_MATH_SYMBOL.end()) {
		return ite->second.first;
	}
	return 0;
}

bool Syntax::IsLeftBrcket(char ch) {
	return ch == CHAR_LEFT_BRACKET;
}
bool Syntax::IsRightBrcket(char ch) {
	return ch == CHAR_RIGHT_BRACKET;
}

bool Syntax::IsVariableSelfAssignSymbol(MathSymbol value) {
	static const std::unordered_set<MathSymbol> selfAssignSymbol = {
		MathSymbol::AssignAdd,
		MathSymbol::AssignDiv,
		MathSymbol::AssignSub,
		MathSymbol::AssignMul,
		MathSymbol::AssignMod,
	};
	return selfAssignSymbol.find(value) != selfAssignSymbol.end();
}
bool Syntax::IsWordValidSymbol(char ch) {
	if (!IsTextSpecialChar(ch)) {
		return true;
	}
	return IsTextSpace(ch) ||
		   (ch == CHAR_LEFT_BRACKET) ||
		   (ch == CHAR_RIGHT_BRACKET) ||
		   (ch == CHAR_SPLIT_SYMBOL) ||
		   (ch == CHAR_ARRAY_BEGIN) ||
		   (ch == CHAR_ARRAY_END) ||
		   (ch == CHAR_INSIDE_SYMBOL);
}

bool Syntax::SearchNextInside(const std::string& src, std::size_t size, std::size_t pos) {
	for (auto i = pos; i < size; ++i) {
		if (MatchInsideSymbol(src, size, i, &i)) {
			return true;
		}
		char ch = src[i];
		if (!IsWordValidSymbol(ch)) {
			MathSymbol symbol;
			if (!MatchMathSymbol(src, size, i, &i, &symbol)) {
				return false;
			}
		}
	}
	return false;
}

bool Syntax::SearchNextArray(const std::string& src, std::size_t size, std::size_t pos) {
	for (auto i = pos; i < size; ++i) {
		if (MatchArrayBegin(src, size, i, &i)) {
			return true;
		}
		char ch = src[i];
		if (!IsWordValidSymbol(ch)) {
			MathSymbol symbol;
			if (!MatchMathSymbol(src, size, i, &i, &symbol)) {
				return false;
			}
		}
	}
	return false;
}

bool Syntax::MatchImport(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_IMPORT_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchExport(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_EXPORT_SIGN, src, size, pos, nextPos);
}

bool Syntax::MatchEnum(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_ENUM_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchExtends(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto& sign : SET_EXTENDS_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Syntax::MatchObject(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_OBJECT_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchInsideSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_INSIDE_SYMBOL, src, size, pos, nextPos);
}

bool Syntax::MatchNew(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_NEW_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchObjectBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchBlockBegin(src, size, pos, nextPos);
}
bool Syntax::MatchObjectEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchBlockEnd(src, size, pos, nextPos);
}
bool Syntax::MatchArrayBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_ARRAY_BEGIN, src, size, pos, nextPos);
}
bool Syntax::MatchArrayEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_ARRAY_END, src, size, pos, nextPos);
}
bool Syntax::MatchDoubleSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, DoubleSymbol* symbol) {
	for (auto& pair : MAP_DOUBLE_SYMBOL) {
		if (MatchSign(pair.second, src, size, pos, nextPos)) {
			*symbol = pair.first;
			return true;
		}
	}
	return false;
}
bool Syntax::MatchNotSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_NOT_SYMBOL, src, size, pos, nextPos);
}
bool Syntax::MatchConst(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_CONST_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchReturn(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_RETURN_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchSplitSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_SPLIT_SYMBOL, src, size, pos, nextPos);
}
bool Syntax::MatchFunction(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FUNCTION_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchBreak(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_BREAK_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchContinue(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_CONTINUE_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchTry(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_TRY_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchCatch(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_CATCH_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchFinally(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FINALLY_SIGN, src, size, pos, nextPos);
}

bool Syntax::MatchEcho(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_ECHO_SIGN, src, size, pos, nextPos);
}

bool Syntax::MatchBlockBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_BLOCK_BEGIN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Syntax::MatchBlockEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_BLOCK_END) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}

bool Syntax::MatchConditionIf(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_CONDITION_IF_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Syntax::MatchConditionElse(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_CONDITION_ELSE_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}

bool Syntax::MatchFor(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FOR_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchForeach(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FOREACH_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchForeachIn(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FOREACH_IN_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchWhile(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_WHILE_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchDo(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_DO_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchLoop(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_LOOP_SIGN, src, size, pos, nextPos);
}

bool Syntax::MatchLeftBrcket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_LEFT_BRACKET, src, size, pos, nextPos);
}
bool Syntax::MatchRightBrcket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_RIGHT_BRACKET, src, size, pos, nextPos);
}

bool Syntax::MatchMathSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, MathSymbol* symbol) {
	for (auto& pair : MAP_SET_MATH_SYMBOL) {
		const auto& setPair = pair.second;
		const auto& signSet = setPair.second;
		for (auto& sign : signSet) {
			if (MatchSign(sign, src, size, pos, nextPos)) {
				*symbol = pair.first;
				return true;
			}
		}
	}
	return false;
}

bool Syntax::MatchNull(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_NULL_SIGN, src, size, pos, nextPos);
}

bool Syntax::MatchBool(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, bool* value) {
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

bool Syntax::MatchNumber(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, double* number) {
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

	std::size_t checkSize = 1;
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
	auto tempStr = src.substr(beginPos, tempSize);
	if (bPoint) {
		tempStr.insert(p, 1, '0');
	}
	*number = atof(tempStr.c_str());
	*nextPos = pos;
	return true;
}

bool Syntax::MatchName(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* name) {
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
	auto tempName = src.substr(beginPos, tempSize);
	if (IsSpecialSign(tempName)) {
		return false;
	}
	*name = std::move(tempName);
	*nextPos = pos;
	return true;
}

bool Syntax::MatchAssign(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_ASSIGN_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}

bool Syntax::MatchComment(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_COMMENT_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Syntax::MatchCommentBlockBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_COMMENT_BLOCK_BEGIN_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchCommentBlockEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_COMMENT_BLOCK_END_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchVariableDefine(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (const auto& sign : SET_VARIABLE_DEFINE_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Syntax::MatchVariableSet(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_SET_SIGN, src, size, pos, nextPos);
}
bool Syntax::MatchSign(const std::string& sign, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
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
bool Syntax::MatchSign(char sign, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	if (pos >= size) {
		return false;
	}
	if (src[pos] == sign) {
		*nextPos = pos + 1;
		return true;
	}
	return false;
}

bool Syntax::MatchPair(const std::string& signLeft, const std::string& signRight, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* result) {
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
bool Syntax::MatchPair(char signLeft, char signRight, const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, std::string* result) {
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
