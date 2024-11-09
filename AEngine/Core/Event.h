#pragma once

#include <functional>
#include <vector>
#include <map>

namespace aengine {

	/// <summary>
	/// Integer representing ID of a callback function, unique to a specific Event object. At the moment of subscription equals the total number of callbacks ever subscribed to the specific event. If stored, backdrop value from subscription can be used to unsubscribe the callback function from the event.
	/// </summary>
	using backdrop = unsigned int;

	template <typename... Args>
	class Action {
	private:

		using handler = std::function<void(Args...)>;

		std::map<backdrop, handler> handlers;
		backdrop nextBackdrop = 0;

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
			handlers[nextBackdrop] = func;
			nextBackdrop++;
			return nextBackdrop - 1;
		}

		/// <summary>
		/// Unsubscribes function (callback) from this event by function id
		/// (its index in the handlers list).
		/// </summary>
		/// <param name="id">ID of the desired function to unsubscribe. Unsigned Int = Backdrop</param>
		void Unsubscribe(const backdrop id) {
			handlers.erase(id);
		}

		void Invoke(Args... args) {
			for (std::pair<const backdrop, handler> h : handlers) {
				h.second(args...);
			}
		}
	};

	template <typename R, typename... Args>
	class Func {
	private:

		using handler = std::function<R(Args...)>;

		std::map<backdrop, handler> handlers;
		backdrop nextBackdrop = 0;

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
			handlers[nextBackdrop] = func;
			nextBackdrop++;
			return nextBackdrop - 1;
		}

		/// <summary>
		/// Unsubscribes function (callback) from this event by function id
		/// (its index in the handlers list).
		/// </summary>
		/// <param name="id">ID of the desired function to unsubscribe. Unsigned Int = Backdrop</param>
		void Unsubscribe(const backdrop id) {
			handlers.erase(id);
		}

		void Invoke(Args... args) {
			for (std::pair<const backdrop, handler> h : handlers) {
				h.second(args...);
			}
		}
	};
}