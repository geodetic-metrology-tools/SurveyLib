#include <SpatialObjFns.h>
#include <SpatialObjCFns.h>

#include <tut/tut.hpp>

#include <string>

#include <sstream>
#include <fstream>
#include <iostream>



namespace tut
{
    struct test_DLLMultipleTransformations{};
    typedef test_group<test_DLLMultipleTransformations> factory;
    typedef factory::object object;
}


namespace tut
{
    tut::factory tf("Test of SurveyLibDLL");
}

namespace tut
{
    /*! Testing valid options */
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("SurveyLib DLL test");

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
        set_test_name("SurveyLib DLL test");

		int returnData = 0;

		
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		char * geoid = "CG2000";

		returnData = transformToMLA (2180.15185, 2701.74391, 2359.87975, &x, &y, &z, "CG2000");
		tut::ensure_distance(x, 863.2361121728145, 1e-6);
		tut::ensure_distance(y, -510.2229651021653, 1e-6);
		tut::ensure_distance(z, -0.3143969823113366, 1e-6);     
    }  
   
}

