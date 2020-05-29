/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public class ValueNull : TypeValue<ValueNull> {
		public static readonly ValueNull DEFAULT_VALUE = new ValueNull();
		public override string ToString() {
			return "null";
		}
		public override Value Clone() {
			return DEFAULT_VALUE;
		}
	}
} // namespace peak.interpreter