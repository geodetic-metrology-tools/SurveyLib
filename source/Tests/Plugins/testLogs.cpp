#include <fstream>

# include <chrono>
#include <iomanip>

#include <tut/tut.hpp>

#include "FileLogHandler.hpp"
#include "ILogHandler.hpp"
#include "Logger.hpp"
#include "LogMessage.hpp"

namespace tut
{
	struct pluginsdata 
	{
		~pluginsdata() { Logger::getLogger().clearHandlers(); Logger::getLogger().clearCounters(); }
	};

	typedef test_group<pluginsdata> tg;
	tg plugins_logs_test_group("Test Plugins package.");
	typedef tg::object testobject;
}

namespace tut
{
	/* ************************************************** *
	 *              TESTS OF LOGMESSAGE                   *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("LogMessage: Test of constructors");

		{
			LogMessage lm(LogMessage::Type::CRITICAL);
			ensure(lm.getMessage().empty());
			ensure(lm.getFile().empty());
			ensure_equals(lm.getLine(), -1);
			ensure(lm.getFunction().empty());
			ensure_equals(lm.getType(), LogMessage::Type::CRITICAL);
		}
		{
			LogMessage lm(LogMessage::Type::INFO, "message");
			ensure_equals(lm.getMessage(), "message");
			ensure_equals(lm.getType(), LogMessage::Type::INFO);
		}
		{
			LogMessage lm(LogMessage::Type::WARNING, "file", 42, "func", "message");
			ensure_equals(lm.getMessage(), "message");
			ensure_equals(lm.getFile(), "file");
			ensure_equals(lm.getLine(), 42);
			ensure_equals(lm.getFunction(), "func");
			ensure_equals(lm.getType(), LogMessage::Type::WARNING);
		}
		// move
		{
			LogMessage l(LogMessage::Type::WARNING, "file", 42, "func", "message");
			LogMessage lm(std::move(l));
			ensure_equals(lm.getMessage(), "message");
			ensure_equals(lm.getFile(), "file");
			ensure_equals(lm.getLine(), 42);
			ensure_equals(lm.getFunction(), "func");
			ensure_equals(lm.getType(), LogMessage::Type::WARNING);
		}
		{
			LogMessage lm = ([]() -> LogMessage { return LogMessage(LogMessage::Type::WARNING, "file", 42, "func", "message"); })();
			ensure_equals(lm.getMessage(), "message");
			ensure_equals(lm.getFile(), "file");
			ensure_equals(lm.getLine(), 42);
			ensure_equals(lm.getFunction(), "func");
			ensure_equals(lm.getType(), LogMessage::Type::WARNING);
		}
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("LogMessage: Test of getters & setters");

		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::ostringstream str;
		LogMessage lm(LogMessage::Type::CRITICAL);
		str << std::put_time(std::localtime(&time), "%D %F");

		lm.setMessage("message");
		lm.setFile("file");
		lm.setLine(42);
		lm.setFunction("function");
		lm.setType(LogMessage::Type::DEBUG);

		ensure_equals(lm.getMessage(), "message");
		ensure_equals(lm.getFile(), "file");
		ensure_equals(lm.getLine(), 42);
		ensure_equals(lm.getFunction(), "function");
		ensure_equals(lm.getType(), LogMessage::Type::DEBUG);
		ensure_equals(lm.getDate("%D %F"),  str.str());
		ensure_equals(lm.getContext(), "at 'file', line 42 in 'function'");
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("LogMessage: Test of operator<<");

		LogMessage lm(LogMessage::Type::FATAL);
		lm << "this is" << "an error message:" << 45 << ' ' << 12.3 << std::endl;

		ensure_equals(lm.getMessage(), "this is an error message: 45   12.3\n");
		ensure_equals(lm.getType(), LogMessage::Type::FATAL);
	}

	/* ************************************************** *
	*               TESTS OF ILOGHANDLER                  *
	* ************************************************** */

	template<>
	template<>
	void testobject::test<4>()
	{
		set_test_name("ILogHandler: Test of getters & setters");

		class DumbHandler : public ILogHandler
		{
		public:
			void log(const LogMessage&) override {};
		};

		DumbHandler h;
		ensure_equals(h.getThreshold(), LogMessage::Type::WARNING);
		h.setThreshold(LogMessage::Type::FATAL);
		ensure_equals(h.getThreshold(), LogMessage::Type::FATAL);
	}

	/* ************************************************** *
	 *                 TESTS OF LOGGER                    *
	 * ************************************************** */
	
	class DumbHandler : public ILogHandler
	{
	public:
		void log(const LogMessage&) override { DumbHandler::i++; j++; };
		static size_t i;
		size_t j = 0;
	};
	size_t DumbHandler::i = 0;

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("Logger: Test of getInstance");

		const auto *l1 = &Logger::getLogger();
		const auto *l2 = &Logger::getLogger();
		ensure(l1);
		ensure_equals(l1, l2);
		ensure_equals(l1->errorNumber(), 0);
		ensure_equals(l1->warningNumber(), 0);
		ensure_not(l1->hasErrors());
		ensure_not(l1->hasWarnings());
	}

	template<>
	template<>
	void testobject::test<6>()
	{
		set_test_name("Logger: Test of handlers");

		auto& logger = Logger::getLogger();
		auto* h1 = new DumbHandler();
		auto* h2 = new DumbHandler();
		auto* h3 = new DumbHandler();

		ensure_equals(DumbHandler::i, 0u);
		logger.addHandlers(h1);
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(DumbHandler::i, 1u);

		logger.addHandlers(h2, h3);
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(DumbHandler::i, 4u);

		logger.removeHandler(h3);
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(DumbHandler::i, 6u);

		logger.clearHandlers();
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(DumbHandler::i, 6u);
	}

	template<>
	template<>
	void testobject::test<7>()
	{
		set_test_name("Logger: Test of log()");

		auto* h1 = new DumbHandler();
		auto* h2 = new DumbHandler();
		auto& logger = Logger::getLogger();
		logger.addHandlers(h1, h2);

		ensure_equals(logger.errorNumber(), 0);
		ensure_equals(logger.warningNumber(), 0);
		ensure_not(logger.hasErrors());
		ensure_not(logger.hasWarnings());

		h1->setThreshold(LogMessage::Type::WARNING);
		logger.log(LogMessage(LogMessage::Type::DEBUG));
		logger.log(LogMessage(LogMessage::Type::INFO));
		logger.log(LogMessage(LogMessage::Type::WARNING));
		logger.log(LogMessage(LogMessage::Type::CRITICAL));
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(h1->j, 3u);
		ensure_equals(h2->j, 3u);
		ensure_equals(logger.errorNumber(), 2);
		ensure_equals(logger.warningNumber(), 1);
		ensure(logger.hasErrors());
		ensure(logger.hasWarnings());

		h1->setThreshold(LogMessage::Type::DEBUG);
		logger.log(LogMessage(LogMessage::Type::DEBUG));
		logger.log(LogMessage(LogMessage::Type::INFO));
		logger.log(LogMessage(LogMessage::Type::WARNING));
		logger.log(LogMessage(LogMessage::Type::CRITICAL));
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(h1->j, 8u); // 3 + 5
		ensure_equals(h2->j, 6u); // 3 + 3
		ensure_equals(logger.errorNumber(), 4);
		ensure_equals(logger.warningNumber(), 2);
		ensure(logger.hasErrors());
		ensure(logger.hasWarnings());

		h1->setThreshold(LogMessage::Type::INFO);
		logger.log(LogMessage(LogMessage::Type::DEBUG));
		logger.log(LogMessage(LogMessage::Type::INFO));
		logger.log(LogMessage(LogMessage::Type::WARNING));
		logger.log(LogMessage(LogMessage::Type::CRITICAL));
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(h1->j, 12u); // 8 + 4
		ensure_equals(h2->j, 9u); // 6 + 3
		ensure_equals(logger.errorNumber(), 6);
		ensure_equals(logger.warningNumber(), 3);
		ensure(logger.hasErrors());
		ensure(logger.hasWarnings());

		h1->setThreshold(LogMessage::Type::FATAL);
		logger.log(LogMessage(LogMessage::Type::DEBUG));
		logger.log(LogMessage(LogMessage::Type::INFO));
		logger.log(LogMessage(LogMessage::Type::WARNING));
		logger.log(LogMessage(LogMessage::Type::CRITICAL));
		logger.log(LogMessage(LogMessage::Type::FATAL));
		ensure_equals(h1->j, 13u); // 12 + 1
		ensure_equals(h2->j, 12u); // 9 + 3
		ensure_equals(logger.errorNumber(), 8);
		ensure_equals(logger.warningNumber(), 4);
		ensure(logger.hasErrors());
		ensure(logger.hasWarnings());
	}

	/* ************************************************** *
	 *                 TESTS OF MACROS                    *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<8>()
	{
		set_test_name("MACROS: Test of macros()");

		class DumbHandler2 : public ILogHandler
		{
		public:
			void log(const LogMessage& m) override
			{
				msg.setMessage(m.getMessage());
				msg.setFile(m.getFile());
				msg.setLine(m.getLine());
				msg.setFunction(m.getFunction());
				msg.setType(m.getType());
			};
			LogMessage msg{ LogMessage::Type::WARNING };
		};
		auto iendswith = [](const std::string &fullString, const std::string &ending) -> bool {
			if (fullString.size() >= ending.size())
			{
				std::string s1 = fullString, s2 = ending;
				std::transform(std::begin(s1), std::end(s1), std::begin(s1), tolower);
				std::transform(std::begin(s2), std::end(s2), std::begin(s2), tolower);
				return (0 == s1.compare(s1.size() - s2.size(), s2.size(), s2));
			}
			else
				return false;
		};

		auto& logger = Logger::getLogger();
		auto* h = new DumbHandler2();
		h->setThreshold(LogMessage::Type::DEBUG);
		logger.addHandlers(h);
		int line = -1;

		line = __LINE__ + 1;
		logDebug() << "this is" << "an error message:" << 45 << ' ' << 12.3;
		ensure_equals(h->msg.getType(), LogMessage::Type::DEBUG);
		ensure_equals(h->msg.getMessage(), "this is an error message: 45   12.3");
		ensure(iendswith(h->msg.getFile(), "testLogs.cpp"));
		ensure_equals(h->msg.getLine(), line);
		ensure(h->msg.getFunction().find("test") != std::string::npos);
		ensure_equals(logger.errorNumber(), 0);
		ensure_equals(logger.warningNumber(), 0);
		ensure_not(logger.hasErrors());
		ensure_not(logger.hasWarnings());

		line = __LINE__ + 1;
		logInfo() << "this is" << "an error message:" << 45 << ' ' << 12.3;
		ensure_equals(h->msg.getType(), LogMessage::Type::INFO);
		ensure_equals(h->msg.getLine(), line);
		ensure_equals(logger.errorNumber(), 0);
		ensure_equals(logger.warningNumber(), 0);
		ensure_not(logger.hasErrors());
		ensure_not(logger.hasWarnings());
		
		line = __LINE__ + 1;
		logWarning() << "this is" << "an error message:" << 45 << ' ' << 12.3;
		ensure_equals(h->msg.getType(), LogMessage::Type::WARNING);
		ensure_equals(h->msg.getLine(), line);
		ensure_equals(logger.errorNumber(), 0);
		ensure_equals(logger.warningNumber(), 1);
		ensure_not(logger.hasErrors());
		ensure(logger.hasWarnings());

		line = __LINE__ + 1;
		logCritical() << "this is" << "an error message:" << 45 << ' ' << 12.3;
		ensure_equals(h->msg.getType(), LogMessage::Type::CRITICAL);
		ensure_equals(h->msg.getLine(), line);
		ensure_equals(logger.errorNumber(), 1);
		ensure_equals(logger.warningNumber(), 1);
		ensure(logger.hasErrors());
		ensure(logger.hasWarnings());

		line = __LINE__ + 1;
		logFatal() << "this is" << "an error message:" << 45 << ' ' << 12.3;
		ensure_equals(h->msg.getType(), LogMessage::Type::FATAL);
		ensure_equals(h->msg.getLine(), line);
		ensure_equals(logger.errorNumber(), 2);
		ensure_equals(logger.warningNumber(), 1);
		ensure(logger.hasErrors());
		ensure(logger.hasWarnings());
	}

	/* ************************************************** *
	 *             TESTS OF FILELOGHANDLER                *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<9>()
	{
		set_test_name("FileLogHandler: Test of log()");

		auto& logger = Logger::getLogger();
		auto* h = new FileLogHandler("./testLogs_test9.log");
		logger.addHandlers(h);

		{
			logCritical() << "lol erreur !!!";
		}

		std::ifstream f("./testLogs_test9.log");
		std::string contents;
		f.seekg(0, std::ios::end);
		contents.resize(f.tellg());
		f.seekg(0, std::ios::beg);
		f.read(&contents[0], contents.size());
		f.close();

		ensure(contents.find("ERROR: 'lol erreur !!!'") != std::string::npos);

		std::remove("./testLogs_test9.log");
	}
}
