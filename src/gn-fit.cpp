#include "gn-fit.h"


void gn_fit(float *sample_x, float *sample_y, uint sample_count, paramff param_func, uint param_count, float *param){
	// allocate memory for vectors and matrices
	float *deriv = new float[sample_count * param_count];
	float *gram_deriv = new float[sum_num(param_count)];
	float *rhs = new float[param_count];
	float *lhs = new float[param_count];
	float norm = INFINITY;
	
	// start iteration loop
	for (uint it = 0; (it < gn_it_max) && (norm > gn_tol); it++){

		// calculate derivative for given parameter with central difference quotient
		uint idx = 0;
		for (uint i = 0; i < sample_count; i++){
			for (uint j = 0; j < param_count; j++){
				const float tmp_param = param[j];
				param[j] += deriv_inc;
				const float tmp_p = param_func(sample_x[i], param);
				param[j] = tmp_param - deriv_inc;
				const float tmp_m = param_func(sample_x[i], param);
				param[j] = tmp_param;

				deriv[idx] = inv_deriv_inc2 * ( tmp_m - tmp_p );
				idx += 1;
			}
		}

		// calculate right hand side
		for (uint i = 0; i < param_count; i++){
			rhs[i] = 0.0f;
			for (uint j = 0; j < sample_count; j++){
				rhs[i] -= deriv[param_count*j + i] * (sample_y[j] - param_func(sample_x[j], param));
			}
		}

		// calculate matrix for cholesky factorization (symmetric, triangle map)
		gram(deriv, sample_count, param_count, gram_deriv);

		// calculate cholesky factorization
		cholesky(gram_deriv, param_count);

		// calculate correction step with forward and back substitution
		fwd_subs(gram_deriv, rhs, lhs, param_count);
		back_subs(gram_deriv, lhs, rhs, param_count);

		// add correction step and calculate squared 2-norm of step
		norm = 0.0f;
		for (uint i = 0; i < param_count; i++){
			param[i] += rhs[i];
			norm += sq(rhs[i]);
		}

	} // for

	// free allocated memory
	delete[] lhs;
	delete[] rhs;
	delete[] gram_deriv;
	delete[] deriv;
}