#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <optional>
#include "commonh.h"

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

		/// <summary>
		/// Removes the first unique pointer from the vector that matches the given raw pointer
		/// </summary>
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

		/// <summary>
		/// Finds the first unique pointer in the vector that satisfies the given condition and returns its raw pointer
		/// </summary>
		template <typename T>
		static T* findUniquePointerBy(const std::vector<std::unique_ptr<T>>& vec, std::function<bool(T*)> func) {
			for (int i = 0; i < vec.size(); i++) {
				if (func(vec[i].get()))
					return vec[i].get();
			}
			return nullptr;
		}

		/// <summary>
		/// Retrieves the first unique pointer in the vector and returns its raw pointer
		/// </summary>
		template <typename T>
		static T* firstUniquePointer(const std::vector<std::unique_ptr<T>>& vec) {
			return vec[0].get();
		}

		/// <summary>
		/// Retrieves the last unique pointer in the vector and returns its raw pointer
		/// </summary>
		template <typename T>
		static T* lastUniquePointer(const std::vector<std::unique_ptr<T>>& vec) {
			return vec[vec.size() - 1].get();
		}

		template <typename T>
		static T first(const std::vector<T>& vec) {
			return vec[0];
		}

		template <typename T>
		static T last(const std::vector<T>& vec) {
			return vec[vec.size() - 1];
		}

		/// <summary>
		/// Returns a vector of elements from the given vec that satisfy the condition
		/// </summary>
		template <typename T>
		static std::vector<T> where(const std::vector<T>& vec, std::function<bool(T)> func) {
			std::vector<T> out;
			for (T i : vec) {
				if (func(i))
					out.push_back(i);
			}
			return out;
		}

		template <typename T>
		static std::optional<T> findLast(const std::vector<T>& vec, std::function<bool(T)> func) {
			for (int i = vec.size() - 1; i >= 0; i--) {
				if (func(vec[i]))
					return i;
			}
			return std::nullopt;
		}

		template <typename T>
		static T min(const std::vector<T>& vec, std::function<float(T)> func) {
			int r = 0;
			float min = INF;
			for (int i = 0; i < vec.size(); i++) {
				if (float t = func(vec[i]); t < min) {
					min = t;
					r = i;
				}
			}
			return vec[r];
		}

		template <typename T>
		static T max(const std::vector<T>& vec, std::function<float(T)> func) {
			int r = 0;
			float max = -INF;
			for (int i = 0; i < vec.size(); i++) {
				if (float t = func(vec[i]); t > max) {
					max = t;
					r = i;
				}
			}
			return vec[r];
		}
	};
}