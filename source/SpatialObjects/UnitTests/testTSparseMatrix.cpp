#include <iomanip>

#include <TMatrix.h>
#include <TSparseMatrix.h>

#include <tut/tut.hpp>

//method for data cout
void writeData (TSparseMatrix * foo)
{
	for(int row=0; row<foo->rowsCount(); ++row)
		{
			for(int col=0; col<foo->columnsCount(); ++col)
			{
				std::cout << std::setprecision(15) << (double)foo->operator()(row, col) << " ";
			}
			std::cout << ";" << std::endl;
		}
}

namespace tut
{
    struct test_TSparseMatrix{};
    typedef test_group<test_TSparseMatrix> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TSparseMatrix");
}


namespace tut
{
	/*
	/ALL THE TEST RESULT ARE CHECKED WITH MATLAB
	*/
	template<>
    template<>
    void object::test<1>()
    {
		//Matrix we are reading from a file is not positiv-definite
		//That is why the test fails
        set_test_name("Problem with Sparse Matrix ");
		TSparseMatrix * foo = TSparseMatrix::read_matrix_file(".\\test_files\\LOld3d.txt");
		std::setprecision(15);

		TSparseMatrix * result = foo->cholesky_decompose_lower_triangular_returning_lower_triangular();
		ensure("Should get the result!",result==NULL);
	}

    template<>
    template<>
    void object::test<2>()
    {
		set_test_name("Second test with simple positive-definit matrix ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple = test.toSparse();

		TSparseMatrix * result = simple->cholesky_decompose_lower_triangular_returning_lower_triangular();
		ensure("Matrix is not positiv-definit!",result!=NULL);
        
	}

	template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Problem with Sparse Matrix (Big size matrix) ");
		TSparseMatrix * foo = TSparseMatrix::read_matrix_file(".\\test_files\\AtPAOld2d.txt");

		//std::cout<<"Number of rows: "<<foo->rowsCount()<<std::endl;

		TSparseMatrix * result = foo->cholesky_decompose_lower_triangular_returning_lower_triangular();
		ensure("Should get the result!",result!=NULL);

	}

	template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Test of transposed method ");

		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple = test.toSparse();
		TSparseMatrix * simpleTrans = simple->transposed();

		TMatrix expected(3,3);
		expected(0,0)= 2; expected(0,1)= -1; expected(0,2)=  0;
		expected(1,0)= 0; expected(1,1)=  2; expected(1,2)= -1;
		expected(2,0)= 0; expected(2,1)=  0; expected(2,2)=  2;

		for(int i=0; i!=simpleTrans->rowsCount(); ++i)
            for(int j=0; j!=simpleTrans->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)simpleTrans->operator()(i,j), expected(i,j), 1e-5);
            }


	}
	/*
	/This function returns wrong result
	*/

	template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Test of symmetric_lower_inverse() method 5");

		TMatrix test(3,3);
		test(0,0)=64; test(0,1)=0; test(0,2)=0;
		test(1,0)=24; test(1,1)=34; test(1,2)=0;
		test(2,0)=32; test(2,1)=57; test(2,2)=101;
		
		TSparseMatrix * simple = test.toSparse();
		TSparseMatrix * simpleTrans = simple->symmetric_lower_inverse();
		

		TMatrix expected(3,3);
		expected(0,0)= 0.028906250000000; expected(0,1)= -0.093750000000000; expected(0,2)= 0.043750000000000;
		expected(1,0)= -0.093750000000000; expected(1,1)= 0.850000000000000; expected(1,2)= -0.450000000000000;
		expected(2,0)= 0.043750000000000; expected(2,1)=  -0.450000000000000; expected(2,2)=  0.250000000000000;

		for(int i=0; i!=simpleTrans->rowsCount(); ++i)
            for(int j=0; j!=simpleTrans->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)simpleTrans->operator()(i,j), expected(i,j), 1e-5);
            }
	}

	template<>
    template<>
    void object::test<6>()
    {
        set_test_name("Test of symmetric_lower_inverse_saving_L(TSparseMatrix*& L) method ");

		TMatrix test(3,3);
		test(0,0)=64; test(0,1)=0; test(0,2)=0;
		test(1,0)=24; test(1,1)=34; test(1,2)=0;
		test(2,0)=32; test(2,1)=57; test(2,2)=101;
		
		TSparseMatrix * simple = test.toSparse();

		TSparseMatrix * L;
		TSparseMatrix * simpleTrans = simple->symmetric_lower_inverse_saving_L(L);

		TMatrix expected(3,3);
		expected(0,0)= 0.028906250000000; expected(0,1)= -0.093750000000000; expected(0,2)= 0.043750000000000;
		expected(1,0)= -0.093750000000000; expected(1,1)= 0.850000000000000; expected(1,2)= -0.450000000000000;
		expected(2,0)= 0.043750000000000; expected(2,1)=  -0.450000000000000; expected(2,2)=  0.250000000000000;

		for(int i=0; i!=simpleTrans->rowsCount(); ++i)
            for(int j=0; j!=simpleTrans->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)simpleTrans->operator()(i,j), expected(i,j), 1e-5);
            }
		TMatrix expectedL(3,3);
		expectedL(0,0)=  8; expectedL(0,1)=  0; expectedL(0,2)=  0;
		expectedL(1,0)=  3; expectedL(1,1)=  5; expectedL(1,2)=  0;
		expectedL(2,0)=  4; expectedL(2,1)=  9; expectedL(2,2)=  2;

		for(int i=0; i!=simpleTrans->rowsCount(); ++i)
            for(int j=0; j!=simpleTrans->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at L(" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)L->operator()(i,j), expectedL(i,j), 1e-5);
            }
	}

	template<>
    template<>
    void object::test<7>()
    {
        set_test_name("Test of multiply_by_number(real) method ");

		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple = test.toSparse();

		real retvalue = 2.0; 
		simple->multiply_by_number(retvalue);


		TMatrix expected(3,3);
		expected(0,0)=  4; expected(0,1)=  0; expected(0,2)=  0;
		expected(1,0)= -2; expected(1,1)=  4; expected(1,2)=  0;
		expected(2,0)=  0; expected(2,1)= -2; expected(2,2)=  4;

		for(int i=0; i!=simple->rowsCount(); ++i)
            for(int j=0; j!=simple->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)simple->operator()(i,j), expected(i,j), 1e-5);
            }
	}

	// This does not work
	template<>
    template<>
    void object::test<8>()
    {
        set_test_name("Test ldlt_decompose_lower_triangular_returning_lower_triangular(real*& D) method ");

		TMatrix test(3,3);
		//test(0,0)=2; test(0,1)=0; test(0,2)=0;
		//test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		//test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		test(0,0)=64; test(0,1)=0; test(0,2)=0;
		test(1,0)=24; test(1,1)=34; test(1,2)=0;
		test(2,0)=32; test(2,1)=57; test(2,2)=101;
		
		TSparseMatrix * toSpar = test.toSparse();

		real * D;
//		std::cout << "Input " << std::endl;
//		writeData(toSpar);
		TSparseMatrix * simple = toSpar->ldlt_decompose_lower_triangular_returning_lower_triangular(D);
//		std::cout << "L " << std::endl;
//		writeData(simple);
//		std::cout << "D[0] = " << (double)D[0] << std::endl;
//		std::cout << "D[1] = " << (double)D[1] << std::endl;
//		std::cout << "D[2] = " << (double)D[2] << std::endl;

		TMatrix expected(3,3);
		expected(0,0)=  1;	  expected(0,1)=   0;					expected(0,2)=  0;
		expected(1,0)= -0.5;  expected(1,1)=  1;					expected(1,2)=  0;
		expected(2,0)=  0;    expected(2,1)= -0.666666666666667;	expected(2,2)=  1;

		/*for(int i=0; i!=simple->rowsCount(); ++i)
            for(int j=0; j!=simple->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)simple->operator()(i,j), expected(i,j), 1e-5);
            }*/
		ensure_distance("D[0]", (double)D[0], 64.0, 1e-5);
		ensure_distance("D[1]", (double)D[1], 85.0, 1e-5);
		ensure_distance("D[2]", (double)D[2], 1.176470588235294, 1e-5);
	}

	template<>
    template<>
    void object::test<9>()
    {
        set_test_name("Test invert_diagonal_matrix() method ");

		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=0; test(1,1)=3; test(1,2)=0;
		test(2,0)=0; test(2,1)=0; test(2,2)=-10;
		
		TSparseMatrix * simple = test.toSparse();

		TSparseMatrix * simpleTrans = simple->invert_diagonal_matrix();

		TMatrix expected(3,3);
		expected(0,0)=  0.5; expected(0,1)=  0;   expected(0,2)=  0;
		expected(1,0)=  0;   expected(1,1)=  0.333333; expected(1,2)=  0;
		expected(2,0)=  0;   expected(2,1)=  0;   expected(2,2)=  -0.1;

		for(int i=0; i!=simpleTrans->rowsCount(); ++i)
            for(int j=0; j!=simpleTrans->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)simpleTrans->operator()(i,j), expected(i,j), 1e-5);
            }
	}

	// This returns strange result: Matrix [ L | (L^-1)t]
	template<>
    template<>
    void object::test<10>()
    {
        set_test_name("Test of invert_lower_triangular_cholesky_decomposed() method ");
		TMatrix test(3,3);
		test(0,0)=64; test(0,1)=0; test(0,2)=0;
		test(1,0)=24; test(1,1)=34; test(1,2)=0;
		test(2,0)=32; test(2,1)=57; test(2,2)=101;
		
		TSparseMatrix * simple = test.toSparse();

		TSparseMatrix * result = simple->cholesky_decompose_lower_triangular_returning_lower_triangular();
		ensure("Matrix is not positiv-definit!",result!=NULL);

		TSparseMatrix * inversCholesky = result->invert_lower_triangular_cholesky_decomposed();
		//writeData(inversCholesky);

		TMatrix expected(3,3);
		expected(0,0)=  0.707106781186547;	 expected(0,1)=  0;						expected(0,2)=  0;
		expected(1,0)=  0.408248290463863;   expected(1,1)=  0.816496580927726;		expected(1,2)=  0;
		expected(2,0)=  0.288675134594813;   expected(2,1)=  0.577350269189626;		expected(2,2)=  0.866025403784439;

		for(int i=0; i!=inversCholesky->rowsCount(); ++i)
            for(int j=0; j!=inversCholesky->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)inversCholesky->operator()(i,j), expected(i,j), 1e-5);
            }
	}

	template<>
    template<>
    void object::test<11>()
    {
        set_test_name("Test of invert_lower_triangular_cholesky_decomposed_returning_lower_triangular() method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple = test.toSparse();

		TSparseMatrix * result = simple->cholesky_decompose_lower_triangular_returning_lower_triangular();
		ensure("Matrix is not positiv-definit!",result!=NULL);
													
		TSparseMatrix * inversCholesky = result->invert_lower_triangular_cholesky_decomposed_returning_lower_triangular();

		TMatrix expected(3,3);
		expected(0,0)=  0.707106781186548;  expected(0,1)=  0;					 expected(0,2)=  0;
		expected(1,0)=  0.408248290463863;  expected(1,1)=  0.816496580927726;   expected(1,2)=  0;
		expected(2,0)=  0.288675134594813;  expected(2,1)=  0.577350269189626;   expected(2,2)=  0.866025403784439;

		for(int i=0; i!=inversCholesky->rowsCount(); ++i)
            for(int j=0; j!=inversCholesky->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)inversCholesky->operator()(i,j), expected(i,j), 1e-10);
            }
	}

	

	template<>
    template<>
    void object::test<12>()
    {
        set_test_name("Test of invert_lower_triangular_ldlt_decomposed_returning_lower_triangular(const real* D) method ");
		TMatrix test(3,3);
		
		test(0,0)=64; test(0,1)=0; test(0,2)=0;
		test(1,0)=24; test(1,1)=34; test(1,2)=0;
		test(2,0)=32; test(2,1)=57; test(2,2)=101;
		
		TSparseMatrix * simple = test.toSparse();
		
		real *D;
		TSparseMatrix * l = simple->ldlt_decompose_lower_triangular_returning_lower_triangular(D);
										
		TSparseMatrix * inversM = l->invert_lower_triangular_ldlt_decomposed_returning_lower_triangular(D);
		//writeData(inversM);

		TMatrix expected(3,3);
		expected(0,0)= 0.028906250000000; expected(0,1)= 0; expected(0,2)= 0;
		expected(1,0)= -0.093750000000000; expected(1,1)=  0.850000000000000; expected(1,2)= 0;
		expected(2,0)= 0.043750000000000; expected(2,1)=  -0.450000000000000; expected(2,2)=  0.250000000000000;

		for(int i=0; i!=inversM->rowsCount(); ++i)
            for(int j=0; j!=inversM->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)inversM->operator()(i,j), expected(i,j), 1e-10);
            }
	}

	template<>
    template<>
    void object::test<13>()
    {
        set_test_name("Test of real* solve_eqn(const real* b) const method ");
		TMatrix test(3,3);
		test(0,0)=8; test(0,1)=0; test(0,2)=0;
		test(1,0)=3; test(1,1)=5; test(1,2)=0;
		test(2,0)=4; test(2,1)=9; test(2,2)=2;
		
		TSparseMatrix * simple = test.toSparse();

		real b[] = {3, 5, 1};
										
		real * x = simple->solve_eqn(b);
   
		ensure_distance("x[0]", (double)x[0],  -0.338281250000000, 1e-6);
		ensure_distance("x[1]", (double)x[1], 3.518750000000000, 1e-6);
		ensure_distance("x[2]", (double)x[2], -1.868750000000000, 1e-6);
	}

	template<>
    template<>
    void object::test<14>()
    {
        set_test_name("Test of real* solve_ldlt(const real* D, const real* b) const method ");
		//From matlab after cholesky decomposition
		TMatrix test(3,3);
		test(0,0)=8; test(0,1)=0; test(0,2)=0;
		test(1,0)=3; test(1,1)=5; test(1,2)=0;
		test(2,0)=4; test(2,1)=9; test(2,2)=2;
		
		TSparseMatrix * toSpar = test.toSparse();
		real *D;
		TSparseMatrix * l = toSpar->ldlt_decompose_lower_triangular_returning_lower_triangular(D);
		real b[] = {3, 5, 1};

		
		real * x = toSpar->solve_ldlt(D, b);
		ensure_distance("x[0]", (double)x[0],  -0.338281250000000, 1e-6);
		ensure_distance("x[1]", (double)x[1], 3.518750000000000, 1e-6);
		ensure_distance("x[2]", (double)x[2], -1.868750000000000, 1e-6);
	
	}

	//// the same as the above, only the "b" argument is being replaced from the solution. L transposed is required as an argument, too. I suggest you don't use that function, rather use the one above.
	//void solve_ldlt_in_place(const TSparseMatrix* LT, const real* D, real* b, int up_to = 0) const;

	//w komentarzu do funkcji jest napisane zeby jej nie uzywac
	template<>
    template<>
    void object::test<15>()
    {
        set_test_name("Test of void solve_ldlt_in_place(const TSparseMatrix* LT, const real* D, real* b, int up_to = 0) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple = test.toSparse();

		real r = 2.0;
										
		real * inversM = simple->solve_eqn(&r);
 
		
		
		/*TMatrix expected(3,3);
		expected(0,0)=  0.707106781186548;  expected(0,1)=  0;					 expected(0,2)=  0;
		expected(1,0)=  0.408248290463863;  expected(1,1)=  0.816496580927726;   expected(1,2)=  0;
		expected(2,0)=  0.288675134594813;  expected(2,1)=  0.577350269189626;   expected(2,2)=  0.866025403784439;

		for(int i=0; i!=inversM->rowsCount(); ++i)
            for(int j=0; j!=inversM->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)inversM->operator()(i,j), expected(i,j), 1e-10);
            }*/
	}

	template<>
    template<>
    void object::test<16>()
    {
        set_test_name("Test of TSparseMatrix* add(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TSparseMatrix * result = simple1->add(*simple2);
										
		TMatrix expected(3,3);
		expected(0,0)=  66;  expected(0,1)=  0;	   expected(0,2)=  0;
		expected(1,0)=  23;  expected(1,1)=  36;   expected(1,2)=  0;
		expected(2,0)=  32;  expected(2,1)=  56;   expected(2,2)=  103;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	template<>
    template<>
    void object::test<17>()
    {
        set_test_name("Test of TSparseMatrix* multiply_F(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TSparseMatrix * result = simple1->multiply_F(*simple2);
								
		TMatrix expected(3,3);
		expected(0,0)=  128;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -16;   expected(1,1)=  68;   expected(1,2)=  0;
		expected(2,0)=  40;   expected(2,1)=  80;   expected(2,2)=  202;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	template<>
    template<>
    void object::test<18>()
    {
        set_test_name("Test of TSparseMatrix* multiply_LM(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TSparseMatrix * result = simple1->multiply_LM(*simple2);
								
		TMatrix expected(3,3);
		expected(0,0)=  128;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -16;   expected(1,1)=  68;   expected(1,2)=  0;
		expected(2,0)=  40;   expected(2,1)=  80;   expected(2,2)=  202;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	//TSparseMatrix* multiply_diagonal_dense(const real* second, int secondCols) const;

	template<>
    template<>
    void object::test<19>()
    {
        set_test_name("Test of TSparseMatrix* multiply_diagonal_dense(const real* second, int secondCols) const method ");
		
		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple = test1.toSparse();

		real firstDAta[] = {3, 5, 1};
		int secondData = 3;

		TSparseMatrix * result = simple->multiply_diagonal_dense(firstDAta, secondData);
	
		////////writeData(result);
		TMatrix expected(3,3);
		expected(0,0)=  192;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  72;   expected(1,1)=  170;   expected(1,2)=  0;
		expected(2,0)=  96;   expected(2,1)=  285;   expected(2,2)=  101;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}

	}

	//this doesn't work
	template<>
    template<>
    void object::test<20>()
    {
        set_test_name("Test of TSparseMatrix* multiply_diagonal_sparse(const real* second, int secondCols) const method ");

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple = test1.toSparse();

		real firstDAta[] = {3, 5, 0};
		int secondData = 3;

		TSparseMatrix * result = simple->multiply_diagonal_sparse(firstDAta, secondData);

		TMatrix expected(3,3);
		expected(0,0)=  192;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  72;   expected(1,1)=  170;   expected(1,2)=  0;
		expected(2,0)=  96;   expected(2,1)=  285;   expected(2,2)=  0;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}

	}

	template<>
    template<>
    void object::test<21>()
    {
        set_test_name("Test of TSparseMatrix* multiply_F(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TSparseMatrix * result = simple1->multiply_F(*simple2);
		///////writeData(result);
								
		TMatrix expected(3,3);
		expected(0,0)=  128;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -16;   expected(1,1)=  68;   expected(1,2)=  0;
		expected(2,0)=  40;   expected(2,1)=  80;   expected(2,2)=  202;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}


	template<>
    template<>
    void object::test<22>()
    {
        set_test_name("Test of TSparseMatrix* multiply_LM(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TSparseMatrix * result = simple1->multiply_LM(*simple2);
		//////////writeData(result);
								
		TMatrix expected(3,3);
		expected(0,0)=  128;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -16;   expected(1,1)=  68;   expected(1,2)=  0;
		expected(2,0)=  40;   expected(2,1)=  80;   expected(2,2)=  202;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	template<>
    template<>
    void object::test<23>()
    {
        set_test_name("Test of real* multiply_returning_diagonal(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=64; test(0,1)=0;  test(0,2)=0;
		test(1,0)=24; test(1,1)=34; test(1,2)=1;
		test(2,0)=0;  test(2,1)=57; test(2,2)=101;

		TSparseMatrix * sparse = test.toSparse();

		TMatrix second(3,3);
		second(0,0)=6; second(0,1)=0; second(0,2)=0;
		second(1,0)=2; second(1,1)=3; second(1,2)=1;
		second(2,0)=0; second(2,1)=5; second(2,2)=1;

		TSparseMatrix * sparseSecond = second.toSparse();

		real * result = sparse->multiply_returning_diagonal(*sparseSecond);
		ensure_distance("result[0]", (double)result[0], 384.0, 1e-5);
		ensure_distance("result[1]", (double)result[1], 107.0, 1e-5);
		ensure_distance("result[2]", (double)result[2], 158.0, 1e-5);
	}


	template<>
    template<>
    void object::test<24>()
    {
        set_test_name("Test of TSparseMatrix* multiply_returning_lower_triangular_F(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TSparseMatrix * result = simple1->multiply_returning_lower_triangular_F(*simple2);
		////writeData(result);
								
		TMatrix expected(3,3);
		expected(0,0)=  128;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -16;   expected(1,1)=  68;   expected(1,2)=  0;
		expected(2,0)=  40;   expected(2,1)=  80;   expected(2,2)=  202;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	template<>
    template<>
    void object::test<25>()
    {
        set_test_name("Test of TSparseMatrix* multiply_returning_lower_triangular_LM(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TSparseMatrix * result = simple1->multiply_returning_lower_triangular_LM(*simple2);
		///////////writeData(result);
								
		TMatrix expected(3,3);
		expected(0,0)=  128;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -16;   expected(1,1)=  68;   expected(1,2)=  0;
		expected(2,0)=  40;   expected(2,1)=  80;   expected(2,2)=  202;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}
	
	template<>
    template<>
    void object::test<26>()
    {
        set_test_name("Test of TSparseMatrix* multiply_three_LM(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TMatrix test2(3,3);
		test2(0,0)=2; test2(0,1)=0; test2(0,2)=0;
		test2(1,0)=-1; test2(1,1)=2; test2(1,2)=0;
		test2(2,0)=0; test2(2,1)=-1; test2(2,2)=2;
		
		TSparseMatrix * simple3 = test.toSparse();

		TSparseMatrix * result = simple3->multiply_three_LM(*simple2, *simple1);
		//////////////writeData(result);
					
		TMatrix expected(3,3);
		expected(0,0)=  256;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -100;   expected(1,1)=  136;   expected(1,2)=  0;
		expected(2,0)=  0;   expected(2,1)=  -42;   expected(2,2)=  404;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	template<>
    template<>
    void object::test<27>()
    {
        set_test_name("Test of TSparseMatrix* multiply_three_F(const TSparseMatrix& second) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TMatrix test2(3,3);
		test2(0,0)=2; test2(0,1)=0; test2(0,2)=0;
		test2(1,0)=-1; test2(1,1)=2; test2(1,2)=0;
		test2(2,0)=0; test2(2,1)=-1; test2(2,2)=2;
		
		TSparseMatrix * simple3 = test.toSparse();

		TSparseMatrix * result = simple3->multiply_three_F(*simple2, *simple1);
		//////////////writeData(result);
					
		TMatrix expected(3,3);
		expected(0,0)=  256;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -100;   expected(1,1)=  136;   expected(1,2)=  0;
		expected(2,0)=  0;   expected(2,1)=  -42;   expected(2,2)=  404;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}


	////real* multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const;
	
	template<>
    template<>
    void object::test<28>()
    {
        set_test_name("Test of real* multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const method ");

		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * first = test.toSparse();

		TMatrix test2(3,3);
		test2(0,0)=64; test2(0,1)=0;  test2(0,2)=0;
		test2(1,0)=24; test2(1,1)=34; test2(1,2)=1;
		test2(2,0)=0;  test2(2,1)=57; test2(2,2)=101;

		TSparseMatrix * second = test.toSparse();

		TMatrix test3(3,3);
		test3(0,0)=6; test3(0,1)=0; test3(0,2)=0;
		test3(1,0)=2; test3(1,1)=3; test3(1,2)=1;
		test3(2,0)=0; test3(2,1)=5; test3(2,2)=1;

		TSparseMatrix * third = test3.toSparse();

		real * result = first->multiply_three_returning_diagonal(*second,*third);
		ensure_distance("result[0]", (double)result[0], 768.0, 1e-5);
		ensure_distance("result[1]", (double)result[1], 179.0, 1e-5);
		ensure_distance("result[2]", (double)result[2], 316.0, 1e-5);
	}


	template<>
    template<>
    void object::test<29>()
    {
        set_test_name("Test of TSparseMatrix* multiply_three_returning_lower_triangular_F(const TSparseMatrix& second, const TSparseMatrix& third) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TMatrix test2(3,3);
		test2(0,0)=2; test2(0,1)=0; test2(0,2)=0;
		test2(1,0)=-1; test2(1,1)=2; test2(1,2)=0;
		test2(2,0)=0; test2(2,1)=-1; test2(2,2)=2;
		
		TSparseMatrix * simple3 = test.toSparse();

		TSparseMatrix * result = simple3->multiply_three_returning_lower_triangular_F(*simple2, *simple1);
		//////////////////writeData(result);
					
		TMatrix expected(3,3);
		expected(0,0)=  256;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -100;   expected(1,1)=  136;   expected(1,2)=  0;
		expected(2,0)=  0;   expected(2,1)=  -42;   expected(2,2)=  404;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	template<>
    template<>
    void object::test<30>()
    {
        set_test_name("Test of TSparseMatrix* multiply_three_returning_lower_triangular_LM(const TSparseMatrix& second, const TSparseMatrix& third) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple1 = test.toSparse();

		TMatrix test1(3,3);
		test1(0,0)=64; test1(0,1)=0;  test1(0,2)=0;
		test1(1,0)=24; test1(1,1)=34; test1(1,2)=0;
		test1(2,0)=32; test1(2,1)=57; test1(2,2)=101;

		TSparseMatrix * simple2 = test1.toSparse();

		TMatrix test2(3,3);
		test2(0,0)=2; test2(0,1)=0; test2(0,2)=0;
		test2(1,0)=-1; test2(1,1)=2; test2(1,2)=0;
		test2(2,0)=0; test2(2,1)=-1; test2(2,2)=2;
		
		TSparseMatrix * simple3 = test.toSparse();

		TSparseMatrix * result = simple3->multiply_three_returning_lower_triangular_LM(*simple2, *simple1);
		//////////////////writeData(result);
					
		TMatrix expected(3,3);
		expected(0,0)=  256;  expected(0,1)=  0;    expected(0,2)=  0;
		expected(1,0)=  -100;   expected(1,1)=  136;   expected(1,2)=  0;
		expected(2,0)=  0;   expected(2,1)=  -42;   expected(2,2)=  404;

		for(int i=0; i!=result->rowsCount(); ++i)
            for(int j=0; j!=result->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)result->operator()(i,j), expected(i,j), 1e-10);
			}
            
	}

	//OPERATORS

	template<>
    template<>
    void object::test<31>()
    {
        set_test_name("Test of real* operator *(const real* right) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=1;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;
		
		TSparseMatrix * simple = test.toSparse();

		real right[] = {2, -1, 3};

		real * result = simple->operator*(right);
		ensure_distance("result[0]", (double)result[0],  7.0, 1e-5);
		ensure_distance("result[1]", (double)result[1], -4.0, 1e-5);
		ensure_distance("result[2]", (double)result[2],  7.0, 1e-5);
	}

	template<>
    template<>
    void object::test<32>()
    {
        set_test_name("Test of real* operator *(const TColumnVector& right) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=0; test(0,2)=0;
		test(1,0)=-1; test(1,1)=2; test(1,2)=0;
		test(2,0)=0; test(2,1)=-1; test(2,2)=2;

		TSparseMatrix * simple = test.toSparse();

		TColumnVector vec(3);
        vec(0) = 3;
        vec(1) = 5;
        vec(2) = 2;

		real * result = simple->operator*(vec);
		ensure_distance("result[0]", (double)result[0],  6.0, 1e-5);
		ensure_distance("result[1]", (double)result[1],  7.0, 1e-5);
		ensure_distance("result[2]", (double)result[2], -1.0, 1e-5);
	}

	template<>
    template<>
    void object::test<33>()
    {
        set_test_name("Test of real operator ()(int row, int column) const method ");
		TMatrix test(3,3);
		test(0,0)=2; test(0,1)=6; test(0,2)=9;
		test(1,0)=-1; test(1,1)=5; test(1,2)=0;
		test(2,0)=103; test(2,1)=-77; test(2,2)=7;

		TSparseMatrix * simple = test.toSparse();

		int rr = 0;
		int cc = 2;

		//real result = simple->operator()(rr, cc);

		for(int i=0; i!=simple->rowsCount(); ++i)
            for(int j=0; j!=simple->columnsCount(); ++j)
            {
                std::stringstream msg;
                msg << "Value mismatch at (" << i << "," << j << ")";
                ensure_distance(msg.str(), (double)simple->operator()(i,j), test(i,j), 1e-10);
			}
	}

}
