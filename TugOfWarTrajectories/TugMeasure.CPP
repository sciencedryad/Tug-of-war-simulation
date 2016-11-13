// =============================================
// INITIALIZE FIRST MEASUREMENT
// =============================================
if(timeIni==0)
{
	if(trajectoryN==1){for(i=0; i<=numberOfTimes;i++){pDist[i] = 0.0;}}
	cargoMotors.SetWalkingDistance(0.0);
	timeIni=1;
}
// =============================================
// OUTPUT of SINGLE TRAJECTORY
// =============================================
if((writeTrajectory==1)&&(trajectoryN==1)&&(t<=tStartDynamicMeasure+trajectoryMaxTime))
{
	foutSingleProbaTrajectory<<t<<"   "<<cargoMotors.GetKp()<<"                     "<<cargoMotors.GetKm()
		<<"                 "<<cargoMotors.GetWaitingTime()<<"               "<<cargoMotors.GetTransitionType()<<endl;
	foutSingleTrajectory<<t<<"   "<<cargoMotors.GetWalkingDistance()
		<<"        "<<cargoMotors.GetWaitingTime()
		<<"        "<<cargoMotors.GetDelta()
		<<"        "<<cargoMotors.GetVelocity()<<endl;

}

// =============================================
// OUTPUT of ALL TRAJECTORIES
// =============================================
if((writeAllTrajectories==1)&&( trajectoryN<=trajectoryNMax)&&(t<=tStartDynamicMeasure+trajectoryMaxTime))
{
	FileNames.itsTrajectoryOut[trajectoryN-1]<<t<<"   "<<cargoMotors.GetWalkingDistance()<<endl;
}

// =============================================
// MEASUREMENT of DYNAMIC PROPERTIES
// =============================================
while ((t>=nextMeasureTime)&&(numberOfMeasurements<=(numberOfTimes-1)))
{
	numberOfMeasurements = numberOfMeasurements + 1;
	pKpKm[cargoMotors.GetOldKp()][cargoMotors.GetOldKm()][numberOfMeasurements]
		= pKpKm[cargoMotors.GetOldKp()][cargoMotors.GetOldKm()][numberOfMeasurements] + 1;
	pDist[numberOfMeasurements]=pDist[numberOfMeasurements]+cargoMotors.GetWalkingDistance();
	//cout<<"numberOfMeasurements = "<<numberOfMeasurements<<", time = "<<t<<endl;
	//cout<<"pDist = "<<pDist[numberOfMeasurements]<<endl;
	//for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
	//	{cout<<kp<<"    "<<km<<"       "<<pKpKm[kp][km][numberOfMeasurements]<<endl;}}cout<<endl;
	nextMeasureTime += timeInterval;
	if(writeConf==1){writeConfig(numberOfMeasurements);}
}
