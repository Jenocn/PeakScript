/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak {

	using interpreter;

	public class VirtualJourney {

		private Space _space = null;
		private List<Sentence> _sentenceList = new List<Sentence>();
		public VirtualJourney(List<Sentence> sentenceList, Space parent = null) {
			_space = new Space(SpaceType.None, parent);
			_sentenceList = sentenceList;
		}

		public bool Execute() {
			_space.Clear();
			foreach (var sentence in _sentenceList) {
				if (!Sentence.IsSuccess(sentence.Execute(_space))) {
					return false;
				}
			}
			return true;
		}

		public Variable FindVariable(string name) {
			return _space.FindVariable(name);
		}
		public bool AddVariable(Variable variable) {
			return _space.AddVariable(variable);
		}
	}
} // namespace peak