/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	public enum SpaceType {
		None,
		Condition,
		Loop,
		Function,
		Object,
	}

	public class Space {
		public static implicit operator bool(Space value) {
			return value != null;
		}
		private SpaceType _spaceType = SpaceType.None;
		private Space _parent = null;
		private List<Space> _spaceOfUsing = new List<Space>();
		private Dictionary<string, Variable> _variables = new Dictionary<string, Variable>();

		public SpaceType spaceType { get => _spaceType; }

		public Space(SpaceType spaceType) {
			_spaceType = spaceType;
		}
		public Space(SpaceType spaceType, Space parent) {
			_spaceType = spaceType;
			_parent = parent;
		}

		public Space CopySpace() {
			Space parent = null;
			if (_parent) {
				parent = _parent.CopySpace();
			}
			var space = new Space(_spaceType, parent);
			space._spaceOfUsing = _spaceOfUsing;

			foreach (var pair in _variables) {
				var tempVariable = pair.Value;
				var tempVlaue = tempVariable.value;
				var variable = new Variable(pair.Key, tempVariable.attribute, tempVlaue ? tempVlaue.Clone() : null);
				space._variables.Add(pair.Key, variable);
			}
			return space;
		}
		public void Clear() {
			_variables.Clear();
		}

		public bool AddVariable(Variable value) {
			if (!value) {
				return false;
			}
			if (_variables.ContainsKey(value.name)) {
				ErrorLogger.LogRuntimeError(value.name);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Space, "The variable \"" + value.name + "\" is exist!");
				return false;
			}
			_variables.Add(value.name, value);
			return true;
		}
		public Variable FindVariable(string name) {
			Variable ret = null;
			if (_variables.TryGetValue(name, out ret)) {
				return ret;
			}
			foreach (var space in _spaceOfUsing) {
				ret = space.FindVariable(name);
				if (ret) {
					return ret;
				}
			}
			if (_parent) {
				return _parent.FindVariable(name);
			}
			return BuiltIn.instance.FindVariable(name);
		}
		public Variable FindVariableFromTop(string name) {
			Variable ret = null;
			if (_variables.TryGetValue(name, out ret)) {
				return ret;
			}
			return null;
		}

		public void AddSpaceOfUsing(Space space) {
			_spaceOfUsing.Add(space);
		}
	}
} // namespace peak.interpreter