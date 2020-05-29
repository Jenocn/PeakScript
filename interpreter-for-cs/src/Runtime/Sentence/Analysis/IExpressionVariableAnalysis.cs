/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {
	public interface IExpressionVariableAnalysis {
		Variable Execute(Space space);
	}
} // namespace peak.interpreter