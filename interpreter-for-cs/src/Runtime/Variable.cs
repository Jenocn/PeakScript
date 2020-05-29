/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public enum VariableAttribute {
		None,
		Const,
	}

	public class Variable {
		public static implicit operator bool(Variable value) {
			return value != null;
		}
		private string _name = "";
		private VariableAttribute _attribute = VariableAttribute.None;
		private Value _value = ValueNull.DEFAULT_VALUE;

		public string name { get => _name; }
		public VariableAttribute attribute { get => _attribute; }
		public Value value { get => _value; }

		public Variable(string name, VariableAttribute attribute, Value value = null) {
			_name = name;
			_attribute = attribute;
			_value = value;
		}

		public bool SetValue(Value value) {
			switch (_attribute) {
			case VariableAttribute.None:
				_value = value;
				return true;
			case VariableAttribute.Const:
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Variable, "Can't set value, The variable \"" + _name + "\" is 'const'!");
				return false;
			}
			return true;
		}
	}
} // namespace peak.interpreter