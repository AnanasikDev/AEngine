#pragma once

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

		template <typename T>
		static void RemoveAt(std::vector<T>& vec, int index) {
			vec.erase(vec.begin() + index);
		}

		template <typename T>
		static bool Contains(std::vector<T>& vec, T obj) {
			auto it = std::find(vec.begin(), vec.end(), obj);
			return it != vec.end();
		}
	};
}