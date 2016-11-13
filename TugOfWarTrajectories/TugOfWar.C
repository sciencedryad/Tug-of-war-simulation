#include "TugDef.CPP"

int main()
{

#include "TugIni.CPP"

cout<<"Start simulation"<<endl;

//for(epsPlus=epsStart;epsPlus<=epsEnd+0.0000001;)
//{
//for(fPlus=fStart;fPlus<=fEnd+0.0000001;)
//{
	//cout<<"eps = "<<epsPlus<<", f = "<<fPlus;//<<endl;
	//epsMinus=epsPlus;
	//fMinus=fPlus;
	//cargoMotors.SetCargoRates(epsPlus,epsMinus,piPlus,piMinus,fPlus,fMinus,gPlus,gMinus);
	for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){pStatKpKmSumTrajec[kp][km] = 0.0;}}
	//cout<<"Start rates:"<<endl; cargoMotors.DisplayRates();
	timeIni=0;
	for(trajectoryN=1;trajectoryN<=numberOfTrajectories;trajectoryN++)
	{
		//cout<<endl;
		//cout<<"Trajectory number = "<<trajectoryN<<endl;
		//cout<<"eps = "<<epsPlus<<", f = "<<fPlus<<", Trajectory "<<trajectoryN;//<<endl;
		//initialize
		t = 0;
		nextMeasureTime =tStartDynamicMeasure + timeInterval;
		numberOfMeasurements = 0;
		tChanged=1;
		if(doChange==1)
		{
			cargoMotors.SetCargoRates(Np,Nm,
				epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus);
			tChanged=0;
		}
		cargoMotors.SetInitialConditions(initialCondition,Np,Nm);
		//if(trajectoryN%4==1){cargoMotors.SetInitialConditions(initialConditionOdd);}//DisplayInichoice(initialConditionOdd);}
		//else if(trajectoryN%4==2){cargoMotors.SetInitialConditions(initialConditionEven);}//DisplayInichoice(initialConditionOdd);}
		//else if(trajectoryN%4==3) {cargoMotors.SetInitialConditions(Plus1Minus0);}//DisplayInichoice(initialConditionEven);}
		//else {cargoMotors.SetInitialConditions(Plus0Minus1);}//DisplayInichoice(initialConditionEven);}
		actualKp=cargoMotors.GetKp();
		actualKm=cargoMotors.GetKm();
		//cout<<", kp = "<<actualKp<<", km = "<<actualKm<<endl;
		pKpKm[actualKp][actualKm][numberOfMeasurements] =
				 pKpKm[actualKp][actualKm][numberOfMeasurements] + 1;
		for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){pStatKpKm[kp][km] = 0.0;}}// end for kp, for km
		//numberOfStatSteps = 0;
		integrateTimeStat = 0;
		distanceStat=0;
		pausingTimeStat=0;
		//cargoMotors.displayState();
		while (t < maxTime)
		{
			//if (cargoMotors.GetState()==UNBOUND){cout<<"UNBOUND"<<endl;cargoMotors.displayState();}
			cargoMotors.makeStep();
			//cargoMotors.displayState();
			t = t + cargoMotors.GetWaitingTime();
			if((tChanged==0)&&(t>tChange))
			{
				#include "TugTimeChange.CPP"
			}
			if(t>tEq)
			{
				//if(equilReIni==1){//reInitialize stationaryStateMeasurement stuff
				//#include "TugReInitialize.CPP"
				//}
				#include "TugMeasureStat.CPP" // measurement of stationary state properties
				//cargoMotors.displayState();
			}
			if(t>tStartDynamicMeasure)
			{
				#include "TugMeasure.CPP"		// measurement of dynamic properties
			}
			//cargoMotors.displayState();
		}//end while t
		timeIni=0;
		#include "TugFinishStatTrajec.CPP"

	}//end for trajectoryN
	//cout<<"trajectoryN = "<<trajectoryN<<endl;

	//#include "TugFinishStat.CPP"

//	fPOld=fPlus;
//	fPlus=fPlus+fIncr;
//
//}
//epsPlus=epsPlus+epsIncr;
//}//end phasediagram loop


cout<<"finish measurements"<<endl<<endl;

//#include "TugFinishDynamic.CPP"

#include "TugFinish.CPP"

return 0;
}// end main
