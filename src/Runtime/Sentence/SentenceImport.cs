/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

namespace peak.interpreter {

	public class SentenceImport : Sentence {
		private string _moduleName = "";
		public SentenceImport(string moduleName) {
			_moduleName = moduleName;
		}
		public override ExecuteResult Execute(Space space) {
			if (space.spaceType != SpaceType.None) {
				ErrorLogger.LogRuntimeError(_moduleName);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Import, "The module \"" + _moduleName + "\" can't import here!");
				return ExecuteResult.Failed;
			}
			var module = ModulePool.instance.UseModule(_moduleName);
			if (module == null) {
				ErrorLogger.LogRuntimeError(_moduleName);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Import, "The module \"" + _moduleName + "\" not found!");
				return ExecuteResult.Failed;
			}
			if (!space.UseModule(module)) {
				ErrorLogger.LogRuntimeError(_moduleName);
				ErrorLogger.LogRuntimeError(ErrorRuntimeCode.Import, "The module \"" + _moduleName + "\" already exists!");
				return ExecuteResult.Failed;
			}
			return ExecuteResult.Successed;
		}

	}

} // namespace peak.interpreter