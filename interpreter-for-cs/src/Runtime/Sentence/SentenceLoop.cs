/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System;

namespace peak.interpreter {
	class SentenceLoop : SentenceReturn {
		private string _indexParam = "";
		private SentenceExpression _condition = null;
		private Sentence _sentence = null;
		public SentenceLoop(string indexParam, SentenceExpression condition, Sentence sentence) {
			_indexParam = indexParam;
			_condition = condition;
			_sentence = sentence;
		}
		public override ExecuteResult Execute(Space space) {
			if (!IsSuccess(_condition.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Loop, "The condition execute failed!");
				return ExecuteResult.Failed;
			}
			var value = _condition.value;
			if (!ValueTool.IsNumber(value)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Loop, "The value of condition isn't a number!");
				return ExecuteResult.Failed;
			}
			var count = Math.Max(0, (int) ((value as ValueNumber).value));
			var tempSpace = new Space(SpaceType.Loop, space);
			if (_indexParam.Length == 0) {
				for (int i = 0; i < count; ++i) {
					tempSpace.Clear();
					var ret = _sentence.Execute(tempSpace);
					if (!IsSuccess(ret)) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Loop, "The sentence execute failed!");
						return ExecuteResult.Failed;
					}
					if (ret == ExecuteResult.Break) {
						break;
					}
				}
			} else {
				tempSpace.Clear();
				var indexVariable = new Variable(_indexParam, VariableAttribute.None);
				if (!tempSpace.AddVariable(indexVariable)) {
					ErrorLogger.LogRuntimeError(_indexParam);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Loop, "The variable \"" + _indexParam + "\" is exist!");
					return ExecuteResult.Failed;
				}
				for (int i = 0; i < count; ++i) {
					if (!indexVariable.SetValue(new ValueNumber(i))) {
						return ExecuteResult.Failed;
					}
					var ret = _sentence.Execute(tempSpace);
					if (!IsSuccess(ret)) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Loop, "The sentence execute failed!");
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
			}
			tempSpace.Clear();
			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter