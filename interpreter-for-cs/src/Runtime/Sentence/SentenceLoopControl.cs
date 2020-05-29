/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	class SentenceLoopControlContinue : Sentence {
		public override ExecuteResult Execute(Space space) {
			return ExecuteResult.Continue;
		}
	}
	class SentenceLoopControlBreak : Sentence {
		public override ExecuteResult Execute(Space space) {
			return ExecuteResult.Break;
		}
	}
} // namespace peak.interpreter