for(i=0;i<nTauBins+1;i++){pTau[i]=0;}
for(i=0;i<(Np+1)*(Nm+1);i++){pDifferentVelocities[i]=0;}

for(i=0;i<nWalkingTimeBins+1;i++){pWalkingTime[i]=0;}
for(i=0;i<extraWalkingTimeBins;i++){pWalkingTimeSmall[i]=0;}

for(i=0;i<nSwitchingTimeBins+1;i++){pSwitchingTime[i]=0;}
for(i=0;i<extraSwitchingTimeBins;i++){pSwitchingTimeSmall[i]=0;}

for(i=0;i<nWalkingDistanceBins+2;i++){pWalkingDistance[i]=0;}
for(i=0;i<extraWalkingDistanceBins;i++){pWalkingDistanceSmall[i]=0;}

for(i=0;i<nSwitchingDistanceBins+2;i++){pSwitchingDistance[i]=0;}
for(i=0;i<extraSwitchingDistanceBins;i++){pSwitchingDistanceSmall[i]=0;}

for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){pStatKpKm[kp][km] = 0.0;}}// end for kp, for km
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){pStatKpKmSumTrajec[kp][km] = 0.0;}}// end for kp, for km
for(i=0;i<(Np+Nm+1);i++){pStatDel[i]=0; pStatSig[i]=0;}
for(i=0;i<(Nm+1);i++){pStatDelSummed[i]=0;}

meanSwitchingTime=0;
meanSwitchingDistance=0;

//numberOfStatSteps = 0;
integrateTimeStat = 0;
distanceStat = 0;

equilReIni=0;