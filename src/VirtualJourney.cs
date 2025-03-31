/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak {

	using interpreter;

	public class VirtualJourney {
		private Executer _executer = null;
		public Space space { get => _executer.space; }
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
		public Value ExecuteFunction(string name, List<Value> args) {
			var variable = _executer.FindVariable(name);
			if (variable && ValueTool.IsFunction(variable.value)) {
				var valueFunc = variable.value as ValueFunction;
				return valueFunc.Call(args, space);
			}
			return ValueNull.DEFAULT_VALUE;
		}
		public Value ExecuteFunction(string name, params Value[] args) {
			int len = args.Length;
			var argList = new List<Value>(len);
			for (var i = 0; i < len; ++i) {
				argList.Add(args[i]);
			}
			return ExecuteFunction(name, argList);
		}
	}
} // namespace peak