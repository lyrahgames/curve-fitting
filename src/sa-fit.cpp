#include "sa-fit.h"


void sa_fit(float *sample_x, float *sample_y, uint sample_count, paramff param_func, uint param_count, float *param){
	float old_cost = sqnorm(sample_x, sample_y, sample_count, param_func, param);
	float temp = sa_temp_max;

	while (temp > sa_temp_min){
		for (uint i = 0; i < sa_it_max; i++){

			const uint rand_param_idx = rand()%param_count;
			const float tmp_param = param[rand_param_idx];
			param[rand_param_idx] = (sa_param_max - sa_param_min)*((float)rand()/(float)RAND_MAX) + sa_param_min;

			float new_cost = sqnorm(sample_x, sample_y, sample_count, param_func, param);

			if (new_cost > old_cost){
				const float prob = exp((old_cost - new_cost)/temp);

				if (prob < (float)rand()/(float)RAND_MAX){
					param[rand_param_idx] = tmp_param;
				}else{
					old_cost = new_cost;
				}
			}else{
				old_cost = new_cost;
			}
		}

		temp *= sa_temp_factor;
	}
}