#include <string>
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <time.h>
#include <cstdlib>
#include "partdist.hpp"
#include "InputSetup.hpp"
#include "Gap.hpp"
#include "Drift.hpp"
#include "Quad.hpp"
#include "Emit.hpp"
#include "EnvXY.hpp"

using namespace std;

//  for compiling : $ g++ BunForDC_wo_root.cpp -o BunForDC_wo_root.exe
//  for  running  : $ ./ BunForDC_wo_root.exe 
int main()
{
//This class is defined in the InputSeteup.hpp file. 
Parameters ReadSetup(1, 1, 938.27, 162.5e6, 299792458,-90,90,0.100, 0.007,0.003,0.05,0.20, 10,0.01,0.03);
double AtomicMass 	= ReadSetup.AtomicMass;
double Charge 		= ReadSetup.Charge;
double E_0 			= ReadSetup.E_0; 
double freq 		= ReadSetup.freq; 
double SpeedofLight = ReadSetup.SpeedofLight; 
double phi_0s 		= ReadSetup.Ph_s ; 
double phi_0s2 		= ReadSetup.Ph_s2; 
double W_0s			= ReadSetup.W_s	; 
double V_eff 		= ReadSetup.V_eff ; 
double V_eff2 		= ReadSetup.V_eff2; 
double L_d 			= ReadSetup.L_d ; 
double L_d2 		= ReadSetup.L_d2; 
double B_prime 		= ReadSetup.B_prime ; 
double aper 		= ReadSetup.aper; 
double L_m 			= ReadSetup.L_m;

/////////////////////////////////////////////////////////////////////
//These number indices on the vectors are increasing by the number of designed elements.
//For the simplicity, I decrease the number of elements to three not to make it crowded. However, these can be increased as much as user's desired design.

std::vector<double> xx_0i;		std::vector<double> xx_1i;	std::vector<double> yy_0i;		std::vector<double> yy_1i;
std::vector<double> xxp_0i; 	std::vector<double> xxp_1i; std::vector<double> yyp_0i; 	std::vector<double> yyp_1i;
std::vector<double> phi_0i;		std::vector<double> phi_1i;
std::vector<double> ww_0i;		std::vector<double> ww_1i;
std::vector<double> dww_0i;		std::vector<double> dww_1i;
std::vector<double> dphi_0i;	std::vector<double> dphi_1i;

std::vector<double> xx_2i;		std::vector<double> xx_3i;  std::vector<double> yy_2i;		std::vector<double> yy_3i;
std::vector<double> xxp_2i; 	std::vector<double> xxp_3i; std::vector<double> yyp_2i; 	std::vector<double> yyp_3i;
std::vector<double> phi_2i;		std::vector<double> phi_3i;
std::vector<double> ww_2i;		std::vector<double> ww_3i;
std::vector<double> dww_2i;		std::vector<double> dww_3i;
std::vector<double> dphi_2i;	std::vector<double> dphi_3i;

std::vector<double> xx_4i;		std::vector<double> xx_5i;  std::vector<double> yy_4i;		std::vector<double> yy_5i;
std::vector<double> xxp_4i; 	std::vector<double> xxp_5i; std::vector<double> yyp_4i; 	std::vector<double> yyp_5i;
std::vector<double> phi_4i;		std::vector<double> phi_5i;
std::vector<double> ww_4i;		std::vector<double> ww_5i;
std::vector<double> dww_4i;		std::vector<double> dww_5i;
std::vector<double> dphi_4i;	std::vector<double> dphi_5i;

std::vector<double>   xx_6i;	std::vector<double>   xx_7i; std::vector<double>  yy_6i;	std::vector<double> yy_7i;
std::vector<double>  xxp_6i; 	std::vector<double>  xxp_7i; std::vector<double> yyp_6i; 	std::vector<double> yyp_7i;
std::vector<double>  phi_6i;	std::vector<double>  phi_7i;
std::vector<double>   ww_6i;	std::vector<double>   ww_7i;
std::vector<double>  dww_6i;	std::vector<double>  dww_7i;
std::vector<double> dphi_6i;	std::vector<double> dphi_7i;

double lambda , gamma, beta, L_s, W_s1, W_s2;
//creating an initial data set by reading a txt file taken from an external simulation program.
partdist(xx_0i, xxp_0i, yy_0i, yyp_0i, phi_0i, ww_0i, dphi_0i, dww_0i);

// design is starting by manually typing the order og the structure.
// later on, this structure try to read from a configuration file.
int num_har = 1;
	Emit(xx_0i, xxp_0i, ww_0i);
	Drift(num_har, lambda, gamma, beta, L_s, xx_0i, xxp_0i, yy_0i, yyp_0i, xx_1i, xxp_1i, yy_1i, yyp_1i, phi_0i, phi_1i, dphi_0i, dphi_1i, dww_0i);
	Emit(xx_1i, xxp_1i, ww_0i);
	Gap(num_har, W_s1, lambda, gamma, beta, L_s, xx_1i, xxp_1i, yy_1i, yyp_1i, xx_2i, xxp_2i, yy_2i, yyp_2i, phi_1i, ww_0i, phi_2i, ww_1i, dphi_1i, dphi_2i, dww_0i, dww_1i);
	Emit(xx_2i, xxp_2i, ww_1i);

return 0;
}