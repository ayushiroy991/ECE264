#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

double simpson_numerical_integration(Integrand intg_arg) {
    double integral;
	double step;
	double updated_lower;
	double updated_upper;
	//double difference_div;
	double sum_div;

	integral = 0.0;
	//difference_div = 0.0;
	//sum_div = 0.0;
	step= (intg_arg.upper_limit - intg_arg.lower_limit)/intg_arg.n_intervals;
	updated_lower = intg_arg.lower_limit;
	updated_upper = updated_lower + step;

	for (int i=0; i < intg_arg.n_intervals; i++){
		//difference_div = (updated_upper - updated_lower)/6.0;
		sum_div = (updated_upper + updated_lower)/2.0;
		integral += ((updated_upper-updated_lower)/6)*(intg_arg.func_to_be_integrated(updated_lower) + 4.0*intg_arg.func_to_be_integrated(sum_div)+ 
																							intg_arg.func_to_be_integrated(updated_upper));
		updated_lower = updated_upper;
		updated_upper  += step;
	}

    return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) {
    double integral;
	double step;
	double updated_lower;
	double updated_upper;
	//double difference_div;
	double sum_div;
	double l;

	integral = 0.0;
	//difference_div = 0.0;
	//sum_div = 0.0;
	//l= 0.0;
	step= (intg_arg.upper_limit - intg_arg.lower_limit)/intg_arg.n_intervals;
	l = (intg_arg.upper_limit - intg_arg.lower_limit);
	updated_lower = intg_arg.lower_limit;
	updated_upper = updated_lower + step;

	for (int i=0; i < intg_arg.n_intervals; i++){

		//difference_div = (updated_upper - updated_lower)/6.0;
		sum_div = (updated_upper + updated_lower)/2.0;

		integral += ((updated_upper-updated_lower)/6.0) * ((intg_arg.func_to_be_integrated(updated_lower)*cos_sin(n*M_PI*updated_lower*2/l)) 
															+ (4*intg_arg.func_to_be_integrated(sum_div) * cos_sin(n*M_PI*sum_div*2/l))
															+ (intg_arg.func_to_be_integrated(updated_upper)*cos_sin(n*M_PI*updated_upper*2/l)));

		/**integral += ((intg_arg.func_to_be_integrated(updated_lower)) * cos_sin((n*M_PI* updated_lower)/l));// * (step/6.0));
		integral += 4*intg_arg.func_to_be_integrated(sum_div)* (cos_sin((n*M_PI*sum_div)/l));
		integral += intg_arg.func_to_be_integrated(updated_upper)*(cos_sin((n*M_PI*updated_upper)/l));
		integral = integral * (updated_upper-updated_lower)/6.0;
		**/
		updated_lower = updated_upper;
		updated_upper += step;
	}
	//integral = 0.0;


    return integral;
}

void fourier_coefficients(Fourier fourier_arg) {

	double l = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2;

	fourier_arg.a_i[0] = simpson_numerical_integration(fourier_arg.intg) * (1/l);
	fourier_arg.b_i[0] = 0.0;

    for (int i = 1; i < fourier_arg.n_terms; i++) {
       fourier_arg.a_i[i] = simpson_numerical_integration_for_fourier(fourier_arg.intg, i, &cos)*(1/l);
       fourier_arg.b_i[i] = simpson_numerical_integration_for_fourier(fourier_arg.intg, i, &sin)*(1/l);
   }
}
