#pragma once

namespace aengine {
	class Component {
	public:
		/// <summary>
		/// Statically converts without checks this component to other via raw pointer.
		/// </summary>
		/// <typeparam name="R"></typeparam>
		/// <returns></returns>
		template <typename R>
		R* to() {
			return static_cast<R*>(this);
		}
	};
}
