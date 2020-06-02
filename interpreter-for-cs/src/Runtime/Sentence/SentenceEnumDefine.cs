/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	public class SentenceEnumDefine : Sentence {
		private string _name = "";
		private LinkedList<KeyValuePair<string, ValueNumber>> _valueList = null;
		public SentenceEnumDefine(string name, LinkedList<KeyValuePair<string, ValueNumber>> valueList) {
			_name = name;
			_valueList = valueList;
		}
		public override ExecuteResult Execute(Space space) {
			var valueObject = new ValueObject();
			var variable = new Variable(_name, VariableAttribute.Const, valueObject);
			if (!space.AddVariable(variable)) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.EnumDefine, "The enum name \"" + _name + "\" is exist!");
				return ExecuteResult.Failed;
			}
			var valueSpace = valueObject.space;
			foreach (var pair in _valueList) {
				var valueVariable = new Variable(pair.Key, VariableAttribute.Const, pair.Value);
				if (!valueSpace.AddVariable(valueVariable)) {
					ErrorLogger.LogRuntimeError(pair.Key);
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.EnumDefine, "The item name \"" + _name + "\" is exist!");
					return ExecuteResult.Failed;
				}
			}
			return ExecuteResult.Successed;
		}

	};
} // namespace peak.interpreter