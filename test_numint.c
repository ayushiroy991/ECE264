#include <stdio.h>
#include <stdlib.h>

//
// You do not have to include numint.h here because you are not 
// calling the function function_to_be_integrated here.
//
#include "numint.h"

//
// Fill in the correct statements to complete the main(..) function.
//
// We expect four arguments:
//
// The first argument is two characters from the sets {"-m", "-t"}
// -m: run mid_point_numerical_integration
// -t: run trapezoidal_numerical_integration
// otherwise: return EXIT_FAILURE
//
// To run any of the two functions, expect the next three arguments
// to be the lower limit of the integration (double), the upper limit
// of the integration (double), and the number of intervals for the
// integration (int).
//
// If the number of intervals is less than 1, set it to 1.
//
// Use atof to convert an argument to a double.
//
// Use atoi to convert an argument to an int.
//
// After you have numerically integrated the function, print the 
// return value, and return EXIT_SUCCESS
//
int main(int argc, char * * argv)
{
   	double integral;
	double upper_limit;
	double lower_limit;
	int n_intervals;
   
   	integral= 0.0;
	lower_limit = atof(argv[2]);
	upper_limit = atof(argv[3]);
	n_intervals = atoi(argv[4]);

	if (n_intervals < 1){
		n_intervals = 1;
	}

	if ('-' == argv[1][0]){

		if ('m' == argv[1][1] && '\0' == argv[1][2]){

			integral = mid_point_numerical_integration(lower_limit, upper_limit, n_intervals);
		}
		else if('t' == argv[1][1] && '\0' == argv[1][2]){
			integral = trapezoidal_numerical_integration(lower_limit, upper_limit, n_intervals);
		}
		else{
			return EXIT_FAILURE;
		}

	}

   	printf("%.10e\n", integral);
   	return EXIT_SUCCESS;
}
