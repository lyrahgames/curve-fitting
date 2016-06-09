#ifndef __MODEL_H__
#define __MODEL_H__

#include <math.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "io-data.h"


typedef std::string (*paramffstr)(float *);


inline float linModel(float x, float *param){
	return x*param[0] + param[1];
}

inline std::string linModelString(float *param){
	char buffer[10];

	sprintf(buffer, "%f\0", param[0]);
	std::string tmp = buffer;
	tmp += "*x+";
	sprintf(buffer, "%f\0", param[1]);
	tmp += buffer;

	return tmp;
}

inline float sin_param(float x, float *param){
	return param[1] * sin(param[0] * x);
}

inline float sin2Model(float x, float *param){
	return sin(param[0]*x)*sin(x)/(x);
}

inline std::string sin2ModelString(float *param){
	char buffer[10];
	std::string tmp = "sin(x)*sin(";
	sprintf(buffer, "%f\0", param[0]);
	tmp += buffer;
	tmp += "*x)/x";

	return tmp;
}

inline float sincos_param(float x, float *param){
	return sin(param[0]*x) + cos(param[1]*x);
}

inline float testModel(float x, float *param){
	return param[0]*( exp(-param[2]*x) - exp(-param[1]*x) )/(param[1]-param[2]);
}

inline std::string testModelString(float *param){
	char buffer[10];

	sprintf(buffer, "%f\0", param[0]);
	std::string tmp = buffer;
	tmp += "*(exp(-";
	sprintf(buffer, "%f\0", param[2]);
	tmp += buffer;
	tmp += "*x)-exp(-";
	sprintf(buffer, "%f\0", param[1]);
	tmp += buffer;
	tmp += "*x))/(";
	tmp += buffer;
	tmp += "-";
	sprintf(buffer, "%f\0", param[2]);
	tmp += buffer;
	tmp += ")";

	return tmp;
}

inline float expModel(float x, float *param){
	return param[0] * exp(param[1] * x);
}

inline std::string expModelString(float *param){
	char buffer[10];

	sprintf(buffer, "%f\0", param[0]);
	std::string tmp = buffer;
	tmp += "*exp(";
	sprintf(buffer, "%f\0", param[1]);
	tmp += buffer;
	tmp += "*x)";

	return tmp;	
}


#endif // __MODEL_H__