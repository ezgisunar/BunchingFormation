#ifndef ENVXY
#define ENVXY

#include <fstream>
#define _USE_MATH_DEFINES
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "InputSetup.hpp"

using namespace std;

void EnvXY( std::vector<double> &xx_0, std::vector<double> &yy_0,
		double &xpos_min, double &ypos_min, double &xpos_max, double &ypos_max) 
{
	cout << "////-Envelope Calc starts -//////"	<< endl;
	double xmax=0;
	double ymax=0;
	double xmin=0;
	double ymin=0;
//cout << "in evn calc xx_0\t:\t" << xx_0.size() << endl;
	for (int i=0; i<xx_0.size(); i++)
	{
		if (xmax < xx_0[i]) xmax=xx_0[i];
		else if(xmin > xx_0[i]) xmin=xx_0[i];
//	cout << "\t\t\t xmin\t:\t" << xmin << endl;
		
		if (ymax < yy_0[i]) ymax=yy_0[i];
		else if (ymin > yy_0[i]) ymin=yy_0[i];
//	cout << "\t\t\t ymin\t:\t" << ymin << endl;			
		
	}

	xpos_min = xmin;
	xpos_max = xmax;
	ypos_min = ymin;
	ypos_max = ymax;
}


#endif
