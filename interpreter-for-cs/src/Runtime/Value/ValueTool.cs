/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {
	public class ValueTool {
		public static readonly Dictionary<int, string> TypeStringMap = new Dictionary<int, string>() {
			{ ValueNull.VALUE_TYPE, "null" },
			{ ValueBool.VALUE_TYPE, "bool" },
			{ ValueArray.VALUE_TYPE, "array" },
			{ ValueString.VALUE_TYPE, "string" },
			{ ValueNumber.VALUE_TYPE, "number" },
			{ ValueFunction.VALUE_TYPE, "function" },
			{ ValueObject.VALUE_TYPE, "object" },
		};
		public static bool IsNull(Value value) {
			return !value || (value.GetValueType() == ValueNull.VALUE_TYPE);
		}
		public static bool IsBool(Value value) {
			return value && (value.GetValueType() == ValueBool.VALUE_TYPE);
		}
		public static bool IsNumber(Value value) {
			return value && (value.GetValueType() == ValueNumber.VALUE_TYPE);
		}
		public static bool IsString(Value value) {
			return value && (value.GetValueType() == ValueString.VALUE_TYPE);
		}
		public static bool IsFunction(Value value) {
			return value && (value.GetValueType() == ValueFunction.VALUE_TYPE);
		}
		public static bool IsArray(Value value) {
			return value && (value.GetValueType() == ValueArray.VALUE_TYPE);
		}
		public static bool IsObject(Value value) {
			return value && (value.GetValueType() == ValueObject.VALUE_TYPE);
		}
		public static string ToString(Value value) {
			if (!value) {
				return ValueNull.DEFAULT_VALUE.ToString();
			}
			return value.ToString();
		}
		public static string ToTypeString(Value value) {
			if (!value) {
				return ToTypeString(ValueNull.DEFAULT_VALUE);
			}
			string ret = "";
			if (TypeStringMap.TryGetValue(value.GetValueType(), out ret)) {
				return ret;
			}
			return "";
		}
		public static bool ToLogic(Value value) {
			if (IsNull(value)) {
				return false;
			}
			if (IsNumber(value)) {
				return (value as ValueNumber).value != 0;
			}
			if (IsBool(value)) {
				return (value as ValueBool).value;
			}
			return true;
		}
		public static bool Equal(Value a, Value b) {
			if (a.GetValueType() != b.GetValueType()) {
				return false;
			}
			if (IsBool(a)) {
				return (a as ValueBool).value == (b as ValueBool).value;
			}
			if (IsNumber(a)) {
				return (a as ValueNumber).value == (b as ValueNumber).value;
			}
			if (IsString(a)) {
				return (a as ValueString).value == (b as ValueString).value;
			}
			if (IsNull(a)) {
				return true;
			}
			return false;
		}
		public static bool More(Value a, Value b) {
			if (a.GetValueType() != b.GetValueType()) {
				return false;
			}
			if (IsNumber(a)) {
				return (a as ValueNumber).value > (b as ValueNumber).value;
			}
			return false;
		}
		public static bool IsInteger(Value value) {
			if (!IsNumber(value)) {
				return false;
			}
			var d = (value as ValueNumber).value;
			var ll = (long) d;
			return ((double) ll) == d;
		}
	}
} // namespace peak.interpreter