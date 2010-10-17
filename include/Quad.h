#ifndef QUAD_H
#define QUAD_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <iosfwd>

#if _DEBUG && __INTEL_COMPILER

class Quad
{
public:
	Quad(_Quad other);
	Quad(double other);
	Quad(int other);
	Quad(const Quad& other);
	Quad();

	Quad& operator =(const Quad& other);
	Quad& operator =(_Quad other);
	Quad& operator =(double other);
	Quad& operator =(int other);

	friend Quad operator +(const Quad& first, const Quad& second);
	friend Quad operator -(const Quad& first, const Quad& second);
	friend Quad operator *(const Quad& first, const Quad& second);
	friend Quad operator /(const Quad& first, const Quad& second);

	friend Quad operator +(double first, const Quad& second);
	friend Quad operator -(double first, const Quad& second);
	friend Quad operator *(double first, const Quad& second);
	friend Quad operator /(double first, const Quad& second);

	friend Quad operator +(const Quad& first, double second);
	friend Quad operator -(const Quad& first, double second);
	friend Quad operator *(const Quad& first, double second);
	friend Quad operator /(const Quad& first, double second);

	friend Quad operator +(int first, const Quad& second);
	friend Quad operator -(int first, const Quad& second);
	friend Quad operator *(int first, const Quad& second);
	friend Quad operator /(int first, const Quad& second);

	friend Quad operator +(const Quad& first, int second);
	friend Quad operator -(const Quad& first, int second);
	friend Quad operator *(const Quad& first, int second);
	friend Quad operator /(const Quad& first, int second);

	friend Quad operator +(_Quad first, const Quad& second);
	friend Quad operator -(_Quad first, const Quad& second);
	friend Quad operator *(_Quad first, const Quad& second);
	friend Quad operator /(_Quad first, const Quad& second);

	friend Quad operator +(const Quad& first, _Quad second);
	friend Quad operator -(const Quad& first, _Quad second);
	friend Quad operator *(const Quad& first, _Quad second);
	friend Quad operator /(const Quad& first, _Quad second);
	
	friend bool operator <(const Quad& first, const Quad& second);
	friend bool operator >(const Quad& first, const Quad& second);
	friend bool operator ==(const Quad& first, const Quad& second);
	friend bool operator !=(const Quad& first, const Quad& second);
	friend bool operator <=(const Quad& first, const Quad& second);
	friend bool operator >=(const Quad& first, const Quad& second);
	
	friend bool operator <(double first, const Quad& second);
	friend bool operator >(double first, const Quad& second);
	friend bool operator ==(double first, const Quad& second);
	friend bool operator !=(double first, const Quad& second);
	friend bool operator <=(double first, const Quad& second);
	friend bool operator >=(double first, const Quad& second);
	
	friend bool operator <(const Quad& first, double second);
	friend bool operator >(const Quad& first, double second);
	friend bool operator ==(const Quad& first, double second);
	friend bool operator !=(const Quad& first, double second);
	friend bool operator <=(const Quad& first, double second);
	friend bool operator >=(const Quad& first, double second);
	
	friend bool operator <(int first, const Quad& second);
	friend bool operator >(int first, const Quad& second);
	friend bool operator ==(int first, const Quad& second);
	friend bool operator !=(int first, const Quad& second);
	friend bool operator <=(int first, const Quad& second);
	friend bool operator >=(int first, const Quad& second);
	
	friend bool operator <(const Quad& first, int second);
	friend bool operator >(const Quad& first, int second);
	friend bool operator ==(const Quad& first, int second);
	friend bool operator !=(const Quad& first, int second);
	friend bool operator <=(const Quad& first, int second);
	friend bool operator >=(const Quad& first, int second);
	
	friend bool operator <(_Quad first, const Quad& second);
	friend bool operator >(_Quad first, const Quad& second);
	friend bool operator ==(_Quad first, const Quad& second);
	friend bool operator !=(_Quad first, const Quad& second);
	friend bool operator <=(_Quad first, const Quad& second);
	friend bool operator >=(_Quad first, const Quad& second);
	
	friend bool operator <(const Quad& first, _Quad second);
	friend bool operator >(const Quad& first, _Quad second);
	friend bool operator ==(const Quad& first, _Quad second);
	friend bool operator !=(const Quad& first, _Quad second);
	friend bool operator <=(const Quad& first, _Quad second);
	friend bool operator >=(const Quad& first, _Quad second);

	Quad operator -();

	Quad& operator +=(const Quad& second);
	Quad& operator -=(const Quad& second);
	Quad& operator *=(const Quad& second);
	Quad& operator /=(const Quad& second);

	Quad& operator +=(double second);
	Quad& operator -=(double second);
	Quad& operator *=(double second);
	Quad& operator /=(double second);

	Quad& operator +=(int second);
	Quad& operator -=(int second);
	Quad& operator *=(int second);
	Quad& operator /=(int second);

	Quad& operator +=(_Quad second);
	Quad& operator -=(_Quad second);
	Quad& operator *=(_Quad second);
	Quad& operator /=(_Quad second);

	operator _Quad() const;
	operator _Quad*();

	double doubleValue;
	_Quad value;
};

typedef Quad TReal;
std::ostream& operator<<(std::ostream& stream, const TReal & value);
std::istream& operator>>(std::istream& stream, TReal & value);

#elif __INTEL_COMPILER

typedef _Quad TReal;
std::ostream& operator<<(std::ostream& stream, const TReal & value);
std::istream& operator>>(std::istream& stream, TReal & value);

#else

typedef double TReal;

#endif

#endif  //QUAD_H
