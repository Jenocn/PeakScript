/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class ValueBool : TypeValue<ValueBool> {
		private bool _value = false;
		public static readonly ValueBool TRUE = new ValueBool(true);
		public static readonly ValueBool FALSE = new ValueBool(false);

		public bool value { get => _value; }

		public ValueBool(bool value) {
			_value = value;
		}
		public override string ToString() {
			return _value ? "true" : "false";
		}
		public override Value Clone() {
			return _value ? TRUE : FALSE;
		}

	}
} // namespace peak.interpreter