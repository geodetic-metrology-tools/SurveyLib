// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <SpatialObjFns.h>
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
    tut::factory tf_surveyLibDLL("Test of SurveyLibDLL");
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

}

