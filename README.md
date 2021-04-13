# BunchingFormation

This algorithm is based on a concept of a beam dynamics code which adopted to a low energy hybrid (f-2f) DTL structure. The program of this algorithm can be divided into two main parts. 
One of them has a general purpose for users. The code should be easily adjusted and compiled with an external platform by users who are not familiar with the programming but focus on designing. Therefore, the "General" purpose can be studied under 3 sub-purposes which we called as "Main", " Plot", "GUI".
  1. MAIN : Interface to input and output data; common data base for exchange between subroutines;control of processes (subroutine calls).
  2. PLOT : Starting of results for plotting; use of libraries of an external plotting software.
  3. GUI : basic tools for easier code handling by the users.
The second main part or purpose is the special tasks or subroutine implementations. These subroutines that we call are "Accelerator Elements", "Space Charge Kick", and "Generation of an input particle distribution". 
  1. Acc. Elem. :
    (a) "GAP"   (Veff,φs)
    (b) "DRIFT" (length, aperture)
    (c) "LENS"  (length, gradient - [T/m], polarity, aperture) – Quadrupole - Solenoid
  2. Space Charge
  3. Part. Dist. Gen. : "DIST" – Uniform, Waterbag
The program can be run as in the following example by writting a structure step by step; 
  call for reading Input file
  call : 
    "DRIFT()"  (1), 
    "LENS()"   (2), 
    "DRIFT()"  (3), 
    "GAP()"    (4), 
    "......"   (X), 
    "DRIFT()"  (9) 
  call for writing Output file
  call Plot
We should mention that for users, there will be a configuration txt file to put the necessary values for the design of the concept. The configuration file will include these parameters; 
  A     (atomic mass), 
  q     (charge of the particle), 
  E0    (input energy of the beam), 
  f     (operating frequency - in our case 162,5 MHz), 
  φs    (phase of synchronous particle at each harmonic section),
  Ws    (energy of synchronous particle at the beginning),
  Veff  (effective voltage for acceleration), 
  Ld    (drift lengths for each one). 
As a remind that Ws, energy of synchronous particle will be calculated at each subroutine by taking the starting information from the input data.

