#include "IShareablePointsListIO.hpp"

#include <fstream>

#include "Logger.hpp"

 std::ifstream IShareablePointsListIO::openRead(const std::string& filename, bool binary)
 {
	 if (filename.empty())
	 {
		 logDebug() << "No file name given, can't open.";
		 throw SPIOException("No file name given, can't open.");
	 }
	 std::ifstream::openmode openmode{};
	 if (binary)
		 openmode |= std::ifstream::binary;
	 std::ifstream file(filename, openmode);
	 if (!file)
	 {
		 logDebug() << "Can't open file" << filename << ".";
		 throw SPIOException("Can't open file.", filename);
	 }
	 return file;
 }

 std::ofstream IShareablePointsListIO::openWrite(const std::string& filename, bool binary)
 {
	 if (filename.empty())
	 {
		 logDebug() << "No file name given, can't open.";
		 throw SPIOException("No file name given, can't open.");
	 }
	 std::ofstream::openmode openmode = std::ofstream::trunc;
	 if (binary)
		 openmode |= std::ofstream::binary;
	 std::ofstream file(filename, openmode);
	 if (!file)
	 {
		 logDebug() << "Can't open file" << filename << ".";
		 throw SPIOException("Can't open file.", filename);
	 }
	 return file;
 }

 std::string IShareablePointsListIO::readFile(const std::string & filename, bool binary)
 {
	 auto file = openRead(filename, binary);
	 auto fbuf = file.rdbuf();
	 const std::streampos size = fbuf->pubseekoff(0, file.end);
	 fbuf->pubseekoff(0, file.beg);
	 auto contents = std::make_unique<char[]>(size);
	 fbuf->sgetn(contents.get(), size);
	 if (binary)
		return std::string(contents.get(), size);
	 return std::string(contents.get());
 }

 void IShareablePointsListIO::writeFile(const std::string & filename, const std::string & contents, bool binary)
 {
	 auto file = openWrite(filename, binary);
	 file.write(contents.c_str(), contents.size());
 }
