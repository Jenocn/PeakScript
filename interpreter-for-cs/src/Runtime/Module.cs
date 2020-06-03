/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class Module {
		private string _name = "";
		private Executer _executer = null;
		private Space _space = null;

		public string name { get => _name; }
		public Space space { get => _space; }

		public Module(string name, Executer executer) {
			_name = name;
			_executer = executer;
			_space = _executer.space;
		}
		public Module(string name, Space space) {
			_name = name;
			_space = space;
		}

		public bool Execute() {
			if (_executer != null) {
				return _executer.Execute();
			}
			return true;
		}
	}

} // namespace peak.interpreter