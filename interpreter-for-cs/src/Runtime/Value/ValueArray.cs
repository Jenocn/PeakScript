/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	public class ValueArray : TypeValue<ValueArray> {
		private List<Variable> _value = new List<Variable>();
		public List<Variable> value { get => _value; }

		public ValueArray() {}
		public ValueArray(List<Variable> value) {
			this._value = value;
		}
		public override string ToString() {
			string ret = "[";
			var arrSize = _value.Count;
			for (var i = 0; i < arrSize; ++i) {
				ret += _value[i].value.ToString();
				if (i != arrSize - 1) {
					ret += ", ";
				}
			}
			ret += "]";
			return ret;
		}
		public override Value Clone() {
			var valueArray = new ValueArray();
			foreach (var item in _value) {
				var variable = new Variable(item.name, item.attribute);
				if (item.value) {
					variable.SetValue(item.value.Clone());
				}
				valueArray.EmplaceBack(variable);
			}
			return valueArray;
		}

		public void Reserve(int size) {
			_value.Capacity = size;
		}
		public void EmplaceBack(Variable variable) {
			_value.Add(variable);
		}
		public void EmplaceBack(Value value) {
			_value.Add(new Variable("", VariableAttribute.None, value));
		}
	}
} // namespace peak.interpreter