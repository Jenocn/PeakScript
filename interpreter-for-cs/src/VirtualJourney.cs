/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak {

	using interpreter;

	public class VirtualJourney {
		private Executer _executer = null;
		public VirtualJourney(Executer executer) {
			_executer = executer;
		}

		public bool Execute() {
			return _executer.Execute();
		}

		public Variable FindVariable(string name) {
			return _executer.FindVariable(name);
		}
		public bool AddVariable(Variable variable) {
			return _executer.AddVariable(variable);
		}
	}
} // namespace peak