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
typedef std::vector<double> VEC;

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

VEC xx_0i, xx_1i, yy_0i, yy_1i, xx_2i, yy_2i;
VEC xxp_0i, xxp_1i, yyp_0i, yyp_1i, xxp_2i, yyp_2i;
VEC phi_0i, phi_1i, phi_2i;
VEC ww_0i, ww_1i, ww_2i;
VEC dww_0i, dww_1i, dww_2i;
VEC dphi_0i, dphi_1i, dphi_2i;

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
