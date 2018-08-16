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
 * IShareablePointsListIO is part of the @ref shpoints module.
 * @ingroup shpoints
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

	/**
	 * @return a ShareablePointsList read from the given JSON file.
	 * @throw SPIOException if an error occurred.
	* @see write(const ShareablePointsList&)
	 */
	virtual ShareablePointsList read() = 0;
	/**
	* @return a ShareableExtraInfos read from the given JSON file.
	* @throw SPIOException if an error occurred.
	* @see write(const ShareableExtraInfos&)
	*/
	virtual ShareableExtraInfos readExtraInfos() = 0;
	/**
	* @return a ShareableFrame read from the given JSON file.
	* @throw SPIOException if an error occurred.
	* @see write(const ShareableFrame&)
	*/
	virtual ShareableFrame readFrame() = 0;
	/**
	* @return a ShareableParams read from the given JSON file.
	* @throw SPIOException if an error occurred.
	* @see write(const ShareableParams&)
	*/
	virtual ShareableParams readParams() = 0;
	/**
	* @return a ShareablePoint read from the given JSON file.
	* @throw SPIOException if an error occurred.
	* @see write(conts ShareablePoint&)
	*/
	virtual ShareablePoint readPoint() = 0;
	/**
	* @return a ShareablePosition read from the given JSON file.
	* @throw SPIOException if an error occurred.
	* @see write(const ShareablePosition&)
	*/
	virtual ShareablePosition readPosition() = 0;

	/**
	* Write the ShareablePointsList to the given file.
	* @throw SPIOException if an error occurred.
	* @see read()
	*/
	virtual void write(const ShareablePointsList& list) = 0;
	/**
	* Write the ShareableExtraInfos to the given file.
	* @throw SPIOException if an error occurred.
	* @see readExtraInfos()
	*/
	virtual void write(const ShareableExtraInfos& info) = 0;
	/**
	* Write the ShareableFrame to the given file.
	* @throw SPIOException if an error occurred.
	* @see readFrame()
	*/
	virtual void write(const ShareableFrame& frame) = 0;
	/**
	* Write the ShareableParams to the given file.
	* @throw SPIOException if an error occurred.
	* @see readParams()
	*/
	virtual void write(const ShareableParams& params) = 0;
	/**
	* Write the ShareablePoint to the given file.
	* @throw SPIOException if an error occurred.
	* @see readPoint()
	*/
	virtual void write(const ShareablePoint& point) = 0;
	/**
	* Write the ShareablePosition to the given file.
	* @throw SPIOException if an error occurred.
	* @see readPosition()
	*/
	virtual void write(const ShareablePosition& position) = 0;

protected:
	/**
	 * @return an ifstream that points to getFilename().
	 * @param binary if true, the file is open in binary mode.
	 * @throw SPIOException if we can't open the file for any reason.
	 */
	std::ifstream openRead(bool binary=false);
	/**
	* @return an ofstream that points to getFilename().
	* @param binary if true, the file is open in binary mode.
	* @throw SPIOException if we can't open the file for any reason.
	*
	* The file is open in truncated mode (all previous content if existed is erased).
	*/
	std::ofstream openWrite(bool binary=false);

protected:
	/** Path to the file where to read or write */
	std::string _filename;
};

/**
 * Exception class for IO operations on @ref shpoints object.
 *
 * SPIOException is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * This class offers a way to store the filename and the offset where the error occurred.
 */
class SPIOException : public std::exception
{
public:
	/**
	 * Constructor.
	 *
	 * @param error the error message
	 * @param filename the path to the file
	 * @param offset the offset inside the file where the error occured (by default = -1)
	 */
	SPIOException(const std::string& error, const std::string& filename, int offset = -1) : _error(error), _filename(filename), _offset(offset) {}

	virtual const char* what() const noexcept override { return _error.c_str(); }

	/**
	 * @return the error message as a string.
	 * @see what()
	 */
	const std::string& error() const noexcept { return _error; }
	/** @return the filename where the error occurred. */
	const std::string& filename() const noexcept { return _filename; }
	/** @return the offset in the file where the error occurred, if it is possible to know. -1 otherwise. */
	int offset() const noexcept { return _offset; }

private:
	/** The error message. */
	std::string _error;
	/** The filename related to the error. */
	std::string _filename;
	/** the offset inside the file where the error occured. */
	int _offset = -1;
};

#endif // ISHAREABLEPOINTSLISTIO_HPP
