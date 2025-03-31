/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class Module {
		private string _name = "";
		private Executer _executer = null;
		private Space _space = null;
		private bool _bExecuted = false;

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
			_bExecuted = true;
		}

		public bool Execute() {
			_bExecuted = true;
			if (_executer != null) {
				return _executer.Execute();
			}
			return true;
		}

		public bool IsExecuted() {
			return _bExecuted;
		}
	}

} // namespace peak.interpreter