/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	class SentenceTryCatchFinally : Sentence {
		private Sentence _senTry = null;
		private Sentence _senCatch = null;
		private Sentence _senFinally = null;
		public SentenceTryCatchFinally(Sentence senTry, Sentence senCatch, Sentence senFinally) {
			_senTry = senTry;
			_senCatch = senCatch;
			_senFinally = senFinally;
		}
		public override ExecuteResult Execute(Space space) {
			if (!IsSuccess(_senTry.Execute(new Space(SpaceType.None, space)))) {
				if (_senCatch) {
					if (!IsSuccess(_senCatch.Execute(new Space(SpaceType.None, space)))) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.TryCatchFinally, "The sentence of catch execute failed!");
						return ExecuteResult.Failed;
					}
				}
			}
			if (_senFinally) {
				if (!IsSuccess(_senFinally.Execute(new Space(SpaceType.None, space)))) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.TryCatchFinally, "The sentence of finally execute failed!");
					return ExecuteResult.Failed;
				}
			}
			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter