#pragma once

#include <string>
#include <sstream>
#include <ctime>  
#include <chrono>

#include "Square/Core/Core.h"

namespace Square {

	enum Severity {
		INFO = 0,
		WARNING = 1,
		ERROR = 2,
		FATAL = 3,
		NUM_SEVERITIES
	};

	class SQUARE_API LogMessage : public std::ostringstream
	{
	public:
		LogMessage(Severity severity, const char* fileName, const char* funcName, int line);
		~LogMessage();

	protected:
		void Print();

	private:
		Severity mSeverity;
		std::string mTimestamp;
		const char* mFileName;
		const char* mFuncName;
		int mLine;
	};

#define LOG_INFO Square::LogMessage(Square::INFO, __FILE__, __FUNCTION__, __LINE__).flush()
#define LOG_WARNING Square::LogMessage(Square::WARNING, __FILE__, __FUNCTION__, __LINE__).flush()
#define LOG_ERROR Square::LogMessage(Square::ERROR, __FILE__, __FUNCTION__, __LINE__).flush()
#define LOG_FATAL Square::LogMessage(Square::FATAL, __FILE__, __FUNCTION__, __LINE__).flush()
#define LOG(severity) LOG_##severity

}