/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	class SentenceVariableSet : Sentence {
		private string _name;
		private SentenceExpression _expression = null;
		public SentenceVariableSet(string name, SentenceExpression expression) {
			_name = name;
			_expression = expression;
		}
		public override ExecuteResult Execute(Space space) {
			var variable = space.FindVariable(_name);
			if (!variable) {
				variable = new Variable(_name, VariableAttribute.None);
				space.AddVariable(variable);
			}
			if (_expression) {
				if (!IsSuccess(_expression.Execute(space))) {
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableSet, "The \"" + _name + "\" expression execute failed!");
					return ExecuteResult.Failed;
				}
				if (!variable.SetValue(_expression.value)) {
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableSet, "The \"" + _name + "\" expression execute failed!");
					return ExecuteResult.Failed;
				}
			}
			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter