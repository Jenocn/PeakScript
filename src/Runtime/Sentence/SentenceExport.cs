/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class SentenceExport : Sentence {
		private string _moduleName = "";
		public SentenceExport(string moduleName) {
			_moduleName = moduleName;
		}

		public override ExecuteResult Execute(Space space) {
			if (space.spaceType != SpaceType.None) {
				ErrorLogger.LogRuntimeError(_moduleName);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Export, "The module \"" + _moduleName + "\" can't export here!");
				return ExecuteResult.Failed;
			}
			if (!space.SetExportModule(_moduleName)) {
				ErrorLogger.LogRuntimeError(_moduleName);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Export, "The module \"" + _moduleName + "\" already export!");
				return ExecuteResult.Failed;
			}
			var module = new Module(_moduleName, space);
			if (!ModulePool.instance.AddModule(_moduleName, module)) {
				ErrorLogger.LogRuntimeError(_moduleName);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Export, "The module \"" + _moduleName + "\" already exists!");
				return ExecuteResult.Failed;
			}
			return ExecuteResult.Successed;
		}

	}

} // namespace peak.interpreter