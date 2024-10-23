#include "Debug.h"
#include <iostream>
#include "Time.h"
#include <format>

namespace aengine {

	std::unique_ptr<DebugSink> Debug::sink = std::unique_ptr<DebugSink>();

	bool Debug::useStyles = true;
	bool Debug::showTime = false;
	bool Debug::showPrefix = false;

	void Debug::setDebugSink(std::unique_ptr<DebugSink> sink) {
		
		Debug::sink = std::move(sink);
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

	void Debug::logException(const std::string& str) {
		logError(str);
		throw std::exception(str);
	}

	std::string Console::getTime() const {
		return std::format("{} ", Time::getCurrentLocalTime("%H:%M:%S"));
	}

	std::string Console::colorify(const std::string& str, int color) const {
		return "\033[" + std::to_string(color) + "m" + str + "\033[" + std::to_string(Debug::White) + "m";
	}

	void Console::log(const std::string& str, Debug::msgType type) const {
		switch (type)
		{
		case Debug::info:
			std::cout << (Debug::showTime ? getTime() : "") << str << std::endl;
			break;
		case Debug::warning:
			std::cout << colorify((Debug::showTime ? getTime() : "") + (Debug::showPrefix ? "Warning: " : "") + str, Debug::Yellow) << std::endl;
			break;
		case Debug::error:
			std::cout << colorify((Debug::showTime ? getTime() : "") + (Debug::showPrefix ? "Error: " : "") + str, Debug::BrightRed) << std::endl;
			break;
		default:
			break;
		}
	}
}
