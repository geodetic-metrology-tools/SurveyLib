#include "IShareablePointsListIO.hpp"

#include <fstream>

#include "Logger.hpp"

 std::ifstream IShareablePointsListIO::openRead(bool binary)
 {
	 if (_filename.empty())
	 {
		 logDebug() << "No file name given, can't open.";
		 throw SPIOException("No file name given, can't open.", _filename);
	 }
	 std::ifstream::openmode openmode{};
	 if (binary)
		 openmode |= std::ifstream::binary;
	 std::ifstream file(_filename, openmode);
	 if (!file)
	 {
		 logDebug() << "Can't open file" << _filename << ".";
		 throw SPIOException("Can't open file" + _filename + ".", _filename);
	 }
	 return file;
 }

 std::ofstream IShareablePointsListIO::openWrite(bool binary)
 {
	 if (_filename.empty())
	 {
		 logDebug() << "No file name given, can't open.";
		 throw SPIOException("No file name given, can't open.", _filename);
	 }
	 std::ofstream::openmode openmode = std::ofstream::trunc;
	 if (binary)
		 openmode |= std::ofstream::binary;
	 std::ofstream file(_filename, openmode);
	 if (!file)
	 {
		 logDebug() << "Can't open file" << _filename << ".";
		 throw SPIOException("Can't open file" + _filename + ".", _filename);
	 }
	 return file;
 }
