#include <stdexcept>
#include <BCAM.h>
#include <TAConverter.h>

#include <tut/tut.hpp>

namespace tut
{
    struct test_BCAM{};
    typedef test_group<test_BCAM> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("BCAM");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Testing string tokenizer");

		std::string strs[3] =  {
			"black_azi_foo",
			"  _black_azi_foo_",
			"P1\tP2  \t_4   5.5 6"
		};

		const char* delims = " \t_";
		
		auto res = TAConverter::tokenizeString(strs[0], delims);
		ensure(res.size() == 3);
		ensure(res[0] == "black");
		ensure(res[1] == "azi");
		ensure(res[2] == "foo");

		res = TAConverter::tokenizeString(strs[1], delims);
		ensure(res.size() == 3);
		ensure(res[0] == "black");
		ensure(res[1] == "azi");
		ensure(res[2] == "foo");
		
		res = TAConverter::tokenizeString(strs[2], delims);
		ensure(res.size() == 5);
		ensure(res[0] == "P1");
		ensure(res[1] == "P2");
		ensure(res[2] == "4");
		ensure(res[3] == "5.5");
		ensure(res[4] == "6");
    }	
	
	template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Testing name to number and vice versa");

		std::string names[4] = {
			"blue_polar_fc",
			"black_polar_rs",
			"blue_azimuthal_c",
			"bla_fc"
		};

		const int bits[4] = {
			TBCAMCalibrationDB::BC_BLUE | TBCAMCalibrationDB::BC_POL | TBCAMCalibrationDB::BC_FRONT | TBCAMCalibrationDB::BC_CAM,
			TBCAMCalibrationDB::BC_BLACK | TBCAMCalibrationDB::BC_POL | TBCAMCalibrationDB::BC_REAR | TBCAMCalibrationDB::BC_SRC,
			TBCAMCalibrationDB::BC_BLUE | TBCAMCalibrationDB::BC_AZI | TBCAMCalibrationDB::BC_CAM,
			12345
		};

		for (int i = 0; i < 3; i++) {
			int num = TBCAMCalibrationDB::getTypeIDfromStr(names[i]);
			string name = TBCAMCalibrationDB::getNameFromType(bits[i]);
			ensure(num == bits[i]);
			ensure(name == names[i]);
		}
		
		try {
			int num = TBCAMCalibrationDB::getTypeIDfromStr(names[3]);
		} catch (std::runtime_error& e)  {
			cout << "\nCaught expected exception: " << e.what() << "\n";
		}
		try {
			string name = TBCAMCalibrationDB::getNameFromType(bits[3]);
		} catch (std::runtime_error& e)  {
			cout << "\nCaught expected exception: " << e.what() << "\n";
		}
	}

	template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Testing whole calibration module");

		TBCAMCalibrationDB cfg;
		cfg.openDB("c:/temp/bcamdata.txt");
		ensure(cfg.isOpen());

		const TReal refvalues_rc[8] = {
			-1.257600e+01,
			-3.513800e+01,
			-8.192200e+01,
			 2.692000e-03,
			 2.480000e-03,
			-1.000000e+00,
			 7.501800e+01,
			 3.146395e+00
		};
		const TReal refvalues_fs[6] = {
			 4.705000e+00,
			-3.670700e+01,
			 3.600000e-01,
			 2.073500e+01,
			-3.667300e+01,
			 3.600000e-01
		};

		const TBCAMCalibrationDB::DBEntry& entry_rc(cfg.getDevice("20MABNDM000112", TBCAMCalibrationDB::getTypeIDfromStr("blue_polar_rc")));
		const TBCAMCalibrationDB::DBEntry& entry_fs(cfg.getDevice("20MABNDM000112", TBCAMCalibrationDB::getTypeIDfromStr("blue_polar_fs")));

		ensure(entry_rc == TBCAMCalibrationDB::DBEntry("20MABNDM000112", TBCAMCalibrationDB::getTypeIDfromStr("blue_polar_rc")));
		ensure(entry_rc.description == "blue_polar_rc");
		ensure(entry_rc.timestamp == "20080618135439");
		
		for (int i = 0; i < 8; i++)
			ensure_distance(refvalues_rc[i], entry_rc.values[i], 1e-3);
		for (int i = 0; i < 6; i++)
			ensure_distance(refvalues_fs[i], entry_fs.values[i], 1e-3);

	}

	template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Testing BCAM observation file reader");

		TReal refCoords[4][2] = {
			{2084.28, 1899.55},
			{2660.52, 1894.91},
			{2084.24, 1899.50},
			{2660.64, 1894.95}
		};

		try {
			TBCAMData xx;
			xx.readLWDAQFile("C:/xxx.txt");
		} catch (std::exception& e) {
			cout << "\nSuccessfully caught expected exception when opening a non-existing data file: " << e.what();
		}

		TBCAMData data;
		data.readLWDAQFile("C:/temp/bcammeasure.txt");
		ensure(data.getNumCoords("20MABNDM000165") == 20);

		TReal x,y;
		for (int i = 0; i < 4; i++) {
			data.getImagePoint(x, y, "20MABNDM000165", i);
			ensure_distance(x, refCoords[i][0], 1e-3);
			ensure_distance(y, refCoords[i][1], 1e-3);
		}
	}
}
