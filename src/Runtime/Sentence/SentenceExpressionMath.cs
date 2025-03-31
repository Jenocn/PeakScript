/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class SentenceExpressionMath : SentenceExpression {
		protected SentenceExpression _left = null;
		protected SentenceExpression _right = null;
		protected IValueCalculate _calculate = null;
		public SentenceExpressionMath(SentenceExpression left, SentenceExpression right, IValueCalculate calculate) {
			_left = left;
			_right = right;
			_calculate = calculate;
		}
		public override ExpressionType GetExpressionType() { return ExpressionType.Math; }
		public override ExecuteResult Execute(Space space) {
			if (!_left || !IsSuccess(_left.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Math, "The math expression execute failed!");
				return ExecuteResult.Failed;
			}
			if (!_right || !IsSuccess(_right.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Math, "The math expression execute failed!");
				return ExecuteResult.Failed;
			}

			var value = _calculate.Calculate(_left.value, _right.value);
			if (!value) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Math, "The math expression execute failed!");
				return ExecuteResult.Failed;
			}
			SetValue(value);
			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter