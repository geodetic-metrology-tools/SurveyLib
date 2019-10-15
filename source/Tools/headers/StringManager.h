/*
� Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef STRING_MANAGER
#define STRING_MANAGER

#include <locale>
#include <string>
#include <vector>

#if defined(__linux__) || defined(__APPLE__)
	#include <unistd.h>
	#define GetCurrentDir getcwd
	#define slash "/"
#else
	#include <direct.h>
	#define GetCurrentDir _getcwd
	#define slash "\\"
#endif


bool isDelim(const char c, const char* delims, int ndelims);

// tokenizes a line by removing delimiters and stores non-delimiter words as separate strings.
// The asterisk is considered to be a separate token and is thus stored in a different field as the keyword itself.
// Parsing stops on a comment sign, the comment is then stored as a single token including the comment character.
std::vector<std::string> const tokenizefileString(const std::string& str);

//Replace a caracter, "occ", by another, "newChar", in the string "path"
std::string replace(const std::string& path, char occ, const std::string& newChar);

//Replace a caracter, "occ", by another, "newChar", in the wild string "path"
std::wstring replace(const std::wstring& path, wchar_t occ, const std::wstring& newChar);

inline std::wstring toWStr(const std::string& str) { return std::wstring(str.begin(), str.end()); }

inline std::string toStr(const std::wstring& str) { return std::string(str.begin(), str.end()); }

/** Returns true if the file exist & is readable **/
bool exist(std::wstring const& filename);

/** @return a copy of the string with all whitespaces on the left removed */
std::string ltrim(std::string str);

/** @return a copy of the string with all whitespaces on the right removed */
std::string rtrim(std::string str);

/** @return a copy of the string with all whitespaces on the sides removed */
inline std::string trim(std::string str) { return rtrim(std::move(ltrim(std::move(str)))); }

/** @return a vector of strings, representing the splitted version of the input based on the given split character */
std::vector<std::string> split(const std::string& base, char c = ' ');

/** @return true if the given character is considered as a space */
template <class charT>
inline bool isSpace(charT c) { return std::isspace(c, std::locale()); }

#endif // STRING_MANAGER
