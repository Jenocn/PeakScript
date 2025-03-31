/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	class SentenceExpressionValueArray : SentenceExpression {
		private List<SentenceExpression> _expressionArray = null;
		public SentenceExpressionValueArray(List<SentenceExpression> valueExpressionArray) {
			_expressionArray = valueExpressionArray;
		}
		public override ExecuteResult Execute(Space space) {
			var valueArray = new ValueArray();
			if (_expressionArray.Count != 0) {
				valueArray.Reserve(_expressionArray.Count);
				for (var i = 0; i < _expressionArray.Count; ++i) {
					var expression = _expressionArray[i];
					if (!IsSuccess(expression.Execute(space))) {
						ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Array, "The array execute failed!");
						return ExecuteResult.Failed;
					}
					var value = expression.value;
					valueArray.EmplaceBack(value);
				}
			}
			SetValue(valueArray);
			return ExecuteResult.Successed;
		}
	}
} // namespace peak.interpreter