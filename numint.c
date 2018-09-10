#include "numint.h"
#include "aux.h"

//
// The function performs numerical integration of the function double
// function_to_be_integrated(double) over the range lower_limit to upper_limit using
// the mid-point rule
//
// The range is divided into n_intervals uniform intervals, where the left-most
// interval has a left boundary of lower_limit and the right-most interval has a
// right boundary of upper_limit (assuming lower_limit <= upper_limit).  If
// lower_limit >= upper_limit, the right-most interval has a right boundary of
// lower_limit and the left-most interval has a left boundary of upper_limit.
// 
// The mid-point rule is used to perform the integration for each interval.  In the
// mid-point rule, the integration is approximated by using the area of a rectangle,
// where the height of the rectange is obtained by
// function_to_be_integrated(mid-point of the interval).  The width of the rectangle
// is (interval boundary closer to upper_limit - interval boundary closer to
// lower_limit).  Note that width could be negative if upper_limit < lower_limit
//
// The integral is the sum of the integration over all intervals.
//
// The caller function has to make sure that n_intervals >= 1.  Therefore, this
// function may assume that n_intervals >= 1
//
double mid_point_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
	double integral;
	int i;
	double new_lower;
	double new_upper;
	double step;
	double  m;

	integral = 0.0;
	step = (upper_limit - lower_limit)/(double)n_intervals;
	new_lower=lower_limit;
	new_upper= lower_limit + step;
	i =0;
	
	
	while (i<n_intervals){

		m = (new_lower+new_upper)/2.0;
		integral = integral +  step*(function_to_be_integrated(m));
		new_lower = new_upper;
		new_upper += step;
		i++;

	}


	return integral;
}

// 
// The function performs numerical integration of the function double
// function_to_be_integrated(double) over the range lower_limit to upper_limit using
// the trapezoidal rule.
//
// The range is divided into n_intervals uniform intervals, where the left-most
// interval has a left boundary of lower_limit and the right-most interval has a
// right boundary of upper_limit (assuming lower_limit <= upper_limit).  If
// lower_limit >= upper_limit, the right-most interval has a right boundary of
// lower_limit and the left-most interval has a left boundary of upper_limit.
// 
// The trapezoidal rule is used to perform the integration for each interval.  In the
// trapezoidal rule, the integration is approximated by the area of a trapezoid,
// where the heights of the parallel boundaries of the trapezoid are obtained by
// function_to_be_integrated(left boundary of the interval) and
// function_to_be_integrated(right boundary of the interval).  The width of the
// trapezoid is (interval boundary closer to upper_limit - interval boundary closer
// to lower_limit).  Note that width could be negative if upper_limit < lower_limit.
// The area of a trapezoid is the average of the two heights multiplied by the width.
//
// The integral is the sum of the integration over all intervals.
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double trapezoidal_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
	double integral;
	double step;
	double new_lower;
	double new_upper;
   	int i;


   	integral = 0.0;
   	step = (upper_limit - lower_limit)/(double)n_intervals;
   	new_lower = lower_limit;
   	new_upper = lower_limit +step;
   	i=0;

	while (i<n_intervals){
	
		integral= integral +  step*((function_to_be_integrated(new_upper)+function_to_be_integrated(new_lower))/2.0);
		new_lower= new_upper;
		new_upper +=step;
		i++;

	}

   	return integral;
}
