/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public enum ExecuteResult {
		Successed,
		Failed,
		Return,
		Continue,
		Break,
	}
	public abstract class Sentence {
		public static implicit operator bool(Sentence value) {
			return value != null;
		}
		public Sentence() {}
		public abstract ExecuteResult Execute(Space space);

		public static bool IsSuccess(ExecuteResult value) {
			return value != ExecuteResult.Failed;
		}
	}
} // namespace peak.interpreter