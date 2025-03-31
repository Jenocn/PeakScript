/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class ValueNumber : TypeValue<ValueNumber> {
		private double _value = 0;
		public double value { get => _value; }
		public ValueNumber(double value) {
			_value = value;
		}
		public override string ToString() {
			return _value.ToString();
		}
		public override Value Clone() {
			return new ValueNumber(_value);
		}
	}
} // namespace peak.interpreter