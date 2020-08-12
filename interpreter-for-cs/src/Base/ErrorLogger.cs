/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System;
using System.Collections.Generic;

namespace peak.interpreter {

	public enum ErrorRuntimeCode {
		None = 0,
		Space,
		Variable,
		Block,
		Condition,
		DoWhile,
		Echo,
		Expression,
		ExpressionDouble,
		FunctionCall,
		Math,
		ExpressionNot,
		SelfAssign,
		Array,
		ExpressionVariable,
		For,
		Foreach,
		FunctionDefine,
		Loop,
		Return,
		TryCatchFinally,
		VariableAssign,
		VariableDefine,
		VariableSet,
		While,
		VariableNameAnalysis,
		VariableArrayItemAnalysis,
		VariableInsideAnalysis,
		New,
		ObjectDefine,
		Inside,
		EnumDefine,
		Import,
		Export,
	}

	public class ErrorLogger {
		private static Action<string> _logger = null;
		private static Dictionary<ErrorRuntimeCode, string> _errorCodeNameMap = null;

		static ErrorLogger() {
			_logger = (string message) => {
				Console.WriteLine(message);
			};
			_errorCodeNameMap = new Dictionary<ErrorRuntimeCode, string>() {
				{ErrorRuntimeCode.Space, "Space"},
				{ErrorRuntimeCode.Variable, "Variable"},
				{ErrorRuntimeCode.Block, "Block, \"{ }\""},
				{ErrorRuntimeCode.Condition, "Condition, \"if-else\""},
				{ErrorRuntimeCode.DoWhile, "DoWhile, \"do-while\""},
				{ErrorRuntimeCode.Echo, "Echo, \"echo\""},
				{ErrorRuntimeCode.Expression, "Expression"},
				{ErrorRuntimeCode.ExpressionDouble, "ExpressionDouble, \"++\",\"--\""},
				{ErrorRuntimeCode.FunctionCall, "FunctionCall, \"function()\""},
				{ErrorRuntimeCode.Math, "Math, \"math expression\""},
				{ErrorRuntimeCode.ExpressionNot, "ExpressionNot, \"!\""},
				{ErrorRuntimeCode.SelfAssign, "SelfAssign, \"+=, -=, *=, /=, %= ...\""},
				{ErrorRuntimeCode.Array, "Array, \"[ ]\""},
				{ErrorRuntimeCode.ExpressionVariable, "ExpressionVariable, \"variable\""},
				{ErrorRuntimeCode.For, "For, \"for(;;)\""},
				{ErrorRuntimeCode.Foreach, "Foreach, \"foreach\",\"for-in\""},
				{ErrorRuntimeCode.FunctionDefine, "FunctionDefine, \"function { }\""},
				{ErrorRuntimeCode.Loop, "Loop, \"loop\""},
				{ErrorRuntimeCode.Return, "Return, \"return\""},
				{ErrorRuntimeCode.TryCatchFinally, "TryCatchFinally, \"try-catch-finally\""},
				{ErrorRuntimeCode.VariableAssign, "VariableAssign, \"=\""},
				{ErrorRuntimeCode.VariableDefine, "VariableDefine, \"var, the, const\""},
				{ErrorRuntimeCode.VariableSet, "VariableSet, \"set\""},
				{ErrorRuntimeCode.While, "While, \"while\""},
				{ErrorRuntimeCode.VariableNameAnalysis, "VariableNameAnalysis, \"variable-name\""},
				{ErrorRuntimeCode.VariableArrayItemAnalysis, "VariableArrayItemAnalysis, \"array [ ]\""},
				{ErrorRuntimeCode.VariableInsideAnalysis, "VariableInsideAnalysis, \"inside.value\""},
				{ErrorRuntimeCode.New, "New, \"new\""},
				{ErrorRuntimeCode.ObjectDefine, "ObjectDefine, \"object\""},
				{ErrorRuntimeCode.Inside, "Inside, \"inside.value\""},
				{ErrorRuntimeCode.EnumDefine, "EnumDefine, \"enum\""},
				{ErrorRuntimeCode.Import, "Import, \"import\""},
				{ErrorRuntimeCode.Export, "Export, \"export\""},
			};
		}
		public static void Locate(Action<string> logger) {
			_logger = logger;
		}
		public static void Log(string message) {
			_logger.Invoke("[!]error: " + message);
		}
		public static void LogParseError(string src, int size, int pos) {
			int lineNum = 0;
			int save0 = 0;
			int save1 = 0;
			for (int i = 0; i < size; ++i) {
				if ((src[i] == '\n') || (i == size - 1)) {
					++lineNum;
					if (i >= pos) {
						save1 = i + 1;
						break;
					}
					save0 = i + 1;
					save1 = save0;
				}
			}
			Log("[" + lineNum + "," + (save1 - save0) + "]: " + src.Substring(save0, save1 - save0));
		}
		public static void LogRuntimeError(ErrorRuntimeCode code, string desc) {
			string ret = "";
			if (_errorCodeNameMap.TryGetValue(code, out ret)) {
				LogRuntimeError(ret + ": " + desc);
			} else {
				LogRuntimeError(desc);
			}
		}
		public static void LogRuntimeError(string desc) {
			Log("[runtime]: " + desc);
		}
	}

}