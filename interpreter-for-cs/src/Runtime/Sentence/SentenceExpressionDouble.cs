/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class SentenceExpressionDouble : SentenceExpression {
		private SentenceExpression _variableExpresison = null;
		private IValueCalculate _calculate = null;
		private bool _bLast = false;

		public SentenceExpressionDouble(SentenceExpression variableExpresison, IValueCalculate calculate, bool last) {
			_variableExpresison = variableExpresison;
			_calculate = calculate;
			_bLast = last;
		}
		public override ExpressionType GetExpressionType() { return ExpressionType.DoubleSymbol; }
		public override ExecuteResult Execute(Space space) {
			if (_variableExpresison.GetExpressionType() != ExpressionType.Variable) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ExpressionDouble, "The expression isn't a type of variable!");
				return ExecuteResult.Failed;
			}
			if (!IsSuccess(_variableExpresison.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ExpressionDouble, "The expression execute failed!");
				return ExecuteResult.Failed;
			}
			var variable = (_variableExpresison as SentenceExpressionVariable).variable;
			var value = _variableExpresison.value;
			if (!ValueTool.IsNumber(value)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ExpressionDouble, "The value of variable isn't a type of 'number'!");
				return ExecuteResult.Failed;
			}
			var ret = _calculate.Calculate(value, new ValueNumber(1));
			if (!ret) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ExpressionDouble, "The calculate is failed!");
				return ExecuteResult.Failed;
			}
			if (!variable.SetValue(ret)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ExpressionDouble, "The variable set value failed!");
				return ExecuteResult.Failed;
			}
			SetValue(_bLast ? value : ret);
			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter