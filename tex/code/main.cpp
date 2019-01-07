#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;


typedef unsigned int uint;

const char* default_file_name = "data.txt";
const uint sample_count = 100;
const float min_x = 0.0f;
const float max_x = 10.0f;


int main(int argc, char **argv)
{
	const char *file_name = nullptr;

	if (argc < 2)
		file_name = default_file_name;
	else
		file_name = argv[1];


	ofstream file;
	file.open(file_name);


	float *data_x = new float[sample_count];
	float *data_y = new float[sample_count];


	for (uint i = 1; i <= sample_count; i++){
		data_x[i] = ((max_x-min_x) * (float)i / (float)sample_count) + min_x;

		const float tmp = (1.0f - 2.0f * (float)rand()/(float)RAND_MAX);
		// data_y[i] = 10.0f * exp(-1.0f/data_x[i]) + 0.5f*tmp;
		// data_y[i] = data_x[i] + 0.8f*data_x[i]*tmp;
		data_y[i] = 0.09f*tmp + sin(3*data_x[i])*sin(data_x[i]) / data_x[i];

		file << data_x[i] << '\t' << data_y[i] << '\n';
	}


	delete[] data_x;
	delete[] data_y;

	file.close();

	return 0;
}