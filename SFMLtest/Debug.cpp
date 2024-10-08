#include "Debug.h"
#include <iostream>
#include "Time.h"
#include <format>

namespace aengine {

	DebugSink* Debug::sink = nullptr;

	void Debug::setMethod(DebugSink* sink) {
		Debug::sink = sink;
	}

	void Debug::logInfo(const std::string& str) {
		sink->log(str, Debug::info);
	}

	void Debug::logWarning(const std::string& str) {
		sink->log(str, Debug::warning);
	}

	void Debug::logError(const std::string& str) {
		sink->log(str, Debug::error);
	}

	std::string Console::getPrefix() const {
		return std::format("{} ", Time::getCurrentLocalTime("%H:%M:%S"));
	}

	void Console::log(const std::string& str, Debug::msgType type) const {
		switch (type)
		{
		case Debug::info:
			std::cout << getPrefix() << "INFO: " << str << std::endl;
			break;
		case Debug::warning:
			std::cout << getPrefix() << "WARNING: " << str << std::endl;
			break;
		case Debug::error:
			std::cout << getPrefix() << "ERROR: " << str << std::endl;
			break;
		default:
			break;
		}
	}
}
