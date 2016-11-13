//===================================
// MOTOR PARAMETERS
//===================================

const int maxFP=15;			// maximal FP searched for
const double sigmaThres=3.0;	// sigma threshold
const double zeroCutoff=0.00001;
const double FPLargerVal=0.5;

const long double doubleLimit = 1e25;
	// ATTENTION, should be larger than exp(2*f) to avoid states with 2 rates that are too large!
//const long double doubleLowLimit = 1e-10;
const double doubleZero=1e-25; // for comparison of doubles with zero

const int useBalancing = 0;//1;//0;/// if = 1: use balancing of matrix, if =0 not
const int useDiscardRates=1;//1;//0;// if =1 use discarding of states with large out rate, if =0 not
const int useSymmetry=0; //if =1 use symmetry for same kind of motors, =0 otherwise
	// don't use it! Somehow there's a factor two for the nondiagonal elements!!!!
const int discardSmallMaxima=1; // discard maxima that are too small

int switchStatesChoice=0;
// = 0 determine L,P,R via velocity
// = 1 take diagonal as P
// = 2 take boundaries as L,R

const int useKinesinRates=0; // if =1 fixes minus direction rates to kinesin rates; for normal calculation = 0
const int boundStatesOnly=0; // only bound states if =1, all states if =0
const int generalOutput = 0; // produces general output appending to generalFile with name given in Para.CPP

// zoom in
const int zoomIn =1;//1;//1; // =0 no zoom in, =1 zoom in
const int zoomDepth = 5; // how many zoom levels

//measure point properties
const int pointMeas=1; //=0 no point meas, = 1 point meas
const int deltaMeas=0;// measure delta value phase trasition
const int measureBifDiag=0;//1; //=0 no bif diag output, = 1 bifurcation diagram output
//const int renormalize=0; // whether to do renormalization for pointMeasure

const int specialDiagonal=1;//1; // consider maxima near diagonal as diagonal, makes sense only for symmetric case
const int special10=0; // if =1: special count of maxima at (1,0) resp. (0,1)
const int scanEps=1; // if =1: first loop over eps, then over f;   if =0: first loop over f, then over eps
// normally use =1!!!!!!  =0 has been implemented for PointMax and FPMax only, and for ZoomIn only
// to get all lines: use special10=0, scanEps=1
//			and    special10=1, scanEps=0
// parameters created by GeneratePara.sh
//#include "Para.CPP"
#include "ParaStat.CPP"


//const int = 4;				// total number of plus motors
//const int Nm = Np;//5;//Np;// Np;	// total number of minus motors
//char MakeFileNames::folder[80]="../Test/";

const int numberOfStates=(Np+1)*(Nm+1) - useSymmetry*Np*(Np+1)/2;
//const int renormNp=(Np+1)/2+1;
//const int renormNm=(Nm+1)/2+1;

const double significance=1;// significance of difference in extrema or maxima
	// should be slightly larger than 1, as it's a factor
	// will not have any effect if equal to 1

//single point only

const double KStart=0.25;
const double KEnd=KStart-1;
const double fStart      = 1.7;//0.1;//2.77123;//3.64218;//0.5;//30;
const double fEnd       = fStart-1;//fStart;
const double KIncr  = 0.03;//0.003;//0.13;
const double fIncr       = 0.07;


// phase diagram
/*
const double KStart = 0.00001;
const double KEnd  = 5.1;
const double fStart   = 0.001;//0.01;//30;
const double fEnd    =4;//fStart;//4;//3.5;//fStart-1;//fStart;
const double KIncr  = 0.01;//0.5;//0.02;//0.003;//0.13;
const double fIncr    = 0.01;
*/

// single line
/*
const double KStart = 0.0001;
const double KEnd  = 5.1;
const double fStart   = 10.5;//0.001;//0.01;//30;
const double fEnd    =fStart;//15;//fStart;//4;//3.5;//fStart-1;//fStart;
const double KIncr  = 0.01;//0.5;//0.02;//0.003;//0.13;
const double fIncr    = 0.05;
*/

// single motor parameters for transition rates
const double piPlus = 1;//5;//5;				// plus motor attachment rate
const double piMinus=piPlus;			// minus motor attachment rate
const double epsStart = KStart*piPlus;//0.2;//0.01;//0.45;//0.1;//0.13;
const double epsEnd  =KEnd*piPlus;//5;//epsStart-1;//epsStart;//0.13;
const double epsIncr  = KIncr*piPlus;//0.003;//0.13;
const VELOCITYMODEL velocChoice = loadSK;//blockRL;;// loadSK for load model (SK), blockRL for block model (RL)
const double FdPlus = 3; 				// plus motor detachment force
const double FdMinus = FdPlus;			// minus motor detachment forces
double FsPlus=fStart*FdPlus; 			// plus motor stall force
double FsMinus=fStart*FdMinus;			// minus motor stall force
double epsPlus=epsStart;				// plus motor detachment rate
double epsMinus=epsPlus;				// minus motor detachment rate
const double gPlus = 1;		// rebinding factor  from unbound cargo state, gPlus = factor for rate 00->10
const double gMinus = gPlus;	// gMinus = factor for rate 00->01, gPlus=gMinus=1 for undisturbed stationary state
const double bPlus = 1; 			// factor for rate 10->00
const double bMinus = bPlus;		// factor for rate 01->00
		// setting b's=0 means that cargo cannot unbind
//const double gamm = 0;				// friction coefficient
const double vPlus = 1.0; 				// plus motor velocity
const double vMinus = vPlus; 			// minus motor velocity (sign is cared for in velocity transition rate)
const double betaPlus = 0.05;//vPlus/FsPlus;//0.0;			// slope of plus motor force-velocity-curve in FsPlus
const double betaMinus=betaPlus;//vMinus/FsMinus;//betaPlus;		// slope of minus motor force-velocity-curve in FsMinus
//const double lambda=1.0;


//const double epsMinusStart=epsPlusStart;
//const double fMinusStart = fPlusStart;
//const double epsMinusEnd=epsPlusEnd;
//const double fMinusEnd = fPlusEnd;

//unsymmety factors
const double epsFactor=1;//0.5;//2; //epsM=epsFactor*epsP
const double fFactor=1; //fM=fFactor*fP



#include "TransitionRates.CPP"


// filenames
#include "StatFiles.CPP"

