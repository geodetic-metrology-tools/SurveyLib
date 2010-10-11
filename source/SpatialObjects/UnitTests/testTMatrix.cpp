#include <TMatrix.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>
#include <sstream>

namespace tut
{
    struct test_TMatrix{};
    typedef test_group<test_TMatrix> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TMatrix class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Test before replacing NAG: Matrix product (square)");
        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        TMatrix B(3,3);
        B(0,0) = 1;  B(0,1) = -2; B(0, 2) = 1;
        B(1,0) = 2;  B(1,1) = 0;  B(1, 2) = -4;
        B(2,0) = 3;  B(2,1) = 9;  B(2, 2) = 2;

        TMatrix expected(3,3);
        expected(0,0)=34;expected(0,1)=75;expected(0,2)=13;
        expected(1,0)=10;expected(1,1)=15;expected(1,2)=-21;
        expected(2,0)=3;expected(2,1)=-32;expected(2,2)=-1;

        TMatrix prod = A*B;
        for(int i=0; i!=prod.numRows(); ++i)
            for(int j=0; j!=prod.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), prod(i,j), expected(i,j), 1e-7);
            }

    }

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Test before replacing NAG: Matrix product (rectangular)");
        
    }

    template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Test before replacing NAG: Matrix-vector product");
        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        TColumnVector v(3);
        v(0) = 2;
        v(1) = -6;
        v(2) = 109;

        TColumnVector expected(3);
        expected(0) = 975;
        expected(1) = 73;
        expected(2) = -210;

        TColumnVector res = A*v;

        std::cout << std::endl;
        for(int i=0; i!=3 ; ++i)
            std::cout << "############" << res(i) << std::endl;

        for(int i=0; i!=3 ; ++i)
        {
            std::stringstream msg;
            msg << "Value mismatch at (" << i << ","<< ")";
            ensure_distance(msg.str(), res(i), expected(i), static_cast<real>(1e-7));
        }
    }

    template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Test before replacing NAG: Solve Ax=B");

        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        TColumnVector b(3);
        b(0) = 5;
        b(1) = 8;
        b(2) = 33;

        TColumnVector expected(3);
        expected(0) = 3.672922252010725;
        expected(1) = 4.120643431635388;
        expected(2) = -1.584450402144772;

        TColumnVector res = A.eqnSolve(b);

        for(int i=0; i!=3 ; ++i)
        {
            std::stringstream msg;
            msg << "Value mismatch at (" << i << ","<< ")";
            ensure_distance(msg.str(), res(i), expected(i), static_cast<real>(1e-7));
        }
    }

    template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Test before replacing NAG: Matrix inverse");
        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        TMatrix expected(3,3);
        expected(0,0)=0.029490616621984;expected(0,1)=-0.034852546916890;expected(0,2)=0.115281501340483;
        expected(1,0)=-0.002680965147453;expected(1,1)=0.184986595174263;expected(1,2)=0.080428954423592;
        expected(2,0)=0.101876675603217;expected(2,1)=-0.029490616621984;expected(2,2)=-0.056300268096515;

        bool b = A.invert();
        ensure("Inversion succeeded", b);

        for(int i=0; i!=A.numRows(); ++i)
            for(int j=0; j!=A.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), A(i,j), expected(i,j), 1e-7);
            }
    }

    template<>
    template<>
    void object::test<6>()
    {
        set_test_name("Test before replacing NAG: Matrix inverse - singular - return false");
    }

        /*std::cout << std::endl;
        for(int i=0; i!=prod.numRows(); ++i)
        {
            for(int j=0; j!=prod.numCols(); ++j)
            {
                std::cout << "C(" << i << "," << j << ")=" << prod(i,j) << ";";
            }
            std::cout << std::endl;
        }*/

}
