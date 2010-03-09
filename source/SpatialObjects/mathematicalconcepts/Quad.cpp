#include "Quad.h"

Quad::Quad()
{
}

Quad::Quad(_Quad other)
{
	doubleValue = (double) other;
	value = other;
}

Quad::Quad(double other)
{
	doubleValue = other;
	value = other;
}

Quad::Quad(int other)
{
	doubleValue = other;
	value = other;
}

Quad::Quad(const Quad& other)
{
	doubleValue = (double) other.value;
	value = other.value;
}

Quad& Quad::operator =(const Quad& other)
{
	doubleValue = (double) other.value;
	value = other.value;
}

Quad& Quad::operator =(_Quad other)
{
	doubleValue = (double) other;
	value = other;
}

Quad& Quad::operator =(double other)
{
	doubleValue = other;
	value = other;
}

Quad& Quad::operator =(int other)
{
	doubleValue = other;
	value = other;
}

Quad operator +(const Quad& first, const Quad& second)
{
	Quad res(first.value + second.value);

	return res;
}

Quad operator -(const Quad& first, const Quad& second)
{
	Quad res(first.value - second.value);

	return res;
}

Quad operator *(const Quad& first, const Quad& second)
{
	Quad res(first.value * second.value);

	return res;
}

Quad operator /(const Quad& first, const Quad& second)
{
	Quad res(first.value / second.value);

	return res;
}

Quad operator +(double first, const Quad& second)
{
	Quad res(first + second.value);

	return res;
}

Quad operator -(double first, const Quad& second)
{
	Quad res(first - second.value);

	return res;
}

Quad operator *(double first, const Quad& second)
{
	Quad res(first * second.value);

	return res;
}

Quad operator /(double first, const Quad& second)
{
	Quad res(first / second.value);

	return res;
}

Quad operator +(const Quad& first, double second)
{
	Quad res(first.value + second);

	return res;
}

Quad operator -(const Quad& first, double second)
{
	Quad res(first.value - second);

	return res;
}

Quad operator *(const Quad& first, double second)
{
	Quad res(first.value * second);

	return res;
}

Quad operator /(const Quad& first, double second)
{
	Quad res(first.value / second);

	return res;
}

Quad operator +(int first, const Quad& second)
{
	Quad res(first + second.value);

	return res;
}

Quad operator -(int first, const Quad& second)
{
	Quad res(first - second.value);

	return res;
}

Quad operator *(int first, const Quad& second)
{
	Quad res(first * second.value);

	return res;
}

Quad operator /(int first, const Quad& second)
{
	Quad res(first / second.value);

	return res;
}

Quad operator +(const Quad& first, int second)
{
	Quad res(first.value + second);

	return res;
}

Quad operator -(const Quad& first, int second)
{
	Quad res(first.value - second);

	return res;
}

Quad operator *(const Quad& first, int second)
{
	Quad res(first.value * second);

	return res;
}

Quad operator /(const Quad& first, int second)
{
	Quad res(first.value / second);

	return res;
}

Quad operator +(_Quad first, const Quad& second)
{
	Quad res(first + second.value);

	return res;
}

Quad operator -(_Quad first, const Quad& second)
{
	Quad res(first - second.value);

	return res;
}

Quad operator *(_Quad first, const Quad& second)
{
	Quad res(first * second.value);

	return res;
}

Quad operator /(_Quad first, const Quad& second)
{
	Quad res(first / second.value);

	return res;
}

Quad operator +(const Quad& first, _Quad second)
{
	Quad res(first.value + second);

	return res;
}

Quad operator -(const Quad& first, _Quad second)
{
	Quad res(first.value - second);

	return res;
}

Quad operator *(const Quad& first, _Quad second)
{
	Quad res(first.value * second);

	return res;
}

Quad operator /(const Quad& first, _Quad second)
{
	Quad res(first.value / second);

	return res;
}

Quad& Quad::operator +=(const Quad& second)
{
	value += second.value;
	doubleValue += second.doubleValue;

	return *this;
}

Quad& Quad::operator -=(const Quad& second)
{
	value -= second.value;
	doubleValue -= second.doubleValue;

	return *this;
}

Quad& Quad::operator *=(const Quad& second)
{
	value *= second.value;
	doubleValue *= second.doubleValue;

	return *this;
}

Quad& Quad::operator /=(const Quad& second)
{
	value /= second.value;
	doubleValue /= second.doubleValue;

	return *this;
}

bool operator <(const Quad& first, const Quad& second)
{
	return first.value < second.value;
}

bool operator >(const Quad& first, const Quad& second)
{
	return first.value > second.value;
}

bool operator ==(const Quad& first, const Quad& second)
{
	return first.value == second.value;
}

bool operator !=(const Quad& first, const Quad& second)
{
	return first.value != second.value;
}

bool operator <=(const Quad& first, const Quad& second)
{
	return first.value <= second.value;
}

bool operator >=(const Quad& first, const Quad& second)
{
	return first.value >= second.value;
}

bool operator <(double first, const Quad& second)
{
	return first < second.value;
}

bool operator >(double first, const Quad& second)
{
	return first > second.value;
}

bool operator ==(double first, const Quad& second)
{
	return first == second.value;
}

bool operator !=(double first, const Quad& second)
{
	return first != second.value;
}

bool operator <=(double first, const Quad& second)
{
	return first <= second.value;
}

bool operator >=(double first, const Quad& second)
{
	return first >= second.value;
}

bool operator <(const Quad& first, double second)
{
	return first.value < second;
}

bool operator >(const Quad& first, double second)
{
	return first.value > second;
}

bool operator ==(const Quad& first, double second)
{
	return first.value == second;
}

bool operator !=(const Quad& first, double second)
{
	return first.value != second;
}

bool operator <=(const Quad& first, double second)
{
	return first.value <= second;
}

bool operator >=(const Quad& first, double second)
{
	return first.value >= second;
}

bool operator <(int first, const Quad& second)
{
	return first < second.value;
}

bool operator >(int first, const Quad& second)
{
	return first > second.value;
}

bool operator ==(int first, const Quad& second)
{
	return first == second.value;
}

bool operator !=(int first, const Quad& second)
{
	return first != second.value;
}

bool operator <=(int first, const Quad& second)
{
	return first <= second.value;
}

bool operator >=(int first, const Quad& second)
{
	return first >= second.value;
}

bool operator <(const Quad& first, int second)
{
	return first.value < second;
}

bool operator >(const Quad& first, int second)
{
	return first.value > second;
}

bool operator ==(const Quad& first, int second)
{
	return first.value == second;
}

bool operator !=(const Quad& first, int second)
{
	return first.value != second;
}

bool operator <=(const Quad& first, int second)
{
	return first.value <= second;
}

bool operator >=(const Quad& first, int second)
{
	return first.value >= second;
}

bool operator <(_Quad first, const Quad& second)
{
	return first < second.value;
}

bool operator >(_Quad first, const Quad& second)
{
	return first > second.value;
}

bool operator ==(_Quad first, const Quad& second)
{
	return first == second.value;
}

bool operator !=(_Quad first, const Quad& second)
{
	return first != second.value;
}

bool operator <=(_Quad first, const Quad& second)
{
	return first <= second.value;
}

bool operator >=(_Quad first, const Quad& second)
{
	return first >= second.value;
}

bool operator <(const Quad& first, _Quad second)
{
	return first.value < second;
}

bool operator >(const Quad& first, _Quad second)
{
	return first.value > second;
}

bool operator ==(const Quad& first, _Quad second)
{
	return first.value == second;
}

bool operator !=(const Quad& first, _Quad second)
{
	return first.value != second;
}

bool operator <=(const Quad& first, _Quad second)
{
	return first.value <= second;
}

bool operator >=(const Quad& first, _Quad second)
{
	return first.value >= second;
}

Quad Quad::operator -()
{
	return Quad(-this->value);
}

Quad::operator _Quad() const
{
	return value;
}

Quad::operator _Quad*()
{
	return &value;
}
