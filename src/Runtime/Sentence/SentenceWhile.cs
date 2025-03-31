/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	class SentenceWhile : SentenceReturn {
		private SentenceExpression _expression = null;
		private Sentence _sentence = null;
		public SentenceWhile(SentenceExpression expression, Sentence sentence) {
			_expression = expression;
			_sentence = sentence;
		}
		public override ExecuteResult Execute(Space space) {
			if (_sentence) {
				var tempSpace = new Space(SpaceType.Loop, space);
				while (true) {
					if (!IsSuccess(_expression.Execute(space))) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.While, "The condition expression execute failed!");
						return ExecuteResult.Failed;
					}
					if (!ValueTool.ToLogic(_expression.value)) {
						break;
					}
					tempSpace.Clear();
					var ret = _sentence.Execute(tempSpace);
					if (!IsSuccess(ret)) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.While, "The sentence execute failed!");
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
			} else {
				while (true) {
					if (!IsSuccess(_expression.Execute(space))) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.While, "The expression execute failed!");
						return ExecuteResult.Failed;
					}
					if (!ValueTool.ToLogic(_expression.value)) {
						break;
					}
				}
			}
			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter