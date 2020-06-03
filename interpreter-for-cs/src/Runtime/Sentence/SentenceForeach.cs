/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	class SentenceForeach : SentenceReturn {
		private string _name = "";
		private SentenceExpression _expression = null;
		private Sentence _sentence = null;
		public SentenceForeach(string name, SentenceExpression expression, Sentence sentence) {
			_name = name;
			_expression = expression;
			_sentence = sentence;
		}
		public override ExecuteResult Execute(Space space) {
			if (!IsSuccess(_expression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Foreach, "The expression execute failed!");
				return ExecuteResult.Failed;
			}
			if (!ValueTool.IsArray(_expression.value)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Foreach, "The expression isn't a array!");
				return ExecuteResult.Failed;
			}
			var arr = (_expression.value as ValueArray).value;
			if (arr.Count == 0) {
				return ExecuteResult.Successed;
			}

			var tempSpace = new Space(SpaceType.Loop, space);
			var itemVariable = new Variable(_name, VariableAttribute.None);
			if (!tempSpace.AddVariable(itemVariable)) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Foreach, "The variable \"" + _name + "\" execute failed!");
				return ExecuteResult.Failed;
			}
			var contentSpace = new Space(SpaceType.Loop, tempSpace);
			foreach (var item in arr) {
				itemVariable.SetValue(item.value);
				contentSpace.Clear();
				var ret = _sentence.Execute(contentSpace);
				if (!IsSuccess(ret)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Foreach, "The sentence execute failed!");
					return ExecuteResult.Failed;
				}
				if (ret == ExecuteResult.Break) {
					break;
				}
				if (ret == ExecuteResult.Return) {
					SetReturnValue((_sentence as SentenceReturn).returnValue);
					tempSpace.Clear();
					return ExecuteResult.Return;
				}
			}

			tempSpace.Clear();
			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter