/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.IO;

namespace peak {
	public class VirtualTool {
		public static string OpenFile(string filename) {
			if (!File.Exists(filename)) {
				return "";
			}
			return File.ReadAllText(filename);
		}
	}
} // namespace peak