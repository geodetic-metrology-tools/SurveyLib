#include "IShareablePointsListIO.hpp"

#include <fstream>

#include "Logger.hpp"

 std::ifstream IShareablePointsListIO::openRead()
 {
	 if (_filename.empty())
	 {
		 logDebug() << "Filename is empty, can't open it.";
		 throw std::ios_base::failure("Filename is empty, can't open it.");
	 }
	 std::ifstream file(_filename);
	 if (!file)
	 {
		 logDebug() << "Can't open file" << _filename << ".";
		 throw std::ios_base::failure("Can't open file" + _filename + ".");
	 }
	 return file;
 }

 std::ofstream IShareablePointsListIO::openWrite()
 {
	 if (_filename.empty())
	 {
		 logDebug() << "Filename is empty, can't open it.";
		 throw std::ios_base::failure("Filename is empty, can't open it.");
	 }
	 std::ofstream file(_filename, std::ofstream::out | std::ofstream::trunc);
	 if (!file)
	 {
		 logDebug() << "Can't open file" << _filename << ".";
		 throw std::ios_base::failure("Can't open file" + _filename + ".");
	 }
	 return file;
 }
