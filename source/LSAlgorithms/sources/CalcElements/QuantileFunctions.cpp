#include "QuantileFunctions.h"

#include <stdexcept>

#include <Quad.h>
#include <QuantileLookupTables.h>

double deviate_chi_sq_approx(double p, double df)
{
	// approximation, Statistical Methods for Research Workers, R. A. Fisher 1925
	double normQuant = normalQuantile(p);
	double lower = 0.5 * pow(normQuant + sqrt(2 * df - 1), 2);
	double upper = 0.5 * pow(normQuant + sqrt(2 * (df + 1) - 1), 2);
	return 0.5 * (lower + upper);
}

double deviates_chi_sq_0975(double df)
{
	double result = 0;
	if (df <= 1000)
	{
		// use lookup table generated with boost: bm::quantile(bm::chi_squared(df), 0.975)
		// only integer degrees of freedom
		result = chiSquaredQuantile0975[(int)df - 1];
	}
	else
	{
		// use approximation rel error for n=1000: ~0.004%
		result = deviate_chi_sq_approx(0.975, df);
	}
	return result;
}
double deviates_chi_sq_0025(double df)
{
	double result = 0;
	if (df <= 1000)
	{
		// use lookup table generated with boost bm::quantile(bm::chi_squared(df), 0.025)
		// only integer degrees of freedom
		result = chiSquaredQuantile0025[(int)df - 1];
	}
	else
	{
		// use approximation rel error for df=1000: ~0.001%
		result = deviate_chi_sq_approx(0.025, df);
	}
	return result;
}

double deviates_students_t_lower_tail_0025(double df)
{
	double result = 0;
	if (df <= 1000)
	{
		// use lookup table generated with boost bm::quantile(bm::students_t(df), 0.025)
		// only integer degrees of freedom
		result = studentQuantile0025[(int)df - 1];
	}
	else
	{
		// approximate with normal quantile, for high degrees of freedom student quantile converges to normal quantile, relative error for df>1000 ~0.1%
		result = normalQuantile(0.025);
	}
	return result;
}

double deviates_students_t_upper_tail_0025(double df)
{
	// symmetry
	return -deviates_students_t_lower_tail_0025(df);
}

double deviates_normal_upper_tail(double p)
{
	return normalQuantile(1 - p);
}

double erfInvNewton(double alpha)
{
	// finding erf^-1(alpha) by solving erf(x)-alpha=0 via a simple newton method
	// erf(x) = int_0^x (2/sqrt(pi)*exp(-x^2))dx , part of cmath
	const double EPSILON = 1e-12; // Desired precision
	double x(0), f(0), df(1), delta(1);
	int counter = 0;
	do
	{
		counter++;
		f = std::erf(x) - alpha;
		df = std::exp(-(x * x)) * 2.0 / sqrt(M_PI);
		// Newton step: solve f + df * delta = 0
		delta = -f / df;
		x += delta;
	} while (std::abs(delta) > EPSILON && counter < 100);

	return x;
}

double normalQuantile(double p)
{
	if (p < 0 || p > 1)
	{
		throw std::runtime_error("Probability has to be in [0,1]");
	}
	return sqrt(2) * erfInvNewton(2 * p - 1);
}
