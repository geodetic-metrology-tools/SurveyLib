#include "FileLogHandler.hpp"

#include <fstream>
#include <string>

#include "LogMessage.hpp"

void FileLogHandler::log(const LogMessage & message)
{
	if (_filePath.empty())
		return;

	std::ofstream file(_filePath, std::ofstream::app);

	file << message.getDate() << ' ' << message.getType() << ": '" << message.getMessage() << "'";
	if (message.getType() == LogMessage::Type::DEBUG || message.getType() >= LogMessage::Type::CRITICAL)
		file << "\n\t" << message.getContext();
	file << std::endl;
}
