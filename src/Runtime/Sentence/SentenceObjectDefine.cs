/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	class SentenceObjectDefine : Sentence {
		private string _name = "";
		private string _parentName = "";
		private LinkedList<Sentence> _sentenceList = null;
		public SentenceObjectDefine(string name, string parentName, LinkedList<Sentence> sentenceList) {
			_name = name;
			_parentName = parentName;
			_sentenceList = sentenceList;
		}
		public override ExecuteResult Execute(Space space) {
			ValueObject parentObject = null;
			if (!string.IsNullOrEmpty(_parentName)) {
				var parentVariable = space.FindVariable(_parentName);
				if (!parentVariable) {
					ErrorLogger.LogRuntimeError(_parentName);
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ObjectDefine, "The extends object \"" + _parentName + "\" of \"" + _name + "\" not found!");
					return ExecuteResult.Failed;
				}
				var parentValue = parentVariable.value;
				if (!ValueTool.IsObject(parentValue)) {
					ErrorLogger.LogRuntimeError(_parentName);
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.ObjectDefine, "The variable \"" + _parentName + "\" isn't a object!");
					return ExecuteResult.Failed;
				}
				parentObject = parentValue as ValueObject;
			}
			var valueObject = new ValueObject(space, parentObject);
			var objectSpace = valueObject.space;
			foreach (var sentence in _sentenceList) {
				if (!IsSuccess(sentence.Execute(objectSpace))) {
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