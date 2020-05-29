/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public enum ExpressionType {
		None,
		Math,
		SelfAssign,
		Variable,
		Function,
		DoubleSymbol,
		Not,
		New,
		Inside,
	}

	public class SentenceExpression : Sentence {
		private Value _value = null;

		public Value value { get => _value; }

		public SentenceExpression() {}
		public SentenceExpression(Value value) {
			_value = value;
		}
		public virtual ExpressionType GetExpressionType() { return ExpressionType.None; }
		public override ExecuteResult Execute(Space space) {
			if (!_value) {
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Expression, "The value is null!");
				return ExecuteResult.Failed;
			}
			return ExecuteResult.Successed;
		}

		protected void SetValue(Value value) {
			_value = value;
		}

	}
} // namespace peak.interpreter