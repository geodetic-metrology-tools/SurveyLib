// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include "Quad.h"

#include <sstream>
#include <tut/tut.hpp>

namespace tut
{
    struct test_QuadSupport{};
    typedef test_group<test_QuadSupport> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test the Quad support");
}

namespace tut
{

	template<>
	template<>
	void object::test<1>()
	{
		set_test_name("TReal operations");

        /* Value passed to a mathematical function is a TReal.
         * This can either be a true Intel _Quad or our debug wrapper.
         * However, mathematical functions operating on quadruple precision
         * types will always return _Quad values.
         *
         * TUT ensure_equals function expects that the last three parameters
         * are of the same type. For that reason we need to cast the result
         * of the mathematical function to TReal explicitly - to make it work
         * in case of debug wrapper.
         */
		ensure_equals("ceil",  static_cast<TReal>(ceilq(TReal(2.3))),   TReal(3), TReal(1e-9));
		ensure_equals("floor", static_cast<TReal>(floorq(TReal(2.3))),  TReal(2.0), TReal(1e-9));
		ensure_equals("fmod",  static_cast<TReal>(fmodq(TReal(5.3),    TReal(2.0))), TReal(1.3), TReal(1e-9));
		ensure_equals("fabs",  static_cast<TReal>(fabsq(TReal(-2.0))),  TReal(2.0), TReal(1e-9));

		ensure_equals("exp",   static_cast<TReal>(expq(TReal(-2.123))), TReal(0.119672073228513), TReal(1e-9));
		ensure_equals("log",   static_cast<TReal>(logq(TReal(131.32))), TReal(4.87763709263339), TReal(1e-9));
		ensure_equals("log10", static_cast<TReal>(log10q(TReal(23.11))),TReal(1.36379994547911), TReal(1e-9));

		ensure_equals("pow",   static_cast<TReal>(powq(TReal(2.123), TReal(3.2123))), TReal(11.2269416700306), TReal(1e-9));
		ensure_equals("sqrt",  static_cast<TReal>(sqrtq(TReal(131.32))), TReal(11.4594938806214), TReal(1e-9));

		ensure_equals("sin",   static_cast<TReal>(sinq(TReal(2.123))), TReal(0.851370621147159), TReal(1e-9));
		ensure_equals("cos",   static_cast<TReal>(cosq(TReal(2.123))), TReal(-0.524564643726109), TReal(1e-9));
		ensure_equals("tan",   static_cast<TReal>(tanq(TReal(2.123))), TReal(-1.62300420230321), TReal(1e-9));

		ensure_equals("sinh",  static_cast<TReal>(sinhq(TReal(2.123))), TReal(4.118248177279596), TReal(1e-9));
		ensure_equals("cosh",  static_cast<TReal>(coshq(TReal(2.123))), TReal(4.237920250508108), TReal(1e-9));
		ensure_equals("tanh",  static_cast<TReal>(tanhq(TReal(2.123))), TReal(0.971761603297239), TReal(1e-9));

		ensure_equals("asin",  static_cast<TReal>(asinq(TReal(0.123))), TReal(0.123312275191872), TReal(1e-9));
		ensure_equals("acos",  static_cast<TReal>(acosq(TReal(0.123))), TReal(1.447484051603025), TReal(1e-9));
		ensure_equals("atan",  static_cast<TReal>(atanq(TReal(0.123))), TReal(0.122385281471803), TReal(1e-9));
		ensure_equals("atan2", static_cast<TReal>(atan2q(TReal(0.123),TReal(4.1121323))), TReal(0.0299025731966842), TReal(1e-9));

	}

	template<>
	template<>
	void object::test<2>()
	{
		set_test_name("TReal IO");
		TReal value = -2.4578;
		std::stringstream stream;
		stream << value;
		stream >> value;
		ensure_equals("After in/out to stream", value, TReal(-2.4578), TReal(1e-9));
	}

    template<>
	template<>
	void object::test<3>()
	{
        set_test_name("Basic assignments");
        
        // Construct from double
        TReal value = 2.5;
        ensure_equals("Construction (double)", value, TReal(2.5), TReal(1e-9));
        
        // Copy construction
        TReal copy = value;
        ensure_equals("Copy construction", copy, value, TReal(1e-9));

        // Assignment operator (from TReal)
        TReal foo = 3;
        foo = value;
        ensure_equals("Assignment operator (TReal) ", foo, value, TReal(1e-9));

#if __INTEL_COMPILER && USE_QUAD
        // Assignment operator (from _Quad)
        foo = _Quad(5.25);
        ensure_equals("Assignment operator (_Quad) ", foo, TReal(5.25), TReal(1e-9));
#endif

        // Assignment operator (from double)
        foo = 6.24424;
        ensure_equals("Assignment operator (double) ", foo, TReal(6.24424), TReal(1e-9));

        // Assignment operator (from int)
        foo = 128;
        ensure_equals("Assignment operator (int) ", foo, TReal(128), TReal(1e-9));

        // TReal -> double
        double bar = value;
        ensure_equals("TReal -> double", bar, 2.5, 1e-9);
    }

    template<>
	template<>
	void object::test<4>()
	{
        set_test_name("Basic operations");

        TReal a = 2.5;
        TReal b = 7.5;

        TReal c = a + b;
        ensure_equals("TReal = TReal + TReal", c, TReal(10), TReal(1e-9));

        double d = a + b;
        ensure_equals("double = TReal + TReal", d, 10.0, 1e-9);

        TReal e = a + 2.0 + b + 3;
        ensure_equals("TReal = different types", e, TReal(15), TReal(1e-9));

        // Adding to double:
        double f = 10;
        f += TReal(5);
        ensure_equals("TReal -> double", f, 15.0, 1e-9);

        TReal g = TReal(10) + fabsq(TReal(-5)) + fabs(3.0) + TReal(7);
        ensure_equals("g", g, TReal(25), TReal(1e-9));
    }

    template<>
	template<>
	void object::test<5>()
	{
        set_test_name("Compound assignment");

        TReal a = 10;

        a += 5;
        ensure_equals("+=", a, TReal(15), TReal(1e-9));

        a -= 5;
        ensure_equals("-=", a, TReal(10), TReal(1e-9));

        a *= 5;
        ensure_equals("*=", a, TReal(50), TReal(1e-9));

        a /= 2;
        ensure_equals("/=", a, TReal(25), TReal(1e-9));
    }

    int fun(TReal) {return 1;}
#if USE_QUAD
    int fun(double) {return 2;}
#endif
    int fun(long double) {return 2;}
    int fun(int) {return 4;}
    template<>
	template<>
	void object::test<6>()
	{
        set_test_name("Functions and type selection");

        TReal a = 10;
        ensure_equals("TReal variant called", fun(a), 1);
        ensure_equals("TReal variant called", fun(a+1), 1);
        ensure_equals("TReal variant called", fun(1+a), 1);
        ensure_equals("TReal variant called", fun(a+1.0), 1);
        ensure_equals("TReal variant called", fun(1.0+a), 1);
    }
}
