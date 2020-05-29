/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class SentenceDoWhile : Sentence {
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
				if (!IsSuccess(_sentence.Execute(tempSpace))) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.DoWhile, "The sentence execute failed!");
					return ExecuteResult.Failed;
				}
				if (!IsSuccess(_expression.Execute(space))) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.DoWhile, "The condition expression execute failed!");
					return ExecuteResult.Failed;
				}
				if (!ValueTool.ToLogic(_expression.value)) {
					break;
				}
			}
			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter