/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System;
using System.Collections.Generic;

namespace peak.interpreter {

	class SentenceFunctionDefine : Sentence {
		private string _name;
		private List<string> _params = null;
		private Sentence _content = null;
		public SentenceFunctionDefine(string name, List<string> params_, Sentence content) {
			_name = name;
			_params = params_;
			_content = content;
		}
		public override ExecuteResult Execute(Space space) {
			Func<List<Value>, Space, Value> func = (List<Value> args, Space s) => {
				var result = _content.Execute(s);
				if (!IsSuccess(result)) {
					return null;
				}
				if (result == ExecuteResult.Return) {
					return (_content as SentenceReturn).returnValue;
				}
				return new ValueNull();
			};

			var variable = space.FindVariableFromTop(_name);
			if (variable) {
				var value = variable.value;
				if (ValueTool.IsFunction(value)) {
					if ((value as ValueFunction).AddFunction(_params, func)) {
						return ExecuteResult.Successed;
					}
				}
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionDefine, "The \"" + _name + "\" is exist!");
				return ExecuteResult.Failed;
			} else {
				variable = new Variable(_name, VariableAttribute.None);
				var value = new ValueFunction(_params, func);
				variable.SetValue(value);
				space.AddVariable(variable);
			}

			return ExecuteResult.Successed;
		}

	}
} // namespace peak.interpreter