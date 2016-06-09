#ifndef __SA_FIT_H__
#define __SA_FIT_H__

#include <stdlib.h>

#include "math-utils.h"


// constants
const float sa_temp_max = 1000.0f;
const float sa_temp_min = 1e-6f;
const float sa_temp_factor = 0.999f;
const uint sa_it_max = 1;
const float sa_param_max = 10.0f;
const float sa_param_min = 0.0f;


// fit given sample data through simulated annealing
void sa_fit(float *sample_x, float *sample_y, uint sample_count, paramff param_func, uint param_count, float *param);


#endif // __SA_FIT_H__