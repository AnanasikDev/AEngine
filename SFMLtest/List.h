#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <optional>

namespace aengine {
	class List {
	public:
		template <typename T>
		static void remove(std::vector<T>& vec, T obj) {
			auto it = std::find(vec.begin(), vec.end(), obj);
			if (it != vec.end()) {
				vec.erase(it);
			}
		}

		template <typename T>
		static void removeIf(std::vector<T>& vec, std::function<bool(T)> condition) {
			for (int i = 0; i < vec.size(); i++) {
				if (condition(vec[i]))
				{
					removeAt(vec, i);
					return;
				}
			}
		}

		template <typename T>
		static void removeSmartPtr(std::vector<std::unique_ptr<T>>& vec, T* obj) {
			for (int i = 0; i < vec.size(); i++) {
				if (vec[i].get() == obj)
				{
					removeAt(vec, i);
					return;
				}
			}
		}

		template <typename T>
		static void removeAt(std::vector<T>& vec, int index) {
			vec.erase(vec.begin() + index);
		}

		template <typename T>
		static bool contains(const std::vector<T>& vec, T obj) {
			auto it = std::find(vec.begin(), vec.end(), obj);
			return it != vec.end();
		}

		template <typename T>
		static std::optional<T> find(const std::vector<T>& vec, const T& obj) {
			auto it = std::find(vec.begin(), vec.end(), obj);
			return *it;
		}

		template <typename T>
		static std::optional<T> findBy(const std::vector<T>& vec, std::function<bool(const T&)> func) {
			for (int i = 0; i < vec.size(); i++) {
				if (func(vec[i]))
					return vec[i];
			}
			return std::nullopt;
		}

		template <typename T>
		static T* findUniquePointerBy(const std::vector<std::unique_ptr<T>>& vec, std::function<bool(const T&)> func) {
			for (int i = 0; i < vec.size(); i++) {
				if (func(vec[i]))
					return vec[i].get();
			}
			return nullptr;
		}
	};
}