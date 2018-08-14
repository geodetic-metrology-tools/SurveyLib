/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef ISHAREABLEPOINTSLISTIO_HPP
#define ISHAREABLEPOINTSLISTIO_HPP

#include <exception>
#include <string>

class ShareableExtraInfos;
class ShareableFrame;
struct ShareableParams;
struct ShareablePoint;
class ShareablePointsList;
struct ShareablePosition;

/**
 * Serialization interface for Shareable Points.
 *
 * In order to serialize a ShareablePointsList into any format, you need to inherit from this class and implement all required functions.
 */
class IShareablePointsListIO
{
public:
	/**
	 * Constructor.
	 *
	 * @param filename the name (path) of the file to read / write.
	 */
	IShareablePointsListIO(std::string filename="") : _filename(filename) {}
	virtual ~IShareablePointsListIO() = default;

	/**
	 * Set the file where to read / write.
	 * @see getFilename()
	 */
	void setFilename(const std::string& filename) { _filename = filename; }
	/**
	 * Get the file where to read / write.
	 * @see setFilename()
	 */
	const std::string& getFilename() const noexcept { return _filename; }

	virtual ShareablePointsList read() = 0;
	virtual ShareableExtraInfos readExtraInfos() = 0;
	virtual ShareableFrame readFrame() = 0;
	virtual ShareableParams readParams() = 0;
	virtual ShareablePoint readPoint() = 0;
	virtual ShareablePosition readPosition() = 0;

	virtual void write(const ShareablePointsList& list) = 0;
	virtual void write(const ShareableExtraInfos& info) = 0;
	virtual void write(const ShareableFrame& frame) = 0;
	virtual void write(const ShareableParams& params) = 0;
	virtual void write(const ShareablePoint& point) = 0;
	virtual void write(const ShareablePosition& position) = 0;

protected:
	std::ifstream openRead(bool binary=false);
	std::ofstream openWrite(bool binary=false);

protected:
	/** Path to the file where to read or write */
	std::string _filename;
};

class SPIOException : public std::exception
{
public:
	SPIOException(const std::string& error, const std::string& filename, int offset = -1) : _error(error), _filename(filename), _offset(offset) {}

	virtual const char* what() const noexcept override { return _error.c_str(); }

	const std::string& error() const noexcept { return _error; }
	const std::string& filename() const noexcept { return _filename; }
	int offset() const noexcept { return _offset; }

private:
	std::string _error;
	std::string _filename;
	int _offset = -1;
};

#endif // ISHAREABLEPOINTSLISTIO_HPP
