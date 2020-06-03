/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	public class SentenceBlock : SentenceReturn {
		private List<Sentence> _list = new List<Sentence>();
		public override ExecuteResult Execute(Space space) {
			var tempSpace = new Space(space.spaceType, space);
			foreach (var sentence in _list) {
				var executeRet = sentence.Execute(tempSpace);
				if (!IsSuccess(executeRet)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Block, "The sentence execute failed!");
					return ExecuteResult.Failed;
				}
				if (executeRet == ExecuteResult.Return) {
					SetReturnValue((sentence as SentenceReturn).returnValue);
					return ExecuteResult.Return;
				}
				if (executeRet == ExecuteResult.Break) {
					return ExecuteResult.Break;
				}
				if (executeRet == ExecuteResult.Continue) {
					return ExecuteResult.Continue;
				}
			}
			tempSpace.Clear();
			return ExecuteResult.Successed;
		}
		public void Push(Sentence sentence) {
			_list.Add(sentence);
		}

	}
} // namespace peak.peak.interpreter