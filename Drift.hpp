#ifndef DRIFT
#define DRIFT

#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "InputSetup.hpp"

using namespace std;

void Drift(int &num_har, double &lambda, double &gamma, double &beta, double &L_s, 
	std::vector<double> &X_0i, std::vector<double> &Xp_0i, 
	std::vector<double> &Y_0i, std::vector<double> &Yp_0i, 
	std::vector<double> &X_1i, std::vector<double> &Xp_1i, 
	std::vector<double> &Y_1i, std::vector<double> &Yp_1i,
	std::vector<double> &Ph_0i, std::vector<double> &Ph_1i, 
	std::vector<double> &dPh_0i, std::vector<double> &dPh_1i,std::vector<double> &dW_0i) 
{
	cout << "===DRIFT::::Started===" << endl;
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
	/////////////////////////////////////////////////////////////////
	/////////////EssentialParameterCalculation//////////////////////
	lambda 	= SpeedofLight/(freq*num_har);  //[m]
	gamma 	= 1 + W_0s/(E_0*AtomicMass);
	beta 	= sqrt( 1 - (1/gamma)*(1/gamma) );
	L_s 	= beta*lambda/2;
	/*	cout << "Sync Length:\t" << L_s << endl;
		cout << "lambda:\t" << lambda << endl;
		cout << "gamma:\t" << gamma << endl;
		cout << "beta:\t" << beta << endl;
	*/	
	if(num_har == 2)
	{
		phi_0s  = phi_0s2;
		L_d 	= L_d2;
		V_eff 	= V_eff2;
	}
	////////////////////////////////////////////////////////////////////////
	///////////Transversal Gap Transformation///////////////////////////////
	double number =X_0i.size(); 
	for (int i = 0; i < number; ++i)
	{
		X_1i.push_back(X_0i[i] + Xp_0i[i]*L_d);
		Xp_1i.push_back(Xp_0i[i]);
	
	}
		number =Y_0i.size(); 
	for (int i = 0; i < number; ++i)
	{
		Y_1i.push_back(Y_0i[i] + Yp_0i[i]*L_d);
		Yp_1i.push_back(Yp_0i[i]);
	}
	////////////////////////////////////////////////////////////////////////
	double factor_d = L_d * 2 * M_PI / ((AtomicMass * E_0) * pow(gamma, 3) * pow(beta, 3) * lambda);
	cout << "DRIFT::factor:\t" << factor_d << "\tL_drift:\t" << L_d << endl;
	////////////////////////////////////////////////////////////////////////
	///////////Longitudinal Gap Transformation//////////////////////////////
		number =Ph_0i.size();
	for (int i = 0; i < number; ++i)
	{
		dPh_0i[i] = Ph_0i[i] - phi_0s;
		dPh_1i.push_back( dPh_0i[i] - dW_0i[i]*factor_d );
	//cout << "dphi0:\t"<< dPh_0i[i] << "\tdW_0i x factor\t" << dW_0i[i]*factor_d  << "\tdphi1:\t"<< dPh_1i[i] << endl;
		 Ph_1i.push_back( dPh_1i[i] + phi_0s );
	//	dPh_0i[i] = dPh_0i[i] + phi_0s;

	}
	cout << "===DRIFT::::Finished===" << endl;
}

#endif
