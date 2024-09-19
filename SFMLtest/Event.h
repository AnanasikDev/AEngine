#pragma once

#include "List.h"
#include <functional>
#include <vector>

namespace aengine {

	template <typename... Args>
	class Action {
	private:

		using handler = std::function<void(Args...)>;
		std::vector<handler> handlers;

	public:

		Action& operator+=(const handler& handler) {
			Subscribe(handler);
			return *this;
		}

		Action& operator-=(const handler& handler) {
			Unsubscribe(handler);
			return *this;
		}

		void Subscribe(const handler& func) {
			handlers.push_back(func);
		}

		void Unsubscribe(const handler& func) {
			List::Remove(handlers, func);
		}

		void Invoke(Args... args) {
			for (const handler& h : handlers) {
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
}