/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	public class ParseData {
		public bool bSuccess = false;
		public List<Sentence> sentenceList = new List<Sentence>();
	};

	public class ParseTool {
		private delegate Sentence SentenceParseFunc(string src, int size, int pos, out int nextPos);
		private delegate SentenceExpression SentenceExpressionParseFunc(string src, int size, int pos, out int nextPos);

		private static List<SentenceParseFunc> _sentenceParseList = new List<SentenceParseFunc>() {
			_ParseVariableAssign,
			_ParseVariableDefine,
			_ParseVariableSet,
			_ParseFunctionDefine,
			_ParseObjectDefine,
			_ParseEnumDefine,
			_ParseCondition,
			_ParseLoop,
			_ParseForeach,
			_ParseFor,
			_ParseWhile,
			_ParseDoWhile,
			_ParseBlock,
			_ParseEcho,
			_ParseLoopControl,
			_ParseReturn,
			_ParseImport,
			_ParseExport,
			_ParseTryCatchFinally,
			_ParseExpressionToEnd,
			_ParseFunctioCall,
		};
		private static List<SentenceExpressionParseFunc> _sentenceValueParseList = new List<SentenceExpressionParseFunc>() {
			_ParseString,
			_ParseNumber,
			_ParseInside,
			_ParseArrayItem,
			_ParseArray,
			_ParseDoubleExpression,
			_ParseNotExpression,
			_ParseFunctioCall,
			_ParseVariableName,
			_ParseNew,
			_ParseBool,
			_ParseNull,
		};
		private static List<SentenceExpressionParseFunc> _sentenceVariableParseList = new List<SentenceExpressionParseFunc>() {
			_ParseInside,
			_ParseArrayItem,
			_ParseVariableName,
		};

		private static List<SentenceExpressionParseFunc> __sentenceArrayItemParseList = new List<SentenceExpressionParseFunc>() {
			_ParseArray,
			_ParseFunctioCall,
			_ParseVariableName,
		};
		private static List<SentenceExpressionParseFunc> __sentenceInsideHeaderParseList = new List<SentenceExpressionParseFunc>() {
			_ParseNew,
			_ParseFunctioCall,
			_ParseArrayItem,
			_ParseVariableName,
		};
		private static List<SentenceExpressionParseFunc> __sentenceInsideAppendParseList = new List<SentenceExpressionParseFunc>() {
			_ParseArrayItem,
			_ParseFunctioCall,
			_ParseVariableName,
		};

		public static ParseData Load(string src) {
			var retData = new ParseData();
			retData.bSuccess = true;
			int pos = 0;
			var size = src.Length;
			while (pos < size) {
				JumpEnd(src, size, pos, out pos);
				if (pos >= size || src[pos] == '\0') {
					break;
				}
				var parseSentence = ParseSentence(src, size, pos, out pos);
				if (!parseSentence) {
					retData.bSuccess = false;
					ErrorLogger.LogParseError(src, size, pos);
					break;
				}
				retData.sentenceList.Add(parseSentence);
			}
			return retData;
		}

		private static bool Jump(string src, int size, int pos, out int nextPos) {
			bool bJump = false;
			bool bRet = false;
			do {
				bJump = false;
				bJump |= JumpTextSpace(src, size, pos, out pos);
				bJump |= JumpComment(src, size, pos, out pos);
				bJump |= JumpCommentBlock(src, size, pos, out pos);
				bRet |= bJump;
			} while (bJump);
			nextPos = pos;
			return bRet;
		}
		private static bool JumpEnd(string src, int size, int pos, out int nextPos) {
			bool bJump = false;
			bool bRet = false;
			do {
				bJump = false;
				bool bEnd = JumpTextSpaceAndEnd(src, size, pos, out pos);
				bJump |= bEnd;
				bJump |= JumpComment(src, size, pos, out pos);
				bJump |= JumpCommentBlock(src, size, pos, out pos);
				bRet |= bEnd;
			} while (bJump);
			nextPos = pos;
			if (Grammar.IsGrammarEndSign('\n')) {
				bRet |= (pos >= size);
			}
			return bRet;
		}

		private static bool JumpTextSpace(string src, int size, int pos, out int nextPos) {
			var beginPos = pos;
			while (pos < size) {
				if (!Grammar.IsTextSpace(src[pos])) {
					break;
				}
				++pos;
			}
			nextPos = pos;
			return pos != beginPos;
		}
		private static bool JumpTextSpaceAndEnd(string src, int size, int pos, out int nextPos) {
			bool bRet = false;
			while (pos < size) {
				char ch = src[pos];
				bool bEnd = Grammar.IsGrammarEndSign(ch);
				if (!bEnd && !Grammar.IsTextSpace(ch)) {
					break;
				}
				bRet |= bEnd;
				++pos;
			}
			nextPos = pos;
			return bRet;
		}
		private static bool JumpComment(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (Grammar.MatchComment(src, size, pos, out pos)) {
				while (pos <= size) {
					if ((pos == size) || Grammar.IsTextNewLine(src[pos])) {
						nextPos = pos;
						return true;
					}
					++pos;
				}
			}
			return false;
		}

		private static bool JumpCommentBlock(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			int findBegin = 0;
			if (Grammar.MatchCommentBlockBegin(src, size, pos, out pos)) {
				while (pos < size) {
					if (Grammar.MatchCommentBlockBegin(src, size, pos, out pos)) {
						++findBegin;
						continue;
					}
					if (Grammar.MatchCommentBlockEnd(src, size, pos, out pos)) {
						if (findBegin == 0) {
							nextPos = pos;
							return true;
						}
						--findBegin;
						continue;
					}
					++pos;
				}
			}
			return false;
		}

		private static Sentence ParseSentence(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			foreach (var func in _sentenceParseList) {
				var parseData = func.Invoke(src, size, pos, out nextPos);
				if (parseData) {
					return parseData;
				}
			}
			return null;
		}

		private static SentenceExpression _ParseExpression(string src, int size, int pos, out int nextPos) {
			return _ParseExpressionMath(src, size, pos, out nextPos);
		}

		private static SentenceExpression _ParseExpressionValue(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			foreach (var func in _sentenceValueParseList) {
				var value = func.Invoke(src, size, pos, out nextPos);
				if (value) {
					return value;
				}
			}
			return null;
		}

		private static SentenceExpression _ParseVariable(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			foreach (var func in _sentenceVariableParseList) {
				var value = func.Invoke(src, size, pos, out nextPos);
				if (value) {
					return value;
				}
			}
			return null;
		}

		private static SentenceExpression __ParseExpressionValueForArrayValue(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			foreach (var func in __sentenceArrayItemParseList) {
				var value = func.Invoke(src, size, pos, out nextPos);
				if (value) {
					return value;
				}
			}
			return null;
		}

		private static SentenceExpression __ParseExpressionInsideHeader(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			foreach (var func in __sentenceInsideHeaderParseList) {
				var value = func.Invoke(src, size, pos, out nextPos);
				if (value) {
					return value;
				}
			}
			return null;
		}

		private static SentenceExpression __ParseExpressionInsideAppend(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			foreach (var func in __sentenceInsideAppendParseList) {
				var value = func.Invoke(src, size, pos, out nextPos);
				if (value) {
					return value;
				}
			}
			return null;
		}

		private static Sentence _ParseImport(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchImport(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);

			if (pos >= size) {
				return null;
			}
			char sign = src[pos];
			if (!Grammar.IsGrammarStringSign(sign)) {
				return null;
			}
			string moduleName;
			if (!Grammar.MatchPair(sign, sign, src, size, pos, out pos, out moduleName)) {
				return null;
			}

			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return new SentenceImport(moduleName);
		}
		private static Sentence _ParseExport(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchExport(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);

			if (pos >= size) {
				return null;
			}
			char sign = src[pos];
			if (!Grammar.IsGrammarStringSign(sign)) {
				return null;
			}
			string moduleName;
			if (!Grammar.MatchPair(sign, sign, src, size, pos, out pos, out moduleName)) {
				return null;
			}

			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return new SentenceExport(moduleName);
		}

		private static Sentence _ParseReturn(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchReturn(src, size, pos, out pos)) {
				return null;
			}
			if (!Jump(src, size, pos, out pos)) {
				return null;
			}

			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}

			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}

			nextPos = pos;
			return new SentenceReturn(expression);
		}
		private static Sentence _ParseFunctionDefine(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (Grammar.MatchFunction(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
			}
			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			if (!Grammar.MatchLeftBrcket(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			List<string> params_ = new List<string>();
			string paramName;
			while (Grammar.MatchName(src, size, pos, out pos, out paramName)) {
				params_.Add(paramName);
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchSplitSymbol(src, size, pos, out pos)) {
					break;
				}
				Jump(src, size, pos, out pos);
			}
			if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			var contentSentence = _ParseBlock(src, size, pos, out pos);
			if (!contentSentence) {
				return null;
			}
			nextPos = pos;
			return new SentenceFunctionDefine(name, params_, contentSentence);
		}

		private static Sentence _ParseEnumDefine(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchEnum(src, size, pos, out pos)) {
				return null;
			}
			if (!Jump(src, size, pos, out pos)) {
				return null;
			}
			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			if (!Grammar.MatchObjectBegin(src, size, pos, out pos)) {
				return null;
			}
			var checkNameSet = new HashSet<string>();
			var checkValueSet = new HashSet<double>();
			var valueList = new LinkedList<KeyValuePair<string, ValueNumber>>();
			double indexValue = 0;
			while (true) {
				if (pos >= size) {
					return null;
				}
				Jump(src, size, pos, out pos);
				if (Grammar.MatchObjectEnd(src, size, pos, out pos)) {
					break;
				}
				string valueName = "";
				if (!Grammar.MatchName(src, size, pos, out pos, out valueName)) {
					return null;
				}
				Jump(src, size, pos, out pos);
				if (Grammar.MatchAssign(src, size, pos, out pos)) {
					Jump(src, size, pos, out pos);
					if (!Grammar.MatchNumber(src, size, pos, out pos, out indexValue)) {
						return null;
					}
					Jump(src, size, pos, out pos);
				}

				var valueNumber = new ValueNumber(indexValue);
				if (!ValueTool.IsInteger(valueNumber)) {
					return null;
				}

				if (checkNameSet.Contains(valueName)) {
					return null;
				}
				if (checkValueSet.Contains(indexValue)) {
					return null;
				}
				checkNameSet.Add(valueName);
				checkValueSet.Add(indexValue);
				valueList.AddLast(new KeyValuePair<string, ValueNumber>(valueName, valueNumber));

				Jump(src, size, pos, out pos);
				if (!Grammar.MatchSplitSymbol(src, size, pos, out pos)) {
					if (Grammar.MatchObjectEnd(src, size, pos, out pos)) {
						break;
					}
					return null;
				}

				indexValue += 1;
			}
			nextPos = pos;
			return new SentenceEnumDefine(name, valueList);
		}

		private static Sentence _ParseObjectDefine(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (Grammar.MatchObject(src, size, pos, out pos)) {
				if (!Jump(src, size, pos, out pos)) {
					return null;
				}
			}
			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			string parentName = "";
			if (Grammar.MatchExtends(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchName(src, size, pos, out pos, out parentName)) {
					return null;
				}
				Jump(src, size, pos, out pos);
			}
			if (!Grammar.MatchObjectBegin(src, size, pos, out pos)) {
				return null;
			}

			var sentenceList = new LinkedList<Sentence>();
			while (true) {
				if (pos >= size) {
					return null;
				}
				Jump(src, size, pos, out pos);
				if (Grammar.MatchObjectEnd(src, size, pos, out pos)) {
					break;
				}
				var sentence = ParseSentence(src, size, pos, out pos);
				if (!sentence) {
					return null;
				}
				sentenceList.AddLast(sentence);
			}
			nextPos = pos;
			return new SentenceObjectDefine(name, parentName, sentenceList);
		}

		private static Sentence _ParseVariableDefine(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			bool bConst = Grammar.MatchConst(src, size, pos, out pos);
			if (bConst && !Jump(src, size, pos, out pos)) {
				return null;
			}
			if (Grammar.MatchVariableDefine(src, size, pos, out pos)) {
				if (!Jump(src, size, pos, out pos)) {
					return null;
				}
			} else {
				if (!bConst) {
					return null;
				}
			}

			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}

			var beginPos = pos;
			Jump(src, size, pos, out pos);

			var attribute = bConst ? VariableAttribute.Const : VariableAttribute.None;

			if (!Grammar.MatchAssign(src, size, pos, out pos)) {
				pos = beginPos;
				if (bConst) {
					return null;
				}
				if (JumpEnd(src, size, pos, out pos)) {
					nextPos = pos;
					return new SentenceVariableDefine(name, attribute, null);
				}
				return null;
			}

			Jump(src, size, pos, out pos);
			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}
			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}

			nextPos = pos;
			return new SentenceVariableDefine(name, attribute, expression);
		}

		private static Sentence _ParseVariableAssign(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			var variableExpression = _ParseVariable(src, size, pos, out pos);
			if (!variableExpression) {
				return null;
			}

			Jump(src, size, pos, out pos);
			if (!Grammar.MatchAssign(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}
			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return new SentenceVariableAssign(variableExpression, expression);
		}

		private static Sentence _ParseVariableSet(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchVariableSet(src, size, pos, out pos)) {
				return null;
			}
			if (!Jump(src, size, pos, out pos)) {
				return null;
			}

			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}

			var beginPos = pos;
			Jump(src, size, pos, out pos);

			if (!Grammar.MatchAssign(src, size, pos, out pos)) {
				pos = beginPos;
				if (!JumpEnd(src, size, pos, out pos)) {
					return null;
				}
				nextPos = pos;
				return new SentenceVariableSet(name, null);
			}

			Jump(src, size, pos, out pos);
			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}
			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}

			nextPos = pos;
			return new SentenceVariableSet(name, expression);
		}

		private static Sentence _ParseExpressionToEnd(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}
			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return expression;
		}

		private static Sentence _ParseCondition(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchConditionIf(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			bool bBracket = Grammar.MatchLeftBrcket(src, size, pos, out pos);
			if (bBracket) {
				Jump(src, size, pos, out pos);
			}
			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}
			if (bBracket) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					return null;
				}
			}
			Jump(src, size, pos, out pos);
			var sentence = ParseSentence(src, size, pos, out pos);
			if (!sentence) {
				return null;
			}

			Sentence sentenceElse = null;

			Jump(src, size, pos, out pos);
			if (Grammar.MatchConditionElse(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
				sentenceElse = _ParseCondition(src, size, pos, out pos);
				if (!sentenceElse) {
					sentenceElse = ParseSentence(src, size, pos, out pos);
					if (!sentenceElse) {
						return null;
					}
				}
			}

			nextPos = pos;
			return new SentenceCondition(expression, sentence, sentenceElse);
		}

		private static Sentence _ParseLoop(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchLoop(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);

			bool bBracket = Grammar.MatchLeftBrcket(src, size, pos, out pos);
			if (bBracket) {
				Jump(src, size, pos, out pos);
			}

			string name;
			var savePos = pos;
			bool bMatchName = Grammar.MatchName(src, size, pos, out pos, out name);
			if (bMatchName) {
				Jump(src, size, pos, out pos);
			}

			if (Grammar.MatchForeachIn(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
			} else {
				if (bMatchName) {
					pos = savePos;
					name = "";
				}
			}

			var condition = _ParseExpression(src, size, pos, out pos);
			if (!condition) {
				return null;
			}

			if (bBracket) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					return null;
				}
			}

			Jump(src, size, pos, out pos);
			var sentence = ParseSentence(src, size, pos, out pos);
			if (!sentence) {
				return null;
			}
			nextPos = pos;
			return (new SentenceLoop(name, condition, sentence));
		}

		private static Sentence _ParseFor(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchFor(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			bool bBracket = Grammar.MatchLeftBrcket(src, size, pos, out pos);
			if (bBracket) {
				Jump(src, size, pos, out pos);
			}

			var sentence0 = ParseSentence(src, size, pos, out pos);
			if (!sentence0) {
				sentence0 = _ParseExpression(src, size, pos, out pos);
				Jump(src, size, pos, out pos);
				if ((pos >= size) || !Grammar.IsGrammarEndSign(src[pos])) {
					return null;
				}
				++pos;
			}
			var expression0 = _ParseExpression(src, size, pos, out pos); {
				Jump(src, size, pos, out pos);
				if ((pos >= size) || !Grammar.IsGrammarEndSign(src[pos])) {
					return null;
				}
				++pos;
			}
			var expression1 = _ParseExpression(src, size, pos, out pos);
			if (bBracket) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					return null;
				}
			}
			Jump(src, size, pos, out pos);
			var content = ParseSentence(src, size, pos, out pos);
			if (!content && !JumpEnd(src, size, pos, out pos)) {
				return null;
			}

			nextPos = pos;
			return (new SentenceFor(sentence0, expression0, expression1, content));
		}

		private static Sentence _ParseForeach(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchForeach(src, size, pos, out pos)) {
				if (!Grammar.MatchFor(src, size, pos, out pos)) {
					return null;
				}
			}
			Jump(src, size, pos, out pos);

			bool bBracket = Grammar.MatchLeftBrcket(src, size, pos, out pos);
			if (bBracket) {
				Jump(src, size, pos, out pos);
			}

			if (Grammar.MatchVariableDefine(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
			}
			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			if (!Grammar.MatchForeachIn(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}

			if (bBracket) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					return null;
				}
			}
			Jump(src, size, pos, out pos);
			var sentence = ParseSentence(src, size, pos, out pos);
			if (!sentence) {
				return null;
			}
			nextPos = pos;
			return (new SentenceForeach(name, expression, sentence));
		}

		private static Sentence _ParseWhile(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchWhile(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			bool bBracket = Grammar.MatchLeftBrcket(src, size, pos, out pos);
			if (bBracket) {
				Jump(src, size, pos, out pos);
			}
			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}
			if (bBracket) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					return null;
				}
			}
			Jump(src, size, pos, out pos);
			var sentence = ParseSentence(src, size, pos, out pos);
			if (!sentence && !JumpEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return (new SentenceWhile(expression, sentence));
		}

		private static Sentence _ParseDoWhile(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchDo(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			var sentence = ParseSentence(src, size, pos, out pos);
			if (!sentence) {
				return null;
			}

			Jump(src, size, pos, out pos);
			if (!Grammar.MatchWhile(src, size, pos, out pos)) {
				return null;
			}

			Jump(src, size, pos, out pos);
			bool bBracket = Grammar.MatchLeftBrcket(src, size, pos, out pos);
			if (bBracket) {
				Jump(src, size, pos, out pos);
			}

			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}
			if (bBracket) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					return null;
				}
			}
			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return (new SentenceDoWhile(expression, sentence));
		}

		private static Sentence _ParseBlock(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchBlockBegin(src, size, pos, out pos)) {
				return null;
			}

			var sentenceBlock = (new SentenceBlock());
			while (true) {
				if (pos >= size) {
					return null;
				}
				JumpEnd(src, size, pos, out pos);
				if (Grammar.MatchBlockEnd(src, size, pos, out pos)) {
					break;
				}

				var parseSentence = ParseSentence(src, size, pos, out pos);
				if (!parseSentence) {
					return null;
				}
				sentenceBlock.Push(parseSentence);
			}

			nextPos = pos;
			return sentenceBlock;
		}

		private static Sentence _ParseEcho(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchEcho(src, size, pos, out pos)) {
				return null;
			}
			if (!Jump(src, size, pos, out pos)) {
				return null;
			}

			var expression = _ParseExpression(src, size, pos, out pos);
			if (!expression) {
				return null;
			}

			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}

			nextPos = pos;
			return (new SentenceEcho(expression));
		}

		private static Sentence _ParseTryCatchFinally(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchTry(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			var sentence = ParseSentence(src, size, pos, out pos);
			if (!sentence) {
				return null;
			}
			Jump(src, size, pos, out pos);

			Sentence catchSentence = null;
			if (Grammar.MatchCatch(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
				catchSentence = ParseSentence(src, size, pos, out pos);
				if (!catchSentence) {
					return null;
				}
				Jump(src, size, pos, out pos);
			}
			Sentence finallySentence = null;
			if (Grammar.MatchFinally(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
				finallySentence = ParseSentence(src, size, pos, out pos);
				if (!finallySentence) {
					return null;
				}
			}
			nextPos = pos;
			return (new SentenceTryCatchFinally(sentence, catchSentence, finallySentence));
		}

		private static Sentence _ParseLoopControl(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			Sentence sentence = null;
			do {
				if (Grammar.MatchContinue(src, size, pos, out pos)) {
					sentence = (new SentenceLoopControlContinue());
					break;
				}
				if (Grammar.MatchBreak(src, size, pos, out pos)) {
					sentence = (new SentenceLoopControlBreak());
					break;
				}
				return null;
			} while (false);
			if (!JumpEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return sentence;
		}

		private static SentenceExpression _ParseString(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.IsGrammarStringSign(src[pos])) {
				return null;
			}
			char sign = src[pos];
			string temp;
			if (Grammar.MatchPair(sign, sign, src, size, pos, out pos, out temp)) {
				nextPos = pos;
				return (new SentenceExpression((new ValueString(temp))));
			}
			return null;
		}

		private static SentenceExpression _ParseNumber(string src, int size, int pos, out int nextPos) {
			double temp = 0;
			if (Grammar.MatchNumber(src, size, pos, out nextPos, out temp)) {
				return (new SentenceExpression((new ValueNumber(temp))));
			}
			return null;
		}

		private static SentenceExpression _ParseBool(string src, int size, int pos, out int nextPos) {
			bool temp = false;
			if (Grammar.MatchBool(src, size, pos, out nextPos, out temp)) {
				return (new SentenceExpression((new ValueBool(temp))));
			}
			return null;
		}

		private static SentenceExpression _ParseNull(string src, int size, int pos, out int nextPos) {
			if (Grammar.MatchNull(src, size, pos, out nextPos)) {
				return (new SentenceExpression((new ValueNull())));
			}
			return null;
		}
		private static SentenceExpression _ParseArray(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchArrayBegin(src, size, pos, out pos)) {
				return null;
			}
			List<SentenceExpression> temp = new List<SentenceExpression>();
			while (true) {
				Jump(src, size, pos, out pos);
				var expression = _ParseExpression(src, size, pos, out pos);
				if (!expression) {
					break;
				}
				temp.Add(expression);
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchSplitSymbol(src, size, pos, out pos)) {
					break;
				}
			}
			if (!Grammar.MatchArrayEnd(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return (new SentenceExpressionValueArray(temp));
		}

		private static SentenceExpression _ParseArrayItem(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.SearchNextArray(src, size, pos)) {
				return null;
			}
			var valueExpression = __ParseExpressionValueForArrayValue(src, size, pos, out pos);
			if (!valueExpression) {
				return null;
			}
			Jump(src, size, pos, out pos);
			if (!Grammar.MatchArrayBegin(src, size, pos, out pos)) {
				return null;
			}
			List<SentenceExpression> indexExpressionVec = new List<SentenceExpression>();
			while (true) {
				Jump(src, size, pos, out pos);
				var indexExpression = _ParseExpression(src, size, pos, out pos);
				if (!indexExpression) {
					return null;
				}
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchArrayEnd(src, size, pos, out pos)) {
					return null;
				}
				indexExpressionVec.Add(indexExpression);

				var savePos = pos;
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchArrayBegin(src, size, pos, out pos)) {
					pos = savePos;
					break;
				}
			}
			if (indexExpressionVec.Count == 0) {
				return null;
			}
			nextPos = pos;

			var analysis = new ExpressionVariableAnalysisArrayItem(valueExpression, indexExpressionVec);
			return (new SentenceExpressionVariable(analysis));
		}

		private static SentenceExpression _ParseVariableName(string src, int size, int pos, out int nextPos) {
			string name;
			if (Grammar.MatchName(src, size, pos, out nextPos, out name)) {
				var analysis = new ExpressionVariableAnalysisName(name);
				return (new SentenceExpressionVariable(analysis));
			}
			return null;
		}

		private static SentenceExpression _ParseFunctioCall(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			if (!Grammar.MatchLeftBrcket(src, size, pos, out pos)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			List<SentenceExpression> args = new List<SentenceExpression>();
			while (true) {
				var argExpression = _ParseExpression(src, size, pos, out pos);
				if (!argExpression) {
					break;
				}
				args.Add(argExpression);
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchSplitSymbol(src, size, pos, out pos)) {
					break;
				}
				Jump(src, size, pos, out pos);
			}
			if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
				return null;
			}
			nextPos = pos;
			return (new SentenceExpressionFunctionCall(name, args));
		}

		private static SentenceExpression _ParseDoubleExpression(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			DoubleSymbol symbol;
			bool bDouble = Grammar.MatchDoubleSymbol(src, size, pos, out pos, out symbol);
			bool bLast = !bDouble;
			var variableSentence = _ParseVariable(src, size, pos, out pos);
			if (!variableSentence) {
				return null;
			}
			if (!bDouble && !Grammar.MatchDoubleSymbol(src, size, pos, out pos, out symbol)) {
				return null;
			}
			var calculate = _GetCalculate(symbol);
			if (calculate == null) {
				return null;
			}
			nextPos = pos;
			return (new SentenceExpressionDouble(variableSentence, calculate, bLast));
		}

		private static SentenceExpression _ParseNotExpression(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchNotSymbol(src, size, pos, out pos)) {
				return null;
			}
			var expression = _ParseExpressionValue(src, size, pos, out pos);
			if (!expression) {
				if (!Grammar.MatchLeftBrcket(src, size, pos, out pos)) {
					return null;
				}
				expression = _ParseExpressionMathBracket(src, size, pos, out pos, true);
				if (!expression) {
					return null;
				}
			}
			nextPos = pos;
			return (new SentenceExpressionNot(expression));
		}

		private static SentenceExpression _ParseNew(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.MatchNew(src, size, pos, out pos)) {
				return null;
			}
			if (!Jump(src, size, pos, out pos)) {
				return null;
			}
			string name;
			if (!Grammar.MatchName(src, size, pos, out pos, out name)) {
				return null;
			}
			Jump(src, size, pos, out pos);
			if (Grammar.MatchLeftBrcket(src, size, pos, out pos)) {
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					return null;
				}
			}
			nextPos = pos;
			return (new SentenceExpressionNew(name));
		}

		private static SentenceExpression _ParseInside(string src, int size, int pos, out int nextPos) {
			nextPos = pos;
			if (!Grammar.SearchNextInside(src, size, pos)) {
				return null;
			}
			var header = __ParseExpressionInsideHeader(src, size, pos, out pos);
			if (!header) {
				return null;
			}
			Jump(src, size, pos, out pos);
			if (!Grammar.MatchInsideSymbol(src, size, pos, out pos)) {
				return null;
			}
			List<SentenceExpression> insides = new List<SentenceExpression>();
			bool bTailCall = false;
			while (true) {
				Jump(src, size, pos, out pos);
				var append = __ParseExpressionInsideAppend(src, size, pos, out pos);
				if (!append) {
					return null;
				}
				insides.Add(append);

				var savePos = pos;
				Jump(src, size, pos, out pos);
				if (!Grammar.MatchInsideSymbol(src, size, pos, out pos)) {
					bTailCall = (append.GetExpressionType() == ExpressionType.Function);
					pos = savePos;
					break;
				}
			}
			if (insides.Count == 0) {
				return null;
			}
			nextPos = pos;
			if (bTailCall) {
				return (new SentenceExpressionInside(header, insides));
			}
			var analysis = (new ExpressionVariableAnalysisInside(header, insides));
			return (new SentenceExpressionVariable(analysis));
		}

		private static SentenceExpression _ParseExpressionMath(string src, int size, int pos, out int nextPos) {
			return _ParseExpressionMathBracket(src, size, pos, out nextPos, false);
		}

		private delegate bool MathCalcLoopFunc(MathSymbol symbol, ref Stack<SentenceExpression> stack0, ref Stack<MathSymbol> stack1);
		private static SentenceExpression _ParseExpressionMathBracket(string src, int size, int pos, out int nextPos, bool bBracket) {
			nextPos = pos;
			Stack<SentenceExpression> expressionStack = new Stack<SentenceExpression>();
			Stack<MathSymbol> symbolStack = new Stack<MathSymbol>();

			MathCalcLoopFunc calcLoopFunc = (MathSymbol symbol, ref Stack<SentenceExpression> stack0, ref Stack<MathSymbol> stack1) => {
				int level = Grammar.GetMathSymbolLevel(symbol);
				while (stack1.Count != 0) {
					int preLevel = Grammar.GetMathSymbolLevel(stack1.Peek());
					if (preLevel < level) {
						break;
					}
					if (stack0.Count < 2) {
						return false;
					}
					var topSymbol = stack1.Peek();
					stack1.Pop();
					var vr = stack0.Peek();
					stack0.Pop();
					var vl = stack0.Peek();
					stack0.Pop();
					var calculate = _GetCalculate(topSymbol);
					if (calculate == null) {
						return false;
					}
					SentenceExpressionMath expression = null;
					if (Grammar.IsVariableSelfAssignSymbol(topSymbol)) {
						expression = (new SentenceExpressionSelfAssign(vl, vr, calculate));
					} else {
						expression = (new SentenceExpressionMath(vl, vr, calculate));
					}
					stack0.Push(expression);
				}
				return true;
			};

			while (true) {
				bool bRet = false;
				Jump(src, size, pos, out pos);
				if (Grammar.MatchLeftBrcket(src, size, pos, out pos)) {
					Jump(src, size, pos, out pos);
					var priorityExpression = _ParseExpressionMathBracket(src, size, pos, out pos, true);
					if (!priorityExpression) {
						return null;
					}
					expressionStack.Push(priorityExpression);
					bRet = true;
				} else {
					var value = _ParseExpressionValue(src, size, pos, out pos);
					if (value) {
						expressionStack.Push(value);
						bRet = true;
					}
				}

				if (!bRet) {
					break;
				}

				var saveJumpBeginPos = pos;
				Jump(src, size, pos, out pos);

				if (pos >= size) {
					break;
				}

				if (bBracket && Grammar.MatchRightBrcket(src, size, pos, out pos)) {
					break;
				}

				var symbol = MathSymbol.None;
				if (Grammar.MatchMathSymbol(src, size, pos, out pos, out symbol)) {
					bRet = false;
					if (!calcLoopFunc(symbol, ref expressionStack, ref symbolStack)) {
						return null;
					}
					symbolStack.Push(symbol);
				} else {
					pos = saveJumpBeginPos;
					break;
				}
				if (bRet) {
					break;
				}
			}

			if (!calcLoopFunc(MathSymbol.None, ref expressionStack, ref symbolStack)) {
				return null;
			}

			if (expressionStack.Count != 1) {
				return null;
			}

			nextPos = pos;

			return expressionStack.Peek();
		}

		private static IValueCalculate _GetCalculate(MathSymbol symbol) {
			switch (symbol) {
			case MathSymbol.Mul:
				return ValueCalculateMul.instance;
			case MathSymbol.Div:
				return ValueCalculateDiv.instance;
			case MathSymbol.Mod:
				return ValueCalculateMod.instance;
			case MathSymbol.Add:
				return ValueCalculateAdd.instance;
			case MathSymbol.Sub:
				return ValueCalculateSub.instance;
			case MathSymbol.Less:
				return ValueCalculateLess.instance;
			case MathSymbol.LessEqual:
				return ValueCalculateSameOrLess.instance;
			case MathSymbol.Equal:
				return ValueCalculateSame.instance;
			case MathSymbol.NotEqual:
				return ValueCalculateNotSame.instance;
			case MathSymbol.More:
				return ValueCalculateMore.instance;
			case MathSymbol.MoreEqual:
				return ValueCalculateSameOrMore.instance;
			case MathSymbol.LogicAnd:
				return ValueCalculateLogicAnd.instance;
			case MathSymbol.LogicOr:
				return ValueCalculateLogicOr.instance;
			case MathSymbol.AssignAdd:
				return ValueCalculateAdd.instance;
			case MathSymbol.AssignSub:
				return ValueCalculateSub.instance;
			case MathSymbol.AssignMul:
				return ValueCalculateMul.instance;
			case MathSymbol.AssignDiv:
				return ValueCalculateDiv.instance;
			case MathSymbol.AssignMod:
				return ValueCalculateMod.instance;
			default:
				break;
			}

			return null;
		}

		private static IValueCalculate _GetCalculate(DoubleSymbol symbol) {
			switch (symbol) {
			case DoubleSymbol.AddAdd:
				return ValueCalculateAdd.instance;
			case DoubleSymbol.SubSub:
				return ValueCalculateSub.instance;
			default:
				break;
			}
			return null;
		}

	}
} // namespace peak.interpreter