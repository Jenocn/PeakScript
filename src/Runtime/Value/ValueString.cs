/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class ValueString : TypeValue<ValueString> {
		private string _value = "";
		public string value { get => _value; }
		public ValueString(string value) {
			_value = value;
		}
		public override string ToString() {
			return _value;
		}
		public override Value Clone() {
			return new ValueString(_value);
		}

	}
} // namespace peak.interpreter