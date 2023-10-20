#include <tut/tut.hpp>

#include "StringManager.h"

namespace tut
{
	struct toolsstringmanagerdata {};

	typedef test_group<toolsstringmanagerdata> tg;
	tg tools_stringmanager_group("Test Tools package.");
	typedef tg::object testobject;
}

namespace tut
{
	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("StringManager: Test of ltrim");

		// copy
		std::string test = " \n\t\r   test \n\t\r   ";
		std::string tmp = ltrim(test);
		ensure_equals("test \n\t\r   ", tmp);
		ensure_equals(" \n\t\r   test \n\t\r   ", test);
		// move
		test = ltrim(std::move(test));
		ensure_equals("test \n\t\r   ", test);
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("StringManager: Test of rtrim");

		// copy
		std::string test = " \n\t\r   test \n\t\r   ";
		std::string tmp = rtrim(test);
		ensure_equals(" \n\t\r   test", tmp);
		ensure_equals(" \n\t\r   test \n\t\r   ", test);
		// move
		test = rtrim(std::move(test));
		ensure_equals(" \n\t\r   test", test);
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("StringManager: Test of trim");

		// copy
		std::string test = " \n\t\r   test \n\t\r   ";
		std::string tmp = trim(test);
		ensure_equals("test", tmp);
		ensure_equals(" \n\t\r   test \n\t\r   ", test);
		// move
		test = trim(std::move(test));
		ensure_equals("test", test);
	}

	template<>
	template<>
	void testobject::test<4>()
	{
		set_test_name("StringManager: Test of isSpace");

		ensure(isSpace(' '));
		ensure(isSpace('\t'));
		ensure(isSpace('\n'));
		ensure(isSpace('\r'));
		ensure(isSpace('\v'));
		ensure(isSpace('\f'));

		ensure(isSpace(L' '));
		ensure(isSpace(L'\t'));
		ensure(isSpace(L'\n'));
		ensure(isSpace(L'\r'));
		ensure(isSpace(L'\v'));
		ensure(isSpace(L'\f'));

		ensure_not(isSpace('a'));
		ensure_not(isSpace('Z'));
		ensure_not(isSpace('-'));
		ensure_not(isSpace('*'));
		ensure_not(isSpace('5'));

		ensure_not(isSpace(L'a'));
		ensure_not(isSpace(L'Z'));
		ensure_not(isSpace(L'-'));
		ensure_not(isSpace(L'*'));
		ensure_not(isSpace(L'5'));
	}
}
