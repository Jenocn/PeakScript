/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class SentenceDoWhile : SentenceReturn {
		private SentenceExpression _expression = null;
		private Sentence _sentence = null;
		public SentenceDoWhile(SentenceExpression expression, Sentence sentence) {
			_expression = expression;
			_sentence = sentence;
		}
		public override ExecuteResult Execute(Space space) {
			var tempSpace = new Space(SpaceType.Loop, space);
			while (true) {
				tempSpace.Clear();
				var ret = _sentence.Execute(tempSpace);
				if (!IsSuccess(ret)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.DoWhile, "The sentence execute failed!");
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
				if (!IsSuccess(_expression.Execute(space))) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.DoWhile, "The condition expression execute failed!");
					return ExecuteResult.Failed;
				}
				if (!ValueTool.ToLogic(_expression.value)) {
					break;
				}
			}
			tempSpace.Clear();
			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter