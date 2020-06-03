/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	class SentenceFor : SentenceReturn {
		private Sentence _sentence0 = null;
		private SentenceExpression _expression0 = null;
		private SentenceExpression _expression1 = null;
		private Sentence _content = null;
		public SentenceFor(Sentence sentence0,
			SentenceExpression expression0,
			SentenceExpression expression1,
			Sentence content) {
			_sentence0 = sentence0;
			_expression0 = expression0;
			_expression1 = expression1;
			_content = content;
		}
		public override ExecuteResult Execute(Space space) {
			var tempSpace = new Space(SpaceType.Loop, space);
			if (_sentence0) {
				if (!IsSuccess(_sentence0.Execute(tempSpace))) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.For, "The 'sentence0' of 'for' execute failed!");
					return ExecuteResult.Failed;
				}
			}

			var contentSpace = new Space(SpaceType.Loop, tempSpace);
			while (true) {
				if (_expression0) {
					if (!IsSuccess(_expression0.Execute(tempSpace))) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.For, "The condition0-expression of 'for' execute failed!");
						return ExecuteResult.Failed;
					}
					if (!ValueTool.ToLogic(_expression0.value)) {
						break;
					}
				}
				if (_content) {
					contentSpace.Clear();
					var ret = _content.Execute(contentSpace);
					if (!IsSuccess(ret)) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.For, "The sentence of 'for' execute failed!");
						return ExecuteResult.Failed;
					}
					if (ret == ExecuteResult.Break) {
						break;
					}
					if (ret == ExecuteResult.Return) {
						SetReturnValue((_content as SentenceReturn).returnValue);
						tempSpace.Clear();
						return ExecuteResult.Return;
					}
				}
				if (_expression1) {
					if (!IsSuccess(_expression1.Execute(tempSpace))) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.For, "The condition1-expression of 'for' execute failed!");
						return ExecuteResult.Failed;
					}
				}
			}
			tempSpace.Clear();
			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter