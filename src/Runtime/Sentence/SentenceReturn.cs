/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class SentenceReturn : Sentence {
		private SentenceExpression _returnExpression = null;
		private Value _returnValue = null;

		public Value returnValue { get => _returnValue; }

		public SentenceReturn() { }

		public SentenceReturn(SentenceExpression expression) {
			_returnExpression = expression;
		}
		public override ExecuteResult Execute(Space space) {
			if (!IsSuccess(_returnExpression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Return, "The expression execute failed!");
				return ExecuteResult.Failed;
			}
			SetReturnValue(_returnExpression.value);
			return ExecuteResult.Return;
		}

		protected void SetReturnValue(Value value) {
			_returnValue = value;
		}

	}
} // namespace peak.interpreter