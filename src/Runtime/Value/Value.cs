/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public abstract class Value {
		public static implicit operator bool(Value value) {
			return value != null;
		}
		public Value() {}
		public abstract int GetValueType();
		public abstract Value Clone();
		public override string ToString() { return ""; }
	}

	public class TypeValueCount {
		private static int _count = 0;
		private int _index = 0;
		public int index { get => _index; }
		public TypeValueCount() {
			_index = _count;
			++_count;
		}
	}

	public abstract class TypeValue<T> : Value {
		private static TypeValueCount _count = new TypeValueCount();
		public static int VALUE_TYPE { get => _count.index; }
		public sealed override int GetValueType() {
			return TypeValue<T>.VALUE_TYPE;
		}
	}
} // peak.interpreter