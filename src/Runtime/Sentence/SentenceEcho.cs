/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	class SentenceEcho : Sentence {
		private SentenceExpression _expression = null;
		public SentenceEcho(SentenceExpression expression) {
			_expression = expression;
		}
		public override ExecuteResult Execute(Space space) {
			if (!IsSuccess(_expression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Echo, "The parameter expression execute failed!");
				return ExecuteResult.Failed;
			}
			var value = _expression.value;
			System0.Echo(ValueTool.ToString(value));

			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter