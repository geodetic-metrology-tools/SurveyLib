#ifndef SURVEYLIB_VERSION_H
#define SURVEYLIB_VERSION_H

#include <string>
#include <cstdio>
#include <StringManager.h>

#define SurveyLib_VERSION_MAJOR 3
#define SurveyLib_VERSION_MINOR 5
#define SurveyLib_VERSION_PATCH 0

static std::wstring getSurveyLibVersion(void) {
	static char str[128];
	_snprintf(str, 128, "v%d.%02d.%02d", SurveyLib_VERSION_MAJOR, SurveyLib_VERSION_MINOR, SurveyLib_VERSION_PATCH);
	return toWStr(std::string(str));
}

#endif
