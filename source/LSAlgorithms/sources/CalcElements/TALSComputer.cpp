#include "TALSComputer.h"

#include <iostream>
#include <memory>

#include "QuantileFunctions.h"

//////////////////////////
// no argument constructor
//////////////////////////
TALSComputer::TALSComputer() : fError("")
{
}

/////////////
// destructor
/////////////
TALSComputer::~TALSComputer()
{
}

limits TALSComputer::calcSigmaZeroLimits(const int nbObs, const int nbUnk, const int nbCnstr)
{
	// computes and saves limits of interval for test chi of S0 validity
	struct limits resultat;
	resultat.s0PostUpLimit = LITERAL(0.0);
	resultat.s0PostLoLimit = LITERAL(0.0);
	double d = LITERAL(0.0);

	d = nbObs - (nbUnk - nbCnstr);

	if (d > 0)
	{
		double chiUp = deviates_chi_sq_0975(d);
		double chiLow = deviates_chi_sq_0025(d);

		if (fError == "")
		{
			// Limits
			resultat.s0PostUpLimit = sqrtq(chiUp / d);
			resultat.s0PostLoLimit = sqrtq(chiLow / d);
		}
	}
	return resultat;
}
