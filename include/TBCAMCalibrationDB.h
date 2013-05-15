#include <string>
#include <vector>

class TBCAMCalibrationDB {
	private:
		static const int DESCR_BUF_LEN = 64;

	public:
		// Possible types of a BCAM and masks to work with te patterns
		enum eCamBits {
			BC_BLUE    = (1<<0),
			BC_BLACK   = (1<<1),
			BC_AZI     = (1<<2),
			BC_POL     = (1<<3),
			BC_SRC     = (1<<4),
			BC_CAM     = (1<<5),
			BC_FRONT   = (1<<6),
			BC_REAR    = (1<<7),

			BC_COLOR_MASK   = (BC_BLUE|BC_BLACK),
			BC_AZI_POL_MASK = (BC_POL|BC_AZI),
			BC_SRC_CAM_MASK = (BC_CAM|BC_SRC),
		};
		
		static const int fBlueAzi[2];
		static const int fBlackAzi[2];
		static const int fBluePolar[4];
		static const int fBlackPolar[4];
		static const int fAllTypes[12];
		static const std::string fAllNames[12];
		static const int fNumAllDevices = 12;

		// indices of the calibration result
		enum {
			BC_SOURCE0_X, BC_SOURCE0_Y, BC_SOURCE0_Z, // Coordinates of LED 0
			BC_SOURCE1_X, BC_SOURCE1_Y, BC_SOURCE1_Z, // Coordinates of LED 1
			BC_NUM_SOURCE_COORDS
		};
		enum {
			BC_PP_X,   BC_PP_Y,  BC_PP_Z,  // Coordinates of Pivot Point
			BC_AD_X ,  BC_AD_Y,  BC_AD_Z,  // Direction of optical axis
			BC_CCD_PP, BC_ROT_CCD,         // camera constant and CCD rotation
			BC_CCD_CX, BC_CCD_CY,          // x and y center of CCD
			BC_NUM_CAM_PARAMETERS
		};

		// data transfer object
		struct DBEntry {
			char ID[DESCR_BUF_LEN];
			char timestamp[DESCR_BUF_LEN];
			char description[DESCR_BUF_LEN];
			int  type;
			float values[BC_NUM_CAM_PARAMETERS];
		};

		TBCAMCalibrationDB() : 
			fIsOpen(false) {}

		// get the integer encoding of a sting like "black_azimuthal_c"
		static int getTypeIDfromStr(const std::string& name);
		// get the descriptive name  like "black_azimuthal_c" from a bit pattern
		static std::string getNameFromType(int type);

		// read the information DO THIS BEFORE ANY OPERATION
		void openDB(const std::string& DBlocation);

		inline bool isOpen() {
			return fIsOpen;
		}

		// returns the number of read calibration entries
		int getNumDevices() {
			return fEntries.size();
		}

		// get the lookup index for a device by its serial number and a bit combination that describes the type.
		// Each serial number consists of up to 4 devices that have calibration data
		long findDevice(const std::string& ID, int type);
		// finally get the device by its lookup index
		DBEntry getDevice(long idx);

		// convinience function when the lookup key is not of interest (e.g. for reuse)
		inline DBEntry getDevice(const std::string& ID, int type) {
			return getDevice(findDevice(ID, type));
		}

		// returns:
		//  -1: a is newer than b
		//   1: a is older than b
		//   0: a exactly as old as b
		static int compareTimes(const char* a, const char* b);

	private:
		bool fIsOpen;
		std::vector<DBEntry> fEntries;
};