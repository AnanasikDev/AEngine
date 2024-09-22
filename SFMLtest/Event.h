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
		template <typename TThisPtr>
		std::vector<std::function<void(TThisPtr, Args...)>> handlers2;

	public:

		Action& operator+=(const handler& func) {
			Subscribe(func);
			return *this;
		}

		Action& operator-=(const handler& func) {
			Unsubscribe(func);
			return *this;
		}

		void Subscribe(const handler& func) {
			handlers.push_back(func);
		}

		void Unsubscribe(const handler& func) {
			for (int i = 0; i < handlers.size(); i++) {

				auto hash1 = static_cast<const void (*)(Args...)>(&handlers[i]);
				auto hash2 = static_cast<const void (*)(Args...)>(&func);

				if (hash1 == hash2) {
					List::RemoveAt(handlers, i);
					return;
				}
			}
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