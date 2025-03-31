/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	class SentenceVariableDefine : Sentence {
		private string _name = "";
		private VariableAttribute _attribute = VariableAttribute.None;
		private Variable _variable = null;
		private SentenceExpression _expression = null;
		public SentenceVariableDefine(string name, VariableAttribute attribute, SentenceExpression expression = null) {
			_name = name;
			_attribute = attribute;
			_expression = expression;
		}
		public override ExecuteResult Execute(Space space) {
			Value value = null;
			if (_expression) {
				if (!IsSuccess(_expression.Execute(space))) {
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableDefine, "The \"" + _name + "\" expression execute failed!");
					return ExecuteResult.Failed;
				}
				value = _expression.value;
			} else {
				if (_attribute == VariableAttribute.Const) {
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableDefine, "The const-variable \"" + _name + "\" isn't assign!");
					return ExecuteResult.Failed;
				}
			}
			_variable = new Variable(_name, _attribute, value);
			if (!space.AddVariable(_variable)) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableDefine, "The variable \"" + _name + "\" is exist!");
				return ExecuteResult.Failed;
			}
			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter