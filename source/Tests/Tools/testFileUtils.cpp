#include <filesystem>

#include <tut/tut.hpp>

#include "FileUtils.h"

namespace fs = std::filesystem;

namespace tut
{
struct toolsfileutilsdata
{
};

typedef test_group<toolsfileutilsdata> tg;
tg tools_fileutils_group("Test Tools - FileUtils package.");
typedef tg::object testobject;
} // namespace tut

namespace tut
{
template<>
template<>
void testobject::test<1>()
{
	set_test_name("FileUtils: Test of macros");

#ifdef WIN32
	ensure_equals(slash, '\\');
#else
	ensure_equals(slash, '/');
#endif
}

template<>
template<>
void testobject::test<10>()
{
	set_test_name("FileUtils: Test of getCurrentDirectory");

	ensure_equals(svlTools::getCurrentDirectory(), fs::current_path().string());
}

template<>
template<>
void testobject::test<11>()
{
	set_test_name("FileUtils: Test of getPathFileName");

	const std::string relative = "file.txt";
#ifdef WIN32
	const std::string absolute = "C:/file.txt";
#else
	const std::string absolute = "/file.txt";
#endif
	ensure_equals(svlTools::getPathFileName(relative), (fs::current_path() / fs::path(relative)).string());
	ensure_equals(svlTools::getPathFileName(absolute), fs::path(absolute).make_preferred().string());
}

template<>
template<>
void testobject::test<12>()
{
	set_test_name("FileUtils: Test of changePathDirSlash");

	const std::string filename = "the/cake\\is\\a/lie";

	std::string result = filename;
	svlTools::changePathDirSlash(result);
	ensure_equals(result, fs::path(filename).make_preferred().string());
}

template<>
template<>
void testobject::test<13>()
{
	set_test_name("FileUtils: Test of getFilePathWithoutExtension");

	std::string noext = "the/cake/is/a/lie";
	std::string withext = "the/cake/is/a/lie.lol";
	std::string multext = "the/cake/is/a/lie.lol.haha.thing";
	svlTools::changePathDirSlash(noext);
	svlTools::changePathDirSlash(withext);
	svlTools::changePathDirSlash(multext);

	ensure_equals(svlTools::getFilePathWithoutExtension(noext), noext);
	ensure_equals(svlTools::getFilePathWithoutExtension(withext), noext);
	const fs::path path(multext);
	std::string result = svlTools::getFilePathWithoutExtension(multext);
	svlTools::changePathDirSlash(result);
	ensure_equals(result, (path.parent_path() / path.stem()).make_preferred().string());
}

template<>
template<>
void testobject::test<14>()
{
	set_test_name("FileUtils: Test of createOutputFile");

	const std::string file = svlTools::getPathFileName("testFileUtils/createOutputFile.test");
	svlTools::createOutputFile(file);

	fs::path p = fs::path(file).parent_path();
	ensure(fs::exists(p));

	fs::remove_all(p);
}
} // namespace tut
