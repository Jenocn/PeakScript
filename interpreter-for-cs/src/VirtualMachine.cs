/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System;

namespace peak {
	using interpreter;
	public class VirtualMachine {
		public static VirtualJourney Load(string src, Space parent = null) {
			var parseData = ParseTool.Load(src);
			if (!parseData.bSuccess) {
				return null;
			}
			return new VirtualJourney(parseData.sentenceList, parent);
		}
		public static VirtualJourney LoadFile(string filename, Space parent = null) {
			var src = VirtualTool.OpenFile(filename);
			return Load(src, parent);
		}
		public static void LocateLogger(Action<string> logger) {
			LocateLogger(logger, logger);
		}
		public static void LocateLogger(Action<string> echo, Action<string> errorLogger) {
			System0.LocateEcho(echo);
			ErrorLogger.Locate(errorLogger);
		}
	}
} // namespace peak