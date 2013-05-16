#ifndef _TBCAMDATA_H_
#define _TBCAMDATA_H_

#include <map>
#include <vector>
#include <string>

#include "Quad.h"

class TBCAMData {
	public:
		void readLWDAQFile(const std::string& filelocation);
		int getNumCoords(const std::string& serial);
		void getImagePoint(TReal& x, TReal& y, const std::string& serial, int idx);
		inline void clear() {
			fPoints.clear();
		}

	private:
		std::map<std::string, std::vector<float>> fPoints;
};

#endif