/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef ISHAREABLEPOINTSLISTIO_HPP
#define ISHAREABLEPOINTSLISTIO_HPP

#include <string>
#include <unordered_set>

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
 * The implementations should take in consideration the Fields members (exportFieldsPoint, exportFieldsParams, exportFieldsInfos,
 * exportFieldsFrame and exportFieldsPointsList) to export only the required data.
 *
 * This class offers methods to de-serialize data from/to strings. Though, it also offers 2 static methods to read/write files: readFile()
 * and writeFile().
 */
class IShareablePointsListIO
{
public:
	/**
	 * Represent the different fields that will be written when we serialize a class.
	 * @see exportFieldsPoint, exportFieldsParams, exportFieldsInfos, exportFieldsFrame, exportFieldsPointsList
	 */
	class Fields
	{
	public:
		/**
		 * Constructor
		 * @param the list of possible fields for the class.
		 */
		Fields(std::unordered_set<std::string> allfields) : _allFields(std::move(allfields)), _selectedFields(_allFields) {}
		/** Add a field to be written. The field has to be in the allFields list. */
		bool addField(const std::string &field)
		{
			if (_allFields.find(field) == std::cend(_allFields))
				return false;
			return _selectedFields.insert(field).second;
		}
		/** Add multiple fields. */
		template<class... Ts>
		void addField(const std::string &field, Ts... rest)
		{
			addField(field);
			addField(rest...);
		}
		/** Prevent a field to be written. */
		bool removeField(const std::string &field) { return _selectedFields.erase(field) == 1; }
		/** Remove multiple fields. */
		template<class... Ts>
		void removeField(const std::string &field, Ts... rest)
		{
			removeField(field);
			removeField(rest...);
		}
		/** Remove all fields to be written */
		void clear() noexcept { _selectedFields.clear(); }
		/** Tells if the given field will be written or not. */
		bool hasField(const std::string &field) const { return _selectedFields.find(field) != std::cend(_selectedFields); }
		/** Return all the fields that are marked to be written. */
		const std::unordered_set<std::string> &getFields() const noexcept { return _selectedFields; }
		/** Return all the possible fields */
		const std::unordered_set<std::string> &getAllFields() const noexcept { return _allFields; }

	protected:
		/** The list of all possible fields. */
		std::unordered_set<std::string> _allFields;
		/** The list of fields that are marked to be written. */
		std::unordered_set<std::string> _selectedFields;
	};

	/**
	 * @return a string that represents the content of the file.
	 * @param filename the path to the file to open
	 * @param binary if the file should be open in binary mode
	 */
	static std::string readFile(const std::string &filename, bool binary = false);
	/**
	 * Write the given contents to the file.
	 * @param filename the path to the file to open
	 * @param contents the contents to write
	 * @param binary if the file should be open in binary mode
	 */
	static void writeFile(const std::string &filename, const std::string &contents, bool binary = false);

	virtual ~IShareablePointsListIO() = default;

	/** @return true if it reads / write utf8 */
	virtual bool utf8() const noexcept { return _utf8; }
	/** @param isutf8 tells if we should read / write utf8 */
	virtual void utf8(bool isutf8) noexcept { _utf8 = isutf8; }

	/** @return the MIME type asociated with the managed format. */
	virtual const std::string &getMIMEType() const = 0;
	/**
	 * Tell if the given content is treated as empty.
	 * The default only tests if the contents is only composed of whitespaces.
	 *
	 * @return true if the content should be treated as empty (only meaningless characters like whitespaces and comments)
	 */
	virtual bool isEmpty(const std::string &contents) const;

	/**
	 * @return a ShareablePointsList read from the given JSON file.
	 * @param contents the content containing the structure to read
	 * @throw SPIOException if an error occurred.
	 * @see write(const ShareablePointsList&)
	 */
	virtual ShareablePointsList read(const std::string &contents) = 0;
	/**
	 * @return a ShareableExtraInfos read from the given JSON file.
	 * @param contents the content containing the structure to read
	 * @throw SPIOException if an error occurred.
	 * @see write(const ShareableExtraInfos&)
	 */
	virtual ShareableExtraInfos readExtraInfos(const std::string &contents) = 0;
	/**
	 * @return a ShareableFrame read from the given JSON file.
	 * @param contents the content containing the structure to read
	 * @throw SPIOException if an error occurred.
	 * @see write(const ShareableFrame&)
	 */
	virtual ShareableFrame readFrame(const std::string &contents) = 0;
	/**
	 * @return a ShareableParams read from the given JSON file.
	 * @param contents the content containing the structure to read
	 * @throw SPIOException if an error occurred.
	 * @see write(const ShareableParams&)
	 */
	virtual ShareableParams readParams(const std::string &contents) = 0;
	/**
	 * @return a ShareablePoint read from the given JSON file.
	 * @param contents the content containing the structure to read
	 * @throw SPIOException if an error occurred.
	 * @see write(conts ShareablePoint&)
	 */
	virtual ShareablePoint readPoint(const std::string &contents) = 0;
	/**
	 * @return a ShareablePosition read from the given JSON file.
	 * @param contents the content containing the structure to read
	 * @throw SPIOException if an error occurred.
	 * @see write(const ShareablePosition&)
	 */
	virtual ShareablePosition readPosition(const std::string &contents) = 0;

	/**
	 * Write the ShareablePointsList to the given file.
	 * @return a string representation of the structure.
	 * @throw SPIOException if an error occurred.
	 * @see read()
	 */
	virtual std::string write(const ShareablePointsList &list) = 0;
	/**
	 * Write the ShareableExtraInfos to the given file.
	 * @return a string representation of the structure.
	 * @throw SPIOException if an error occurred.
	 * @see readExtraInfos()
	 */
	virtual std::string write(const ShareableExtraInfos &info) = 0;
	/**
	 * Write the ShareableFrame to the given file.
	 * @return a string representation of the structure.
	 * @throw SPIOException if an error occurred.
	 * @see readFrame()
	 */
	virtual std::string write(const ShareableFrame &frame) = 0;
	/**
	 * Write the ShareableParams to the given file.
	 * @return a string representation of the structure.
	 * @throw SPIOException if an error occurred.
	 * @see readParams()
	 */
	virtual std::string write(const ShareableParams &params) = 0;
	/**
	 * Write the ShareablePoint to the given file.
	 * @return a string representation of the structure.
	 * @throw SPIOException if an error occurred.
	 * @see readPoint()
	 */
	virtual std::string write(const ShareablePoint &point) = 0;
	/**
	 * Write the ShareablePosition to the given file.
	 * @return a string representation of the structure.
	 * @throw SPIOException if an error occurred.
	 * @see readPosition()
	 */
	virtual std::string write(const ShareablePosition &position) = 0;

protected:
	/**
	 * @return an ifstream that points to the filename.
	 * @param filename the file to open.
	 * @param binary if true, the file is open in binary mode.
	 * @throw SPIOException if we can't open the file for any reason.
	 */
	static std::ifstream openRead(const std::string &filename, bool binary = false);
	/**
	 * @return an ofstream that points to the filename.
	 * @param filename the file to open.
	 * @param binary if true, the file is open in binary mode.
	 * @throw SPIOException if we can't open the file for any reason.
	 *
	 * The file is open in truncated mode (all previous content if existed is erased).
	 */
	static std::ofstream openWrite(const std::string &filename, bool binary = false);

public:
	/** List of fields that will be written when we serialize a ShareablePosition. */
	Fields exportFieldsPosition{{"x", "y", "z", "sigmax", "sigmay", "sigmaz", "isfreex", "isfreey", "isfreez"}};
	/** List of fields that will be written when we serialize a ShareablePoint. */
	Fields exportFieldsPoint{{"name", "position", "inlineComment", "headerComment", "active", "extraInfos"}};
	/** List of fields that will be written when we serialize a ShareableParams. */
	Fields exportFieldsParams{{"precision", "coordsys", "extraInfos"}};
	/** List of fields that will be written when we serialize a ShareableExtraInfos. */
	Fields exportFieldsInfos{{}};
	/** List of fields that will be written when we serialize a ShareableFrame. */
	Fields exportFieldsFrame{{"name", "translation", "rotation", "scale", "isfreescale", "innerFrames", "points"}};
	/** List of fields that will be written when we serialize a ShareablePointsList. */
	Fields exportFieldsPointsList{{"title", "params", "rootFrame"}};

private:
	bool _utf8 = true;
};

#endif // ISHAREABLEPOINTSLISTIO_HPP
