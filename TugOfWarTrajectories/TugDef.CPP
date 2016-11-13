//*******************************************************************
// libraries
//*******************************************************************
//#include<iostream.h>
//#include<fstream.h>
#include<iostream>
#include<fstream>
#include<time.h>
#include<cmath>
//#include<stdlib.h>
//#include<malloc.h>
//#include<math.h>
using namespace std;

//*******************************************************************
// RANDOM NUMBERS
//*******************************************************************
#include "RandomMTImproved.CPP"
// Mersenne Twister Random Number Generator
// improved initialization and speed
// provides routines
// - to initialize: void init_genrand(unsigned long seed)
// - to call: double genrand_real1(void)
#define randomInitialize init_genrand
#define randomDouble01 genrand_real1
#define randomInteger genrand_int

//*******************************************************************
// types
//*******************************************************************

enum TRANSITIONS {AttachPlusMotor=1, AttachMinusMotor=2,
	DetachPlusMotor=3, DetachMinusMotor=4, NoMove=5,NotValid=0};

enum STATES {UNBOUND=0, BOUND=1};

enum INICHOICE {Plus1Minus0=1, Plus0Minus1=2, PlusMinus1Random=3,Plus1Minus1=4,PlusNMinus0=5,Plus0MinusN=6,PlusNMinusN=7,Random=8};

enum DIRECTION {Plus=1,Zero=0,Minus=-1};
//enum DIRECTION {Plus=1,Minus=-1};

enum VELOCITYMODEL{loadSK=1,blockRL=2};

enum SWITCHSTATES {P=0,L=1,R=2};

//*******************************************************************
// debugging
//*******************************************************************
#define DEBUG
#include "Assert.CPP"

//*******************************************************************
// parameters
//*******************************************************************
#include "TugPara.CPP"

//*******************************************************************
// subroutines
//*******************************************************************
#include "TugMeasureSubroutines.CPP"

//*******************************************************************
// globals
//*******************************************************************
#include "TugGlobals.CPP"
//#include "TugMeasurePara.CPP"

//*******************************************************************
// subroutines
//*******************************************************************
#include "TugMeasureSubroutines2.CPP"

void DisplayInichoice(const INICHOICE& iniCond)
{
if      (iniCond==Plus1Minus0){cout<<", kpIni = 1, kmIni = 0";}
else if (iniCond==Plus0Minus1){cout<<", kpIni = 0, kmIni = 1";}
else if (iniCond==PlusMinus1Random){cout<<", 1 plus or minus motor at random";}
else if (iniCond==Plus1Minus1){cout<<", kpIni = 1, kmIni = 1";}
else if (iniCond==PlusNMinus0){cout<<", kpIni = Np, kmIni = 0";}
else if (iniCond==Plus0MinusN){cout<<", kpIni = 0, kmIni = Nm";}
else if (iniCond==PlusNMinusN){cout<<", kpIni = Np, kmIni = Nm";}
cout<<endl;
}

