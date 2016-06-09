#include "io-data.h"


void loadSampleData(const char *file_path, std::vector<float> &x_vec, std::vector<float> &y_vec){
	std::ifstream file;
	file.open(file_path);

	while (!file.eof()){
		float tmp;

		file >> tmp;
		if (file.fail())
			break;

		x_vec.push_back(tmp);

		file >> tmp;
		if (file.fail())
			break;
		
		y_vec.push_back(tmp);
	}

	file.close();
}