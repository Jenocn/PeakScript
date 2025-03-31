/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class SentenceExpressionVariable : SentenceExpression {
		private IExpressionVariableAnalysis _analysis = null;
		private Variable _variable = null;

		public Variable variable { get => _variable; }

		public SentenceExpressionVariable(IExpressionVariableAnalysis variableAnalysis) {
			_analysis = variableAnalysis;
		}
		public override ExecuteResult Execute(Space space) {
			_variable = _analysis.Execute(space);
			if (!_variable) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ExpressionVariable, "The variable-expression execute failed!");
				return ExecuteResult.Failed;
			}
			SetValue(_variable.value);
			return ExecuteResult.Successed;
		}
		public override ExpressionType GetExpressionType() { return ExpressionType.Variable; }
	}
} // namespace peak.interpreter