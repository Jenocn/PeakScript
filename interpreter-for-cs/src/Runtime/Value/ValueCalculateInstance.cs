/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class ValueCalculateAdd : ValueCalculateSingleton<ValueCalculateAdd> {
		public override Value Calculate(Value left, Value right) {
			if (ValueTool.IsString(left) || ValueTool.IsString(right)) {
				return (new ValueString(ValueTool.ToString(left) + ValueTool.ToString(right)));
			}
			if (ValueTool.IsNumber(left) && ValueTool.IsNumber(right)) {
				return (new ValueNumber((left as ValueNumber).value + (right as ValueNumber).value));
			}
			return null;
		}
	}
	public class ValueCalculateSub : ValueCalculateSingleton<ValueCalculateSub> {
		public override Value Calculate(Value left, Value right) {
			if (ValueTool.IsNumber(left) && ValueTool.IsNumber(right)) {
				return (new ValueNumber((left as ValueNumber).value - (right as ValueNumber).value));
			}
			return null;
		}
	}
	public class ValueCalculateMul : ValueCalculateSingleton<ValueCalculateMul> {
		public override Value Calculate(Value left, Value right) {
			if (ValueTool.IsNumber(left) && ValueTool.IsNumber(right)) {
				return (new ValueNumber((left as ValueNumber).value * (right as ValueNumber).value));
			}
			return null;
		}
	}
	public class ValueCalculateDiv : ValueCalculateSingleton<ValueCalculateDiv> {
		public override Value Calculate(Value left, Value right) {
			if (ValueTool.IsNumber(left) && ValueTool.IsNumber(right)) {
				return (new ValueNumber((left as ValueNumber).value / (right as ValueNumber).value));
			}
			return null;
		}
	}
	public class ValueCalculateMod : ValueCalculateSingleton<ValueCalculateMod> {
		public override Value Calculate(Value left, Value right) {
			if (ValueTool.IsNumber(left) && ValueTool.IsNumber(right)) {
				return (new ValueNumber((double) ((long) (left as ValueNumber).value % (long) (right as ValueNumber).value)));
			}
			return null;
		}
	}

	public class ValueCalculateSame : ValueCalculateSingleton<ValueCalculateSame> {
		public override Value Calculate(Value left, Value right) {
			return (new ValueBool(ValueTool.Equal(left, right)));

		}
	}
	public class ValueCalculateNotSame : ValueCalculateSingleton<ValueCalculateNotSame> {
		public override Value Calculate(Value left, Value right) {
			return (new ValueBool(!ValueTool.Equal(left, right)));
		}
	}
	public class ValueCalculateMore : ValueCalculateSingleton<ValueCalculateMore> {
		public override Value Calculate(Value left, Value right) {
			return (new ValueBool(ValueTool.More(left, right)));
		}
	}
	public class ValueCalculateSameOrMore : ValueCalculateSingleton<ValueCalculateSameOrMore> {
		public override Value Calculate(Value left, Value right) {
			return (new ValueBool(ValueTool.More(left, right) || ValueTool.Equal(left, right)));
		}
	}
	public class ValueCalculateLess : ValueCalculateSingleton<ValueCalculateLess> {
		public override Value Calculate(Value left, Value right) {
			return (new ValueBool(ValueTool.More(right, left)));
		}
	}
	public class ValueCalculateSameOrLess : ValueCalculateSingleton<ValueCalculateSameOrLess> {
		public override Value Calculate(Value left, Value right) {
			return (new ValueBool(ValueTool.More(right, left) || ValueTool.Equal(right, left)));
		}
	}

	public class ValueCalculateLogicAnd : ValueCalculateSingleton<ValueCalculateLogicAnd> {
		public override Value Calculate(Value left, Value right) {
			return new ValueBool(ValueTool.ToLogic(left) && ValueTool.ToLogic(right));
		}
	}
	public class ValueCalculateLogicOr : ValueCalculateSingleton<ValueCalculateLogicOr> {
		public override Value Calculate(Value left, Value right) {
			return new ValueBool(ValueTool.ToLogic(left) || ValueTool.ToLogic(right));
		}
	}
} // namespace peak.interpreter