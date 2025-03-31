using System.Collections.Generic;

namespace peak.interpreter {
	public class ExpressionVariableAnalysisName : IExpressionVariableAnalysis {
		private string _name;
		public ExpressionVariableAnalysisName(string name) {
			_name = name;
		}
		public Variable Execute(Space space) {
			var ret = space.FindVariable(_name);
			if (!ret) {
				ErrorLogger.LogRuntimeError(_name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableNameAnalysis, "The variable \"" + _name + "\" not found!");
			}
			return ret;
		}
		public void SetName(string name) {
			_name = name;
		}
	}

	public class ExpressionVariableAnalysisArrayItem : IExpressionVariableAnalysis {

		private SentenceExpression _valueExpression = null;
		private List<SentenceExpression> _indexExpressionVec = null;
		public ExpressionVariableAnalysisArrayItem(SentenceExpression valueExpression, List<SentenceExpression> indexExpressionVec) {
			_valueExpression = valueExpression;
			_indexExpressionVec = indexExpressionVec;
		}
		public Variable Execute(Space space) {
			if (!Sentence.IsSuccess(_valueExpression.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableArrayItemAnalysis, "The expression execute failed!");
				return null;
			}
			var retValue = _valueExpression.value;
			Variable retVariable = null;

			var expressionVecSize = _indexExpressionVec.Count;
			for (var i = 0; i < expressionVecSize; ++i) {
				if (!ValueTool.IsArray(retValue)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableArrayItemAnalysis, "The result of expression isn't a array!");
					return null;
				}
				var arr = (retValue as ValueArray).value;
				var expression = _indexExpressionVec[i];
				if (!Sentence.IsSuccess(expression.Execute(space))) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableArrayItemAnalysis, "The expression execute failed!");
					return null;
				}
				var indexValue = expression.value;
				if (!ValueTool.IsInteger(indexValue)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableArrayItemAnalysis, "The index isn't a integer value!");
					return null;
				}
				var index = (int) ((indexValue as ValueNumber).value);
				if (index >= arr.Count) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableArrayItemAnalysis, "The index out of range!");
					return null;
				}
				retVariable = arr[index];
				if (!retVariable) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableArrayItemAnalysis, "The array value is invalid!");
					return null;
				}
				retValue = retVariable.value;
			}

			return retVariable;
		}
	}

	public class ExpressionVariableAnalysisInside : IExpressionVariableAnalysis {
		private SentenceExpression _header = null;
		private List<SentenceExpression> _insides = null;
		public ExpressionVariableAnalysisInside(SentenceExpression header, List<SentenceExpression> insides) {
			_header = header;
			_insides = insides;
		}
		public Variable Execute(Space space) {
			if (!Sentence.IsSuccess(_header.Execute(space))) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableInsideAnalysis, "The header expression execute failed!");
				return null;
			}
			var headerValue = _header.value;
			if (!ValueTool.IsObject(headerValue)) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableInsideAnalysis, "The header expression isn't a object!");
				return null;
			}
			var tempValue = headerValue;
			Variable retVariable = null;
			foreach (var expression in _insides) {
				if (!ValueTool.IsObject(tempValue)) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableInsideAnalysis, "The expression isn't a object!");
					return null;
				}
				var objSpace = (tempValue as ValueObject).space;
				if (expression.GetExpressionType() != ExpressionType.Variable) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableInsideAnalysis, "The inside expression can't return a variable!");
					return null;
				}
				if (!Sentence.IsSuccess(expression.Execute(objSpace))) {
					ErrorLogger.LogRuntimeError(ErrorRuntimeCode.VariableInsideAnalysis, "The inside expression execute failed!");
					return null;
				}
				retVariable = (expression as SentenceExpressionVariable).variable;
				tempValue = expression.value;
			}
			return retVariable;
		}
	}

} // namespace peak.interpreter