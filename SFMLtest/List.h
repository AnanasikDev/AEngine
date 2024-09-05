#include <vector>

namespace aengine {
	class List {
	public:
		template <typename T>
		static void Remove(std::vector<T>& vec, T obj) {
			auto it = std::find(vec.begin(), vec.end(), obj);
			if (it != vec.end()) {
				vec.erase(it);
			}
		}
	};
}