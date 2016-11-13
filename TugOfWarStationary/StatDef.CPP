//*******************************************************************
// libraries
//*******************************************************************
//#include<iostream.h>
//#include<fstream.h>
#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
//#include<string>
//#include<malloc.h>
#include<math.h>
#include<cmath>
#include<limits>
//#include "NR/nr.h"

using namespace std;

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

#include "VecMatRoutines.CPP"
#include "MatInvert.CPP"


//*******************************************************************
// types
//*******************************************************************

enum TRANSITIONS {AttachPlusMotor=1, AttachMinusMotor=2,
	DetachPlusMotor=3, DetachMinusMotor=4, notMove=5,NotValid=0};

enum STATES {Middle=0,Left=1,Up=2,Right=3,Low=4,LLCorner=5,LUCorner=6,RUCorner=7,RLCorner=8};

enum VELOCITYMODEL{loadSK=1,blockRL=2};

enum SWITCHSTATES {P=0,L=1,R=2};

//*******************************************************************
// structures
//*******************************************************************

struct points
{
	int point1;
	int point2;
};

//*******************************************************************
// debugging
//*******************************************************************
#define DEBUG
#include "Assert.CPP"

//*******************************************************************
// parameters
//*******************************************************************
//#include "StatPara.CPP"

#include "StatPara.CPP"

void test()
{
int i =Np;
i=Nm;
}

//*******************************************************************
// subroutines
//*******************************************************************
#include "StatIndexClass.CPP"
#include "StatSubroutines.CPP"

//*******************************************************************
// globals
//*******************************************************************
//#include "TugGlobals.CPP"
//#include "TugMeasurePara.CPP"

#include "StatMatrixClass.CPP"
//#include "StatGammaClass.CPP"


//*******************************************************************
// subroutines
//*******************************************************************
//#include "TugMeasureSubroutines2.CPP"



