#include "../../Headerfiles/Tools/Logger.hpp"

const std::string getString(bx::LogLevel type) {
	switch (type) {
	case bx::LogLevel::Tracing:		return "TRACING";
	case bx::LogLevel::Debugging:	return "DEBUGGING";
	case bx::LogLevel::Info:		return "INFO";
	case bx::LogLevel::Warning:		return "WARNING";
	case bx::LogLevel::Error:		return "ERROR";
	case bx::LogLevel::Fatal:		return "FATAL";
	default: return "";
	}
}

std::string getCurrentTime() {
	time_t		now = time(NULL);
	struct tm	tstruct;
	char		buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%X %d.%m.%Y", &tstruct);
	return buf;
}

bx::Logger::Logger() {}

void bx::Logger::logOnFile(LogLevel level, const std::string& message, const std::string& currentFile,
	uint lineNumber, const std::string& logFileName) {
	std::string output = getCurrentTime() + " [" + getString(level) + "]: " + message +
		"\t Appeared at " + currentFile + " in line " + std::to_string(lineNumber) + "\n";

	std::ofstream logFile(logFileName, std::ios::out | std::ios::app);
	logFile << output;
	logFile.close();
}

void bx::Logger::logOnConsole(LogLevel level, const std::string& message, const std::string& currentFile, uint lineNumber) {
	std::cerr << "[" << getString(level) << "]: " << message <<
		"\t Appeared at " + currentFile << " in line: " << lineNumber << "\n";
}

bool bx::Logger::filter(LogLevel level) {

	if (comparisonSign == "<")			{ return level < levelFilter;  }
	else if (comparisonSign == "<=")	{ return level <= levelFilter; }
	else if (comparisonSign == ">")		{ return level > levelFilter; }
	else if (comparisonSign == ">=")	{ return level >= levelFilter; }
	else if (comparisonSign == "==")	{ return level == levelFilter; }
	else if (comparisonSign == "!=")	{ return level != levelFilter; }
	else { 
		logOnConsole(LogLevel::Warning, "Passed invalid comparison sign therefore < is used", "Logger", __LINE__);
		return level < levelFilter;
	}
}

void bx::Logger::setEnableFile(bool value) {
	enableFile = value;
}

void bx::Logger::setEnableConsole(bool value) {
	enableConsole = value;
}

void bx::Logger::setFilter(const std::string& sign, LogLevel level) {
	levelFilter = level;
	comparisonSign = sign;
}

void bx::Logger::log(LogLevel level, const std::string& message, const std::string& currentFile,
	uint lineNumber, const std::string& logFileName) {

	if (!filter(level)) { return; }

	if (enableFile && logFileName != "")	{ logOnFile(level, message, currentFile, lineNumber, logFileName); }
	else if (enableConsole)					{ logOnConsole(level, message, currentFile, lineNumber); }
}
