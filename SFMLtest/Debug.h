#pragma once

#include <string>
#include <memory>

namespace aengine {

	class DebugSink;

	class Debug {
	public:

		static void setMethod(std::unique_ptr<DebugSink> sink);

		static void logInfo(const std::string& str);
		static void logWarning(const std::string& str);
		static void logError(const std::string& str);

		enum msgType {
			info,
			warning,
			error
		};
	private:
		static std::unique_ptr<DebugSink> sink;
	};

	/// <summary>
	/// Abstract class that logs messages. Users do not know specify the debug target just contents of their logs.
	/// </summary>
	class DebugSink {
	public:
		virtual void log(const std::string& str, Debug::msgType type) const = 0;

	private:
		virtual std::string getPrefix() const = 0;
	};

	class Console : public DebugSink {
	public:
		void log(const std::string& str, Debug::msgType type) const override;

	private:
		std::string getPrefix() const override;
	};
}
