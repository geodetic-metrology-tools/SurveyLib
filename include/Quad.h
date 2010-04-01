#ifndef QUAD_H
#define QUAD_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if _DEBUG

class Quad
{
public:
	Quad(_Quad other);
	Quad(double other);
	Quad(int other);
	Quad(const Quad& other);
	Quad();

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

	operator _Quad() const;
	operator _Quad*();

	double doubleValue;
	_Quad value;
};

typedef Quad quad;

#else

typedef _Quad quad;

#endif

#endif  //QUAD_H
