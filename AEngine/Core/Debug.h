#pragma once

#include <string>
#include <memory>

namespace aengine {

	class DebugSink;

	class Debug {
	public:

		/// <summary>
		/// When true allows Console to print out colorful text
		/// </summary>
		static bool useStyles;
		static bool showTime;

		/// <summary>
		/// INFO, WARNING, ERROR prefixes are always shown when set to true, otherwise always hidden
		/// </summary>
		static bool showPrefix;

		static void setDebugSink(std::unique_ptr<DebugSink> sink);

		static void logInfo(const std::string& str);
		static void logWarning(const std::string& str);
		static void logError(const std::string& str);

		/// <summary>
		/// invokes logError and throws a std::exception
		/// </summary>
		static void logException(const std::string& str);

		enum msgType {
			info,
			warning,
			error
		};

		/// <summary>
		/// ANSI sequences
		/// </summary>
		enum consoleColor {
			Black = 30,
			BrightBlack = 90,
			Red = 31,
			BrightRed = 91,
			Green = 32,
			BrightGreen = 92,
			Yellow = 33,
			BrightYellow = 93,
			Blue = 34,
			BrightBlue = 94,
			Magenta = 35,
			BrightMagenta = 95,
			Cyan = 36,
			BrightCyan = 96,
			White = 37,
			BrightWhite = 97
		};

	private:
		static std::unique_ptr<DebugSink> sink;
	};

	/// <summary>
	/// Abstract class that logs messages. Users do not specify the debug target just contents of their logs.
	/// </summary>
	class DebugSink {
	public:
		virtual void log(const std::string& str, Debug::msgType type) const = 0;

	private:
		virtual std::string getTime() const = 0;
	};

	class Console : public DebugSink {
	public:
		std::string colorify(const std::string& str, int color) const;
		void log(const std::string& str, Debug::msgType type) const override;

	private:
		std::string getTime() const override;
	};
}
