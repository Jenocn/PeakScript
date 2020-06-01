#include "Grammar.h"

using namespace peak::interpreter;

// text
static const std::set<char> SET_TEXT_SPACE = {' ', '\n', '\r', '\t'};
static const std::set<char> SET_TEXT_NEW_LINE = {'\n', '\r'};

// grammar
static const std::set<char> SET_STRING_SIGN = {'\"', '\'', '`'};
static const std::set<char> SET_END_SIGN = {'\n', '\r', ';'};
static const std::set<std::string> SET_VARIABLE_DEFINE_SIGN = {"var", "the"};
static const std::set<std::string> SET_ASSIGN_SIGN = {"=", "is", "as"};
static const std::set<std::string> SET_BOOL_TRUE_SIGN = {"true", "yes"};
static const std::set<std::string> SET_BOOL_FALSE_SIGN = {"false", "no"};
static const std::set<std::string> SET_CONDITION_IF_SIGN = {"if"};
static const std::set<std::string> SET_CONDITION_ELSE_SIGN = {"else"};
static const std::set<std::string> SET_BLOCK_BEGIN = {"{", "begin"};
static const std::set<std::string> SET_BLOCK_END = {"}", "end"};
static const std::set<std::string> SET_COMMENT_SIGN = {"//", "#"};
static const std::set<std::string> SET_EXTENDS_SIGN = {":", "extends"};
static const std::map<MathSymbol, std::pair<int, std::set<std::string>>> MAP_SET_MATH_SYMBOL = {
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
static const std::map<DoubleSymbol, std::string> MAP_DOUBLE_SYMBOL = {
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

static const char CHAR_NOT_SYMBOL = '!';
static const char CHAR_LEFT_BRACKET = '(';
static const char CHAR_RIGHT_BRACKET = ')';
static const char CHAR_SPLIT_SYMBOL = ',';
static const char CHAR_ARRAY_BEGIN = '[';
static const char CHAR_ARRAY_END = ']';
static const char CHAR_INSIDE_SYMBOL = '.';

bool Grammar::IsTextSpace(char ch) {
	return (SET_TEXT_SPACE.find(ch) != SET_TEXT_SPACE.end());
}
bool Grammar::IsTextNewLine(char ch) {
	return (SET_TEXT_NEW_LINE.find(ch) != SET_TEXT_NEW_LINE.end());
}
bool Grammar::IsTextSpecialChar(char ch) {
	return (ch >= 0 && ch <= 47) || (ch >= 58 && ch <= 64) || (ch >= 91 && ch <= 94) || (ch == 96) || (ch >= 123 && ch <= 127);
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
		// temp todo...

		return false;
	} while (false);

	return pos >= size || IsTextSpecialChar(value[pos]);
}
int Grammar::GetMathSymbolLevel(MathSymbol value) {
	auto ite = MAP_SET_MATH_SYMBOL.find(value);
	if (ite != MAP_SET_MATH_SYMBOL.end()) {
		return ite->second.first;
	}
	return 0;
}

bool Grammar::IsLeftBrcket(char ch) {
	return ch == CHAR_LEFT_BRACKET;
}
bool Grammar::IsRightBrcket(char ch) {
	return ch == CHAR_RIGHT_BRACKET;
}

bool Grammar::IsVariableSelfAssignSymbol(MathSymbol value) {
	static const std::set<MathSymbol> selfAssignSymbol = {
		MathSymbol::AssignAdd,
		MathSymbol::AssignDiv,
		MathSymbol::AssignSub,
		MathSymbol::AssignMul,
		MathSymbol::AssignMod,
	};
	return selfAssignSymbol.find(value) != selfAssignSymbol.end();
}
bool Grammar::IsWordValidSymbol(char ch) {
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

bool Grammar::SearchNextInside(const std::string& src, std::size_t size, std::size_t pos) {
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

bool Grammar::SearchNextArray(const std::string& src, std::size_t size, std::size_t pos) {
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

bool Grammar::MatchExtends(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	for (auto& sign : SET_EXTENDS_SIGN) {
		if (MatchSign(sign, src, size, pos, nextPos)) {
			return true;
		}
	}
	return false;
}
bool Grammar::MatchObject(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_OBJECT_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchInsideSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_INSIDE_SYMBOL, src, size, pos, nextPos);
}

bool Grammar::MatchNew(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_NEW_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchObjectBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchBlockBegin(src, size, pos, nextPos);
}
bool Grammar::MatchObjectEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchBlockEnd(src, size, pos, nextPos);
}
bool Grammar::MatchArrayBegin(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_ARRAY_BEGIN, src, size, pos, nextPos);
}
bool Grammar::MatchArrayEnd(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_ARRAY_END, src, size, pos, nextPos);
}
bool Grammar::MatchDoubleSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, DoubleSymbol* symbol) {
	for (auto& pair : MAP_DOUBLE_SYMBOL) {
		if (MatchSign(pair.second, src, size, pos, nextPos)) {
			*symbol = pair.first;
			return true;
		}
	}
	return false;
}
bool Grammar::MatchNotSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_NOT_SYMBOL, src, size, pos, nextPos);
}
bool Grammar::MatchConst(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_CONST_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchReturn(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_RETURN_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchSplitSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_SPLIT_SYMBOL, src, size, pos, nextPos);
}
bool Grammar::MatchFunction(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FUNCTION_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchBreak(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_BREAK_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchContinue(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_CONTINUE_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchTry(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_TRY_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchCatch(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_CATCH_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchFinally(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FINALLY_SIGN, src, size, pos, nextPos);
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

bool Grammar::MatchFor(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FOR_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchForeach(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FOREACH_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchForeachIn(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_FOREACH_IN_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchWhile(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_WHILE_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchDo(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_DO_SIGN, src, size, pos, nextPos);
}
bool Grammar::MatchLoop(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_LOOP_SIGN, src, size, pos, nextPos);
}

bool Grammar::MatchLeftBrcket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_LEFT_BRACKET, src, size, pos, nextPos);
}
bool Grammar::MatchRightBrcket(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(CHAR_RIGHT_BRACKET, src, size, pos, nextPos);
}

bool Grammar::MatchMathSymbol(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos, MathSymbol* symbol) {
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
bool Grammar::MatchVariableSet(const std::string& src, std::size_t size, std::size_t pos, std::size_t* nextPos) {
	return MatchSign(STRING_SET_SIGN, src, size, pos, nextPos);
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
