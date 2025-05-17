/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System;
using System.Collections.Generic;

namespace peak.interpreter {

	public class ValueFunction : TypeValue<ValueFunction> {

		private List<string> _params = new List<string>();
		private Func<List<Value>, Space, Value> _function = null;
		private ValueFunction() {}
		public ValueFunction(int paramSize, Func<List<Value>, Space, Value> func) {
			for (var i=0; i<paramSize; ++i)
			{
				_params.Add("%" + i);
			}
			_function = func;
		}
		public ValueFunction(List<string> params_, Func<List<Value>, Space, Value> func) {
			_params = params_;
			_function = func;
		}
		public Value Call(List<Value> args, Space space) {
			if (_params.Count != args.Count) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "The function (" + args.Count + " params) not found!");
				return null;
			}
			var tempSpace = new Space(SpaceType.Function, space);
			for (int i = 0; i < args.Count; ++i) {
				var tempVariable = new Variable(_params[i], VariableAttribute.None);
				if (!tempSpace.AddVariable(tempVariable)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "The function params name is exist!");
					return null;
				}
				tempVariable.SetValue(args[i]);
			}
			var result = _function.Invoke(args, tempSpace);
			tempSpace.Clear();
			return result;
		}
		public override string ToString() {
			string ret = "function (";
			for (var i = 0; i < _params.Count; ++i)
			{
				ret += _params[i];
				if (i < _params.Count - 1)
				{
					ret += ", ";
				}
			}
			ret += ")";
			return ret;
		}
		public override Value Clone() {
			return new ValueFunction(_params, _function);
		}
	}
} // namespace peak.interpreter