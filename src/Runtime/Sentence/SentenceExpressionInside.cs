/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	public class SentenceExpressionInside : SentenceExpression {
		private SentenceExpression _header = null;
		private List<SentenceExpression> _insides = null;
		public SentenceExpressionInside(SentenceExpression header, List<SentenceExpression> insides) {
			_header = header;
			_insides = insides;
		}
		public override ExpressionType GetExpressionType() { return ExpressionType.Inside; }
		public override ExecuteResult Execute(Space space) {
			if (!Sentence.IsSuccess(_header.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Inside, "The header expression execute failed!");
				return ExecuteResult.Failed;
			}
			var headerValue = _header.value;
			if (!ValueTool.IsObject(headerValue)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Inside, "The header expression isn't a object!");
				return ExecuteResult.Failed;
			}
			var tempValue = headerValue;
			foreach (var expression in _insides) {
				if (!ValueTool.IsObject(tempValue)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Inside, "The expression isn't a object!");
					return ExecuteResult.Failed;
				}
				var objSpace = (tempValue as ValueObject).space;
				var expType = expression.GetExpressionType();
				var executeRet = ExecuteResult.Failed;
				if (expType == ExpressionType.Function) {
					executeRet = (expression as SentenceExpressionFunctionCall).ExecuteFromInside(objSpace, space);
				} else {
					executeRet = expression.Execute(objSpace);
				}
				if (!Sentence.IsSuccess(executeRet)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Inside, "The inside expression execute failed!");
					return ExecuteResult.Failed;
				}
				tempValue = expression.value;
			}
			SetValue(tempValue);
			return ExecuteResult.Successed;
		}

	}

} // namespace peak.interpreter