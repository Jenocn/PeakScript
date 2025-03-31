/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class SentenceExpressionSelfAssign : SentenceExpressionMath {
		public SentenceExpressionSelfAssign(SentenceExpression left, SentenceExpression right, IValueCalculate calculate):
			base(left, right, calculate) {
			}
		public override ExpressionType GetExpressionType() { return ExpressionType.SelfAssign; }
		public override ExecuteResult Execute(Space space) {
			if (_left.GetExpressionType() != ExpressionType.Variable) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.SelfAssign, "The expression target isn't a variable!");
				return ExecuteResult.Failed;
			}

			if (!IsSuccess(base.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.SelfAssign, "The [self-assign-expression] execute failed!");
				return ExecuteResult.Failed;
			}

			var temp = _left as SentenceExpressionVariable;
			var variable = temp.variable;
			if (!variable) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.SelfAssign, "The [self-assign-expression] execute failed!");
				return ExecuteResult.Failed;
			}

			if (!variable.SetValue(value)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.SelfAssign, "The [self-assign-expression] execute failed!");
				return ExecuteResult.Failed;
			}

			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter