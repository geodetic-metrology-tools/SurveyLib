#include "FileLogHandler.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>

#include "LogMessage.hpp"
#include "Logger.hpp"

const char *DATEFORMAT = "%Y-%m-%d";

std::string FileLogHandler::addDate(const std::string &filename)
{
	namespace fs = std::filesystem;
	using chrono = std::chrono::system_clock;

	const fs::path file = filename;
	const std::string extension = file.extension().string();

	auto now = chrono::to_time_t(chrono::now());
	std::ostringstream oss;
	oss << (file.parent_path() / file.stem()).string() << '_' << std::put_time(std::localtime(&now), DATEFORMAT) << extension;
	return oss.str();
}

void FileLogHandler::removeOldLogs(const std::string &filename, int nbdays)
{
	namespace fs = std::filesystem;
	using chrono = std::chrono::system_clock;

	const fs::path filepath = filename;
	std::regex regx((filepath.stem()).string() + R"""(_(\d{4}-\d{2}-\d{2}))""" + filepath.extension().string() + '$');
	std::smatch match;
	std::string file, date;

	for (const auto &f : fs::directory_iterator(filepath.parent_path()))
	{
		file = f.path().string();
		if (!f.exists() || !f.is_regular_file() || !std::regex_search(file, match, regx))
			continue;
		date = match[1];
		// we check if the file is old enough
		std::tm tm = {};
		std::istringstream iss(date);
		iss >> std::get_time(&tm, DATEFORMAT);
		auto chronodate = chrono::from_time_t(std::mktime(&tm));
		if (chronodate < chrono::now() - std::chrono::hours(nbdays * 24))
		{
			try
			{
				fs::remove(f);
				logInfo() << "Log file '" << file << "' has been removed.";
			}
			catch (const fs::filesystem_error &e)
			{
				logDebug() << "Can't remove file '" << file << "':" << e.what();
			}
		}
	}
}

void FileLogHandler::log(const LogMessage &message)
{
	if (_filePath.empty())
		return;

	std::ofstream file;
	try
	{
		file.open(_filePath, std::ofstream::app);
		if (!file)
			return;
	}
	catch (const std::exception &e)
	{
		return; // we can't notify the error here, we are in the logging loop...
	}

	file << message.getDate() << ' ' << message.getType() << ": '" << message.getMessage() << "'";
	if (message.getType() == LogMessage::Type::DEBUG || message.getType() >= LogMessage::Type::CRITICAL)
		file << "\n\t" << message.getContext();
	file << std::endl;
}
