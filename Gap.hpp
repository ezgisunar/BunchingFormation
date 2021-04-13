#ifndef GAP
#define GAP

#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "InputSetup.hpp"

using namespace std;


void Gap(int &num_har, double &W_1s, double &lambda, double &gamma, double &beta, double &L_s,
		std::vector<double> &X_0i,  std::vector<double> &Xp_0i, std::vector<double> &Y_0i,  std::vector<double> &Yp_0i, 
		std::vector<double> &X_1i,  std::vector<double> &Xp_1i, std::vector<double> &Y_1i,  std::vector<double> &Yp_1i,
		std::vector<double> &Ph_0i, std::vector<double> &W_0i,
		std::vector<double> &Ph_1i, std::vector<double> &W_1i, 
		std::vector<double> &dPh_0i,std::vector<double> &dPh_1i,
		std::vector<double> &dW_0i, std::vector<double> &dW_1i) 
{
	cout << "===GAP::::Started===" << endl;
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
	/////////////EssentialParameterCalculation///////////////////////
	if(num_har ==2)	
	{
		phi_0s  = phi_0s2;
		L_d 	= L_d2;
		V_eff 	= V_eff2;
	}
	//Because of inserting an extra test particle
	//size of W_0i is one particle higher than X_0i
	double number =W_0i.size();

	W_1s = W_0s + Charge * V_eff * cos((phi_0s)*M_PI / 180);
	//W_1s = W_0s + Charge*V_eff*TMath::Cos(TMath::Pi() - (phi_0s)*TMath::Pi()/180);
		cout << "GAP :: Energy for Sync Par\t" << W_1s  << "\tMeV at\t" << phi_0s << "\tdeg" << endl;
	lambda 	= SpeedofLight/(freq*num_har);  //[m]
	gamma 	= 1 + W_1s/(E_0*AtomicMass);
	beta 	= sqrt( 1 - (1/gamma)*(1/gamma) );
	L_s 	= beta*lambda/2;
	/*	cout << "Sync Length:\t" << L_s << endl;
		cout << "lambda:\t" << lambda << endl;
		cout << "gamma:\t" << gamma << endl;
		cout << "beta:\t" << beta << endl;
	*/	
	/////////////////////////////////////////////////////////////////
	///////////Transversal Gap Transformation///////////////////////////////
	number = X_0i.size();
	for (int i = 0; i < number; ++i)
	{
		X_1i.push_back( X_0i[i]);
		Xp_1i.push_back(Xp_0i[i] - M_PI * Charge * V_eff * sin(phi_0s / 180 * M_PI) * X_0i[i] /
						(AtomicMass * Charge * pow(gamma * beta, 3) * pow(SpeedofLight, 2) * lambda));
	}
	number = Y_0i.size();
	for (int i = 0; i < number; ++i)
	{
		Y_1i.push_back( Y_0i[i]);
		Yp_1i.push_back(Yp_0i[i] - M_PI * Charge * V_eff * sin(phi_0s / 180 * M_PI) * Y_0i[i] /
						(AtomicMass * Charge * pow(gamma * beta, 3) * pow(SpeedofLight, 2) * lambda));
	}
	/////////////////////////////////////////////////////////////////
	///////////Longitudinal Gap Transformation///////////////////////////////
	number =W_0i.size();
	for (int i = 0; i < number; ++i)
	{
			
		Ph_0i[i] = Ph_0i[i]* num_har;
		dPh_1i.push_back( Ph_0i[i] );
	//	 dW_1i.push_back(  dW_0i[i] + Charge*V_eff*( TMath::Cos(dPh_1i[i]*TMath::Pi()/180)  - TMath::Cos(phi_0s*TMath::Pi()/180) ) );
		dW_1i.push_back(dW_0i[i] + Charge * V_eff * (cos((dPh_1i[i] + phi_0s) * M_PI / 180)));
		W_1i.push_back(dW_1i[i] + W_1s);
		Ph_1i.push_back(dPh_1i[i] / num_har);
		Ph_0i[i] = Ph_0i[i] / num_har;
	}
	cout << "===GAP::::Finished===" << endl;
}



#endif