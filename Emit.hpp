#ifndef EMIT
#define EMIT

#include <string>
#include <iostream>
#include <fstream>
#include "InputSetup.hpp"

void Emit( std::vector<double> &X_0i, std::vector<double> &Xp_0i, std::vector<double> &W_0i) {

	Parameters ReadSetup(1, 1, 938.27, 162.5e6, 299792458,-90,90,0.100, 0.007,0.003,0.05,0.20, 10,0.01,0.03);
double AtomicMass 	= ReadSetup.AtomicMass;
double Charge 		= ReadSetup.Charge;
double E_0 			= ReadSetup.E_0; 
double SpeedofLight = ReadSetup.SpeedofLight; 
double W_0s			= ReadSetup.W_s	; 


int N = X_0i.size();

double aavg, bavg, xxavg, yyavg, xyavg, emit_rms /* rms emittance */ ;
double alpha, beta, gamma, rel_beta, rel_gamma, emit_norm;

//Float_t ek, m_0, c;
//W_0s ---> ek = 0.020; // Kinetic energy (MeV)
//E_0 ---> m_0 = 938.272; // Proton rest mass energyy (MeV/c*c)
//SpeedofLight ---> c = 299792458; 	 // speed of light (m)
aavg = 0;
bavg = 0;


for (int i = 0; i < N; i++)  // take data value for each coloumn and row one by one and take the average values for x-x'  
{
	aavg += X_0i[i];
	bavg += Xp_0i[i];
}

aavg =aavg/N;
bavg =bavg/N;

for (int i = 0; i < N; i++)  // take data value for each coloumn and row one by one and take the average values for x-x'  
{

	xxavg += ( X_0i[i]-aavg)*( X_0i[i]-aavg);		// xx average
    yyavg += (Xp_0i[i]-bavg)*(Xp_0i[i]-bavg);		// x'x' average
    xyavg += ( X_0i[i]-aavg)*(Xp_0i[i]-bavg);		// xx' average

}
xxavg = xxavg/N;
yyavg = yyavg/N;
xyavg = xyavg/N;

emit_rms = sqrt (xxavg*yyavg-xyavg*xyavg); 
cout << " emit_rms:\t" << emit_rms <<"\t mm.mrad" << endl;

// Twiss parameters
beta = xxavg / emit_rms;
alpha = - xyavg / emit_rms;
gamma = yyavg / emit_rms;
rel_gamma = 1 + (W_0s/E_0);
rel_beta = sqrt(1-1/(rel_gamma*rel_gamma));
emit_norm = emit_rms * rel_gamma * rel_beta ; // unit : "m*rad"

cout << " emit_norm:\t" << emit_norm <<"\t mm.mrad" << endl;

}

#endif
