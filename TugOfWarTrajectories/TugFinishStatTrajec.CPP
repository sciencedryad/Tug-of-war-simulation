
//normalize pStat
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
{
	pStatKpKm[kp][km] = pStatKpKm[kp][km]/integrateTimeStat;
	//if(pStatKpKm[kp][km]<1e-7){pStatKpKm[kp][km]=0;};
	pStatKpKmSumTrajec[kp][km]=pStatKpKmSumTrajec[kp][km]+pStatKpKm[kp][km];
	//ASSERT(pStatKpKmSumTrajec[kp][km]>=0);
}}// end for kp, for km

//meanSwitchingTime += cargoMotors.GetMeanSwitchingTime()/cargoMotors.GetNumberOfSwitches();
//meanSwitchingTime += (integrateTimeStat-pausingTimeStat/2-cargoMotors.GetSwitchingTime())/(cargoMotors.GetNumberOfSwitches());
//meanSwitchingDistance +=  (distanceStat-cargoMotors.GetSwitchingDistance())/(cargoMotors.GetNumberOfSwitches());
//meanPausingTime += pausingTimeStat/(2*cargoMotors.GetNumberOfSwitches());
//cout<<"time "<<t<<", mean switchTime ="<< meanSwitchingTime<<", mean SwitchDist = "<<meanSwitchingDistance
//	<<", mean pause time = "<<meanPausingTime<<endl;

cout<<endl;
cout<<" number of pauses = "<<cargoMotors.GetNumberOfPauses()
	<<", meanPauseTime = "<<cargoMotors.GetMeanPauseTime()<<endl;
cout<<" number of single plus runs = "<<cargoMotors.GetNumberOfSinglePlusRuns()
	<<", meanSinglePlusRunTime = "<<cargoMotors.GetMeanSinglePlusRunTime()<<endl;
cout<<" number of single minus runs = "<<cargoMotors.GetNumberOfSingleMinusRuns()
	<<", meanSingleMinusRunTime = "<<cargoMotors.GetMeanSingleMinusRunTime()<<endl;
cout<<" number of long plus runs = "<<cargoMotors.GetNumberOfLongPlusRuns()
	<<", meanLongPlusRunTime = "<<cargoMotors.GetMeanLongPlusRunTime()
	<<", meanLongPlusRunTimeWithoutPause = "<<cargoMotors.GetMeanLongPlusRunTimeWithoutPause()<<endl;
cout<<" number of long minus runs = "<<cargoMotors.GetNumberOfLongMinusRuns()
	<<", meanLongMinusRunTime = "<<cargoMotors.GetMeanLongMinusRunTime()
	<<", meanLongMinusRunTimeWithoutPause = "<<cargoMotors.GetMeanLongMinusRunTimeWithoutPause()<<endl;
cout<<" meanSingleRunDistSmallPlus = "<<cargoMotors.GetMeanRunDistancePlus()
	<<", meanSwitchingDistPlus = "<<cargoMotors.GetMeanSwitchingDistancePlus()<<endl;
cout<<" meanSingleRunDistSmallMinus = "<<cargoMotors.GetMeanRunDistanceMinus()
	<<", meanSwitchingDistMinus = "<<cargoMotors.GetMeanSwitchingDistanceMinus()<<endl;
cout<<endl;

// some output
//cout.precision(4);
//cout<<"trajectory number = "<<trajectoryN<<", eps = "<<epsPlus<<", f = "<<fPlus<<endl;
//for(kp=0;kp<=Np;kp++){cout<<"  ";for(km=0;km<=Nm;km++){cout<<pStatKpKm[kp][km]<<"  ";}cout<<endl;}//
//for(kp=0;kp<=Np;kp++){cout<<"  ";for(km=0;km<=Nm;km++){cout<<pStatKpKmSumTrajec[kp][km]<<"  ";}cout<<endl;}//
//for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){cout<<kp<<"  "<<km<<": "<<pStatKpKm[kp][km]<<"  "<<endl;;}cout<<endl;}//



