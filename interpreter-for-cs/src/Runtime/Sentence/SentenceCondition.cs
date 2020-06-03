/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	class SentenceCondition : SentenceReturn {
		private SentenceExpression _expression = null;
		private Sentence _sentenceTrue = null;
		private Sentence _sentenceFalse = null;

		public SentenceCondition(SentenceExpression expression, Sentence sentenceTrue, Sentence sentenceFalse) {
			_expression = expression;
			_sentenceTrue = sentenceTrue;
			_sentenceFalse = sentenceFalse;
		}
		public override ExecuteResult Execute(Space space) {
			if (!IsSuccess(_expression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Condition, "The condition expression execute failed!");
				return ExecuteResult.Failed;
			}
			bool bTrue = ValueTool.ToLogic(_expression.value);
			var tempSentence = bTrue ? _sentenceTrue : _sentenceFalse;
			if (tempSentence) {
				var tempSpace = new Space(SpaceType.Condition, space);
				var executeRet = tempSentence.Execute(tempSpace);
				if (!IsSuccess(executeRet)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Condition, bTrue ? "The 'true' code sentence execute failed!" : "The 'false' code sentence execute failed!");
					return ExecuteResult.Failed;
				}
				if (executeRet == ExecuteResult.Return) {
					SetReturnValue((tempSentence as SentenceReturn).returnValue);
					return ExecuteResult.Return;
				}
				if (executeRet == ExecuteResult.Continue) {
					return ExecuteResult.Continue;
				}
				if (executeRet == ExecuteResult.Break) {
					return ExecuteResult.Break;
				}
				tempSpace.Clear();
			}
			
			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter