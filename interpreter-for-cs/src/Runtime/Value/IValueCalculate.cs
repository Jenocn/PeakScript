/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public abstract class IValueCalculate {
		public abstract Value Calculate(Value left, Value right);
	}

	public abstract class ValueCalculateSingleton<T> : IValueCalculate where T : class, new() {
		private static T _instance = new T();
		public static T instance { get => _instance; }
	}
} // namespace peak.interpreter