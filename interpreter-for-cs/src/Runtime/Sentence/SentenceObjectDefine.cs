/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	class SentenceObjectDefine : Sentence {
		private string _name = "";
		private List<Sentence> _sentenceList = null;
		public SentenceObjectDefine(string name, List<Sentence> sentenceList) {
			_name = name;
			_sentenceList = sentenceList;
		}
		public override ExecuteResult Execute(Space space) {
			var tempSpace = new Space(SpaceType.Object);
			tempSpace.AddSpaceOfUsing(space);
			var valueObject = new ValueObject(tempSpace);
			foreach (var sentence in _sentenceList) {
				if (!IsSuccess(sentence.Execute(tempSpace))) {
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ObjectDefine, "The object build failed!");
					return ExecuteResult.Failed;
				}
			}

			if (!space.AddVariable(new Variable(_name, VariableAttribute.None, valueObject))) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ObjectDefine, "The object \"" + _name + "\" is exist!");
				return ExecuteResult.Failed;
			}

			return ExecuteResult.Successed;
		}

	}

} // namespace peak.interpreter