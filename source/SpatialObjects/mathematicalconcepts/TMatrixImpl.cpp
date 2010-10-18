#include <TMatrixImpl.h>

#include <Eigen/LU>

TMatrixImpl::TMatrixImpl()
{
}

TMatrixImpl::TMatrixImpl(int rows, int cols, double value)
: fMatrix(Eigen::MatrixXd::Constant(rows, cols, value))
{
}

void TMatrixImpl::setConstant(double value)
{
    fMatrix.setConstant(value);
}

void TMatrixImpl::initDiag(double value)
{
    fMatrix.setIdentity(rows(), cols());
    fMatrix *= value;
}

void TMatrixImpl::resize(int rows, int cols)
{
    fMatrix.setConstant(rows, cols, 0.0);
}

double & TMatrixImpl::operator()(int row, int col)
{
    return fMatrix(row,col);
}

double TMatrixImpl::operator()(int row, int col) const
{
    return fMatrix(row,col);
}

TMatrixImpl & TMatrixImpl::operator+=(const TMatrixImpl & rhs)
{
    fMatrix += rhs.fMatrix;
    return *this;
}

TMatrixImpl & TMatrixImpl::operator-=(const TMatrixImpl & rhs)
{
    fMatrix -= rhs.fMatrix;
    return *this;
}

TMatrixImpl & TMatrixImpl::operator*=(const TMatrixImpl & rhs)
{
    fMatrix *= rhs.fMatrix;
    return *this;
}

TMatrixImpl TMatrixImpl::operator*(TMatrixImpl & rhs) const
{
    TMatrixImpl res;
    res.fMatrix = this->fMatrix * rhs.fMatrix;
    return res;
}

TMatrixImpl & TMatrixImpl::operator*=(double value)
{
    fMatrix *= value;
    return *this;
}

TMatrixImpl & TMatrixImpl::transpose()
{
    fMatrix.transposeInPlace();
    return *this;
}

bool TMatrixImpl::invert()
{
    Eigen::LU<Eigen::MatrixXd> lu(fMatrix);
    if(lu.isInvertible())
    {
        fMatrix = lu.inverse();
        return true;
    }
    return false;
}

TMatrixImpl TMatrixImpl::solve(const TMatrixImpl & b) const
{
    TMatrixImpl result;
    // TODO: Report if can be solved
    Eigen::LU<Eigen::MatrixXd> lu(fMatrix);
    lu.solve(b.fMatrix, &result.fMatrix);
    return result;
}