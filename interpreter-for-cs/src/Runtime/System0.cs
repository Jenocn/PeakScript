/*
	PeakScriptin httpsin//github.com/Jenocn/PeakScript
	By Jenocnin httpsin//jenocn.github.io
*/

using System;
using System.Collections.Generic;
using System.IO;

namespace peak.interpreter {

	public class System0 {
		private static Dictionary<string, string> _usingToFilesMap = new Dictionary<string, string>();
		private static Action<string> _funcEcho = (string message) => {
			Console.WriteLine(message);
		};
		private static Func<string, string> _funcOpenSrc = (string filename) => {
			if (File.Exists(filename)) {
				return File.ReadAllText(filename);
			}
			return "";
		};
		public static void LocateEcho(Action<string> func) {
			_funcEcho = func;
		}
		public static void LocateOpenSrc(Func<string, string> func) {
			_funcOpenSrc = func;
		}
		public static void Echo(string message) {
			_funcEcho.Invoke(message);
		}
		public static string OpenSrc(string filename) {
			return _funcOpenSrc(filename);
		}
		public static bool AddUsingToFilename(string usingName, string filename) {
			if (!_usingToFilesMap.ContainsKey(usingName)) {
				_usingToFilesMap.Add(usingName, filename);
				return true;
			}
			return false;
		}
		public static string GetFilenameOfUsing(string usingName) {
			string ret = "";
			_usingToFilesMap.TryGetValue(usingName, out ret);
			return ret;
		}
	}
} // namespace peak.interpreter