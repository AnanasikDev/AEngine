#pragma once
#include <string>
#include <sstream>

namespace aengine {
	template <typename T>
	std::string str(const T& value)
	{
		std::ostringstream ss;
		ss << value;
		return ss.str();
	}

	template <typename T>
	std::string str(const T&& value)
	{
		std::ostringstream ss;
		ss << value;
		return ss.str();
	}
}
