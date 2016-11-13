// FINAL MEASUREMENTS AND OUTPUT

ASSERT(integrateTimeStat>0);
ASSERT(trajectoryN==(numberOfTrajectories+1));
ASSERTperm(numberOfTimes==numberOfMeasurements);
//cout<<"FINAL MEASUREMENT, numberOfMeasurements = "<<numberOfMeasurements<<endl;


FileNames.openFinalFiles();

ofstream foutProba;
ofstream fout;

//============================================
// STATIONARY STATE PROBABILITIES
//============================================
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
{
		pStatKpKm[kp][km]=pStatKpKmSumTrajec[kp][km]/numberOfTrajectories;
		if(boundStatesOnly==1)
		{
			if((kp>0)||(km>0)){pStatKpKm[kp][km]/=pStatKpKm[0][0];}
		}
}}
	//cout<<"Final Trajectory"<<endl;
	//for(kp=0;kp<=Np;kp++){cout<<"  ";for(km=0;km<=Nm;km++){cout<<pStatKpKm[kp][km]<<"  ";}cout<<endl;}//


//if(epsPlus==epsEnd)
//{

	// calculate pDelta and pSigma
	for(i=0;i<(Np+Nm+1);i++){pStatDel[i]=0; pStatSig[i]=0;}
	for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
	{
		del = kp - km;
		pStatDel[del+Nm] = pStatDel[del+Nm] + pStatKpKm[kp][km];
		sig = kp + km;
		pStatSig[sig] = pStatSig[sig] + pStatKpKm[kp][km];
	}}// end for kp, for km

	/*
	fout.open(MakeFileNames::pStatDelFile);
		fout<<"# del      pStatDel"<<endl;
		for(del=-Nm;del<=Np;del++){fout<<del<<"    "<<pStatDel[del+Nm]<<endl;}
	fout.close();
	fout.open(MakeFileNames::pStatSigFile);
		fout<<"# del      pStatSig"<<endl;
		for(sig=0;del<=(Np+Nm);del++){fout<<sig<<"    "<<pStatSig[del+Nm]<<endl;}
	fout.close();
*/
//}

//for(del=-Nm;del<=0;del++){pStatDelSummed[del+Nm] =  pStatDel[del+Nm] + pStatDel[-del+Nm];}// end for kp, for km

// stationary state: pStatKpKm
foutProba.open(MakeFileNames::pStatKpKmFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	for(kp=0;kp<=Np;kp++)
	{
		for(km=0;km<=Nm;km++)
		{
			foutProba.width(4);foutProba.precision(6);
			foutProba<<kp<<"  "<<km<<"       "<<pStatKpKm[kp][km]<<endl;
		}//end for km
		foutProba<<endl;
	}// end for kp
foutProba.close();

// stationary state: pStatDel, pStatSig
foutProba.open(MakeFileNames::pStatDelFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# delta = kp-km   pStat(delta)"<<endl;
	for(del=-Nm;del<=Np;del++)
	{
		foutProba.width(4);foutProba.precision(6);
		foutProba<<del;
		foutProba<<"   "<<pStatDel[del+Nm]<<endl;
	}// end for del
foutProba.close();
foutProba.open(MakeFileNames::pStatSigFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# sigma = kp+km   pStat(sigma)"<<endl;
	for(sig=0;sig<=Np+Nm;sig++)
	{
		foutProba.width(4);foutProba.precision(6);
		foutProba<<sig;
		foutProba<<"   "<<pStatSig[sig]<<endl;
	}// end for del
foutProba.close();

//============================================
// DYNAMIC PROBABILITIES p(kp,km,t) and x(t) (average)
//============================================
for(i=0; i<=numberOfMeasurements;i++)
{
	normalization = 0;
	for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
	{
		pKpKm[kp][km][i] = pKpKm[kp][km][i]/(1.0*numberOfTrajectories);
		normalization = normalization + pKpKm[kp][km][i];
	}}// end for kp, for km
	ASSERTperm(normalization<1.0000001);ASSERTperm(normalization>0.999999);
	pDist[i]=pDist[i]/numberOfTrajectories;
}//end for i

// probability distribution of bound plus and minus motors: kp,km
foutProba.open(MakeFileNames::pKpKmFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);
	for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
	{
		for(i=0; i<=numberOfMeasurements-1;i++)
		{
			foutProba.width(1);foutProba.precision(1);
			foutProba<<tStartDynamicMeasure+i*timeInterval;
			foutProba.width(4);foutProba.precision(4);
			foutProba<<"  "<<pKpKm[kp][km][i]<<endl;
		}//end for i
		foutProba<<endl;
	}}// end for kp, for km
	foutProba<<endl;
foutProba.close();

foutProba.open(MakeFileNames::pDistFile);
	for(i=0; i<=numberOfMeasurements-1;i++)
	{
		foutProba.width(1);foutProba.precision(1);
		foutProba<<tStartDynamicMeasure+i*timeInterval;
		foutProba.width(4);foutProba.precision(4);
		foutProba<<"  "<<pDist[i]<<endl;
	}//end for i
foutProba.close();

//============================================
// WAITING TIMES tau
//============================================
//cout<<"Distibution of WaitingTimes"<<endl;
//for(i=0;i<=nTauBins;i++){cout<<i<<"  "<<i*deltaTau<<"   "<<pTau[i]<<endl;}
normalization = 0;
for(i=0;i<=nTauBins;i++) {normalization = normalization + pTau[i];}
for(i=0;i<=nTauBins;i++) {pTau[i] = pTau[i]/normalization;}

// output probability distribution of waiting times tau
foutProba.open(MakeFileNames::pWaitingTimeFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# waiting time distribution"<<endl;
	foutProba<<"# time bin (lower boundary)      probability"<<endl;
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);
	for(i=0;i<=nTauBins;i++){foutProba<<i*deltaTau<<"      "<<pTau[i]<<endl;}
foutProba.close();

//============================================
// VELOCITY DISTIBUTION
//============================================
//cout<<"Distibution of Velocities"<<endl;
//for(i=0;i<=nVBins+1;i++) {cout<<i<<"  "<<" v ="<<vMin+(i-1)*deltaV<<"   "<<pVelocity[i]<<endl;}
//cout<<"number of different velocities = "<<cargoMotors.GetNumberOfDifferentVelocities()<<endl;
//for(i=0;i<(Np+1)*(Nm+1);i++) {cout<<i<<"  "<<" v ="<<cargoMotors.GetOccuredVelocity(i)<<endl;}
//cout<<"velocity distribution pv[kp,km]"<<endl;
//for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++) {cout<<kp<<"   "<<km<<"   "<<pVelocity[kp][km]
//	<<" for v ="<<cargoMotors.GetVelocityKpKm(kp,km)<<endl;}}

for(i=0;i<cargoMotors.GetNumberOfDifferentVelocities();i++){pDifferentVelocities[i]=0;}
normalization = 0;
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
{
	normalization = normalization + pVelocity[kp][km];
	for(i=0;i<cargoMotors.GetNumberOfDifferentVelocities();i++)
	{
		if((cargoMotors.GetVelocityKpKm(kp,km)>cargoMotors.GetOccuredVelocity(i)-0.00001)
			&&(cargoMotors.GetVelocityKpKm(kp,km)<cargoMotors.GetOccuredVelocity(i)+0.00001))
		{
			pDifferentVelocities[i] = pDifferentVelocities[i] + pVelocity[kp][km];
		}
	}//end for i
}}// end for kp, for km
for(i=0;i<cargoMotors.GetNumberOfDifferentVelocities();i++) {pDifferentVelocities[i] = pDifferentVelocities[i]/normalization;}


//cout<<"velocity distribution pv[i]"<<endl;
//for(i=0;i<cargoMotors.GetNumberOfDifferentVelocities();i++){cout<<i<<", v = "<<cargoMotors.GetOccuredVelocity(i)<<", p = "<<pDifferentVelocities[i]<<endl;}
//cout<<"total number of measurements = "<<normalization<<endl;

/*for(i=0;i<cargoMotors.GetNumberOfDifferentVelocities();i++){pDifferentVelocities[i]=0;}
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
{
	for(i=0;i<cargoMotors.GetNumberOfDifferentVelocities();i++)
	{
		if((cargoMotors.GetVelocityKpKm(kp,km)>cargoMotors.GetOccuredVelocity(i)-0.00001)
			&&(cargoMotors.GetVelocityKpKm(kp,km)<cargoMotors.GetOccuredVelocity(i)+0.00001))
		{
			pDifferentVelocities[i] = pDifferentVelocities[i] + pStatKpKm[kp][km];
		}
	}//end for i
}}
*/

// output probability distribution of velocities v
foutProba.open(MakeFileNames::pVelocityFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# velocity distribution"<<endl;
	foutProba<<"# velocity value      probability"<<endl;
	foutProba.precision(4);
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);
	for(i=0;i<cargoMotors.GetNumberOfDifferentVelocities();i++)
	{
		foutProba<<cargoMotors.GetOccuredVelocity(i)<<"      ";
		foutProba.precision(6);
		foutProba<<pDifferentVelocities[i]<<endl;
		foutProba.precision(4);
	}
foutProba.close();

/*
// output probability distribution of velocities v
foutProba.open(MakeFileNames::pVelocityFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# velocity distribution"<<endl;
	foutProba<<"# velocity bin (lower boundary)      probability"<<endl;
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);
	for(i=0;i<=nVBins+2;i++) {foutProba<<vMin+(i-1)*deltaV<<"   "<<pVelocity[i]<<endl;}
foutProba.close();
*/

//============================================
// WALKING TIMES
//============================================
//cout<<"Distibution of WalkingTimes"<<endl;
//for(i=0;i<=nWalkingTimeBins;i++) {cout<<i<<"  "<<pWalkingTime[i]<<endl;}
normalization = 0;
for(i=0;i<=nWalkingTimeBins;i++) {normalization = normalization + pWalkingTime[i];}
if (normalization>0)
{for(i=0;i<=nWalkingTimeBins;i++) {pWalkingTime[i] = pWalkingTime[i]/normalization;}}
//cout<<endl;
//for(i=0;i<extraWalkingTimeBins;i++) {cout<<i<<"  "<<pWalkingTimeSmall[i]<<endl;;}
//normalization = 0;
//for(i=0;i<extraWalkingTimeBins;i++) {normalization = normalization + pWalkingTimeSmall[i];}
normalization = normalization *  ( extraWalkingTimeMax/extraWalkingTimeBins) / (walkingTimeMax/nWalkingTimeBins);
if (normalization>0)
{for(i=0;i<extraWalkingTimeBins;i++) {pWalkingTimeSmall[i] = pWalkingTimeSmall[i]/normalization;}}

// output probability distribution of walking times
foutProba.open(MakeFileNames::pWalkingTimeFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# walking time distribution"<<endl;
	foutProba<<"# time bin (lower boundary)      probability"<<endl;
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);
	if(extraWalkingTimeMax>0)
		{for(i=0;i<extraWalkingTimeBins;i++){foutProba<<i*extraDeltaWalkT<<"         "<<pWalkingTimeSmall[i]<<endl;}}
	n = floor(extraWalkingTimeMax/deltaWalkT);
	//cout<<"number of extraWalkingTimeMax = "<<n;
	for(i=n;i<=nWalkingTimeBins;i++) {	foutProba<<i*deltaWalkT<<"         "<<pWalkingTime[i]<<endl;}
	//for(i=0;i<=nWalkingTimeBins;i++) {	foutProba<<i*deltaT<<"         "<<pWalkingTime[i]<<endl;}
foutProba.close();

//============================================
// SWITCHING TIMES & PAUSE-to-PAUSE TIMES
//============================================
//cout<<"Distibution of SwitchingTimes"<<endl;
//for(i=0;i<=nSwitchingTimeBins;i++) {cout<<i<<"  "<<pSwitchingTime[i]<<endl;}
//normalization = 0;
//for(i=0;i<=nSwitchingTimeBins;i++) {normalization = normalization + pSwitchingTime[i];}
//if (normalization>0)
//{for(i=0;i<=nSwitchingTimeBins;i++) {pSwitchingTime[i] = pSwitchingTime[i]/normalization;}}
normP=0;normM=0;
for(i=0;i<=nSwitchingTimeBins;i++)
	{normP += pSingleRunTimePlus[i]; normM += pSingleRunTimeMinus[i];}
if (normP>0){for(i=0;i<=nSwitchingTimeBins;i++) {pSingleRunTimePlus[i] /= normP;}}
if (normM>0){for(i=0;i<=nSwitchingTimeBins;i++) {pSingleRunTimeMinus[i] /= normM;}}

normP=0;normM=0;normalization=0;
for(i=0;i<=nSwitchingTimeBins;i++)
	{normP += pSwitchingTimePlusToMinus[i]; normM += pSwitchingTimeMinusToPlus[i];normalization+=pPauseTime[i];}
if (normP>0){for(i=0;i<=nSwitchingTimeBins;i++) {pSwitchingTimePlusToMinus[i] /= normP;}}
if (normM>0){for(i=0;i<=nSwitchingTimeBins;i++) {pSwitchingTimeMinusToPlus[i] /= normM;}}
if(normalization>0){for(i=0;i<=nSwitchingTimeBins;i++) {pPauseTime[i] /= normalization;}}
//cout<<endl;
//for(i=0;i<extraSwitchingTimeBins;i++) {cout<<i<<"  "<<pSwitchingTimeSmall[i]<<endl;;}
//normalization = 0;
//for(i=0;i<extraSwitchingTimeBins;i++) {normalization = normalization + pSwitchingTimeSmall[i];}
//normalization = normalization *  ( extraSwitchingTimeMax/extraSwitchingTimeBins) / (switchingTimeMax/nSwitchingTimeBins);
//if (normalization>0)
//{cout<<"extraSwitchingTimeBins"<<endl;for(i=0;i<extraSwitchingTimeBins;i++) {pSwitchingTimeSmall[i] = pSwitchingTimeSmall[i]/normalization;}}

normP = normP *  ( extraSwitchingTimeMax/extraSwitchingTimeBins) / (switchingTimeMax/nSwitchingTimeBins);
if (normP>0)
{cout<<"extraSwitchingTimeBins"<<endl;for(i=0;i<extraSwitchingTimeBins;i++) {pSingleRunTimePlusSmall[i] /= normP;}}
if (normP>0)
{cout<<"extraSwitchingTimeBins"<<endl;for(i=0;i<extraSwitchingTimeBins;i++) {pSwitchingTimePlusToMinusSmall[i] /= normP;}}
normM = normM *  ( extraSwitchingTimeMax/extraSwitchingTimeBins) / (switchingTimeMax/nSwitchingTimeBins);
if (normM>0)
{cout<<"extraSwitchingTimeBins"<<endl;for(i=0;i<extraSwitchingTimeBins;i++) {pSingleRunTimeMinusSmall[i] /= normM;}}
if (normM>0)
{cout<<"extraSwitchingTimeBins"<<endl;for(i=0;i<extraSwitchingTimeBins;i++) {pSwitchingTimeMinusToPlusSmall[i] /= normM;}}
normalization = normalization *  ( extraSwitchingTimeMax/extraSwitchingTimeBins) / (switchingTimeMax/nSwitchingTimeBins);
if (normalization>0)
{cout<<"extraSwitchingTimeBins"<<endl;for(i=0;i<extraSwitchingTimeBins;i++) {pPauseTimeSmall[i] /= normalization;}}

// output probability distribution of switching times
foutProba.open(MakeFileNames::pSwitchingTimeFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# switching time distribution"<<endl;
	foutProba<<"# time bin (lower boundary)     long plus run (switch plus->minus)     long minus run (switch minus->plus) "
	<<"    pause   single plus run   single minus run"<<endl;
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);foutProba.precision(6);
	if(extraSwitchingTimeMax>0)
		{for(i=0;i<extraSwitchingTimeBins;i++){foutProba<<i*extraDeltaSwitchT
			<<"    "<<pSwitchingTimePlusToMinusSmall[i]
			<<"    "<<pSwitchingTimeMinusToPlusSmall[i]
			<<"    "<<pPauseTimeSmall[i]
			<<"    "<<pSingleRunTimePlusSmall[i]
			<<"    "<<pSingleRunTimeMinusSmall[i]
			<<endl;}}
	n = floor(extraSwitchingTimeMax/deltaSwitchT);
	//cout<<"extraswitchingTimeMax = "<<extraSwitchingTimeMax<<", n = "<<n<<endl;
	//cout<<"number of extraSwitchingTimeMax = "<<n;
	for(i=n;i<=nSwitchingTimeBins;i++)
	{
		foutProba<<i*deltaSwitchT<<"   "
			<<pSwitchingTimePlusToMinus[i]<<"   "
			<<pSwitchingTimeMinusToPlus[i]<<"   "
			<<pPauseTime[i]<<"  "
			<<pSingleRunTimePlus[i]<<"  "
			<<pSingleRunTimeMinus[i]
			<<endl;
	}
	//for(i=0;i<=nSwitchingTimeBins;i++) {	foutProba<<i*deltaT<<"         "<<pSwitchingTime[i]<<endl;}
foutProba.close();
/*
foutProba.open(MakeFileNames::pSwitchingTimeLogFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# log switching time distribution"<<endl;
	foutProba<<"# t   log(prob)"<<endl;
	for(i=n;i<=nSwitchingTimeBins;i++)
	{
		if(pSwitchingTimePlusToMinus[i]>0){	foutProba<<i*deltaSwitchT<<"    "<<log(pSwitchingTimePlusToMinus[i]);}
		//else{foutProba<<"   -";}
		foutProba<<endl;
	}
foutProba.close();
*/

//============================================
// SWITCHING DISTANCES
//============================================
//cout<<"Distibution of SwitchingDistances"<<endl;
//for(i=0;i<=nSwitchingDistanceBins+1;i++)
//	{cout.width(6);cout<<i<<" dist = ";cout.width(6);cout<<switchingDistanceMin + (i-1)*deltaSwitchX<<"         "<<pSwitchingDistance[i]<<endl;;}
normalization = 0;
for(i=0;i<=nSwitchingDistanceBins+1;i++) {normalization = normalization + pSwitchingDistance[i];}
if (normalization>0)
{for(i=0;i<=nSwitchingDistanceBins+1;i++) {pSwitchingDistance[i] = pSwitchingDistance[i]/normalization;}}
//cout<<endl;
//for(i=0;i<extraSwitchingDistanceBins;i++)
//	 {cout<<i<<" dist = "<<extraSwitchingDistanceMin + i *extraDeltaSwitchX<<"         "<<pSwitchingDistanceSmall[i]<<endl;;}
normalization = normalization *  ( extraSwitchingDistanceMax/extraSwitchingDistanceBins) / (switchingDistanceMax/nSwitchingDistanceBins);
if (normalization>0)
{for(i=0;i<extraSwitchingDistanceBins;i++) {pSwitchingDistanceSmall[i] = pSwitchingDistanceSmall[i]/normalization;}}


normalization = 0;
for(i=0;i<=nSwitchingDistanceBins+1;i++) {normalization = normalization + pSingleRunDistance[i];}
if (normalization>0)
{for(i=0;i<=nSwitchingDistanceBins+1;i++) {pSingleRunDistance[i] /= normalization;}}
normalization = normalization *  ( extraSwitchingDistanceMax/extraSwitchingDistanceBins) / (switchingDistanceMax/nSwitchingDistanceBins);
if (normalization>0)
{for(i=0;i<extraSwitchingDistanceBins;i++) {pSingleRunDistanceSmall[i] /=normalization;}}


// output probability distribution of switching Distances
foutProba.open(MakeFileNames::pSwitchingDistanceFile);
	//cout<<MakeFileNames::pSwitchingDistanceFile<<endl;
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# switching Distance distribution"<<endl;
	foutProba<<"# Distance bin (lower boundary)      probability for:       switch         single run"<<endl;
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);foutProba.precision(6);
	done=0;
	for(i=0; i<=nSwitchingDistanceBins;i++)
	{
			x = switchingDistanceMin + (i)*deltaSwitchX;
			if((x>=extraSwitchingDistanceMin)&&(x<extraSwitchingDistanceMax))
			{
				if(done==0)
				{for(n=0;n<extraSwitchingDistanceBins;n++)
				 {
				 	foutProba<<extraSwitchingDistanceMin + n *extraDeltaSwitchX
					<<"         "<<pSwitchingDistanceSmall[n]
					<<"         "<<pSingleRunDistanceSmall[i]<<endl;
					//cout<<n<<"  "<<extraDeltaSwitchX<<endl;
				}}
				done = 1;
			}
			else
			{foutProba<<x<<"         "<<pSwitchingDistance[i]<<"         "<<pSingleRunDistance[i]<<endl;}
	}//end for i
foutProba.close();
/*
foutProba.open(MakeFileNames::pSwitchingTimeLogFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# log switching distance distribution"<<endl;
	foutProba<<"# x   log(prob)"<<endl;
	for(i=0;i<=nSwitchingDistanceBins;i++)
	{
		x = switchingDistanceMin + (i)*deltaSwitchX;
		if((x>=0)&&(pSwitchingDistance[i])>0){	foutProba<<x<<"    "<<log(pSwitchingDistance[i]);}
		foutProba<<endl;
	}
foutProba.close();
*/
//============================================
// WALKING DISTANCES
//============================================
//cout<<"Distibution of WalkingDistances"<<endl;
//for(i=0;i<=nWalkingDistanceBins+1;i++)
//	{cout.width(6);cout<<i<<" dist = ";cout.width(6);cout<<walkingDistanceMin + (i-1)*deltaWalkX<<"         "<<pWalkingDistance[i]<<endl;;}
normalization = 0;
for(i=0;i<=nWalkingDistanceBins+1;i++) {normalization = normalization + pWalkingDistance[i];}
if (normalization>0)
{for(i=0;i<=nWalkingDistanceBins+1;i++) {pWalkingDistance[i] = pWalkingDistance[i]/normalization;}}
//cout<<endl;
//for(i=0;i<extraWalkingDistanceBins;i++)
//	 {cout<<i<<" dist = "<<extraWalkingDistanceMin + i *extraDeltaWalkX<<"         "<<pWalkingDistanceSmall[i]<<endl;;}
normalization = normalization *  ( extraWalkingDistanceMax/extraWalkingDistanceBins) / (walkingDistanceMax/nWalkingDistanceBins);
if (normalization>0)
{for(i=0;i<extraWalkingDistanceBins;i++) {pWalkingDistanceSmall[i] = pWalkingDistanceSmall[i]/normalization;}}

// output probability distribution of walking Distances
foutProba.open(MakeFileNames::pWalkingDistanceFile);
	if(!foutProba) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutProba<<"# walking Distance distribution"<<endl;
	foutProba<<"# Distance bin (lower boundary)      probability"<<endl;
	foutProba.setf(ios::left); foutProba.setf(ios::showpoint|ios::fixed);
	done=0;
	for(i=0; i<nWalkingDistanceBins+2;i++)
	{
			x = walkingDistanceMin + (i-1)*deltaWalkX;
			if((x>=extraWalkingDistanceMin)&&(x<extraWalkingDistanceMax))
			{
				if(done==0)
				{for(n=0;n<extraWalkingDistanceBins;n++)
				 {
				 	foutProba<<extraWalkingDistanceMin + n *extraDeltaWalkX<<"         "<<pWalkingDistanceSmall[n]<<endl;
					//cout<<n<<"  "<<extraDeltaWalkX<<endl;
				}}
				done = 1;
			}
			else
			{foutProba<<x<<"         "<<pWalkingDistance[i]<<endl;}
	}//end for i
/*
	nmin = floor(abs(walkingDistanceextraWalkingDistanceMin)/deltaWalkX);
	nmax = floor(extraWalkingDistanceMax/deltaWalkX);
	cout<<"nmin = "<<nmin<<", nmax = "<<nmax<<", walkingDistanceMin = "<<walkingDistanceMin<<", deltaWalkX = "<<deltaWalkX<<endl;
	for(i=0;i<=nmin;i++) {
	cout<<i<<"  "<<walkingDistanceMin + (i-1)*deltaWalkX<<endl;
	foutProba<<walkingDistanceMin + (i-1)*deltaWalkX<<"         "<<pWalkingDistance[i]<<endl;}
	for(i=0;i<extraWalkingDistanceBins;i++){foutProba<<extraWalkingDistanceMin + i*extraDeltaWalkX<<"         "<<pWalkingDistanceSmall[i]<<endl;}
	for(i=nmax;i<=nWalkingDistanceBins+2;i++) {	foutProba<<walkingDistanceMin + (i-1)*deltaWalkX<<"         "<<pWalkingDistance[i]<<endl;}
*/
foutProba.close();


//============================================
// MEAN SWITCHING TIMES AND DISTANCES
//============================================
//meanSwitchingTime /= numberOfTrajectories;
//meanSwitchingDistance /= numberOfTrajectories;
//meanPausingTime /= numberOfTrajectories;
//FileNames.itsMeansOut<<"# mean switch time,   mean switch distance  mean pausing time"<<endl;
FileNames.itsMeansOut<<"# mean switch time aus Vtlg., mean switch distance aus Vtlg, mean pause to pause time"<<endl;
FileNames.itsMeansOut<<"# "<<endl;
//FileNames.itsMeansOut<<meanSwitchingTime<<"    "<<meanSwitchingDistance<<"    "<<meanPausingTime<<endl;

meanSwitchingTime =0;
sTime=0+0.5*deltaSwitchT;
for(i=0;i<=nSwitchingTimeBins;i++)
{
	meanSwitchingTime += pSwitchingTimePlusToMinus[i]*sTime;
	//cout<<i<<", "<<sTime<<" , "<<meanSwitchingTime<<endl;
	sTime+=deltaSwitchT;
}
FileNames.itsMeansOut<<meanSwitchingTime<<"   ";

meanSwitchingDistance =0;
sDist=switchingDistanceMin;//+0.5*deltaSwitchX; //this is taken care of in measure of switchDist
for(i=0;i<=nSwitchingDistanceBins;i++)
{
	meanSwitchingDistance += pSwitchingDistance[i]*fabs(sDist);
	//cout<<i<<", "<<sTime<<" , "<<meanSwitchingTime<<endl;
	sDist+=deltaSwitchX;
}
FileNames.itsMeansOut<<meanSwitchingDistance<<"   ";

meanPausingTime =0;
sTime=0+0.5*deltaSwitchT;
for(i=0;i<=nSwitchingTimeBins;i++)
{
	meanPausingTime += pPauseTime[i]*sTime;
	//cout<<i<<", "<<sTime<<" , "<<meanSwitchingTime<<endl;
	sTime+=deltaSwitchT;
}
FileNames.itsMeansOut<<meanPausingTime<<endl;


//=========================================
//gnufile
//=========================================
FileNames. itsGnuPhaseDiagOut<<"reset"<<endl<<endl;

//	<<"#set terminal postscript enhanced color"<<endl
//	<<"#set output \"PhaseDiagN"<<Np<<".eps\""<<endl
//	<<"set terminal x11"<<endl<<endl
//	<<"set title \"N = "<<Np<<"\""<<endl
//	<<"set xlabel \"f\""<<endl<<"set ylabel \"K\""<<endl<<endl;

FileNames. itsGnuPhaseDiagOut<<"pi = "<<piPlus<<endl;
FileNames. itsGnuPhaseDiagOut<<"eps = "<<epsPlus<<endl;
FileNames. itsGnuPhaseDiagOut<<"f = "<<FsPlus/FdMinus<<endl;
FileNames. itsGnuPhaseDiagOut<<endl;

FileNames. itsGnuPhaseDiagOut<<"set logscale y"<<endl;

FileNames. itsGnuPhaseDiagOut<<"plot[][0.0001:]\\"<<endl;
FileNames. itsGnuPhaseDiagOut<<"\"pSwitchingTime.dat\" u ($1):($2/"<<deltaSwitchT<<") w lp"<<endl;

//=========================================
// PARAMETER FILES
//=========================================

FileNames.itsParaOut<<"Parameters for tug of war simulation in folder "<<FileNames.folder<<endl;
FileNames.itsParaOut<<"numberOfTrajectories = "<<numberOfTrajectories<<", equilibration time = "<<tEq
	<<", maxTime = "<<maxTime<<", numberOfTimes = "<<numberOfTimes
	<<", timeInterval = "<< timeInterval <<endl;
FileNames.itsParaOut<<"Np = "<<Np<<", Nm = "<<Nm<<endl;
FileNames.itsParaOut<<"inititalCondition = "<<initialCondition<<endl;
FileNames.itsParaOut<<"random number seed  = "<<seed<<", writeTrajectory = "<<writeTrajectory<<endl;
FileNames.itsParaOut<<"epsP = "<<epsPlus<<", epsM = "<<epsMinus<<", piP = "<<piPlus<<", piM = "<<piMinus
	<<" => KP = "<<epsPlus/piMinus<<",  KM = "<<epsMinus/piMinus<<endl;
FileNames.itsParaOut<<"FsP = "<<FsPlus<<", FsM = "<<FsMinus<<", FdP = "<<FdPlus<<", FdM = "<<FdMinus
	<<" => fP = "<<FsPlus/FdMinus<<", fM = "<<FsMinus/FdPlus<<endl;
FileNames.itsParaOut<<"gPlus = "<<gPlus<<", gMinus = "<<gMinus<<"bPlus = "<<bPlus<<", bMinus = "<<bMinus<<endl;
FileNames.itsParaOut<<"vP = "<<vPlus<<"vM ="<<vMinus<<", velocityModel = ";
	if(velocChoice==loadSK){FileNames.itsParaOut<<"loadSK";}
	else if(velocChoice==blockRL){FileNames.itsParaOut<<"blockRL";}
	else {FileNames.itsParaOut<<"undefined";}
	FileNames.itsParaOut<<", betaPlus = "<<betaPlus<<", betaMinus = "<<betaMinus<<endl;
//FileNames.itsParaOut<<"epsFactor = "<<epsFactor<<", fFactor = "<<fFactor<<endl;
//FileNames.itsParaOut<<"bound states only: ";
//	if(boundStatesOnly==1){FileNames.itsParaOut<<" yes";} else{FileNames.itsParaOut<<" no";}
//	FileNames.itsParaOut<<endl;
FileNames.itsParaOut<<"used time: "<<timeUsed<<" sec"
		<<" = "<<timeUsed/60<<" min"
		<<" = "<<timeUsed/3600<<" h"<<endl;


FileNames.itsParaDatOut<<Np<<endl<<Nm<<endl;
FileNames.itsParaDatOut<<epsPlus<<endl<<epsMinus<<endl<<piPlus<<endl<<piMinus<<endl
	<<FsPlus<<endl<<FsMinus<<endl<<FdPlus<<endl<<FdMinus<<endl<<vPlus<<endl<<vMinus<<endl<<betaPlus<<endl<<betaMinus<<endl
	<<gPlus<<endl<<gMinus<<endl<<bPlus<<endl<<bMinus<<endl;

//******************************************************************
// some final screen output
//******************************************************************
//cout<<"number of stationary state measurements = "<<numberOfStatSteps<<
cout<<" total integration time = "<<integrateTimeStat<<endl;

//******************************************************************
// TIME MEASUREMENT
//******************************************************************

time (&time2); // set time2 to current time (in sec since 1970)
timeUsed = difftime(time2,time1);
cout<<"used time: "<<timeUsed<<" sec"
		<<" = "<<timeUsed/60<<" min"
		<<" = "<<timeUsed/3600<<" h"<<endl;



//******************************************************************
// CLOSE FILES
//******************************************************************
FileNames.closeFinalFiles();
FileNames.closePermanentFiles();
foutSingleProbaTrajectory.close();
foutSingleTrajectory.close();
