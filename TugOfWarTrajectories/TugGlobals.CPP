#include "TugRateClass.CPP"
	// class containing transition rates, velocities etc.

int numberOfFinishedTrajectories = 0;

double pKpKm[Np+1][Nm+1][numberOfTimes+1];
double pDist[numberOfTimes+1];

//stationary state probability densities
double pStatKpKm[Np+1][Nm+1];
double pStatDel[Np+Nm+1];
double pStatDelSummed[Nm+1];
double pStatSig[Np+Nm+1];
double pStatKpKmSumTrajec[Np+1][Nm+1];


double pTau[nTauBins+1];
double pVelocity[Np+1][Nm+1];
double pDifferentVelocities[(Np+1)*(Nm+1)];
//double pVelocity[nVBins+3];

double pWalkingTime[nWalkingTimeBins+1];
double pWalkingTimeSmall[extraWalkingTimeBins];

double pWalkingDistance[nWalkingDistanceBins+1];
double pWalkingDistanceSmall[extraWalkingDistanceBins];

double pSingleRunTimePlus[nSwitchingTimeBins+1];
double pSingleRunTimePlusSmall[extraSwitchingTimeBins];
double pSingleRunTimeMinus[nSwitchingTimeBins+1];
double pSingleRunTimeMinusSmall[extraSwitchingTimeBins];
double pSwitchingTimePlusToMinus[nSwitchingTimeBins+1];
double pSwitchingTimePlusToMinusSmall[extraSwitchingTimeBins];
double pSwitchingTimeMinusToPlus[nSwitchingTimeBins+1];
double pSwitchingTimeMinusToPlusSmall[extraSwitchingTimeBins];
double pPauseTime[nSwitchingTimeBins+1];
double pPauseTimeSmall[extraSwitchingTimeBins+1];


double pSingleRunDistance[nSwitchingDistanceBins+1];
double pSingleRunDistanceSmall[extraSwitchingDistanceBins];
double pSwitchingDistance[nSwitchingDistanceBins+1];
double pSwitchingDistanceSmall[extraSwitchingDistanceBins];

double meanPausingTime;
double meanSwitchingTime;
double meanSwitchingDistance;

#include "TugCargoClass.CPP"

Cargo cargoMotors(initialCondition,Np,Nm);//,epsPlus,epsMinus,piPlus,piMinus,fPlus,fMinus,gPlus,gMinus);
