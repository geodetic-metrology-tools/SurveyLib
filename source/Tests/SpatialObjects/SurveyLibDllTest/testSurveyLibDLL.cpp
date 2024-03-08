#include <SpatialObjFns.h>
#include <SpatialObjCFns.h>

#include <tut/tut.hpp>



namespace tut
{
    struct test_DLLMultipleTransformations{};
    typedef test_group<test_DLLMultipleTransformations> factory;
    typedef factory::object object;
}


namespace tut
{
    tut::factory tf_surveyLibDLL("Test of SpatialObjDLL");
}

namespace tut
{
    /*! Testing valid options */
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("SpatialObj DLL test");

		double x = 2180.15185;
		double y = 2701.74391;
		double N = 0;

		getCG2000NMachine(x, y, &N);
                
		tut::ensure_distance(N, 3.199512306355874e-4, 1e-6);
    }

	template<>
    template<>
    void object::test<2>()
    {
        set_test_name("SpatialObj DLL test");

		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

		transformToMLA (2180.15185, 2701.74391, 2359.87975, &x, &y, &z, "CG2000");

		// TODO fix this test
		tut::skip("Fix this test: returned values are wrong (see comments in code file).");
		tut::ensure_distance(x, 863.2361121728145, 1e-6); // x = -2180.0877673905798
		tut::ensure_distance(y, -510.2229651021653, 1e-6); // y = -2701.5209778501535
		tut::ensure_distance(z, -0.3143969823113366, 1e-6); // z = -2360.1941469823109
    }

	template<>
	template<>
	void object::test<3>()
	{
		set_test_name("SpatialObj DLL test");

		double x = 5800;
		double y = 9000;
		double xi = 0;
		double eta = 0;
		double n = 0;
		std::string geoid = "CG2000_Machine";

		std::cout << "\n Point (" << x << "," << y << ")\n";

		getXiGon(x, y, &xi, geoid.c_str());
		getEtaGon(x, y, &eta, geoid.c_str());
		getCG2000NMachine(x, y, &n);
		std::cout << std::fixed << std::setprecision(10) << "xi CG2000 = " << xi << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "eta CG2000 = " << eta << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "N CG2000 = " << n << "m\n";

		geoid = "CG1985_Machine";

		getXiGon(x, y, &xi, geoid.c_str());
		getEtaGon(x, y, &eta, geoid.c_str());
		getCG1985NMachine(x, y, &n);
		std::cout << std::fixed << std::setprecision(10) << "xi CG1985 = " << xi << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "eta CG1985 = " << eta << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "N CG1985 = " << n << "m\n";

		geoid = "CG1985_MachineGrid";
		getXiGon(x, y, &xi, geoid.c_str());
		getEtaGon(x, y, &eta, geoid.c_str());
		getCG1985NMachineGrid(x, y, &n);
		std::cout << std::fixed << std::setprecision(10) << "xi CG1985 Grid = " << xi << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "eta CG1985 Grid = " << eta << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "N CG1985 Grid = " << n << "m\n";

		geoid = "Sphere";
		getXiGon(x, y, &xi, geoid.c_str());
		getEtaGon(x, y, &eta, geoid.c_str());
		getCGSphereN(x, y, &n);
		std::cout << std::fixed << std::setprecision(10) << "xi Sphere = " << xi << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "eta Sphere = " << eta << "gon\n";
		std::cout << std::fixed << std::setprecision(10) << "N Sphere = " << n << "m\n";



		//tut::ensure_distance(xi, 3.199512306355874e-4, 1e-6);
	}




}

