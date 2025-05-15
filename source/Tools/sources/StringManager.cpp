// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <algorithm>
#include <cstring>
#include <fstream>

#include "StringManager.h"

bool isDelim(const char c, const char* delims, int ndelims)
{
	return std::find(delims, delims + ndelims, c) != delims + ndelims;
}

// tokenizes a line by removing delimiters and stores non-delimiter words as separate strings.
// The asterisk is considered to be a separate token and is thus stored in a different field as the keyword itself.
// Parsing stops on a comment sign, the comment is then stored as a single token including the comment character.
std::vector<std::string> const tokenizefileString(const std::string& str){
	enum {
		STATE_TOKEN,
		STATE_DELIM
	};

	size_t delimlen(std::strlen(" \t"));
	size_t commentslen(std::strlen("%$"));
	std::vector<std::string> result(0);

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
                result.push_back(std::move(str.substr(start, end - start + 1)));
                start = end + 1;
			}
		}
		if (state == STATE_TOKEN || state == STATE_DELIM) {
			// check for comment
			if (isDelim(str[end], "%$", (int)commentslen)) {
				start = end;
				end = length;
				result.push_back(std::move(str.substr(start, end - start)));
			}
		}
		end++;
	} while (str[end - 1] != 0);

	// Remove the last token of a line if it starts with a comment (%) chararcter.
	if (result.size() != 0)
	{
		if (result.back().at(0) == '%')
		{
			result.pop_back();
		}
	}
	
	return result;
}

//Replace a caracter, "occ", by another, "newChar", in the string "path"
std::string replace(const std::string& path, char occ, const std::string& newChar)
{
	std::string result;
	result.reserve(path.size());

	for (const auto& c : path)
	{
		if (c == occ)
			result += newChar;
		else
			result += c;
	}

	return result;
}

//Replace a caracter, "occ", by another, "newChar", in the wild string "path"
std::wstring replace(const std::wstring& path, wchar_t occ, const std::wstring& newChar)
{
	std::wstring result;
	result.reserve(path.size());

	for (const auto& c : path)
	{
		if (c == occ)
			result += newChar;
		else
			result += c;
	}

	return result;
}

bool exist(std::wstring const& filename)
{
	std::ifstream file;
	// check if it's a file
	try
	{
		file.open(toStr(filename));
	}
	catch(const std::logic_error &)
	{
		return false;
	}

	return file.good();
}

std::string ltrim(std::string str)
{
	str.erase(std::begin(str), std::find_if(std::begin(str), std::end(str), [](auto ch) { return !std::isspace(ch, std::locale()); }));
	return str;
}

std::string rtrim(std::string str)
{
	str.erase(std::find_if(std::rbegin(str), std::rend(str), [](auto ch) { return !std::isspace(ch, std::locale()); }).base(), std::end(str));
	return str;
}

std::vector<std::string> split(const std::string & base, char c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : base)
	{
		if (n != c)
			buff += n;
		else if (n == c && buff != "")
		{
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "") v.push_back(buff);

	return v;
}
