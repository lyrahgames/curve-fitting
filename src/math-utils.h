#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#include <math.h>
#include <string.h>


typedef unsigned int uint;

// type definition of parameter function
// template <class T>
// using paramf = T (*)(T, T*);
// using paramff = paramf<float>;
typedef float (*paramff)(float, float*);


// constant increment for numerical derivative (central difference)
const float deriv_inc = 1e-3f;
const float inv_deriv_inc2 = 0.5f / deriv_inc;


// return square of given argument
template <class T>
inline T sq(T arg) { return (arg*arg); }

// get sum of numbers from to 1 to n
inline uint sum_num(uint n) { return (n*n + n)>>1; }
// get memory index of triangular mapped matrix
inline uint tri_map(uint row, uint col) { return sum_num(row) + col; }
// get memory index of rectangular mapped matrix (row-major)
inline uint quad_map(uint row, uint col, uint col_count) { return row*col_count + col; }


// calculate cholesky factorization of matix (saved with triangle map)
inline void cholesky(float *mat, uint dim){
	for (uint j = 0; j < dim; j++){
		const uint sum_j = sum_num(j);

		float tmp = 0.0f;
		for (uint k = 0; k < j; k++){
			tmp += sq(mat[sum_j + k]);
		}

		const uint diag_idx = sum_j + j;
		mat[diag_idx] = sqrtf( mat[diag_idx] - tmp );

		for (uint i = j + 1; i < dim; i++){
			const uint sum_i = sum_num(i);

			float tmp = 0.0f;
			for (uint k = 0; k < j; k++){
				tmp += mat[sum_j + k] * mat[sum_i + k];
			}

			const uint idx = sum_i + j;
			mat[idx] = (mat[idx] - tmp)/mat[diag_idx];
		}
	}
}

// calculate forward substitution (lower triangel matrix, triangle map)
inline void fwd_subs(float *mat, float* in, float* out, uint dim){
	for (uint i = 0; i < dim; i++){
		const uint sum_i = sum_num(i);

		float tmp = 0.0f;
		for (uint j = 0; j < i; j++){
			tmp += mat[sum_i + j] * out[j];
		}

		out[i] = (in[i] - tmp)/mat[sum_i + i];
	}
}

// calculate back substitution (lower triangle matrix (will be transpnated), triangle map)
inline void back_subs(float *mat, float *in, float *out, uint dim){
	for (uint i = dim - 1; i != (uint)(-1); --i){
		float tmp = 0.0f;
		for (uint j = i+1; j < dim; j++){
			tmp += mat[tri_map(j,i)] * out[j];
		}

		out[i] = (in[i] - tmp)/mat[tri_map(i,i)];
	}
}

// calculate matrix-vector-multiplication
inline void mat_vec_mult(float *mat, float *in, uint in_dim, float *out, uint out_dim){
	for (uint i = 0; i < out_dim; i++){
		out[i] = 0.0f;
		for (uint j = 0; j < in_dim; j++){
			out[i] += mat[quad_map(i,j,in_dim)] * in[j];
		}
	}
}

// calculate matrix-vector-multiplication with transposed matrix
inline void mat_t_vec_mult(float *mat, float *in, uint in_dim, float *out, uint out_dim){
	for (uint i = 0; i < out_dim; i++){
		out[i] = 0.0f;
		for (uint j = 0; j < in_dim; j++){
			out[i] += mat[quad_map(j,i,in_dim)] * in[j];
		}
	}
}

// calculate gram matrix M = A^T A (saved as triangle map)
inline void gram(float *mat, uint row_count, uint col_count, float *gram_mat){
	uint idx = 0;

	for (uint i = 0; i < col_count; i++){
		for (uint j = 0; j <= i; j++){
			gram_mat[idx] = 0.0f;
			for (uint k = 0; k < row_count; k++){
				const uint tmp = col_count * k;
				gram_mat[idx] += mat[tmp + i] * mat[tmp + j];
			}

			idx += 1;
		}
	}
}

// calculate squared norm for given measurement and parameter
inline float sqnorm(float *sample_x, float *sample_y, uint sample_count, paramff param_func, float *param){
	float sum = 0.0f;

	for (uint i = 0; i < sample_count; i++){
		sum += sq( sample_y[i] - param_func(sample_x[i], param) );
	}

	return sum;
}

// check if vector consists only of valied data
inline bool isValid(float *vec, uint size){
	bool valid = true;

	for (uint i = 0;  i < size; i++){
		if (!isnormal(vec[i])){
			valid = false;
			break;
		}
	}

	return valid;
}


#endif // __MATH_UTILS_H__