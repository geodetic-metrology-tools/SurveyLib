#ifndef TMATRIX_IMPL_79CFF806_6A12_46e0_BC89_66C513C8875F
#define TMATRIX_IMPL_79CFF806_6A12_46e0_BC89_66C513C8875F

#include <Eigen/Core>

class TMatrixImpl
{
public:
    TMatrixImpl();

    
    TMatrixImpl(int rows, int cols, double value);

    void setConstant(double value);
    void initDiag(double value);
    void resize(int rows, int cols);

    int rows() const { return fMatrix.rows(); }
    int cols() const { return fMatrix.cols(); }

    double & operator()(int row, int col);
    double operator()(int row, int col) const;
    TMatrixImpl & operator+=(const TMatrixImpl & rhs);
    TMatrixImpl & operator-=(const TMatrixImpl & rhs);
    TMatrixImpl & operator*=(const TMatrixImpl & rhs);
    TMatrixImpl operator*(TMatrixImpl & rhs) const;
    TMatrixImpl & operator*=(double value);
    TMatrixImpl & transpose();
    bool invert();
    TMatrixImpl solve(const TMatrixImpl & b) const;

private:
    Eigen::MatrixXd fMatrix;
};

#endif