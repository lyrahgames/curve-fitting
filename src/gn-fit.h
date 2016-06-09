#ifndef __GN_FIT_H__
#define __GN_FIT_H__

#include "math-utils.h"


// constants
const float gn_tol = 1e-8f;
const uint gn_it_max = 10;

// gauss-newton-algorithm for fitting of measurement
void gn_fit(float *sample_x, float *sample_y, uint sample_count, paramff param_func, uint param_count, float *param);


#endif // __GN_FIT_H__