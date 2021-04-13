#ifndef PARTDIST
#define PARTDIST

#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "InputSetup.hpp"

using namespace std;

void partdist( 
	std::vector<double> &X_0i, std::vector<double> &Xp_0i, 
	std::vector<double> &Y_0i, std::vector<double> &Yp_0i, 
	std::vector<double> &Ph_0i, std::vector<double> &W_0i, 
	std::vector<double> &dPh_0i,std::vector<double> &dW_0i) 
{

	Parameters ReadSetup(1, 1, 938.27, 162.5e6, 299792458,-90,90,0.100, 0.007,0.003,0.05,0.20, 10,0.01,0.03);

double phi_0s 		= ReadSetup.Ph_s ; 
double W_0s			= ReadSetup.W_s	; 


	std::string cizgi;
	int number =0; 
	double dumm=0;
	double x,xp,y,yp,z,zp,phi,W, a;
	std::fstream myfile;
	myfile.open("PhaseSpace.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, cizgi))
		{
			dumm++;
	        //  if (cizgi[0]=='N' || cizgi[0]=='x' ) continue;
		      if (dumm < 3 ) continue;
		        myfile >> x >> xp >> y >> yp >> z >> zp >> phi >> a >> W >> a;     
		        X_0i.push_back(x); 		Xp_0i.push_back(xp);
		        Y_0i.push_back(y); 		Yp_0i.push_back(yp);
//		        Zpos.push_back(z); 		Zdeg.push_back(zp);
		        Ph_0i.push_back(phi);	W_0i.push_back(W); //[MeV]
		        dW_0i.push_back((W - W_0s));
		        dPh_0i.push_back( phi - phi_0s);
		        number++;
		    }
	      }
	  myfile.close();
	int par_num = X_0i.size();
		std::cout << "PARDIST::Xpos size0:\t\t" << X_0i.size() << std::endl;
par_num = Y_0i.size();
		std::cout << "PARDIST::Ypos size0:\t\t" << Y_0i.size() << std::endl;

}


#endif