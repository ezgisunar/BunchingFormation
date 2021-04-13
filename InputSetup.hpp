#ifndef INPUTSETUP
#define INPUTSETUP

class Parameters {
    public:
     int AtomicMass, Charge;
     double E_0, freq, SpeedofLight,Ph_s, Ph_s2, W_s, V_eff, V_eff2, L_d, L_d2,B_prime, aper, L_m;

     Parameters(int a1, int a2, double a3, double a4, double a5, double a6, double a7, double a8,
              double a9, double a10, double a11, double a12, double a13, double a14, double a15 )
     {
       AtomicMass   = a1;
       Charge       = a2;
       E_0          = a3;
       freq         = a4;
       SpeedofLight = a5;
       Ph_s         = a6;
       Ph_s2        = a7;
       W_s          = a8;
       V_eff        = a9;
       V_eff2       = a10;
       L_d          = a11;
       L_d2         = a12;
       B_prime      = a13;
       aper         = a14;
       L_m          = a15;
     }
};

/*
void ReadSetup( double &AtomicMass, double &Charge, double &E_0, double &freq, double &SpeedofLight,
  double &Ph_s, double &Ph_s2, double &W_s, double &V_eff, double &V_eff2, double &L_d, double &L_d2,
  double &B_0, double &aper, double &L_m)
{
  
  std::string cizgi,bilinmeyen;
  std::string parameter[16];
  double value[16];
  int dum=0;
  double deger;
  std::ifstream data;
  data.open("BunForLibrary_wo_root/setup_tracewin.txt");
  if (data.is_open())
  {
    while (getline(data, cizgi))
    {
      if (cizgi[0] == '#' && cizgi[1] == '#')
        continue;
      data >> bilinmeyen >> deger;
      std::cout << bilinmeyen << ":\t" << deger << std::endl;
      parameter[dum] = bilinmeyen;
      value[dum] = deger;
      dum++;
    }     
        }
    data.close();

  AtomicMass    = value[0]; 
  Charge      = value[1]; 
  E_0       = value[2]; 
  freq      = value[3]; 
  SpeedofLight  = value[4]; 
  Ph_s      = value[5]; 
  Ph_s2       = value[6]; 
  W_s       = value[7]; 
  V_eff       = value[8]; 
  V_eff2      = value[9]; 
  L_d       = value[10]; 
  L_d2      = value[11]; 
  B_0       = value[12];
  aper      = value[13];
  L_m       = value[14];



}
*/

#endif