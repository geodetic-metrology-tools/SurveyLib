#ifndef STRING_MANAGER
#define STRING_MANAGER

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef __linux__    
	#include <unistd.h>
    #define GetCurrentDir getcwd
	#define slash "/"
#else
    #include <direct.h>
    #define GetCurrentDir _getcwd
	#define slash "\\"
#endif

namespace
{
	std::string getCurrentDirectory() { 
	
		char cCurrentPath[FILENAME_MAX];
		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
			return "";
		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

		return std::string(cCurrentPath);
	}

	inline bool isDelim(const char c, const char* delims, int ndelims) {
		for (int i = 0; i < ndelims; i++)
			if (c == delims[i]) return true;
		
		return false;
	}

	// tokenizes a line by removing delimiters and stores non-delimiter words as separate strings.
	// The asterisk is considered to be a separate token and is thus stored in a different field as the keyword itself.
	// Parsing stops on a comment sign, the comment is then stored as a single token including the comment character.
	std::vector<std::string> const tokenizefileString(const std::string& str){
		using namespace std;
		enum {
			STATE_TOKEN,
			STATE_DELIM
		};

		size_t delimlen(strlen(" \t"));
		size_t commentslen(strlen("%$#"));
		vector<string> result(0);

		bool inString(false);
		size_t start(0);
		size_t end(0);
		size_t length(str.length());
		int state(STATE_DELIM);

		do {
			if (state == STATE_DELIM) {
				if (!isDelim(str[end], " \t", (int)delimlen + 1)) {
					start = end;
					state = STATE_TOKEN;
				}
			}
			if (state == STATE_TOKEN) {
				if (!inString&& str[end] == '\"')
					inString = true;
				else if (inString&& str[end] == '\"')
					inString = false;
				// the nul-character is a delimiter: reason for delimlen+1
				if (!inString && isDelim(str[end], " \t", (int)delimlen + 1)) {
					result.push_back(std::move(str.substr(start, end - start)));
					state = STATE_DELIM;
				}
				// this is the beginning of a keyword, keep it as an extra token
				if (str[end] == '*') {
					result.push_back("*");
					start = end + 1;
				}
			}
			if (state == STATE_TOKEN || state == STATE_DELIM) {
				// check for comment
				if (isDelim(str[end], "%$#", (int)commentslen)) {
					start = end;
					end = length;
					result.push_back(std::move(str.substr(start, end - start)));
				}
			}
			end++;
		} while (str[end - 1] != 0);

		return result;
	}

	//Replace a caracter, "occ", by another, "newChar", in the string "path"
	inline std::string replace(std::string path, char occ, std::string newChar)
	{
		while (true)
		{
			std::size_t found = path.rfind(occ);
			if (found != std::string::npos)
				path.replace(path.begin() + found, path.begin() + found + 1, newChar.begin(), newChar.end());
			else
				break;
		}
		return path;
	};

	//Replace a caracter, "occ", by another, "newChar", in the wild string "path"
	inline std::wstring replace(std::wstring path, wchar_t occ, std::wstring newChar)
	{
		std::string s = replace(std::string(path.begin(), path.end()), occ, std::string(newChar.begin(), newChar.end()));
		return std::wstring(s.begin(), s.end());
	};

	inline std::wstring toWStr(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}

	inline std::string toStr(const std::wstring str)
	{
		return std::string(str.begin(), str.end());
	}

	/** Returns true if the file exist & is readable **/
	bool exist(std::wstring const& filename)
	{
		try
		{
			// check if it's a file
			std::ifstream file(filename, std::ios::in);
			if(file.good())
			{
				file.close();
				return true;
			}
			// check if it's a folder
			//QDir folder(filename);
			//if(folder.exists())
			//	return true;
		}
		catch(const std::logic_error & e)
		{
			return false;
		}
		return false;
	}

}


#endif // STRING_MANAGER