#ifndef __LM_FIT_H__
#define __LM_FIT_H__

#include "math-utils.h"


const float lm_damp_default = 0.5f;
const float lm_beta0 = 0.3;
const float lm_beta1 = 0.9;
const uint lm_it_max = 30;
const float lm_tol = 1e-8;

void lm_fit(float *sample_x, float *sample_y, uint sample_count, paramff param_func, uint param_count, float *param);


#endif // __LM_FIT_H__