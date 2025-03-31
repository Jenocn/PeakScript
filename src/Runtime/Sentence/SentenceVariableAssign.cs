/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	class SentenceVariableAssign : Sentence {
		private SentenceExpression _variableExpression = null;
		private SentenceExpression _expression = null;
		public SentenceVariableAssign(SentenceExpression variableExpression, SentenceExpression expression) {
			_variableExpression = variableExpression;
			_expression = expression;
		}
		public override ExecuteResult Execute(Space space) {
			if (_variableExpression.GetExpressionType() != ExpressionType.Variable) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableAssign, "The result of expression isn't a variable!");
				return ExecuteResult.Failed;
			}
			if (!IsSuccess(_variableExpression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableAssign, "The expression execute failed!");
				return ExecuteResult.Failed;
			}
			var variable = (_variableExpression as SentenceExpressionVariable).variable;
			if (!IsSuccess(_expression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableAssign, "The expression execute failed!");
				return ExecuteResult.Failed;
			}
			if (!variable.SetValue(_expression.value)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableAssign, "The expression execute failed!");
				return ExecuteResult.Failed;
			}
			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter