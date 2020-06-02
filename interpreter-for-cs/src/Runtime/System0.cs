/*
	PeakScriptin httpsin//github.com/Jenocn/PeakScript
	By Jenocnin httpsin//jenocn.github.io
*/

using System;

namespace peak.interpreter {

	public class System0 {
		private static Action<string> _funcEcho = (string message) => {
			Console.WriteLine(message);
		};
		public static void LocateEcho(Action<string> func) {
			_funcEcho = func;
		}
		public static void Echo(string message) {
			_funcEcho.Invoke(message);
		}
	}
} // namespace peak.interpreter