/*
	PeakScriptin httpsin//github.com/Jenocn/PeakScript
	By Jenocnin httpsin//jenocn.github.io
*/

using System;
using System.Collections.Generic;

namespace peak.interpreter {

	public class System0 {
		private static Action<string> _funcEcho = (string message) => {
			Console.WriteLine(message);
		};
		private static BuiltIn _buildIn = new BuiltIn();
		public static void LocateEcho(Action<string> func) {
			_funcEcho = func;
		}
		public static void Echo(string message) {
			_funcEcho.Invoke(message);
		}
		public static Variable FindVariable(string name) {
			Variable ret = null;
			if (_buildIn.variables.TryGetValue(name, out ret)) {
				return ret;
			}
			return null;
		}

		private class BuiltIn {
			public Dictionary<string, Variable> variables = new Dictionary<string, Variable>();
			public BuiltIn() {
				Action<string, int, Func<List<Value>, Space, Value>> _Emplace = (string name, int paramSize, Func<List<Value>, Space, Value> func) => {
					var value = new ValueFunction(paramSize, func);
					var variable = new Variable(name, VariableAttribute.Const, value);
					variables.Add(name, variable);
				};

				// print
				_Emplace.Invoke("print", 1, (List<Value> args, Space s) => {
					string ret = "";
					foreach (var arg in args) {
						ret += ValueTool.ToString(arg);
					}
					Echo(ret);
					return ValueNull.DEFAULT_VALUE;
				});
				// type
				_Emplace("type", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					return new ValueString(ValueTool.ToTypeString(args[0]));
				});
				// is_null
				_Emplace("is_null", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					bool ret = true;
					foreach (var arg in args) {
						ret &= ValueTool.IsNull(arg);
					}
					return new ValueBool(ret);
				});
				// is_number
				_Emplace("is_number", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					bool ret = true;
					foreach (var arg in args) {
						ret &= ValueTool.IsNumber(arg);
					}
					return new ValueBool(ret);
				});
				// is_bool
				_Emplace("is_bool", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					bool ret = true;
					foreach (var arg in args) {
						ret &= ValueTool.IsBool(arg);
					}
					return new ValueBool(ret);
				});
				// is_string
				_Emplace("is_string", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					bool ret = true;
					foreach (var arg in args) {
						ret &= ValueTool.IsString(arg);
					}
					return new ValueBool(ret);
				});
				// is_array
				_Emplace("is_array", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					bool ret = true;
					foreach (var arg in args) {
						ret &= ValueTool.IsArray(arg);
					}
					return new ValueBool(ret);
				});
				// is_function
				_Emplace("is_function", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					bool ret = true;
					foreach (var arg in args) {
						ret &= ValueTool.IsFunction(arg);
					}
					return new ValueBool(ret);
				});
				// is_object
				_Emplace("is_object", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					bool ret = true;
					foreach (var arg in args) {
						ret &= ValueTool.IsObject(arg);
					}
					return new ValueBool(ret);
				});
				// len
				_Emplace("len", 1, (List<Value> args, Space s) => {
					if (args.Count == 0) {
						return null;
					}
					var value = args[0];
					if (ValueTool.IsArray(value)) {
						return new ValueNumber((double) (value as ValueArray).value.Count);
					} else if (ValueTool.IsString(value)) {
						return new ValueNumber((double) (value as ValueString).value.Length);
					}
					return ValueNull.DEFAULT_VALUE;
				});
			}
		}
	}
} // namespace peak.interpreter