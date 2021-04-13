The aim and process of the program
----
# BunchingFormation
This algorithm is based on a concept of a beam dynamics code which adopted to a low energy hybrid (f-2f) DTL structure. The program of this algorithm can be divided into two main parts.

---------------------
One of them has a general purpose for users. The code should be easily adjusted and compiled with an external platform by users who are not familiar with the programming but focus on designing. Therefore, the "General" purpose can be studied under 3 sub-purposes which we called as "Main", " Plot", "GUI".
  1. MAIN : Interface to input and output data; common data base for exchange between subroutines;control of processes (subroutine calls).
  2. PLOT : Starting of results for plotting; use of libraries of an external plotting software.
  3. GUI : basic tools for easier code handling by the users.
----------------------
The second main part or purpose is the special tasks or subroutine implementations. These subroutines that we call are "Accelerator Elements", "Space Charge Kick", and "Generation of an input particle distribution".
 1. Accelerator Elements :
    a. "GAP"   (Veff,φs)
    b. "DRIFT" (Ld, a) - (length of drift, aperture)
    c. "LENS"  (Lm, gradient - [T/m], polarity, aperture) – Quadrupole - Solenoid
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

-----------
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

Some explanations about procedures that I use and problems that I face with 
----------------------
9 sutunluk parametre ve N-satirdan olusan 'bir veri dosyam var. Bu bilgileri "partdist.hpp" den her sutundaki bilgiyi tek boyutlu vectorlere yazdiriyorum ve baslangic bilgilerimi depolamis oluyorum. "partdist.hpp"nin okudugu external dosyadan alinan input data set, dosyalardaki "PhaseSpace.txt" dosyasi.

Bu txt dosyasindan aldigim input data bilgilerini manual'de elle tanimladigim fonksiyonlarin icine atarak sirayla isleme sokuyorum. Bu fonksiyonlar aslinda simulasyonumda kullanmak istedigim elementlerin tepkilerini iceren fonksiyonlar. (eg. QUAD dedigim sey aslinda 4-kutuplu bir miknatis. Bu miknatis transverse direction'nin bir yonunde parcaciklari converge ediyor, diger yonde diverge.) Yani bu fonksiyonlar input vectorleri aliyor, output vectorleri olusturuyor. Ben bu birbirini takip eden input-output dongusel vectorleri elimde tutmak istiyorum cunku bazen plot etmek, bazen depolanan bilgileri kullanarak kapladiklari alani, olusturduklari envelope'u hesaplamak icin kullanmak istiyorum. Bu sebeple bu vectorleri silip geri kullanamiyorum ya da bu amacimi gerceklestirecek recursive bir dongu olusturamadim kafamda. 
Bu olusturamadigim dongu bana bircok vector tanimlamasi yapmaya ve upuzun , karmasik parametrelerden olusan fonskiyon satirlari yazmama sebep oluyor. 
Bir yol, recursive dongu olusturmak olabilir tabi ama ben beceremedim....
Ikinci aklima gelen, bunlari multi-dimensional vectorler olarak yazmak olabilir fakat bu multi-dimensional vectorlerde adres kullanimini cozemedigim icin fonksiyonlarda kullanamadim. 
Bu yetersizliklerimle ben de teker teker vectorleri tanimlayip hem fonksiyonlari header'larda tanimlarken "karmasa" olusturuyorum hem de kullanim sirasinda isimleri karistirarak takibi zor bir durum olusturuyorum.
Bunlari elegant bir kod yazabilmek icin istememin disinda ileri adimlarda bu fonksiyon siralamasini configuration file'dan okuyarak yapmak istiyorum. el ile main func.'a yazarak yapmak istemiyorum. O yuzden kodun user'dan bagimsiz calisan bir sistem yazmak istiyorum.



Main function ile baslayalim. 

Buradaki ilk problem InputSetup.hpp dosyasinda tanimlayamaya calistigim "Parameters" class ile ilgili. Bunu tam olarak nasil kullanacagimi bilemedigim icin design'
da kullanacagim sabit parametre degerleri icin olusturdum. Bu parametrelerin degelerin user tarafindan configuration file'dan okunarak alinacak ve tum algorithma boyunca sabit kalacak. 
