//******************************************************************
// variables
//******************************************************************
time_t time1,time2;		//time measurement variables
double timeUsed=0;		//time difference

double t; // actual time for single trajectory
double nextMeasureTime;// time for next measurements
int numberOfMeasurements; //actual number of measurements until now
int trajectoryN; // number of actual trajectory

double normalization,normP,normM;
//double deltaT,deltaX;
double x,v;

int i,j,n,nmin,nmax,l;
int kp,km;

// variables for stationary state measurement
//int numberOfStatSteps;
int actualKp,actualKm;
int del,sig;
double waitTime;
double integrateTimeStat, distanceStat, pausingTimeStat;
double sTime,sDist;

// variables for stationary measurement
double fPOld;

int done;
int tChanged;
int timeIni;


//******************************************************************
// initialize random number generator
//******************************************************************
randomInitialize(seed);
//randomDouble01(void)  -> double random in (0,1)
//randomInteger(int)	  -> integrer random in ?[0,int)

//******************************************************************
// initialize variables
//******************************************************************
//kpIni = cargoMotors.GetKp();
//kmIni = cargoMotors.GetKm();

//******************************************************************
// initialize filenames
//******************************************************************
MakeFileNames FileNames(folderName);
FileNames.makeNames();
FileNames.openPermanentFiles();

// ================================================
// test parameters
// ================================================
ASSERTperm(Np>=0);
ASSERTperm(Nm>=0);
//ASSERTperm(kpIni>=0);
//ASSERTperm(kmIni>=0);
//ASSERTperm(kpIni<=Np);
//ASSERTperm(kmIni<=Nm);
ASSERTperm(epsPlus>=0);
ASSERTperm(epsMinus>=0);
ASSERTperm(piPlus>=0);
ASSERTperm(piMinus>=0);
ASSERTperm(timeInterval>0);


// ================================================
// initialize measurement variables
// ================================================
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
{
	for(i=0; i<=numberOfTimes;i++)
	{
		pKpKm[kp][km][i] = 0.0;
	}//end for i
	pVelocity[kp][km] = 0;
}}// end for kp, for km
for(i=0; i<=numberOfTimes;i++)
{
	pDist[i] = 0.0;
}//end for i

for(i=0;i<nTauBins+1;i++){pTau[i]=0;}
for(i=0;i<(Np+1)*(Nm+1);i++){pDifferentVelocities[i]=0;}

for(i=0;i<nWalkingTimeBins+1;i++){pWalkingTime[i]=0;}
for(i=0;i<extraWalkingTimeBins;i++){pWalkingTimeSmall[i]=0;}

for(i=0;i<nWalkingDistanceBins+2;i++){pWalkingDistance[i]=0;}
for(i=0;i<extraWalkingDistanceBins;i++){pWalkingDistanceSmall[i]=0;}

for(i=0;i<nSwitchingTimeBins+1;i++){pSingleRunTimePlus[i]=0;}
for(i=0;i<extraSwitchingTimeBins;i++){pSingleRunTimePlusSmall[i]=0;}
for(i=0;i<nSwitchingTimeBins+1;i++){pSingleRunTimeMinus[i]=0;}
for(i=0;i<extraSwitchingTimeBins;i++){pSingleRunTimeMinusSmall[i]=0;}
for(i=0;i<nSwitchingTimeBins+1;i++){pSwitchingTimePlusToMinus[i]=0;}
for(i=0;i<extraSwitchingTimeBins;i++){pSwitchingTimePlusToMinusSmall[i]=0;}
for(i=0;i<nSwitchingTimeBins+1;i++){pSwitchingTimeMinusToPlus[i]=0;}
for(i=0;i<extraSwitchingTimeBins;i++){pSwitchingTimeMinusToPlusSmall[i]=0;}
for(i=0;i<nSwitchingTimeBins+1;i++){pPauseTime[i]=0;}
for(i=0;i<extraSwitchingTimeBins;i++){pPauseTimeSmall[i]=0;}

for(i=0;i<nSwitchingDistanceBins+2;i++){pSingleRunDistance[i]=0;}
for(i=0;i<extraSwitchingDistanceBins;i++){pSingleRunDistanceSmall[i]=0;}
for(i=0;i<nSwitchingDistanceBins+2;i++){pSwitchingDistance[i]=0;}
for(i=0;i<extraSwitchingDistanceBins;i++){pSwitchingDistanceSmall[i]=0;}

for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){pStatKpKm[kp][km] = 0.0;}}// end for kp, for km
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){pStatKpKmSumTrajec[kp][km] = 0.0;}}// end for kp, for km
for(i=0;i<(Np+Nm+1);i++){pStatDel[i]=0; pStatSig[i]=0;}
for(i=0;i<(Nm+1);i++){pStatDelSummed[i]=0;}

cargoMotors.SetCargoRates(Np,Nm,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus);

//meanSwitchingTime=0;
//meanSwitchingDistance=0;
//meanPausingTime=0;
//numberOfStatSteps = 0;
integrateTimeStat = 0;
distanceStat = 0;
pausingTimeStat=0;

//******************************************************************
// initialize time measurement
//******************************************************************
time (&time1); // set time1 to current time (in sec since 1970)

//******************************************************************
// OPEN FILES
//******************************************************************
ofstream foutSingleProbaTrajectory(MakeFileNames::singleProbaTrajectoryFile);
	if(!foutSingleProbaTrajectory) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutSingleProbaTrajectory<<"# time,   no of +motors kp,  no of -motors km,   waiting time tau,   transitionType"<<endl;
	foutSingleProbaTrajectory.width(7); foutSingleProbaTrajectory.setf(ios::left);
	foutSingleProbaTrajectory.precision(7); foutSingleProbaTrajectory.setf(ios::showpoint|ios::fixed);
ofstream foutSingleTrajectory(MakeFileNames::singleTrajectoryFile);
	if(!foutSingleTrajectory) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutSingleTrajectory<<"# time      walking distance       waiting time     delta"<<endl;
	foutSingleTrajectory.width(7); foutSingleTrajectory.setf(ios::left);
	foutSingleTrajectory.precision(7); foutSingleTrajectory.setf(ios::showpoint|ios::fixed);


//******************************************************************
// WRITE PARAMETERS to parameterFile
//******************************************************************

ofstream foutPara(MakeFileNames::parameterFile);
	if(!foutPara) {cout<<"Unable to open file! ";ASSERTperm(0);}
foutPara<<"Np = "<<Np<<", Nm = "<<Nm<<", initialCondition = "<<initialCondition<<endl;
foutPara<<"epsPlus = "<<epsPlus<<", epsMinus = "<<epsMinus<<", piPlus = "<<piPlus<<", piMinus = "<<piMinus<<endl;
foutPara<<"FsPlus = "<<FsPlus<<", FsMinus = "<<FsMinus<<", FdPlus = "<<FdPlus<<", FdMinus = "<<FdMinus<<endl;
foutPara<<"vPlus = "<<vPlus<<", vMinus = "<<vMinus<<", betaPlus = "<<betaPlus<<", betaMinus = "<<betaMinus
<<", gPlus = "<<gPlus<<", gMinus = "<<gMinus<<endl;
foutPara<<"maxTime = "<<maxTime<<", measureTimeInterval = "<<timeInterval<<", number of time bins = "<<numberOfTimes
	<<", equilTime = "<<tEq<<endl;
foutPara<<"numberOfTrajectories = "<<numberOfTrajectories<<endl;
foutPara.close();

//******************************************************************
// WRITE PARAMETERS to paraFile
//******************************************************************

foutPara.open(MakeFileNames::paraFile);
	if(!foutPara) {cout<<"Unable to open file! ";ASSERTperm(0);}
foutPara<<"const int Np = "<<Np<<";"<<endl;
foutPara<<"const int Nm = "<<Nm<<";"<<endl;
foutPara<<"const int numberOfTimes = "<<numberOfTimes<<";"<<endl;
foutPara<<"const double maxTime = "<<maxTime<<";"<<endl;
foutPara<<"const char folder[80]=\""<<FileNames.folder<<"\";"<<endl;
foutPara.close();

//******************************************************************
// WRITE PARAMETERS on screen
//******************************************************************
cout<<"Cargo transport with 2 species of molecular motors, output to folder "<<FileNames.folder<<endl;
cout<<"Np = "<<Np<<", Nm = "<<Nm<<", initialCondition = "<<initialCondition;
DisplayInichoice(initialCondition);
cout<<"epsPlus = "<<epsPlus<<", epsMinus = "<<epsMinus<<", piPlus = "<<piPlus<<", piMinus = "<<piMinus<<endl;
cout<<"FsPlus = "<<FsPlus<<", FsMinus = "<<FsMinus<<", FdPlus = "<<FdPlus<<", FdMinus = "<<FdMinus<<endl;
cout<<"vPlus = "<<vPlus<<", vMinus = "<<vMinus<<", betaPlus = "<<betaPlus<<", betaMinus = "<<betaMinus
<<", gPlus = "<<gPlus<<", gMinus = "<<gMinus<<endl;
cout<<"maxTime = "<<maxTime<<", measureTimeInterval = "<<timeInterval<<", number of time bins = "<<numberOfTimes
	<<", equilTime = "<<tEq<<endl;
cout<<"numberOfTrajectories = "<<numberOfTrajectories<<endl;
cout<<endl;

