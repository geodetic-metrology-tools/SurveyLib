// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <iostream>
#include <string>

#include "ConsoleLogHandler.hpp"
#include "LogMessage.hpp"

void ConsoleLogHandler::log(const LogMessage & message)
{
	std::ostream &out = (message.getType() <= LogMessage::Type::WARNING) ? std::cout : std::cerr;
	
	out << message.getDate() << ' ' << message.getType() << ": '" << message.getMessage() << "'";
	if (message.getType() == LogMessage::Type::DEBUG || message.getType() >= LogMessage::Type::CRITICAL)
		out << "\n\t'" << message.getContext();
	out << std::endl;
}
