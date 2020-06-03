/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System;
using System.Collections.Generic;

namespace peak.interpreter {

	public class ValueFunction : TypeValue<ValueFunction> {

		private Dictionary<int, KeyValuePair<List<string>, Func<List<Value>, Space, Value>>> _functionMap = new Dictionary<int, KeyValuePair<List<string>, Func<List<Value>, Space, Value>>>();
		private ValueFunction() {}
		public ValueFunction(int paramSize, Func<List<Value>, Space, Value> func) {
			AddFunction(paramSize, func);
		}
		public ValueFunction(List<string> params_, Func<List<Value>, Space, Value> func) {
			AddFunction(params_, func);
		}
		public Value Call(List<Value> args, Space space) {
			KeyValuePair<List<string>, Func<List<Value>, Space, Value>> ret;
			if (!_functionMap.TryGetValue(args.Count, out ret)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "The function (" + args.Count + " params) not found!");
				return null;
			}
			var tempSpace = new Space(SpaceType.Function, space);
			var params_ = ret.Key;
			var func = ret.Value;
			var paramSize = params_.Count;
			for (int i = 0; i < args.Count; ++i) {
				if (i >= paramSize) {
					break;
				}
				var tempVariable = new Variable(params_[i], VariableAttribute.None);
				if (!tempSpace.AddVariable(tempVariable)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "The function params name is exist!");
					return null;
				}
				tempVariable.SetValue(args[i]);
			}
			var result = func.Invoke(args, tempSpace);
			tempSpace.Clear();
			return result;
		}
		public override string ToString() {
			return "function";
		}
		public override Value Clone() {
			var valueFunc = new ValueFunction();
			valueFunc._functionMap = _functionMap;
			return valueFunc;
		}

		public bool AddFunction(int paramSize, Func<List<Value>, Space, Value> func) {
			if (!_functionMap.ContainsKey(paramSize)) {
				_functionMap.Add(paramSize, new KeyValuePair<List<string>, Func<List<Value>, Space, Value>>(new List<string>(), func));
				return true;
			}
			return false;
		}
		public bool AddFunction(List<string> params_, Func<List<Value>, Space, Value> func) {
			var size = params_.Count;
			if (!_functionMap.ContainsKey(size)) {
				_functionMap.Add(size, new KeyValuePair<List<string>, Func<List<Value>, Space, Value>>(params_, func));
				return true;
			}
			return false;
		}

	}
} // namespace peak.interpreter