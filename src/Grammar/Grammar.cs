/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	enum MathSymbol {
		None,
		LessEqual, // <=
		MoreEqual, // >=
		Equal, // ==
		NotEqual, // !=
		LogicAnd, // &&
		LogicOr, // ||
		AssignAdd, // +=
		AssignSub, // -=
		AssignMul, // *=
		AssignDiv, // /=
		AssignMod, // %=
		Less, // <
		More, // >
		Mul, // *
		Div, // /
		Mod, // %
		Add, // +
		Sub, // -
	}

	enum DoubleSymbol {
		AddAdd, // ++
		SubSub, // --
	}

	class Grammar {
		private static readonly HashSet<char> SET_TEXT_SPACE = new HashSet<char>() { ' ', '\n', '\r', '\t' };
		private static readonly HashSet<char> SET_TEXT_NEW_LINE = new HashSet<char>() { '\n', '\r' };

		// grammar
		private static readonly HashSet<char> SET_STRING_SIGN = new HashSet<char>() { '\"', '\'', '`' };
		private static readonly HashSet<char> SET_END_SIGN = new HashSet<char>() { '\n', '\r', ';', '\0' };
		private static readonly HashSet<string> SET_VARIABLE_DEFINE_SIGN = new HashSet<string>() { "var", "the" };
		private static readonly HashSet<string> SET_ASSIGN_SIGN = new HashSet<string>() { "=", "is", "as" };
		private static readonly HashSet<string> SET_BOOL_TRUE_SIGN = new HashSet<string>() { "true", "yes" };
		private static readonly HashSet<string> SET_BOOL_FALSE_SIGN = new HashSet<string>() { "false", "no" };
		private static readonly HashSet<string> SET_CONDITION_IF_SIGN = new HashSet<string>() { "if" };
		private static readonly HashSet<string> SET_CONDITION_ELSE_SIGN = new HashSet<string>() { "else" };
		private static readonly HashSet<string> SET_BLOCK_BEGIN = new HashSet<string>() { "{", "begin" };
		private static readonly HashSet<string> SET_BLOCK_END = new HashSet<string>() { "}", "end" };
		private static readonly HashSet<string> SET_COMMENT_SIGN = new HashSet<string>() { "//", "#" };
		private static readonly HashSet<string> SET_EXTENDS_SIGN = new HashSet<string>() { ":", "extends" };
		private static readonly Dictionary<MathSymbol, KeyValuePair<int, HashSet<string>>> MAP_SET_MATH_SYMBOL = new Dictionary<MathSymbol, KeyValuePair<int, HashSet<string>>>() {
			{ MathSymbol.AssignMul, new KeyValuePair<int, HashSet<string>>(110, new HashSet<string>() { "*=" }) },
			{ MathSymbol.AssignDiv, new KeyValuePair<int, HashSet<string>>( 110, new HashSet<string>() { "/=" }) },
			{ MathSymbol.AssignMod, new KeyValuePair<int, HashSet<string>>( 110, new HashSet<string>() { "%=" }) },
			{ MathSymbol.AssignAdd, new KeyValuePair<int, HashSet<string>>( 110, new HashSet<string>() { "+=" }) },
			{ MathSymbol.AssignSub, new KeyValuePair<int, HashSet<string>>( 110, new HashSet<string>() { "-=" }) },
			{ MathSymbol.Mul, new KeyValuePair<int, HashSet<string>>( 100, new HashSet<string>() { "*" }) },
			{ MathSymbol.Div, new KeyValuePair<int, HashSet<string>>( 100, new HashSet<string>() { "/" }) },
			{ MathSymbol.Mod, new KeyValuePair<int, HashSet<string>>( 100, new HashSet<string>() { "%" }) },
			{ MathSymbol.Add, new KeyValuePair<int, HashSet<string>>( 90, new HashSet<string>() { "+" }) },
			{ MathSymbol.Sub, new KeyValuePair<int, HashSet<string>>( 90, new HashSet<string>() { "-" }) },
			{ MathSymbol.Less, new KeyValuePair<int, HashSet<string>>( 80, new HashSet<string>() { "<" }) },
			{ MathSymbol.LessEqual, new KeyValuePair<int, HashSet<string>>( 80, new HashSet<string>() { "<=" }) },
			{ MathSymbol.More, new KeyValuePair<int, HashSet<string>>( 80, new HashSet<string>() { ">" }) },
			{ MathSymbol.MoreEqual, new KeyValuePair<int, HashSet<string>>( 80, new HashSet<string>() { ">=" }) },
			{ MathSymbol.Equal, new KeyValuePair<int, HashSet<string>>( 70, new HashSet<string>() { "==" }) },
			{ MathSymbol.NotEqual, new KeyValuePair<int, HashSet<string>>( 70, new HashSet<string>()  { "!=" }) },
			{ MathSymbol.LogicAnd, new KeyValuePair<int, HashSet<string>>( 60, new HashSet<string>() { "&&", "and" }) },
			{ MathSymbol.LogicOr, new KeyValuePair<int, HashSet<string>>( 60, new HashSet<string>() { "||", "or" }) },
		};
		private static readonly Dictionary<DoubleSymbol, string> MAP_DOUBLE_SYMBOL = new Dictionary<DoubleSymbol, string>() {
			{ DoubleSymbol.AddAdd, "++" },
			{ DoubleSymbol.SubSub, "--" },
		};
		private static readonly HashSet<MathSymbol> SET_SELF_ASSIGN_SYMBOL = new HashSet<MathSymbol>() {
				MathSymbol.AssignAdd,
				MathSymbol.AssignDiv,
				MathSymbol.AssignSub,
				MathSymbol.AssignMul,
				MathSymbol.AssignMod,
		};
		private const string STRING_COMMENT_BLOCK_BEGIN_SIGN = "/*";
		private const string STRING_COMMENT_BLOCK_END_SIGN = "*/";
		private const string STRING_NULL_SIGN = "null";
		private const string STRING_ECHO_SIGN = "echo";
		private const string STRING_FOR_SIGN = "for";
		private const string STRING_FOREACH_SIGN = "foreach";
		private const string STRING_FOREACH_IN_SIGN = "in";
		private const string STRING_WHILE_SIGN = "while";
		private const string STRING_DO_SIGN = "do";
		private const string STRING_LOOP_SIGN = "loop";
		private const string STRING_TRY_SIGN = "try";
		private const string STRING_CATCH_SIGN = "catch";
		private const string STRING_FINALLY_SIGN = "finally";
		private const string STRING_BREAK_SIGN = "break";
		private const string STRING_CONTINUE_SIGN = "continue";
		private const string STRING_FUNCTION_SIGN = "function";
		private const string STRING_RETURN_SIGN = "return";
		private const string STRING_SET_SIGN = "set";
		private const string STRING_CONST_SIGN = "const";
		private const string STRING_NEW_SIGN = "new";
		private const string STRING_OBJECT_SIGN = "object";
		private const string STRING_ENUM_SIGN = "enum";
		private const string STRING_IMPORT_SIGN = "import";
		private const string STRING_EXPORT_SIGN = "export";

		private const char CHAR_NOT_SYMBOL = '!';
		private const char CHAR_LEFT_BRACKET = '(';
		private const char CHAR_RIGHT_BRACKET = ')';
		private const char CHAR_SPLIT_SYMBOL = ',';
		private const char CHAR_ARRAY_BEGIN = '[';
		private const char CHAR_ARRAY_END = ']';
		private const char CHAR_INSIDE_SYMBOL = '.';

		public static bool IsTextSpace(char ch) {
			return SET_TEXT_SPACE.Contains(ch);
		}
		public static bool IsTextNewLine(char ch) {
			return SET_TEXT_NEW_LINE.Contains(ch);
		}
		public static bool IsTextSpecialChar(char ch) {
			return (ch >= 0 && ch <= 47) || (ch >= 58 && ch <= 64) || (ch >= 91 && ch <= 94) || (ch == 96) || (ch >= 123 && ch <= 127);
		}
		public static bool IsTextNumber(char ch) {
			return ch >= '0' && ch <= '9';
		}
		public static bool IsGrammarStringSign(char ch) {
			return SET_STRING_SIGN.Contains(ch);
		}
		public static bool IsGrammarEndSign(char ch) {
			return SET_END_SIGN.Contains(ch);
		}
		public static bool IsSpecialSign(string value) {
			int pos = 0;
			int size = value.Length;
			do {
				if (MatchVariableDefine(value, size, 0, out pos)) {
					break;
				}
				if (MatchNull(value, size, 0, out pos)) {
					break;
				}
				bool bBoolValue = false;
				if (MatchBool(value, size, 0, out pos, out bBoolValue)) {
					break;
				}
				if (MatchEcho(value, size, 0, out pos)) {
					break;
				}
				if (MatchForeach(value, size, 0, out pos)) {
					break;
				}
				if (MatchFor(value, size, 0, out pos)) {
					break;
				}
				if (MatchWhile(value, size, 0, out pos)) {
					break;
				}
				if (MatchLoop(value, size, 0, out pos)) {
					break;
				}
				if (MatchBlockBegin(value, size, 0, out pos)) {
					break;
				}
				if (MatchBlockEnd(value, size, 0, out pos)) {
					break;
				}
				if (MatchTry(value, size, 0, out pos)) {
					break;
				}
				if (MatchCatch(value, size, 0, out pos)) {
					break;
				}
				if (MatchFinally(value, size, 0, out pos)) {
					break;
				}
				if (MatchBreak(value, size, 0, out pos)) {
					break;
				}
				if (MatchContinue(value, size, 0, out pos)) {
					break;
				}
				if (MatchDo(value, size, 0, out pos)) {
					break;
				}
				if (MatchConditionIf(value, size, 0, out pos)) {
					break;
				}
				if (MatchConditionElse(value, size, 0, out pos)) {
					break;
				}
				if (MatchReturn(value, size, 0, out pos)) {
					break;
				}
				if (MatchNew(value, size, 0, out pos)) {
					break;
				}
				if (MatchAssign(value, size, 0, out pos)) {
					break;
				}
				if (MatchExtends(value, size, 0, out pos)) {
					break;
				}
				if (MatchObject(value, size, 0, out pos)) {
					break;
				}
				if (MatchEnum(value, size, 0, out pos)) {
					break;
				}
				if (MatchImport(value, size, 0, out pos)) {
					break;
				}
				if (MatchExport(value, size, 0, out pos)) {
					break;
				}
				// temp todo...

				return false;
			} while (false);

			return pos >= size || IsTextSpecialChar(value[pos]);
		}
		public static bool IsLeftBrcket(char ch) {
			return ch == CHAR_LEFT_BRACKET;
		}
		public static bool IsRightBrcket(char ch) {
			return ch == CHAR_RIGHT_BRACKET;
		}
		public static bool IsVariableSelfAssignSymbol(MathSymbol value) {
			return SET_SELF_ASSIGN_SYMBOL.Contains(value);
		}
		public static bool IsWordValidSymbol(char ch) {
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
		public static bool SearchNextInside(string src, int size, int pos) {
				for (var i = pos; i < size; ++i) {
				if (MatchInsideSymbol(src, size, i, out i)) {
					return true;
				}
				char ch = src[i];
				if (!IsWordValidSymbol(ch)) {
					MathSymbol symbol;
					if (!MatchMathSymbol(src, size, i, out i, out symbol)) {
						return false;
					}
				}
			}
			return false;
		}
		public static bool SearchNextArray(string src, int size, int pos) {
			for (var i = pos; i < size; ++i) {
				if (MatchArrayBegin(src, size, i, out i)) {
					return true;
				}
				char ch = src[i];
				if (!IsWordValidSymbol(ch)) {
					MathSymbol symbol;
					if (!MatchMathSymbol(src, size, i, out i, out symbol)) {
						return false;
					}
				}
			}
			return false;
		}

		public static int GetMathSymbolLevel(MathSymbol value) {
			KeyValuePair<int, HashSet<string>> ret;
			if (MAP_SET_MATH_SYMBOL.TryGetValue(value, out ret)) {
				return ret.Key;
			}
			return 0;
		}
		
		public static bool MatchExtends(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			foreach (var sign in SET_EXTENDS_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			return false;
		}
		public static bool MatchImport(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_IMPORT_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchExport(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_EXPORT_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchEnum(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_ENUM_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchObject(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_OBJECT_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchInsideSymbol(string src, int size, int pos, out int nextPos) {
			return MatchSign(CHAR_INSIDE_SYMBOL, src, size, pos, out nextPos);
		}
		public static bool MatchNew(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_NEW_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchObjectBegin(string src, int size, int pos, out int nextPos) {
			return MatchBlockBegin(src, size, pos, out nextPos);
		}
		public static bool MatchObjectEnd(string src, int size, int pos, out int nextPos) {
			return MatchBlockEnd(src, size, pos, out nextPos);
		}
		public static bool MatchArrayBegin(string src, int size, int pos, out int nextPos) {
			return MatchSign(CHAR_ARRAY_BEGIN, src, size, pos, out nextPos);
		}
		public static bool MatchArrayEnd(string src, int size, int pos, out int nextPos) {
			return MatchSign(CHAR_ARRAY_END, src, size, pos, out nextPos);
		}
		public static bool MatchDoubleSymbol(string src, int size, int pos, out int nextPos, out DoubleSymbol symbol) {
			foreach (var pair in MAP_DOUBLE_SYMBOL) {
				if (MatchSign(pair.Value, src, size, pos, out nextPos)) {
					symbol = pair.Key;
					return true;
				}
			}
			symbol = DoubleSymbol.AddAdd;
			nextPos = pos;
			return false;
		}
		public static bool MatchNotSymbol(string src, int size, int pos, out int nextPos) {
			return MatchSign(CHAR_NOT_SYMBOL, src, size, pos, out nextPos);
		}
		public static bool MatchConst(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_CONST_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchReturn(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_RETURN_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchSplitSymbol(string src, int size, int pos, out int nextPos) {
			return MatchSign(CHAR_SPLIT_SYMBOL, src, size, pos, out nextPos);
		}
		public static bool MatchFunction(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_FUNCTION_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchBreak(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_BREAK_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchContinue(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_CONTINUE_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchTry(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_TRY_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchCatch(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_CATCH_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchFinally(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_FINALLY_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchEcho(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_ECHO_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchBlockBegin(string src, int size, int pos, out int nextPos) {
			foreach (var sign in SET_BLOCK_BEGIN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			nextPos = pos;
			return false;
		}
		public static bool MatchBlockEnd(string src, int size, int pos, out int nextPos) {
			foreach (var sign in SET_BLOCK_END) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			nextPos = pos;
			return false;
		}
		public static bool MatchConditionIf(string src, int size, int pos, out int nextPos) {
			foreach (var sign in SET_CONDITION_IF_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			nextPos = pos;
			return false;
		}
		public static bool MatchConditionElse(string src, int size, int pos, out int nextPos) {
			foreach (var sign in SET_CONDITION_ELSE_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			nextPos = pos;
			return false;
		}
		public static bool MatchFor(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_FOR_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchForeach(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_FOREACH_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchForeachIn(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_FOREACH_IN_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchWhile(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_WHILE_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchDo(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_DO_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchLoop(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_LOOP_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchLeftBrcket(string src, int size, int pos, out int nextPos) {
			return MatchSign(CHAR_LEFT_BRACKET, src, size, pos, out nextPos);
		}
		public static bool MatchRightBrcket(string src, int size, int pos, out int nextPos) {
			return MatchSign(CHAR_RIGHT_BRACKET, src, size, pos, out nextPos);
		}
		public static bool MatchMathSymbol(string src, int size, int pos, out int nextPos, out MathSymbol symbol) {
			foreach (var pair in MAP_SET_MATH_SYMBOL) {
				var setPair = pair.Value;
				var signSet = setPair.Value;
				foreach (var sign in signSet) {
					if (MatchSign(sign, src, size, pos, out nextPos)) {
						symbol = pair.Key;
						return true;
					}
				}
			}
			nextPos = pos;
			symbol = MathSymbol.None;
			return false;
		}
		public static bool MatchNull(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_NULL_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchBool(string src, int size, int pos, out int nextPos, out bool value) {
			foreach (var sign in SET_BOOL_TRUE_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					value = true;
					return true;
				}
			}
			foreach (var sign in SET_BOOL_FALSE_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					value = false;
					return true;
				}
			}
			nextPos = pos;
			value = false;
			return false;
		}
		public static bool MatchNumber(string src, int size, int pos, out int nextPos, out double number) {
			nextPos = pos;
			number = 0;
			if (pos >= size) {
				return false;
			}
			char ch = src[pos];
			bool bSub = (ch == '-');
			bool bPoint = (ch == '.');

			if (!IsTextNumber(ch) && !bSub && !bPoint) {
				return false;
			}
			var beginPos = pos;
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

			int checkSize = 1;
			int p = 0;
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
			var tempSize = pos - beginPos;
			if (tempSize < checkSize) {
				return false;
			}
			var tempStr = src.Substring(beginPos, tempSize);
			if (bPoint) {
				tempStr.Insert(p, "0");
			}
			if (!double.TryParse(tempStr, out number)) {
				return false;
			}
			nextPos = pos;
			return true;
		}
		public static bool MatchName(string src, int size, int pos, out int nextPos, out string name) {
			nextPos = pos;
			name = "";
			if (pos >= size) {
				return false;
			}
			char ch = src[pos];
			if (IsTextNumber(ch) || IsTextSpecialChar(ch) || IsTextSpace(ch)) {
				return false;
			}
			var beginPos = pos;
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
			var tempSize = pos - beginPos;
			name = src.Substring(beginPos, tempSize);
			if (IsSpecialSign(name)) {
				return false;
			}
			nextPos = pos;
			return true;
		}
		public static bool MatchAssign(string src, int size, int pos, out int nextPos) {
			foreach(var sign in SET_ASSIGN_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			nextPos = pos;
			return false;
		}
		public static bool MatchComment(string src, int size, int pos, out int nextPos) {
			foreach(var sign in SET_COMMENT_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			nextPos = pos;
			return false;
		}
		public static bool MatchCommentBlockBegin(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_COMMENT_BLOCK_BEGIN_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchCommentBlockEnd(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_COMMENT_BLOCK_END_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchVariableDefine(string src, int size, int pos, out int nextPos) {
			foreach(var sign in SET_VARIABLE_DEFINE_SIGN) {
				if (MatchSign(sign, src, size, pos, out nextPos)) {
					return true;
				}
			}
			nextPos = pos;
			return false;
		}
		public static bool MatchVariableSet(string src, int size, int pos, out int nextPos) {
			return MatchSign(STRING_SET_SIGN, src, size, pos, out nextPos);
		}
		public static bool MatchSign(string sign, string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			var signSize = sign.Length;
			if (pos + signSize > size) {
				return false;
			}
			for (int i = 0; i < signSize; ++i) {
				if (sign[i] != src[pos + i]) {
					return false;
				}
			}
			nextPos = pos + signSize;
			return true;
		}
		public static bool MatchSign(char sign, string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (pos >= size) {
				return false;
			}
			if (src[pos] == sign) {
				nextPos = pos + 1;
				return true;
			}
			return false;
		}
		public static bool MatchPair(string signLeft, string signRight, string src, int size, int pos, out int nextPos, out string result) {
			nextPos = pos;
			result = "";
			if (!MatchSign(signLeft, src, size, pos, out pos)) {
				return false;
			}
			bool bSame = signLeft == signRight;
			var beginPos = pos;
			int count = 0;
			while (pos < size) {
				if (!bSame && MatchSign(signLeft, src, size, pos, out pos)) {
					++count;
					continue;
				}
				if (MatchSign(signRight, src, size, pos, out pos)) {
					if (count > 0) {
						--count;
						continue;
					}
					var tempSize = pos - signRight.Length - beginPos;
					result = src.Substring(beginPos, tempSize);
					nextPos = pos;
					return true;
				}
				++pos;
			}
			return false;
		}
		public static bool MatchPair(char signLeft, char signRight, string src, int size, int pos, out int nextPos, out string result) {
			nextPos = pos;
			result = "";
			if (src[pos] != signLeft) {
				return false;
			}
			++pos;
			bool bSame = signLeft == signRight;
			var beginPos = pos;
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
						var tempSize = pos - beginPos;
						result = src.Substring(beginPos, tempSize);
						nextPos = pos + 1;
						return true;
					}
				} while (false);

				bIgnore = (ch == '\\' ? !bIgnore : false);
				++pos;
			}
			return false;
		}
	}
} // namespace peak.interpreter