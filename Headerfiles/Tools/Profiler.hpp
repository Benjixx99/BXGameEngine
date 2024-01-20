#pragma once

#include <fstream>
#include <chrono>
#include <mutex>
#include <algorithm>

#define PROFILING 1
#ifdef PROFILING
	#define PROFILE_SCOPE(name) ProfileTimer##__LINE__(name)
	#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
	#define PROFILE_SCOPE(name)
	#define PROFILE_FUNCTION()
#endif // PROFILING

namespace bx {

	namespace time {
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		using Clock = std::chrono::high_resolution_clock;
		using Microsec = std::chrono::microseconds;
	}

	struct ProfileResult {
		std::string name = "Default";
		size_t start = 0;
		size_t end = 0;
		size_t threadID = 0;
	};

	class Profiler {
		std::string outputFile = "result.json";
		std::ofstream outputStream;
		std::mutex lock;
		size_t profileCount = 0;

		Profiler() {
			outputStream = std::ofstream(outputFile);
			writeHeader();
		}
		void writeHeader() { outputStream << "{\"otherData\": {},\"traceEvents\":["; }
		void writeFooter() { outputStream << "]}"; }

	public:
		~Profiler() { writeFooter(); }
		
		static Profiler& instance() {
			static Profiler instance;
			return instance;
		}
		
		void writeProfile(const ProfileResult& result) { 
			std::lock_guard<std::mutex> lock(lock);

			if (profileCount++ > 0) { outputStream << ","; }

			std::replace(result.name.begin(), result.name.end(), '"', '\'');

			outputStream << "\n{";
			outputStream << "\"cat\":\"function\",";
			outputStream << "\"dur\":" << (result.end - result.start) << ",";
			outputStream << "\"name\":\"" << result.name << "\",";
			outputStream << "\"ph\":\"X\",";
			outputStream << "\"pid\":0,";
			outputStream << "\"tid\":" << result.threadID << ",";
			outputStream << "\"ts\":" << result.start;
			outputStream << "}";
		}
	};

	class ProfileTimer {
		ProfileResult result;
		time::TimePoint startPoint;
		bool stopped = false;
	public:
		ProfileTimer(const std::string& name) {
			result.name = name;
			start();
		}
		~ProfileTimer() { stop(); }
		void start() { 
			static size_t lastStartTime = 0;

			startPoint = time::Clock::now(); 
			result.start = std::chrono::time_point_cast<time::Microsec>(startPoint).time_since_epoch().count();
			result.start += (result.start == lastStartTime ? 1 : 0);
			lastStartTime = result.start;
			
			stopped = false;
		}
		void stop() {
			if (stopped) { return; }

			auto endPoint = time::Clock::now();
			result.end = std::chrono::time_point_cast<time::Microsec>(endPoint).time_since_epoch().count();
			result.threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Profiler::instance().writeProfile(result);
			
			stopped = true;
		}
	};
}