/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System;

namespace peak {
	using interpreter;
	public class VirtualMachine {
		public static ModulePool modulePool { get => ModulePool.instance; }
		public static VirtualJourney Load(string src) {
			var executer = Executer.Create(src);
			if (executer != null) {
				return new VirtualJourney(executer);
			}
			return null;
		}
		public static VirtualJourney LoadFile(string filename) {
			var src = VirtualTool.OpenSrc(filename);
			return Load(src);
		}
		public static void LocateLogger(Action<string> logger) {
			LocateLogger(logger, logger);
		}
		public static void LocateLogger(Action<string> echo, Action<string> errorLogger) {
			System0.LocateEcho(echo);
			ErrorLogger.Locate(errorLogger);
		}
		public static void LocateOpenSrc(Func<string, string> func) {
			System0.LocateOpenSrc(func);
		}
	}
} // namespace peak