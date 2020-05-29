/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	class SentenceExpressionNew : SentenceExpression {
		private string _name;
		public SentenceExpressionNew(string name) {
			_name = name;
		}
		public override ExpressionType GetExpressionType() { return ExpressionType.New; }
		public override ExecuteResult Execute(Space space) {
			var variable = space.FindVariable(_name);
			if (!variable) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.New, "The \"" + _name + "\" not found!");
				return ExecuteResult.Failed;
			}
			var newValue = variable.value.Clone();
			SetValue(newValue);
			return ExecuteResult.Successed;
		}

	}

} // namespace peak.interpreter