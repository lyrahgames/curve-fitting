#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gn-fit.h"
#include "sa-fit.h"
#include "lm-fit.h"
#include "model.h"
#include "io-data.h"


// define path to gnuplot command
#ifdef __WIN__
const char* gnuplot_cmd = "gnuplot\\bin\\gnuplot -persist";
#else
const char* gnuplot_cmd = "gnuplot -persist";
#endif


int main(int argc, char **argv){
	// initialize random number generator
	srand(time(NULL));

	// initialize parameter
	const uint param_count = 1;
	const paramff model = sin2Model;
	const paramffstr model_str = sin2ModelString;
	const float tmp_init_param[] = {2.8f, 1.0f, 1.0f}; 
	// const float tmp_init_param[] = {0.01f, 0.1f, 0.001f};
	const std::vector<float> init_param(tmp_init_param, tmp_init_param + param_count) ;
	// init_param[0] = init_param[1] = init_param[2] = 1.0f;
	const char* file_path = "../data/rand-nonlin-data";
	
	// load data to be fitted
	std::vector<float> x_data, y_data;
	loadSampleData(file_path, x_data, y_data);
	const uint data_count = y_data.size();

	// calculate parameters with different methods for same initial values
	std::vector<float> gn_param = init_param;
	gn_fit(x_data.data(), y_data.data(), data_count, model, param_count, gn_param.data());

	std::vector<float> lm_param = init_param;
	lm_fit(x_data.data(), y_data.data(), data_count, model, param_count, lm_param.data());

	std::vector<float> sa_param = init_param;
	sa_fit(x_data.data(), y_data.data(), data_count, model, param_count, sa_param.data());

	std::vector<float> lmsa_param = sa_param;
	lm_fit(x_data.data(), y_data.data(), data_count, model, param_count, lmsa_param.data());


	// show initial values
	printf("----------\n");
	printf("sample data file:\t%s\n", file_path);
	printf("sample data count:\t%u\n", data_count);
	printf("parameter count:\t%u\n", param_count);
	printf("start parameter:\n");
	vecOut(init_param.data(), param_count);
	printf("----------\n");
	printf("\n");

	// output of calculated parameters
	printf("----------\n");
	std::cout << "gauss-newton (GN):" << std::endl;
	vecOut(gn_param.data(), param_count);
	printf("\n");
	std::cout << "levenberg-marquardt (LM):" << std::endl;
	vecOut(lm_param.data(), param_count);
	printf("\n");
	std::cout << "simulated annealing (SA):" << std::endl;
	vecOut(sa_param.data(), param_count);
	printf("\n");
	std::cout << "levenberg-marquardt with parameters from simulated annealing (LMSA):" << std::endl;
	vecOut(lmsa_param.data(), param_count);
	printf("----------\n");
	printf("\n");

	// open pipeline to gnuplot and plot calculated data
	FILE *gp_pipe;

	if ((gp_pipe = popen(gnuplot_cmd, "w")) == NULL){
		printf("could not open pipeline:\n");
		printf("%s\n", gnuplot_cmd);
	}

	fprintf(gp_pipe, "plot '%s' using 1:2 with points pt 13 title 'Data'\n", file_path);
	fprintf(gp_pipe, "replot %s title 'SA'\n", model_str(sa_param.data()).c_str());
	fprintf(gp_pipe, "replot %s title 'LMSA'\n", model_str(lmsa_param.data()).c_str());

	if (isValid(lm_param.data(), param_count)){
		fprintf(gp_pipe, "replot %s title 'LM'\n", model_str(lm_param.data()).c_str());
	}

	if (isValid(gn_param.data(), param_count)){
		fprintf(gp_pipe, "replot %s title 'GN'\n", model_str(gn_param.data()).c_str());
	}

	fclose(gp_pipe);

	return 0;
}