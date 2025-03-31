/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class SentenceExpressionNot : SentenceExpression {
		private SentenceExpression _expression = null;
		public SentenceExpressionNot(SentenceExpression expression) {
			_expression = expression;
		}
		public override ExpressionType GetExpressionType() { return ExpressionType.Not; }
		public override ExecuteResult Execute(Space space) {
			if (!IsSuccess(_expression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ExpressionNot, "The [not-expression] execute failed!");
				return ExecuteResult.Failed;
			}

			var ret = ValueTool.ToLogic(_expression.value);
			SetValue(new ValueBool(!ret));

			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter