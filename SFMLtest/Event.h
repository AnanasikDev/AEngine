#pragma once

#include "List.h"
#include <functional>
#include <vector>

namespace aengine {

	template <typename... Args>
	class Action {
	private:

		std::vector<ActionCallback> handlers;

	public:

		Action& operator+=(const ActionCallback& callback) {
			Subscribe(callback);
			return *this;
		}

		Action& operator-=(const ActionCallback& callback) {
			Unsubscribe(callback);
			return *this;
		}

		void Subscribe(const ActionCallback& callback) {
			handlers.push_back(callback);
		}

		void Unsubscribe(const ActionCallback& callback) {
			List::Remove(handlers, callback);
		}

		void Invoke(Args... args) {
			for (const ActionCallback& h : handlers) {
				h(args...);
			}
		}
	};

	template <typename R, typename... Args>
	class Func {
	private:
		using handler = std::function<R(Args...)>;
		std::vector<handler> handlers;
	public:

		Func() = default;

		void Subscribe(const handler& func) {
			handlers.push_back(func);
		}

		void Invoke(Args... args) {
			for (const handler& h : handlers) {
				h(args...);
			}
		}
	};

	template <typename... Args>
	class ActionCallback {
	public:
		using handler = std::function<void(Args...)>;
		handler function;

		ActionCallback() = default;

		ActionCallback(const handler& action) {
			function = action;
		}
	};
}