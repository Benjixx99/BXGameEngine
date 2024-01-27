#pragma once

#include "../Common/PrimitiveDatatypes.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

namespace bx {

	enum class LogLevel : uchar {
		Tracing,
		Debugging,
		Info,
		Warning,
		Error,
		Fatal
	};

	class Logger {
		LogLevel levelFilter = LogLevel::Error;
		std::string comparisonSign = "<";
		bool enableFile = true;
		bool enableConsole = true;
		
		Logger();
		void logOnFile(LogLevel level, const std::string& message,
			const std::string& currentFile, uint lineNumber, const std::string& logFileName);
		
		void logOnConsole(LogLevel level, const std::string& message, 
			const std::string& currentFile, uint lineNumber);

		bool filter(LogLevel level);
	public:
		Logger(Logger const&) = delete;
		void operator=(Logger const&) = delete;

		static Logger& get() {
			static Logger object;
			return object;
		}

		void setEnableFile(bool value);
		void setEnableConsole(bool value);
		void setFilter(const std::string& comparisonSign, LogLevel levelFilter);
		void log(LogLevel level, const std::string& message, const std::string& currentFile,
			uint lineNumber, const std::string& logFileName = "");
	};
}