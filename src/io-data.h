#ifndef __IO_DATA_H__
#define __IO_DATA_H__

#include <iostream>
#include <vector>
#include <fstream>

#include "math-utils.h"


// load sample data from file in ascii format
void loadSampleData(const char *file_path, std::vector<float> &x_vec, std::vector<float> &y_vec);

// show vector on console
inline void vecOut(const float *vec, uint count){
	for (uint i = 0; i < count; i++){
		// std::cout << vec[i] << '\t';
		printf("%.6f\t", vec[i]);
	}

	// std::cout << std::endl;
	printf("\n");
}


#endif // __IO_DATA_H__