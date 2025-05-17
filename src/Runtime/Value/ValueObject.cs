/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter
{

	public class ValueObject : TypeValue<ValueObject>
	{
		private Space _space = null;
		public Space space { get => _space; }
		public ValueObject(Space usingSpace = null, ValueObject parent = null)
		{
			Space parentSpace = parent ? parent.space.CopySpace() : null;
			_space = new Space(SpaceType.Object, parentSpace);
			if (usingSpace)
			{
				_space.AddSpaceOfUsing(usingSpace);
			}
		}
		public override string ToString()
		{
			string ret = "object { ";
			var variables = _space.variables;
			int index = 0;
			foreach (var item in variables)
			{
				ret += item.Value.name;
				ret += "=";
				ret += item.Value.value.ToString();
				if (index < variables.Count - 1)
				{
					ret += ", ";
				}
				index += 1;
			}
			ret += " }";
			return ret;
		}
		public override Value Clone()
		{
			return new ValueObject(_space.CopySpace());
		}
	}
} // namespace peak.interpreter