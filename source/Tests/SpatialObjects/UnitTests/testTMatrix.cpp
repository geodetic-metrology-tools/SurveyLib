#include <TMatrix.h>
#include <TSparseMatrix.h>
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
        
        TMatrix A(3,2); 
        A(0,0) = 3;  A(0,1) = 2; 
        A(1,0) = -3; A(1,1) = 5; 
        A(2,0) = 7;  A(2,1) = 1;

        TMatrix B(2,3);
        B(0,0) = 1;  B(0,1) = -2; B(0, 2) = 1;
        B(1,0) = 2;  B(1,1) = 0;  B(1, 2) = -4;
        
        TMatrix expected(3,3);
        expected(0,0)=7;expected(0,1)=-6;expected(0,2)=-5;
        expected(1,0)=7;expected(1,1)=6;expected(1,2)=-23;
        expected(2,0)=9;expected(2,1)=-14;expected(2,2)=3;

        TMatrix prod = A*B;

        /*std::cout << std::endl;
        for(int i=0; i!=prod.numRows(); ++i)
        {
            for(int j=0; j!=prod.numCols(); ++j)
            {
                std::cout << "C(" << i << "," << j << ")=" << prod(i,j) << ";";
            }
            std::cout << std::endl;
        }*/

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

        //std::cout << std::endl;
        //for(int i=0; i!=3 ; ++i)
            //std::cout << "############" << res(i) << std::endl;

        for(int i=0; i!=3 ; ++i)
        {
            std::stringstream msg;
            msg << "Value mismatch at (" << i << ","<< ")";
            ensure_distance(msg.str(), res(i), expected(i), static_cast<TReal>(1e-7));
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
            ensure_distance(msg.str(), res(i), expected(i), static_cast<TReal>(1e-7));
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
    
        TMatrix A(2,2); 
        A(0,0) = 1; A(0,1) = 2; 
        A(1,0) = 2; A(1,1) = 4; 
        
        ensure_not("Singular matrix inversion returned true", A.invert());
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

    template<>
    template<>
    void object::test<7>()
    {
        //Copy assignement operator
        set_test_name("Test before replacing NAG: Matrix assignement operator");
    
        TMatrix A(2,2); 
        A(0,0) = 1; A(0,1) = 2; 
        A(1,0) = 2; A(1,1) = 4; 

        TMatrix B = A;

        for(int i=0; i!=A.numRows(); ++i)
            for(int j=0; j!=A.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), B(i,j), A(i,j), 1e-7);
            }
        
        
    }

    template<>
    template<>
    void object::test<8>()
    {
        //Sum of the matix
        set_test_name("Test before replacing NAG: Sum of the matix");
    
        TMatrix A(2,2); 
        A(0,0) = 1; A(0,1) = 2; 
        A(1,0) = 2; A(1,1) = 4; 

        TMatrix B(2,2);
        B(0,0) = 5; B(0,1) = 2; 
        B(1,0) = 3; B(1,1) = 2;
        
        TMatrix C = A + B;
        
        TMatrix expected(2,2);
        expected(0,0)=6; expected(0,1)=4;
        expected(1,0)=5; expected(1,1)=6;

        for(int i=0; i!=C.numRows(); ++i)
            for(int j=0; j!=C.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), C(i,j), expected(i,j), 1e-7);
            }
        
        
    }

    template<>
    template<>
    void object::test<9>()
    {
        //Sum of the matix
        set_test_name("Test before replacing NAG: Sum of the matix +=");
    
        TMatrix A(2,2); 
        A(0,0) = 1; A(0,1) = 2; 
        A(1,0) = 2; A(1,1) = 4; 

        TMatrix B(2,2);
        B(0,0) = 5; B(0,1) = 2; 
        B(1,0) = 3; B(1,1) = 2;
        
        A += B;
        
        TMatrix expected(2,2);
        expected(0,0)=6; expected(0,1)=4;
        expected(1,0)=5; expected(1,1)=6;

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
    void object::test<10>()
    {
        set_test_name("Test before replacing NAG: Difference of the matix");
    
        TMatrix A(2,2); 
        A(0,0) = 1; A(0,1) = 2; 
        A(1,0) = 2; A(1,1) = 4; 

        TMatrix B(2,2);
        B(0,0) = 5; B(0,1) = 2; 
        B(1,0) = 3; B(1,1) = 2;
        
        TMatrix C = A - B;
        
        TMatrix expected(2,2);
        expected(0,0)=-4; expected(0,1)=0;
        expected(1,0)=-1; expected(1,1)=2;

        for(int i=0; i!=A.numRows(); ++i)
            for(int j=0; j!=A.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), C(i,j), expected(i,j), 1e-7);
            }        
    }
    template<>
    template<>
    void object::test<11>()
    {
        set_test_name("Test before replacing NAG: Difference of the matix -=");
    
        TMatrix A(2,2); 
        A(0,0) = 1; A(0,1) = 2; 
        A(1,0) = 2; A(1,1) = 4; 

        TMatrix B(2,2);
        B(0,0) = 5; B(0,1) = 2; 
        B(1,0) = 3; B(1,1) = 2;
        
        A -= B;
        
        TMatrix expected(2,2);
        expected(0,0)=-4; expected(0,1)=0;
        expected(1,0)=-1; expected(1,1)=2;

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
    void object::test<12>()
    {
        set_test_name("Test before replacing NAG: Matrix transposition");
    
        TMatrix A(2,3); 
        A(0,0) = 1; A(0,1) = 2; A(0,2) = 2;
        A(1,0) = 2; A(1,1) = 4; A(1,2) = 2; 

        TMatrix B = A.transposed();


        TMatrix expected(3,2);
        expected(0,0)=1; expected(0,1)=2;
        expected(1,0)=2; expected(1,1)=4;
        expected(2,0)=2; expected(2,1)=2;

        for(int i=0; i!=B.numRows(); ++i)
            for(int j=0; j!=B.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), B(i,j), expected(i,j), 1e-7);
            }
    }

    template<>
    template<>
    void object::test<13>()
    {
        set_test_name("Test before replacing NAG: Matrix product (square)*=");
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

        A *= B;
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
    void object::test<14>()
    {
        set_test_name("Test before replacing NAG: Matrix munliplication by a scalar");
        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        double k = 2;

        TMatrix expected(3,3);
        expected(0,0)=6;  expected(0,1)=4;  expected(0,2)=18;
        expected(1,0)=-6; expected(1,1)=10; expected(1,2)=2;
        expected(2,0)=14; expected(2,1)=2;  expected(2,2)=-4;

       TMatrix C = A*k;
        for(int i=0; i!=C.numRows(); ++i)
            for(int j=0; j!=C.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), C(i,j), expected(i,j), 1e-7);
            }

    }

    template<>
    template<>
    void object::test<15>()
    {
        set_test_name("Test before replacing NAG: Inits matrix to a common value");
        TMatrix A(3,3);

        double val = 5;
        bool bo = A.initDiag(val);
    
        TMatrix expected(3,3);
        expected(0,0)=5; expected(0,1)=0; expected(0,2)=0;
        expected(1,0)=0; expected(1,1)=5; expected(1,2)=0;
        expected(2,0)=0; expected(2,1)=0; expected(2,2)=5;

       /* std::cout << std::endl;
        for(int i=0; i!=A.numRows(); ++i)
        {
            for(int j=0; j!=A.numCols(); ++j)
            {
                std::cout << "C(" << i << "," << j << ")=" << A(i,j) << ";";
            }
            std::cout << std::endl;
        }*/

        if( bo == true)
        {
            for(int i=0; i!=A.numRows(); ++i)
                for(int j=0; j!=A.numCols(); ++j)
                {
                    std::stringstream msg;
                    msg << "Value mismatch at (" << i << "," << j << ")";
                    ensure_distance(msg.str(), A(i,j), expected(i,j), 1e-7);
                }
        }
        else
            std::cout<<"Init faild"<<std::endl;

    }

    template<>
    template<>
    void object::test<16>()
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

        TMatrix B = A.inverse();
        

        for(int i=0; i!=B.numRows(); ++i)
            for(int j=0; j!=B.numCols(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), B(i,j), expected(i,j), 1e-7);
            }
    }



    template<>
    template<>
    void object::test<17>()
    {
        set_test_name("Test before replacing NAG: Clear the matrix");
        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        A.clear();
    
        TMatrix expected(3,3);
        expected(0,0)=0; expected(0,1)=0; expected(0,2)=0;
        expected(1,0)=0; expected(1,1)=0; expected(1,2)=0;
        expected(2,0)=0; expected(2,1)=0; expected(2,2)=0;

       /* std::cout << std::endl;
        for(int i=0; i!=A.numRows(); ++i)
        {
            for(int j=0; j!=A.numCols(); ++j)
            {
                std::cout << "C(" << i << "," << j << ")=" << A(i,j) << ";";
            }
            std::cout << std::endl;
        }*/
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
    void object::test<18>()
    {
        set_test_name("Adding matrixes of wrong sizes");
        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        TMatrix B(2,2);
        B(0,0) = 1;  B(0,1) = -2; 
        B(1,0) = 2;  B(1,1) = 0;

        TMatrix result = A + B;
        ensure_equals("Status should be kNull", result.isInitialise(), false);
    }

    template<>
    template<>
    void object::test<19>()
    {
        set_test_name("Adding matrixes of wrong sizes");
        TMatrix A(3,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;
        A(2,0) = 7;  A(2,1) = 1; A(2, 2) = -2;

        TMatrix B(2,2);
        B(0,0) = 1;  B(0,1) = -2; 
        B(1,0) = 2;  B(1,1) = 0;

        TMatrix result = A - B;
		ensure_equals("Status should be kNull", result.isInitialise(), false);
    }
	
	template<>
    template<>
    void object::test<20>()
    {
		set_test_name("Adding matrixes of wrong sizes");
        TMatrix A(2,3);
        A(0,0) = 3;  A(0,1) = 2; A(0, 2) = 9;
        A(1,0) = -3; A(1,1) = 5; A(1, 2) = 1;

		TColumnVector v(3);
        v(0) = 2;
        v(1) = -6;
        v(2) = 1;

		TColumnVector result = A*v;

		TColumnVector expected(2);
		ensure_distance("result(0)", (double)result(0), 3.0, 1e-7);
		ensure_distance("result(1)", (double)result(1), -35.0, 1e-7);
	}

	template<>
    template<>
    void object::test<21>()
    {
		set_test_name("Specialized memory-friendly method to get main diagonal of A*P*AT");
		
		const int n(8);
		const int u(6);
		
		std::vector<TTriplet> entriesA;
		std::vector<TTriplet> entriesP;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < u; j++) {
				entriesA.push_back(TTriplet(i,j,100*i+j));
			}
		}
		for (int i = 0; i < u; i++) {
			for (int j = 0; j < u; j++) {
				entriesP.push_back(TTriplet(i,j,200*i+j));
			}
		}
		
		TSparseMatrix A(n,u);
		TSparseMatrix P(u,u);
		
		A.setFromTriplets(entriesA.begin(), entriesA.end());
		P.setFromTriplets(entriesP.begin(), entriesP.end());

		// calculate reference result
		TSparseMatrix res = A*P*A.transpose();
		TVector ref = res.diagonal();

		// use new function
		TVector newres(n);
		TSparseUtils::multABATasDiag(newres, A, P);
std::cout << "\n" << ref <<"\n\n";
std::cout << newres<<"\n\n";

		// compare result vectors
		for (int i = 0; i < n; i++)
			ensure_distance("Difference in result for optimized matrix multiplication: ", ref(i)-newres(i), 0.0, 1e-8);
		


	}

}
