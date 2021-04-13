#ifndef QUAD
#define QUAD

#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "InputSetup.hpp"

using namespace std;


void Quad(int &B_sign, double &steplength, int &num_har, double &lambda, double &gamma, double &beta, double &L_s,
		std::vector<double> &X_0i,  std::vector<double> &Xp_0i, std::vector<double> &Y_0i,  std::vector<double> &Yp_0i, 
		std::vector<double> &X_1i,  std::vector<double> &Xp_1i, std::vector<double> &Y_1i,  std::vector<double> &Yp_1i, 
		std::vector<double> &W_0i) 
{
	Parameters ReadSetup(1, 1, 938.27, 162.5e6, 299792458, -90, 90, 0.100, 0.007, 0.003, 0.05, 0.20, 10, 0.01, 0.03);
	double AtomicMass = ReadSetup.AtomicMass;
	double Charge = ReadSetup.Charge;
	double E_0 = ReadSetup.E_0;
	double freq = ReadSetup.freq;
	double SpeedofLight = ReadSetup.SpeedofLight;
	double phi_0s = ReadSetup.Ph_s;
	double phi_0s2 = ReadSetup.Ph_s2;
	double W_0s = ReadSetup.W_s;
	double V_eff = ReadSetup.V_eff;
	double V_eff2 = ReadSetup.V_eff2;
	double L_d = ReadSetup.L_d;
	double L_d2 = ReadSetup.L_d2;
	double B_prime = ReadSetup.B_prime;
	double aper = ReadSetup.aper;
	double L_m = ReadSetup.L_m;
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
	lambda 	= SpeedofLight/(freq*num_har);  //[m]
	gamma 	= 1 + W_0s/(E_0*AtomicMass);
	beta 	= sqrt( 1 - (1/gamma)*(1/gamma) );
	L_s 	= beta*lambda/2;
	/*	cout << "Sync Length:\t" << L_s << endl;
		cout << "lambda:\t" << lambda << endl;
		cout << "gamma:\t" << gamma << endl;
		cout << "beta:\t" << beta << endl;
	*/


	double k_i, gamma_i, beta_i, Mag_strength;
	double number;
		cout << "QUAD::Mag Field Gradient:\t" << B_prime << "\t[T/m]" << endl;
		cout << "============= QUAD Calculation starts !! ===========" << endl;
	/////////////////////////////////////////////////////////////////
	///////////Focusing Plane///////////////////////////////////////
	if(B_sign==0)
	{
		Mag_strength = B_prime/10;
		number = X_0i.size();
		for (int i = 0; i < number; ++i)
		{
			gamma_i = 1 + W_0i[i]/(E_0*AtomicMass);
			beta_i 	= sqrt( 1 - (1/gamma_i)*(1/gamma_i) );
			k_i = Charge*Mag_strength*SpeedofLight/(gamma_i*beta_i*AtomicMass*E_0*1e6) ;
	//		cout << "k_factor:\t" << k_i << endl;
		
			 X_1i.push_back( X_0i[i]*cos(sqrt(k_i)*steplength) +  
			 				 Xp_0i[i]/sqrt(k_i)*sin(sqrt(k_i)*steplength) );
			Xp_1i.push_back( X_0i[i]*(-1)*sqrt(k_i)*sin(sqrt(k_i)*steplength) +  
							 Xp_0i[i]*cos(sqrt(k_i)*steplength) );			
		}
		number = Y_0i.size();
		for (int i = 0; i < number; ++i)
		{
			gamma_i = 1 + W_0i[i]/(E_0*AtomicMass);
			beta_i 	= sqrt( 1 - (1/gamma_i)*(1/gamma_i) );
			k_i = Charge*Mag_strength*SpeedofLight/(gamma_i*beta_i*AtomicMass*E_0*1e6) ;
	//		cout << "k_factor:\t" << k_i << endl;
		
		 	Y_1i.push_back( Y_0i[i]*cosh(sqrt(k_i)*steplength) + 
			 				 Yp_0i[i]/sqrt(k_i)*sinh(sqrt(k_i)*steplength) );
			Yp_1i.push_back( Y_0i[i]*sqrt(k_i)*sinh(sqrt(k_i)*steplength) +  
							 Yp_0i[i]*cosh(sqrt(k_i)*steplength) );
		}
	}
	/////////////////////////////////////////////////////////////////
	///////////DEFocusing Plane/////////////////////////////////////
	else if(B_sign==1)
	{
		Mag_strength = B_prime/20;
		number = X_0i.size();
		for (int i = 0; i < number; ++i)
		{
			gamma_i = 1 + W_0i[i]/(E_0*AtomicMass);
			beta_i 	= sqrt( 1 - (1/gamma_i)*(1/gamma_i) );
			k_i = Charge*Mag_strength*SpeedofLight/(gamma_i*beta_i*AtomicMass*E_0*1e6) ;
	//		cout << "k_factor:\t" << k_i << endl;
		
			
			 X_1i.push_back( X_0i[i]*cosh(sqrt(k_i)*steplength) + 
			 				 Xp_0i[i]/sqrt(k_i)*sinh(sqrt(k_i)*steplength) );
			Xp_1i.push_back( X_0i[i]*sqrt(k_i)*sinh(sqrt(k_i)*steplength) +  
							 Xp_0i[i]*cosh(sqrt(k_i)*steplength) );
 
		}
		number = Y_0i.size();
		for (int i = 0; i < number; ++i)
		{
			gamma_i = 1 + W_0i[i]/(E_0*AtomicMass);
			beta_i 	= sqrt( 1 - (1/gamma_i)*(1/gamma_i) );
			k_i = Charge*Mag_strength*SpeedofLight/(gamma_i*beta_i*AtomicMass*E_0*1e6) ;
	//		cout << "k_factor:\t" << k_i << endl;
		
		 	 Y_1i.push_back( Y_0i[i]*cos(sqrt(k_i)*steplength) +  
			 				 Yp_0i[i]/sqrt(k_i)*sin(sqrt(k_i)*steplength) );
			Yp_1i.push_back( Y_0i[i]*(-1)*sqrt(k_i)*sin(sqrt(k_i)*steplength) +  
							 Yp_0i[i]*cos(sqrt(k_i)*steplength) );			
		}

	}
}

#endif