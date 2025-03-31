/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

using System.Collections.Generic;

namespace peak.interpreter {

	public class ModulePool {
		private static ModulePool _instance = new ModulePool();
		public static ModulePool instance { get => _instance; }
		private Executer _CreateExecuter(string filename) {
			var src = System0.OpenSrc(filename);
			if (!string.IsNullOrEmpty(src)) {
				var ret = Executer.Create(src);
				if (ret != null) {
					return ret;
				}
			}
			foreach (var dir in _searchDirs) {
				var src1 = System0.OpenSrc(dir + filename);
				if (!string.IsNullOrEmpty(src1)) {
					var ret = Executer.Create(src1);
					if (ret != null) {
						return ret;
					}
				}
			}
			return null;
		}

		private Dictionary<string, string> _moduleToFilesMap = new Dictionary<string, string>();
		private Dictionary<string, Module> _modulesMap = new Dictionary<string, Module>();
		private HashSet<string> _searchDirs = new HashSet<string>();

		public void AddSearchDir(string dir) {
			if (!_searchDirs.Contains(dir)) {
				_searchDirs.Add(dir);
			}
		}
		public void RemoveSearchDir(string dir) {
			if (_searchDirs.Contains(dir)) {
				_searchDirs.Remove(dir);
			}
		}

		public bool AddModule(string moduleName, Module module) {
			if (!_modulesMap.ContainsKey(moduleName)) {
				_modulesMap.Add(moduleName, module);
				return true;
			}
			return false;
		}
		public void RemoveModule(string moduleName) {
			_modulesMap.Remove(moduleName);
		}
		public bool AddModuleFilename(string moduleName, string filename) {
			if (!_moduleToFilesMap.ContainsKey(moduleName)) {
				_moduleToFilesMap.Add(moduleName, filename);
				return true;
			}
			return false;
		}

		public Module UseModule(string moduleName) {
			// exists module
			do {
				if (!_modulesMap.TryGetValue(moduleName, out var module)) {
					break;
				}
				if (module == null) {
					RemoveModule(moduleName);
					break;
				}
				if (!module.IsExecuted()) {
					if (!module.Execute()) {
						RemoveModule(moduleName);
						break;
					}
				}
				return module;
			} while (false);

			// create new module
			var executer = _CreateExecuter(moduleName);

			if (executer == null) {
				if (_moduleToFilesMap.TryGetValue(moduleName, out var filename)) {
					executer = _CreateExecuter(filename);
				}

				if (executer == null) {
					return null;
				}
			}

			var ret = new Module(moduleName, executer);
			if (ret.Execute()) {
				_modulesMap.Add(moduleName, ret);
			} else {
				ret = null;
			}

			return ret;
		}
	}

} // namespace peak.interpreter