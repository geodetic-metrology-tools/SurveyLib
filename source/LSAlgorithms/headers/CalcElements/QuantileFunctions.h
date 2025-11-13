/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef QUANTILEFUNCTIONS
#define QUANTILEFUNCTIONS

// chi-square quantiles for p=0.025
double deviates_chi_sq_0025(double df);
// chi-square quantiles for p=0.975
double deviates_chi_sq_0975(double df);
// student-t quantiles for p=0.025
double deviates_students_t_lower_tail_0025(double df);
// student-t quantiles for p=0.975
double deviates_students_t_upper_tail_0025(double df);
double deviates_normal_upper_tail(double p);
// quantile function for normal distribution using inverse error function (only using std library)
double normalQuantile(double p);

// auxiliary functions
// inverse error function via newtons method
double erfInvNewton(double alpha);

#endif
