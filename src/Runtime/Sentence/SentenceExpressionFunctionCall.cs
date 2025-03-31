/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {
	public class SentenceExpressionFunctionCall : SentenceExpression {
		private string _name = "";
		private List<SentenceExpression> _args = null;
		public string functionName { get => _name; }
		public SentenceExpressionFunctionCall(string name, List<SentenceExpression> args) {
			_name = name;
			_args = args;
		}
		public override ExpressionType GetExpressionType() { return ExpressionType.Function; }
		public ExecuteResult ExecuteFromInside(Space objSpace, Space space) {
			var variable = objSpace.FindVariable(_name);
			if (!variable) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "Can't found function \"" + _name + "\"!");
				return ExecuteResult.Failed;
			}
			var value = variable.value;
			if (!ValueTool.IsFunction(value)) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "Can't found function \"" + _name + "\"!");
				return ExecuteResult.Failed;
			}
			List<Value> args = new List<Value>();
			foreach (var expression in _args) {
				if (!expression || !IsSuccess(expression.Execute(space))) {
					ErrorLogger.LogRuntimeError(_name);
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "The parameters of function \"" + _name + "\" execute failed!");
					return ExecuteResult.Failed;
				}
				var arg = expression.value;
				args.Add(arg);
			}
			var result = (value as ValueFunction).Call(args, objSpace);
			if (!result) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.FunctionCall, "The function \"" + _name + "\" execute failed!");
				return ExecuteResult.Failed;
			}
			SetValue(result);
			return ExecuteResult.Successed;
		}
		public override ExecuteResult Execute(Space space) {
			return ExecuteFromInside(space, space);
		}
	}
} // namespace peak.interpreter