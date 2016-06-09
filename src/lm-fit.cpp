#include "lm-fit.h"


void lm_fit(float *sample_x, float *sample_y, uint sample_count, paramff param_func, uint param_count, float *param){
	// allocate memory for vectors and matrices
	float *deriv = new float[sample_count * param_count];
	float *gram_deriv = new float[sum_num(param_count)];
	float *gram_deriv_damp = new float[sum_num(param_count)];
	float *rhs = new float[param_count];
	float *lhs = new float[param_count];
	float *xhs = new float[param_count];
	float *err = new float[sample_count];
	float norm = INFINITY;
	float damp = lm_damp_default;
	
	// start iteration loop
	for (uint it = 0; (it < lm_it_max) && (norm > lm_tol); it++){

		// calculate error vector and derivative for given parameter with central difference quotient
		uint idx = 0;
		float sq_norm_err = 0.0f;

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

			err[i] = (sample_y[i] - param_func(sample_x[i], param));
			sq_norm_err += sq(err[i]);
		}	

		// calculate right hand side
		for (uint i = 0; i < param_count; i++){
			rhs[i] = 0.0f;

			for (uint j = 0; j < sample_count; j++){
				rhs[i] -= deriv[param_count*j + i] * err[j];
			}
		}

		// calculate gram matrix and save diagonal (triangle map)
		gram(deriv, sample_count, param_count, gram_deriv);

		while (true){

			const float sq_damp = sq(damp);
			for (uint i = 0; i < param_count; i++){
				gram_deriv_damp[tri_map(i,i)] = gram_deriv[tri_map(i,i)] + sq_damp;
				for (uint j = 0; j < i; j++){
					gram_deriv_damp[tri_map(i,j)] = gram_deriv[tri_map(i,j)];
				}
			}

			// calculate cholesky factorization
			cholesky(gram_deriv_damp, param_count);

			// calculate correction step with forward and back substitution
			fwd_subs(gram_deriv_damp, rhs, lhs, param_count);
			// back_subs(gram_deriv_damp, lhs, rhs, param_count);
			back_subs(gram_deriv_damp, lhs, xhs, param_count);


			float sq_norm_lin = 0.0f;
			float sq_norm_nonlin = 0.0f;
			for (uint i = 0; i < sample_count; i++){
				float sum = 0.0f;

				for (uint j = 0; j < param_count; j++){
					sum += deriv[i*param_count + j] * xhs[j];
					lhs[j] = param[j] + xhs[j];
				}

				sq_norm_lin += sq( err[i] + sum );
				sq_norm_nonlin += sq( sample_y[i] - param_func(sample_x[i], lhs) );
			}

			const float epsilon = ( sq_norm_err - sq_norm_nonlin ) / ( sq_norm_err - sq_norm_lin );

			if (epsilon <= lm_beta0){
				damp *= 2.0f;
			}else if (epsilon >= lm_beta1){
				damp *= 0.5f;
				break;
			}else{
				break;
			}

		} // while

		// add correction step and calculate squared 2-norm of step
		norm = 0.0f;
		for (uint i = 0; i < param_count; i++){
			param[i] += xhs[i];
			norm += sq(xhs[i]);
		}

	} // for

	// free allocated memory
	delete[] xhs;
	delete[] lhs;
	delete[] rhs;
	delete[] err;
	delete[] gram_deriv_damp;
	delete[] gram_deriv;
	delete[] deriv;
}
