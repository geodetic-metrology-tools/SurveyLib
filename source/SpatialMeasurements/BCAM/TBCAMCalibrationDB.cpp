#include <fstream>
#include <bitset>
#include <stdexcept>

#include "TAConverter.h"
#include "TBCAMCalibrationDB.h"

using namespace std;

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
int TBCAMCalibrationDB::compareTimes(const char* a, const char* b) {
	int len = min(strlen(a), strlen(b));
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

		// 3 descriptions in the front, then 6 to 8 float values
		static_assert(DESCR_BUF_LEN == 64, "Change sscanf buffer size");
		int numArgs = sscanf(line.c_str(), "%64s %64s %64s %f %f %f %f %f %f %f %f",
								linedata.timestamp, linedata.description, linedata.ID,
								linedata.values+0, linedata.values+1, linedata.values+2, linedata.values+3, 
								linedata.values+4, linedata.values+5, linedata.values+6, linedata.values+7);

		if (numArgs < 9)
			throw std::runtime_error("Error while reading calibration file " + DBlocation + " at line " + to_string(nline));

		// store the type also in numeric form
		linedata.type = getTypeIDfromStr(linedata.description);

		// check if the exact device is already stored
		// replace with the newer calibration if this is the case
		bool overwritten(false);
		for (DBEntry& entry : fEntries) {
			if (strcmp(entry.ID, linedata.ID) == 0 && 
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

long TBCAMCalibrationDB::findDevice(const std::string& ID, int type) {
	for (long i = 0; i < (long)fEntries.size(); i++) {
		if (strcmp(fEntries[i].ID, ID.c_str()) == 0 && fEntries[i].type == type)
			return i;
	}

	throw std::runtime_error("Cannot find device with ID " + ID + " and type " + getNameFromType(type));
}

TBCAMCalibrationDB::DBEntry TBCAMCalibrationDB::getDevice(long idx) {
	if (idx < 0 && idx > getNumDevices())
		throw std::runtime_error("Device index " + to_string(idx) + " out of range");

	return fEntries[idx];
}