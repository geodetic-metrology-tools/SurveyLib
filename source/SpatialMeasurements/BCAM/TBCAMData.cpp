#include <fstream>

#include "TAConverter.h"

#include "TBCAMData.h"

using namespace std;

TBCAMData::TBCAMData(const std::string& filelocation) {
	ifstream infile(filelocation);
	if (! infile.is_open())
		throw runtime_error("BCAM data file \'" + filelocation + "\' not found");

	string line;
	while (getline(infile, line)) {
		// tokenize the line
		vector<string> linestrings(TAConverter::tokenizeString(line, " \t"));
		// for non-empty lines: use the serial number as key
		if (linestrings.size() > 1) {
			auto& pointvec(fPoints[linestrings[0]]);
			// iterate over the coordinates in the line
			for (auto coordstr =  linestrings.cbegin()+1; 
				 coordstr != linestrings.cend(); ++coordstr) {
				// add each coordinate to the vector
				pointvec.push_back(stof(*coordstr));
			}
		}
	}
}

int TBCAMData::getNumCoords(const std::string& serial) {
	return (int)fPoints[serial].size()/2;
}

void TBCAMData::getImagePoint(TReal& x, TReal& y, const std::string& serial, int idx) {
	const auto& ptvec(fPoints[serial]);
	x = ptvec.at(idx*2);
	y = ptvec.at(idx*2 +1);
}