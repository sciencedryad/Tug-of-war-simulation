//****************************************************************
// MODEL and OUTPUT CHOICES
//****************************************************************

// velocity model
const VELOCITYMODEL velocChoice = blockRL;//loadSK;

const int setUnboundToZero = 0; // if =1: sets walking time and distance to zero if cargo unbinds.
	// if =0: considers unbound state as normal state

const long double doubleLimit = 1e100;//set large transition rates to doubleLimit
const double doubleZero=1e-20; // for comparison of doubles with zero

// for film
const int writeConf = 0; // writes configuration for film if 1, nothing if 0

// for trajectory
const int writeTrajectory =1;//1; 		// writes first trajectory to single trajectory file if 1, nothing if 0
const int writeAllTrajectories =0;//1;	// writes all trajectories if 1, nothing if 0
	// attention: files get big if all trajectories are written
const int trajectoryMaxTime=1000; 	//maximal time for trajectoy (to avoid crashs due to too large files)
const int trajectoryNMax=10; 		//maximal number of trajectories to write

const int boundStatesOnly=0; // only bound states if =1, all states if =0. Only used for calculation of stationary state probability

int doChange=0; // if =1 does abrupt change of some parameter at time tChange

//int equilReIni=1; // if =1:reinitializing when equilibration is done, not if =0
	// not a constant because is changed to zero after reinitialization
	// not needed because is tested in CargoClass

//****************************************************************
// MOTOR PARAMETERS
//****************************************************************

//#include "Para.CPP"
//#include "ParaTug.CPP"
const int Np = 4;	// number of plus motors
const int Nm = Np;  // number of minus motors
char folderName[80]="Test/"; // folder for file output

// MORE MOTOR PARAMETERS
const int NpChange = 5;
const int NmChange = 5;


//****************************************************************
// SIMULATION TIME PARAMETERS
//****************************************************************
const int numberOfTrajectories = 1;//10;//10;//50;
//const int tEq = 1e7;//1e5;//1e4;//10000; // equilibration time
const double tEq = 1e6;//1e5;//1e5;//*pow(1.3,Np);//1e5;//1e4;//10000; // equilibration time
const double tStartDynamicMeasure = 0;//1e3;//10000;
const double maxTime =tEq+tStartDynamicMeasure+1e7;//1e6;//1e5;//tEq;//1e5;//1000000;//1000000;//1000000.0;
	// must be smaller than 1e7!!!!! WHY, no???

const double tChange = tEq+tStartDynamicMeasure+500;// time for change of some parameter, see file TugTimeChange.CPP
const int numberOfTimes = 10;//2000; // number of time bins for measurements
const double timeInterval = (maxTime - tStartDynamicMeasure)/(1.0*numberOfTimes);; // time interval of measurements

// initial motor numbers
const INICHOICE initialCondition = Random;
//Plus1Minus1;//Plus1Minus1;//PlusMinus1Random;//PlusNMinusN;
	// Plus1Minus0: kp=1,km=0
	// Plus0Minus1: kp=0,km=1
	// PlusMinus1Random: kp or km =1 at random
	// Plus1Minus1: kp=1,km=1
	// PlusNMinus0: kp=Np,km=0
	// Plus0MinusN: kp=0,km=Nm
	// PlusNMinusN: kp=Np,km=Nm
	// Random: random
//const INICHOICE initialConditionOdd = PlusNMinus0;
//const INICHOICE initialConditionEven = Plus0MinusN;


unsigned long int seed = 260; // random number generator seed

// hopping probabilities
/*
const double epsStart=0.4;
const double epsEnd=epsStart;//1.5;
const double fStart=3;
const double fEnd=fStart;//3.0;
const double epsIncr=0.03;
const double fIncr=0.08;
*/

const double FsPlus = 12;//4.5;//0.6;			// plus motor stall force
const double FsMinus = 0.57*FsPlus;		// minus motor stall force
const double FdPlus = 3;//2.5;			// plus motor detachment force
const double FdMinus = FdPlus;		// minus motor detachment force

const double epsPlus=1;			// plus motor detachment rate
const double epsMinus=epsPlus;	// minus motor detachment rate
const double piPlus = 5;			// plus motor attachment rate
const double piMinus=piPlus;		// minus motor attachment rate

const double gPlus = 1;		// rebinding factor when cargo is unbound
const double gMinus = gPlus;	// gPlus=gMinus=1 for undisturbed stationary state

const double bPlus = 1; 			// factor for rate 10->00
const double bMinus = bPlus;		// factor for rate 01->00
		// setting b's=0 means that cargo cannot unbind

const double vPlus = 1; 			//single plus motor velocity
const double vMinus =vPlus;	 	//single minus motor velocity, sign is cared for in velocity transition rate

const double betaPlus=0.05;//vPlus/FsPlus;//0.1;			// slope of plus motor v(F)-curve in FsPlus
const double betaMinus=betaPlus;//vMinus/FsMinus;//betaPlus;		// slope of minus motor v(F)-curve in FsMinus
//const double gamm=0;				// friction coefficient


const double significanceFactor=1.0001; //significanceFactor to count as max

// transition rates
#include "TransitionRates.CPP"

//****************************************************************
// MEASUREMENT PARAMETERS
//****************************************************************

const double tauMax=0.5;		// maximal waiting time for waiting time distibution binning
const int nTauBins = 100;	// number of bins for waiting times tau
const double deltaTau = tauMax/(double(nTauBins));

//const double vMax = double(floor(vPlus));		// maximal velocity for velocity distibution binning
//const double vMin = double(floor(vMinus));		// minimal velocity for velocity distibution binning
//const int nVBins = 20-2;	// number of bins for waiting times tau, will be changed by rates class!
//const double deltaV = (abs(vMin)+abs(vMax))/(double(nVBins)); // will be changed by rates class!

// switching times
const double switchingTimeMax = 50;//15000;//150;		// maximal switching time for walking time distibution binning
const int nSwitchingTimeBins = 500;			// number of bins for switching times tau
const double deltaSwitchT = switchingTimeMax/(double(nSwitchingTimeBins));
const double extraSwitchingTimeMax = 0;		// time until which extra small bins shall be made; no extraBins if equal to zero
const int extraSwitchingTimeBins = 1;			// number of extra bins for small switching times < extraWalkingTimeMax; must be >0
const double extraDeltaSwitchT = extraSwitchingTimeMax/(double(extraSwitchingTimeBins));

// switching distances
const double switchingDistanceMax = switchingTimeMax;//500;//150;	// maximal waiting Distance for switching Distance distibution binning
const double switchingDistanceMin = -switchingDistanceMax;//-500;//150;	// minimal waiting Distance for switching Distance distibution binning
const int nSwitchingDistanceBins =2*nSwitchingTimeBins;//50+50;		// number of bins for switching Distances tau
const double deltaSwitchX = ( abs(switchingDistanceMax) + abs(switchingDistanceMin) )/(double(nSwitchingDistanceBins));
const double extraSwitchingDistanceMax = 0;//1;		// positive distance until which extra small bins shall be made; no extra bins if =0
const double extraSwitchingDistanceMin = 0;//-1;		// negative distance until which extra small bins shall be made; no extra bins if =0
const int extraSwitchingDistanceBins = 2*1;		// number of extra bins for small switching Distances < extraSwitchingDistanceMax, must be >0
const double extraDeltaSwitchX = (abs(extraSwitchingDistanceMin) + abs(extraSwitchingDistanceMax) )/(double(extraSwitchingDistanceBins));

// walking times
const double walkingTimeMax = 100;//15000;//150;		// maximal walking time for walking time distibution binning
const int nWalkingTimeBins = 10;			// number of bins for walking times tau
const double deltaWalkT = walkingTimeMax/(double(nWalkingTimeBins));
const double extraWalkingTimeMax = 0;		// time until which extra small bins shall be made; no extraBins if equal to zero
const int extraWalkingTimeBins = 1;			// number of extra bins for small walking times < extraWalkingTimeMax; must be >0
const double extraDeltaWalkT = extraWalkingTimeMax/(double(extraWalkingTimeBins));

// walking distances
const double walkingDistanceMax = 50;//500;//150;	// maximal waiting Distance for walking Distance distibution binning
const double walkingDistanceMin = -50;//-500;//150;	// minimal waiting Distance for walking Distance distibution binning
const int nWalkingDistanceBins = 50;//50+50;		// number of bins for walking Distances tau
const double deltaWalkX = ( abs(walkingDistanceMax) + abs(walkingDistanceMin) )/(double(nWalkingDistanceBins));
const double extraWalkingDistanceMax = 0;//1;		// positive distance until which extra small bins shall be made; no extra bins if =0
const double extraWalkingDistanceMin = 0;//-1;		// negative distance until which extra small bins shall be made; no extra bins if =0
const int extraWalkingDistanceBins = 2*1;		// number of extra bins for small walking Distances < extraWalkingDistanceMax, must be >0
const double extraDeltaWalkX = (abs(extraWalkingDistanceMin) + abs(extraWalkingDistanceMax) )/(double(extraWalkingDistanceBins));



#include "TugFiles.CPP"
