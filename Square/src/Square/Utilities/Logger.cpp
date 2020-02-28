#include "Square/Utilities/Logger.h"

namespace Square {

	const char* SeverityNames[NUM_SEVERITIES] = {
		"INFO", "WARNING", "ERROR", "FATAL"
	};

	LogMessage::LogMessage(Severity severtity, const char* fileName, const char* funcName, int line)
		: mSeverity(severtity), mFileName(fileName), mFuncName(funcName), mLine(line)
	{
		time_t t;
		struct tm* tmp;
		char MY_TIME[50];
		time(&t);

		tmp = localtime(&t);

		strftime(MY_TIME, sizeof(MY_TIME), "%x - %H:%M:%S", tmp);

		mTimestamp = std::string(MY_TIME);
	}

	LogMessage::~LogMessage()
	{
		Print();
	}

	void LogMessage::Print()
	{
		freopen("Log.txt", "a", stderr);
		fprintf(stderr, "%s [%s] %s : %s (%d) - '%s'\n", mTimestamp.c_str(), SeverityNames[mSeverity], mFileName, mFuncName, mLine, str().c_str());
		fclose(stderr);
	}

}