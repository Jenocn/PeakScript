/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class Executer {
		private ParseData _parseData = null;
		private Space _space = null;
		private Space _outsideSpace = null;
		public Space space { get => _space; }

		public static Executer Create(string src) {
			if (string.IsNullOrEmpty(src)) {
				return null;
			}
			var parseData = ParseTool.Load(src);
			if (!parseData.bSuccess) {
				return null;
			}
			return new Executer(parseData);
		}
		private Executer(ParseData data) {
			_parseData = data;
			_space = new Space(SpaceType.None);
			_outsideSpace = new Space(SpaceType.None);
		}
		~Executer() {
			_space.Clear();
			_outsideSpace.Clear();
		}

		public bool Execute() {
			_space.Clear();
			_space.AddSpaceOfUsing(_outsideSpace);
			foreach (var sentence in _parseData.sentenceList) {
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
			return _outsideSpace.AddVariable(variable);
		}

	}

} // namespace peak.interpreter