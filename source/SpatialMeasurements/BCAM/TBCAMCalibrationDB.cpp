#include <fstream>
#include <bitset>
#include <stdexcept>
#include <algorithm>

#include "TAConverter.h"
#include "TBCAMCalibrationDB.h"

using namespace std;

char const *const TBCAMCalibrationDB::INFILE_DELIMS = " \t";

const int TBCAMCalibrationDB::fBlueAzi[2] = {
	BC_BLUE|BC_AZI|BC_SRC,
	BC_BLUE|BC_AZI|BC_CAM
};
const int TBCAMCalibrationDB::fBlackAzi[2] = {
	BC_BLACK|BC_AZI|BC_SRC,
	BC_BLACK|BC_AZI|BC_CAM
};
const int TBCAMCalibrationDB::fBluePolar[4] = {
    BC_BLUE|BC_POL|BC_FRONT|BC_SRC,
    BC_BLUE|BC_POL|BC_FRONT|BC_CAM,
    BC_BLUE|BC_POL|BC_REAR|BC_SRC,
    BC_BLUE|BC_POL|BC_REAR|BC_CAM,
};
const int TBCAMCalibrationDB::fBlackPolar[4] = {
    BC_BLACK|BC_POL|BC_FRONT|BC_SRC,
    BC_BLACK|BC_POL|BC_FRONT|BC_CAM,
    BC_BLACK|BC_POL|BC_REAR|BC_SRC,
    BC_BLACK|BC_POL|BC_REAR|BC_CAM,
};
const int TBCAMCalibrationDB::fAllTypes[12] = {
    BC_BLUE|BC_AZI|BC_SRC,
    BC_BLUE|BC_AZI|BC_CAM,
    BC_BLACK|BC_AZI|BC_SRC,
    BC_BLACK|BC_AZI|BC_CAM,
    BC_BLUE|BC_POL|BC_FRONT|BC_SRC,
    BC_BLUE|BC_POL|BC_FRONT|BC_CAM,
    BC_BLUE|BC_POL|BC_REAR|BC_SRC,
    BC_BLUE|BC_POL|BC_REAR|BC_CAM,
    BC_BLACK|BC_POL|BC_FRONT|BC_SRC,
    BC_BLACK|BC_POL|BC_FRONT|BC_CAM,
    BC_BLACK|BC_POL|BC_REAR|BC_SRC,
    BC_BLACK|BC_POL|BC_REAR|BC_CAM,
};
const std::string TBCAMCalibrationDB::fAllNames[12] = {
	"blue_azimuthal_s",
	"blue_azimuthal_c",
	"black_azimuthal_s",
	"black_azimuthal_c",
	"blue_polar_fs",
	"blue_polar_fc",
	"blue_polar_rs",
	"blue_polar_rc",
	"black_polar_fs",
	"black_polar_fc",
	"black_polar_rs",
	"black_polar_rc"
};

// returns:
//  -1: a is newer than b
//   1: a is older than b
//   0: a exactly as old as b
int TBCAMCalibrationDB::compareTimes(const std::string& a, const std::string& b) {
	int len = min(a.size(), b.size());
    for (int i = 0; i < len; i++) {
        if (a[i] > b[i])
            return -1;
        else if (a[i] < b[i])
            return  1;
    }
    return 0;
}

int TBCAMCalibrationDB::getTypeIDfromStr(const string& name) {
    int type = 0;
	string errmsg("Cannot convert device type " + name + " to number");

	vector<string> typetokens(TAConverter::tokenizeString(name, "_"));
	if (typetokens.size() != 3)
		 throw runtime_error(errmsg);

    if (typetokens[0] == "blue") type |= BC_BLUE;
    else if (typetokens[0] == "black") type |= BC_BLACK;
	else throw runtime_error(errmsg);

    if (typetokens[1] == "azimuthal") type |= BC_AZI;
    else if (typetokens[1] == "polar") type |= BC_POL;
	else throw runtime_error(errmsg);

    if (typetokens[2] == "s") type |= (BC_SRC);
    else if (typetokens[2] == "c") type |= (BC_CAM);
    else if (typetokens[2] == "fs") type |= (BC_SRC|BC_FRONT);
    else if (typetokens[2] == "fc") type |= (BC_CAM|BC_FRONT);
    else if (typetokens[2] == "rs") type |= (BC_SRC|BC_REAR);
    else if (typetokens[2] == "rc") type |= (BC_CAM|BC_REAR);
	else throw runtime_error(errmsg);

    return type;
}


string TBCAMCalibrationDB::getNameFromType(int type) {
	for (int i = 0; i < 12; i++) {
		if (fAllTypes[i] == type)
			return fAllNames[i];
	}

	throw runtime_error("Cannot convert bitpattern \'" + bitset<8>(type).to_string() + "\' to name");
}

void TBCAMCalibrationDB::openDB(const std::string& DBlocation) {
	ifstream infile(DBlocation);
	if (! infile.is_open())
		throw runtime_error("BCAM calibration file " + DBlocation + " not found");
	
	// step through the lines of the output file
	string line;
	int nline = 0;
	DBEntry linedata;
	while (getline(infile, line)) {
		nline++;

		vector<string> linestrings(TAConverter::tokenizeString(line, INFILE_DELIMS));
		if (linestrings.size() < 9)
			throw std::runtime_error("Error while reading calibration file " + DBlocation + " at line " + to_string(nline));

		// 3 descriptions in the front, then 6 to 8 float values
		linedata.timestamp   = linestrings[0];
		linedata.description = linestrings[1];
		linedata.serial      = linestrings[2];
		linedata.type        = getTypeIDfromStr(linedata.description);

		// TODO: ADD HBCAM support with different ccd center values (e.g depending on serial)
		size_t numValues;
		if (linedata.type & BC_CAM) {
			numValues = BC_NUM_CAM_PARAMETERS-2;
			linedata.values[BC_CCD_CX] = 1.720;
			linedata.values[BC_CCD_CX] = 1.220;
		}
		else if (linedata.type & BC_SRC) {
			numValues = BC_NUM_SOURCE_COORDS;
		}
		else {
			throw std::runtime_error("Error in calibration file " + DBlocation + " at line "  + to_string(nline) + ": Device is neither camera nor source");
		}

		if (numValues > linestrings.size()-3)
			throw std::runtime_error("Error in calibration file " + DBlocation + " at line "  + to_string(nline) + ": Not enough calibration values");

		for (size_t i = 0; i < numValues; i++)
			linedata.values[i] = stod(linestrings[i+3]);

		// check if the exact device is already stored
		// replace with the newer calibration if this is the case
		bool overwritten(false);
		for (DBEntry& entry : fEntries) {
			if (entry.serial == linedata.serial && 
				entry.type == linedata.type && 
				compareTimes(linedata.timestamp, entry.timestamp) == -1) {
					// linedata is newer than entry
					entry = linedata;
					overwritten = true;
			}
		}

		// append the entry if there was no overwrite
		if (! overwritten)
			fEntries.push_back(linedata);
	}

	infile.close();
	fIsOpen = true;
}

const TBCAMCalibrationDB::DBEntry& TBCAMCalibrationDB::getDevice(const std::string& serial, int type) {
	auto entry(find(fEntries.begin(), fEntries.end(), DBEntry(serial, type)));

	if (entry == fEntries.end())
		throw std::runtime_error("Could not find device with serial " + serial + " (" + getNameFromType(type) + ")");

	return *entry;
}