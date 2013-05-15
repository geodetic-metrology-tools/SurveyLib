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
		
		std::vector<string> res; 
		res = TAConverter::tokenizeString(strs[0], delims);
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


	}
}
