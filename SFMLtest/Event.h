#pragma once

#include "List.h"
#include <functional>
#include <vector>

namespace aengine {

	using backdrop = unsigned int;

	template <typename... Args>
	class Action {
	private:

		using handler = std::function<void(Args...)>;
		std::vector<handler> handlers;

	public:

		/// <summary>
		/// If no later unsubscription needed it can be used directly as
		/// myEvent.Subscribe(myFunction);
		/// Otherwise, for later unsubscription the return value must be 
		/// stored like so:
		/// this->myEventBackdrop = myEvent.Subscribe(myFunction);
		/// ...
		/// myEvent.Unsubscribe(this->myEventBackdrop);
		/// 
		/// Lambdas (anonymous functions) CAN also be subscribed and unsubscribed
		/// just like any other function, like so:
		/// myEvent.Subscribe([this](){ this->myMethod(); });
		/// </summary>
		/// <param name="func">Any kind of function (lambda, named function or method) that matches the template</param>
		/// <returns></returns>
		backdrop Subscribe(const handler& func) {
			handlers.push_back(func);
			return handlers.size() - 1;
		}

		/// <summary>
		/// Unsubscribes function (callback) from this event by function id
		/// (its index in the handlers list).
		/// </summary>
		/// <param name="id">ID of the desired function to unsubscribe. Unsigned Int = Backdrop</param>
		void Unsubscribe(const backdrop id) {
			// TODO: WHEN PREVIOUSLY SUBSCRIBED FUNCTIONS ARE UNSUBSCRIBED, THE INDEX OF THIS IS WRONG. NEEDS A FIX (MAP)
			List::RemoveAt(handlers, id);
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