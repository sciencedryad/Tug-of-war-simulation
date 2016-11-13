class Cargo
{
private:
	int itsNp; // actual total number of plus motors
	int itsNm;// actual total number of minus motors
	int itsKp; // actual number of bound plus motors
	int itsKm; // actual number of bound minus motors
	int itsOldKp; // old number of bound plus motors
	int itsOldKm; // old number of bound minus motors
	double itsTime;	// time since start
	double itsWaitingTime,itsOldWaitingTime; // last waiting time for new transition
	double itsSojournDist;
	TRANSITIONS itsTransitionType; // last chosen transition type
	Rates itsTransitionRates; // transition rates for motor attachment, detachment
	STATES itsState;
	double itsVelocity; // actual velocity

// new variables
	SWITCHSTATES itsCurrentState,itsLastState,itsLastMovingState;
	double itsMeanPauseTime;  // mean pausing times
	double itsMeanSinglePlusRunTime,itsMeanSingleMinusRunTime; // mean time for single plus / minus run (until next pause)
	double itsMeanLongPlusRunTime,itsMeanLongMinusRunTime;  // mean switching times for plus->minus, minus->plus
	double itsMeanLongPlusRunTimeWithoutPause,itsMeanLongMinusRunTimeWithoutPause;
		// mean switching times for plus->minus, minus->plus
	double itsPauseTime,itsSinglePlusRunTime,itsSingleMinusRunTime;
	double itsLongPlusRunTime,itsLongMinusRunTime;
	int itsNumberOfPauses; // number of pauses ( number of visits to P)
	int itsNumberOfSinglePlusRuns,itsNumberOfSingleMinusRuns;
	int itsNumberOfLongPlusRuns,itsNumberOfLongMinusRuns;

	double itsSwitchingDistance,itsRunDistance;
	double itsMeanSwitchingDistancePlus,itsMeanRunDistancePlus;
	double itsMeanSwitchingDistanceMinus,itsMeanRunDistanceMinus;

	double itsWalkingDistance; //walking distance
	//double itsAbsoluteWalkingDistance; // absolute walking distance
	double itsWalkingTime; // walking time
	int itsNumberOfCalls;


public:
	Cargo(const INICHOICE& initialCondition, const int& actNp, const int& actNm)
	{
		int kp,km;
		cout<<"Cargo constructor called"<<endl;
		SetInitialConditions(initialCondition,actNp,actNm);
		//displayState();
		for(kp=0;kp<=itsNp;kp++){for(km=0;km<=itsNm;km++)
		{
			ASSERTperm(itsTransitionRates.GetAttachPlus(kp,km)>=0);
			ASSERTperm(itsTransitionRates.GetDetachMinus(kp,km)>=0);
			ASSERTperm(itsTransitionRates.GetAttachPlus(kp,km)>=0);
			ASSERTperm(itsTransitionRates.GetDetachMinus(kp,km)>=0);
			ASSERTperm(itsTransitionRates.GetTotalRate(kp,km)>=0);
		}}
		//itsTransitionRates.DisplayRates();
	};// end constructor
	~Cargo()
	{
		cout<<"Cargo destructor called"<<endl;
	};// end destructor
public:
	int GetKp()const {return itsKp;}
	int GetKm()const {return itsKm;}
	int GetOldKp()const {return itsOldKp;}
	int GetOldKm()const {return itsOldKm;}
	int GetDelta()const {return (itsKp-itsKm);}
	double GetTime()const {return itsTime;}
	double GetWaitingTime()const {return itsWaitingTime;}
	double GetSojournDist()const {return itsSojournDist;}
	TRANSITIONS GetTransitionType()const {return itsTransitionType;}
	double GetVelocity()const {return itsVelocity;}
	double GetWalkingDistance()const {return itsWalkingDistance;};
	//double GetAbsoluteWalkingDistance()const {return itsAbsoluteWalkingDistance;};
	double GetWalkingTime()const {return itsWalkingTime;}
	int GetNumberOfDifferentVelocities()const{return itsTransitionRates.GetNumberOfDifferentVelocities();}
//	int GetNumberOfSwitches()const{return itsNumberOfSwitches;}
//	double GetSwitchingTime()const{return itsSwitchingTime;}
//	double GetSwitchingDistance()const{return itsSwitchingDistance;}
	double GetOccuredVelocity(const int& i){return itsTransitionRates.GetOccuredVelocity(i);};
	double GetVelocityKpKm(const int& kp, const int& km)const{return itsTransitionRates.GetVelocity(kp,km);};
	STATES GetState()const{return itsState;}
//	DIRECTION GetDirection()const{return itsDirection;}
//	DIRECTION GetOldDirection()const{return itsOldDirection;}

	int GetNumberOfPauses()const{return itsNumberOfPauses;}
	double GetMeanPauseTime()const{return itsMeanPauseTime/itsNumberOfPauses;}
	int GetNumberOfSinglePlusRuns()const{return itsNumberOfSinglePlusRuns;}
	double GetMeanSinglePlusRunTime()const{return itsMeanSinglePlusRunTime/itsNumberOfSinglePlusRuns;}
	int GetNumberOfSingleMinusRuns()const{return itsNumberOfSingleMinusRuns;}
	double GetMeanSingleMinusRunTime()const{return itsMeanSingleMinusRunTime/itsNumberOfSingleMinusRuns;}
	int GetNumberOfLongPlusRuns()const{return itsNumberOfLongPlusRuns;}
	double GetMeanLongPlusRunTime()const{return itsMeanLongPlusRunTime/itsNumberOfLongPlusRuns;}
	int GetNumberOfLongMinusRuns()const{return itsNumberOfLongMinusRuns;}
	double GetMeanLongMinusRunTime()const{return itsMeanLongMinusRunTime/itsNumberOfLongMinusRuns;}
	double GetMeanLongPlusRunTimeWithoutPause()const{return itsMeanLongPlusRunTimeWithoutPause/itsNumberOfLongPlusRuns;}
	double GetMeanLongMinusRunTimeWithoutPause()const{return itsMeanLongMinusRunTimeWithoutPause/itsNumberOfLongMinusRuns;}

	double GetMeanSwitchingDistancePlus()const{return itsMeanSwitchingDistancePlus/itsNumberOfLongPlusRuns;}
	double GetMeanSwitchingDistanceMinus()const{return itsMeanSwitchingDistanceMinus/itsNumberOfLongMinusRuns;}
	double GetMeanRunDistancePlus()const{return itsMeanRunDistancePlus/itsNumberOfSinglePlusRuns;}
	double GetMeanRunDistanceMinus()const{return itsMeanRunDistanceMinus/itsNumberOfSingleMinusRuns;}

	void DisplayRates()const{itsTransitionRates.DisplayRates();};
	void SetKpKm(const int& kp, const int& km){itsKp=kp;itsKm=km;};
	void SetTime(const double& t){itsTime=t;};
	void SetWaitingTime(const double& t){itsWaitingTime=t;};
	void SetSojournDist(const double& x){itsSojournDist=x;};
	void SetTransitionType(const TRANSITIONS& trans){itsTransitionType=trans;};
	void SetVelocity(const double v) {itsVelocity=v;};
	void SetWalkingDistance(const double dist) {itsWalkingDistance=dist;};
	void SetWalkingTime(const double t) {itsWalkingTime=t;};
//	void SetCargoParameters(const int& kp, const int& km, const double& t, const double& waitT,
//		const TRANSITIONS& trans, const double& v, const double& walkDist)
//	{
//		itsKp=kp;
//		itsKm=km;
//		itsOldKp=kp;
//		itsOldKm=km;
//		itsTime=t;
//		itsWaitingTime=waitT;
//		itsTransitionType=trans;
//		itsVelocity = v;
//		itsWalkingDistance = walkDist;
//		//cout<<"SetCargoParameters called"<<endl;
//	}//end SetcargoParameters
	void SetCargoRates(const int& actNp, const int& actNm,
		const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
		const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
		const double& vPlus, const double & vMinus, const double& betaPlus,const double& betaMinus,
		const double& gPlus, const double& gMinus)
	{
		itsTransitionRates.initializeRates(actNp,actNm,
			epsPlus, epsMinus, piPlus,piMinus,FsPlus, FsMinus, FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus, gMinus);
		//itsTransitionRates.DisplayRates();
	}//end SetCargoRates
	void SetInitialConditions(const INICHOICE& iniCond, const int& actNp, const int& actNm)
	{
		itsNp=actNp;
		itsNm=actNm;
		if (iniCond==Plus1Minus0){itsKp=1; itsKm=0;}
		else if (iniCond==Plus0Minus1){itsKp=0; itsKm=1;}
		else if (iniCond==PlusMinus1Random)
			{double rand = randomDouble01();
			if (rand<=0.5){itsKp=1; itsKm=0;} else {itsKp=0; itsKm=1;}}
		else if (iniCond==Plus1Minus1){itsKp=1; itsKm=1;}
		else if (iniCond==PlusNMinus0){itsKp=itsNp; itsKm=0;}
		else if (iniCond==Plus0MinusN){itsKp=0; itsKm=itsNm;}
		else if (iniCond==Plus0MinusN){itsKp=itsNp; itsKm=itsNm;}
		else if (iniCond==Random)
			{int randP,randM;
			randP=randomInteger(itsNp+1); randM = randomInteger(itsNm+1);
			ASSERT(randP>=0);ASSERT(randP<=itsNp);ASSERT(randM>=0);ASSERT(randM<=itsNm);
			itsKp=randP; itsKm=randM;}
		ASSERT(itsKp>=0);ASSERT(itsKp<=itsNp);
		ASSERT(itsKm>=0);ASSERT(itsKm<=itsNm);
		//itsKp=kp;
		//itsKm=km;
		itsOldKp=itsKp;
		itsOldKm=itsKm;
		itsTime=0.0;
		itsWaitingTime=0.0;
		itsSojournDist=0.0;
		itsOldWaitingTime=itsWaitingTime;
		itsTransitionType=NotValid;
		itsVelocity = itsTransitionRates.GetVelocity(itsKp,itsKm);
		//if(itsVelocity>0){itsDirection=Plus;}
		//else if (itsVelocity<0){itsDirection=Minus;}
		//else {ASSERT(itsVelocity==0); itsDirection=Zero;}
		itsCurrentState=determineSwitchState();
		itsLastState=itsCurrentState;
		if(itsCurrentState==P){itsLastMovingState=L;}
		else {itsLastMovingState=itsCurrentState;}
		itsMeanPauseTime=0;
		itsMeanSinglePlusRunTime=0;itsMeanSingleMinusRunTime=0;
		itsMeanLongPlusRunTime=0;itsMeanLongMinusRunTime=0;
		itsMeanLongPlusRunTimeWithoutPause=0;itsMeanLongMinusRunTimeWithoutPause=0;
		itsPauseTime=0;itsSinglePlusRunTime=0;itsSingleMinusRunTime=0;
		itsLongPlusRunTime=0;itsLongMinusRunTime=0;
		itsNumberOfPauses=0;
		itsNumberOfSinglePlusRuns=0;itsNumberOfSingleMinusRuns=0;
		itsNumberOfLongPlusRuns=0;itsNumberOfLongMinusRuns=0;

		itsSwitchingDistance=0;
		itsRunDistance=0;
		itsMeanSwitchingDistancePlus=0;
		itsMeanRunDistancePlus=0;
		itsMeanSwitchingDistanceMinus=0;
		itsMeanRunDistanceMinus=0;

//		itsOldDirection=Zero;
//		itsRunTime=0;
//		itsPauseTime=0;
//		itsStateTime=0;
//		itsSwitchingTime=0;
//		itsSwitchingTimeWithoutPause=0;
//		itsMeanSwitchingTime=0;
//		itsMeanSwitchingTimeWithoutPause=0;
		//itsTimeSinceLastPause=0;
		itsWalkingDistance = 0;
		//itsAbsoluteWalkingDistance = 0;
		itsWalkingTime = 0;
		//itsNumberOfSwitches =0;
		//itsNumberOfPauses =0;
		if ((itsKp==0)&&(itsKm==0)){itsState = UNBOUND;}
		else {itsState = BOUND;}
		itsNumberOfCalls = 0;
		//cout<<"SetInitialParameters called"<<endl;
	}
public:
	int makeStep()
	{
		//cout<<"makeStep called"<<endl;
		calculateWaitingTime();
			// calculates total waiting time until next transition and advances time
		chooseTransitionType();
			// calculates transition type, performs transition
		//if 			(itsTransitionType==AttachPlusMotor)	{attachPlus();}
		//else if 		(itsTransitionType==AttachMinusMotor)	{attachMinus();}
		//else if 		(itsTransitionType==DetachPlusMotor)	{detachPlus();}
		//else {ASSERT	(itsTransitionType==DetachMinusMotor); detachMinus();}
		calculateMovement();
			// calculates distance since last transition, velocity, bound/unbound,
			// perform measurements
		//cout<<"waiting time tau = "<<itsWaitingTime<<", transition Type = "<<itsTransitionType<<endl;
		//displayState();
		return 0;
	};//end make Step
	int displayState()const;
private:
	int attachPlus() 	{ASSERT(itsKp<itsNp);	itsKp = itsKp + 1;	return 0; }
	int attachMinus() 	{ASSERT(itsKm<itsNm); 	itsKm = itsKm + 1; 	return 0; }
	int detachPlus() 	{ASSERT(itsKp>0); 	itsKp = itsKp - 1; 	return 0; }
	int detachMinus() 	{ASSERT(itsKm>0); 	itsKm = itsKm - 1; 	return 0; }
	int calculateWaitingTime()
	// calculate waiting time until next transition
	{
		itsOldWaitingTime=itsWaitingTime;
		double rand=0;
		while(rand==0){rand = randomDouble01();}
		itsWaitingTime = -log(rand)/itsTransitionRates.GetTotalRate(itsKp,itsKm);
		//cout<<"kp = "<<itsKp<<", km = "<<itsKm<<", rand  = "<<rand<<", waitingTime = "<<itsWaitingTime<<endl;
		itsTime = itsTime + itsWaitingTime;
		//cout<<"waitTime, Dist "<<itsWaitingTime<<"   "<<itsSojournDist<<endl;
		return 0;
	};//end calculateWaitingTime
	int chooseTransitionType()
	// chooses type of  transition and performs transition
	{
		double rand;
		double proba;
		itsOldKp = itsKp;
		itsOldKm = itsKm;
		rand = randomDouble01() * itsTransitionRates.GetTotalRate(itsKp,itsKm);
		proba = itsTransitionRates.GetAttachPlus(itsKp,itsKm);
		//cout<<"kp = "<<itsKp<<", km = "<<itsKm<<", rand = "<<rand<<", totalRate = "<<itsTransitionRates.GetTotalRate(itsKp,itsKm)<<endl;
		//cout<<"proba = "<<proba<<endl;
		if(rand<proba){itsTransitionType=AttachPlusMotor;attachPlus();}
		else
		{
			proba = proba + itsTransitionRates.GetAttachMinus(itsKp,itsKm); //cout<<"proba = "<<proba<<endl;
			//cout<<"proba = "<<proba<<endl;
			 if(rand<proba){itsTransitionType=AttachMinusMotor;attachMinus();}
			else
			{
				proba = proba + itsTransitionRates.GetDetachPlus(itsKp,itsKm); //cout<<"proba = "<<proba<<endl;
				//cout<<"proba = "<<proba<<endl;
				 if(rand<proba){ itsTransitionType=DetachPlusMotor;detachPlus();}
				else
				{
					proba = proba + itsTransitionRates.GetDetachMinus(itsKp,itsKm); //cout<<"proba = "<<proba<<endl;
					//cout<<"proba = "<<proba<<endl;
					if(rand<proba){itsTransitionType=DetachMinusMotor;detachMinus();}
					//{
					//cout<<"proba = "<<proba + itsTransitionRates.GetDetachMinus(itsKp,itsKm)<<endl;
					//ASSERT(proba + itsTransitionRates.GetDetachMinus(itsKp,itsKm) <= itsTransitionRates.GetTotalRate(itsKp,itsKm)*1.000001);
					//ASSERT(proba + itsTransitionRates.GetDetachMinus(itsKp,itsKm) >= itsTransitionRates.GetTotalRate(itsKp,itsKm)*0.999999);
					//itsTransitionType=DetachMinusMotor;detachMinus();
					//}
					else
					{
						//cout<<"kp = "<<itsKp<<", km = "<<itsKm<<", rand = "<<rand
						//	<<", totalRate = "<<itsTransitionRates.GetTotalRate(itsKp,itsKm)<<endl;
						//cout<<"proba = "<<proba<<endl;
						itsTransitionType=NoMove;
						cout<<"WARNING: no move possible !!!! See line 217 in CargoClass.CPP."<<endl;
						//ASSERT(1<0);
					}
				}
			}
		}
		//cout<<"chosen Transition type = "<<itsTransitionType<<endl;
		//cout<<"proba = "<<proba<<endl;
		return 0;
	};//end chooseTransition
	int calculateMovement()
	{
		// itsWaitingTime is the time spent in the last kp,km state
		// now kp,km have been changed but nothing else yet
		itsNumberOfCalls = itsNumberOfCalls + 1;
		itsSojournDist = itsWaitingTime*itsVelocity;

		calculateBoundMotion();

		itsVelocity = itsTransitionRates.GetVelocity(itsKp,itsKm);
		calculateMotion();
		//calculateDirection();
		//cout<<itsNumberOfCalls<<"  kp = "<<itsKp<<", km = "<<itsKm
			//<<", v = "<<itsVelocity<<", time = "<<itsTime<<", waitingTime "<<itsWaitingTime<<endl;
		return 0;
	}//end calculateMovement
//===========================================================================
//===========================================================================
private:	// measure subroutines, need global variables
//===========================================================================
	int calculateMotion()
	{
		if(itsTime>=tEq){measureVelocity();}
		// itsCurrentState is still the value before the actual step, i.e. the value of the state corresponding to the waitingTime
		if(itsCurrentState==P)
		{
			itsPauseTime+=itsWaitingTime;
			if(itsLastMovingState==L){itsLongPlusRunTime+=itsWaitingTime;}
			else{itsLongMinusRunTime+=itsWaitingTime;}
		}
		else if(itsCurrentState==L)
		{
			itsSinglePlusRunTime+=itsWaitingTime;
			itsLongPlusRunTime+=itsWaitingTime;
			itsRunDistance+=itsSojournDist;
			itsSwitchingDistance+=itsSojournDist;
		}
		else
		{
			ASSERT(itsCurrentState==R);
			itsSingleMinusRunTime+=itsWaitingTime;
			itsLongMinusRunTime+=itsWaitingTime;
			itsRunDistance+=itsSojournDist;
			itsSwitchingDistance+=itsSojournDist;
		}
		itsCurrentState=determineSwitchState();
		// now itsCurrentState is the value after the actual step
		//cout<<"kp-km = "<<itsKp-itsKm<<", states = "<<itsLastState<<", "<<itsLastMovingState<<", "<<itsCurrentState
		//<<", v = "<<itsVelocity<<endl;


		if(itsCurrentState!=itsLastState) // change state!
		{

			if(itsTime>=tEq)
			{
				if(itsLastState==P)  // last state was pause
				{
					measureSwitchRelatedTime(itsPauseTime,pPauseTime,pPauseTimeSmall);
					itsMeanPauseTime+=itsPauseTime;
					itsNumberOfPauses++;
				}
				else if(itsLastState==L)  // last state was plus end run
				{
					measureSwitchRelatedTime(itsSinglePlusRunTime,pSingleRunTimePlus,pSingleRunTimePlusSmall);
					itsMeanSinglePlusRunTime+=itsSinglePlusRunTime;
					itsNumberOfSinglePlusRuns++;
					measureSwitchRelatedDistance(itsRunDistance,pSingleRunDistance,pSingleRunDistanceSmall);
					itsMeanRunDistancePlus+=itsRunDistance;
				}
				else  // last state was minus end run
				{
					ASSERT(itsLastState==R);
					measureSwitchRelatedTime(itsSingleMinusRunTime,pSingleRunTimeMinus,pSingleRunTimeMinusSmall);
					itsMeanSingleMinusRunTime+=itsSingleMinusRunTime;
					itsNumberOfSingleMinusRuns++;
					measureSwitchRelatedDistance(itsRunDistance,pSingleRunDistance,pSingleRunDistanceSmall);
					itsMeanRunDistanceMinus+=itsRunDistance;
				}
			}

			if(itsCurrentState==P)  // enter in P, i.e. start pause
			{
				itsPauseTime=0;
				//cout<<" start pause"<<endl;
			}
			else if(itsCurrentState==L)// start plus directed motion
			{
				//cout<<" start plus run"<<endl;
				itsSinglePlusRunTime=0;
				itsRunDistance=0;
				if (itsCurrentState!=itsLastMovingState)  // switch from minus to plus
				{
					//cout<<"switch"<<endl;
					ASSERT(itsLastMovingState==R);
					if(itsTime>=tEq)
					{
						measureSwitchRelatedTime(itsLongMinusRunTime,pSwitchingTimeMinusToPlus,pSwitchingTimeMinusToPlusSmall);
						measureSwitchRelatedDistance(itsSwitchingDistance,pSwitchingDistance,pSwitchingDistanceSmall);
						itsNumberOfLongMinusRuns++;
						itsMeanLongMinusRunTime+=itsLongMinusRunTime;
						itsMeanLongMinusRunTimeWithoutPause+=(itsLongMinusRunTime-itsPauseTime);
						itsMeanSwitchingDistanceMinus+=itsSwitchingDistance;
					}
					itsLongMinusRunTime=0;
					itsSwitchingDistance=0;
					itsLastMovingState=itsCurrentState;
				}
			}
			else // start minus directed motion
			{
				//cout<<" start minus run"<<endl;
				ASSERT(itsCurrentState==R);
				itsSingleMinusRunTime=0;
				itsRunDistance=0;
				if (itsCurrentState!=itsLastMovingState)  // switch from plus to minus
				{
					//cout<<"switch"<<endl;
					ASSERT(itsLastMovingState==L);
					if(itsTime>=tEq)
					{
						measureSwitchRelatedTime(itsLongPlusRunTime,pSwitchingTimePlusToMinus,pSwitchingTimePlusToMinusSmall);
						measureSwitchRelatedDistance(itsSwitchingDistance,pSwitchingDistance,pSwitchingDistanceSmall);
						itsNumberOfLongPlusRuns++;
						itsMeanLongPlusRunTime+=itsLongPlusRunTime;
						itsMeanLongPlusRunTimeWithoutPause+=(itsLongPlusRunTime-itsPauseTime);
						itsMeanSwitchingDistancePlus+=itsSwitchingDistance;
					}
					itsLongPlusRunTime=0;
					itsSwitchingDistance=0;
					itsLastMovingState=itsCurrentState;
				}
			}

			itsLastState=itsCurrentState;
		}

		return 0;
	}//end subroutine calculateMotion
//===========================================================================
	int calculateBoundMotion()
	{
		if (itsState==BOUND)
		{
			itsWalkingTime += itsWaitingTime;
			//cout<<"Bound, waiting time = "<<itsWaitingTime<<", walkingTIme = "<<itsWalkingTime;
			itsWalkingDistance = itsWalkingDistance +itsSojournDist;// itsWaitingTime*itsVelocity;
			//itsAbsoluteWalkingDistance = itsAbsoluteWalkingDistance + abs(itsWaitingTime*itsVelocity);
			//cout<<", walkingDist = "<<itsWalkingDistance<<endl;
			if(itsTime>=tEq)
			{
				measureWaitingTime();
				//measureVelocity();
			}
			if ((itsKp==0)&&(itsKm==0))
			{
				//cout<<"   before unbinding: walkingTime = "<<itsWalkingTime<<", itsWalkingDistance = "<<itsWalkingDistance<<endl;
				if(itsTime>=tEq)
				{
					measureWalkingTime(); // measure walking time histogram
					measureWalkingDistance(); // measure walking distance histogram
				}
				if(setUnboundToZero==1)
				{
					itsWalkingDistance = 0;
					itsWalkingTime = 0;
					itsState=UNBOUND;
				}
			}
		}
		else
		{
			ASSERT(itsState==UNBOUND);
			if ((itsKp>0)||(itsKm>0))
			{
				itsState=BOUND;
			}
		}
		return 0;
	}
//===========================================================================
	SWITCHSTATES determineSwitchState()
	{
		SWITCHSTATES s;
		if(itsVelocity>doubleZero){s=L;}
		else if (itsVelocity<-doubleZero){s=R;}
		else {ASSERT(itsVelocity==0); s=P;}
		return s;
	}
//===========================================================================
	int measureWaitingTime()
	{
		int i;
		double tBin;
		tBin = deltaTau;
		for(i=0;i<nTauBins;i++)
		{
			if(itsWaitingTime<tBin)
			{
				pTau[i] = pTau[i] + 1;
				return 0;
			}
			tBin = tBin + deltaTau;
		}
		ASSERT(itsWaitingTime>=tauMax);
		pTau[nTauBins] = pTau[nTauBins] + 1;
		return 0;
	}//end subroutine measureWaitingTime
//===========================================================================
	int measureVelocity()
	{
		//cout<<"measure velocity = "<<itsVelocity<<"  "<<itsKp<<"  "<<itsKm<<endl;
		//pVelocity[itsOldKp][itsOldKm] = pVelocity[itsKp][itsKm] + 1;
		pVelocity[itsOldKp][itsOldKm] = pVelocity[itsOldKp][itsOldKm] + itsWaitingTime;
		return 0;
	}//end subroutine measureVelocity
//===========================================================================
	int measureSwitchRelatedTime(const double& time, double* probDist, double* probDistSmall)
	{
		int i;
		double tBin;
		double switchTime;
		switchTime=time;
		ASSERT(switchTime>=0);
		tBin = deltaSwitchT;
		for(i=0;i<nSwitchingTimeBins;i++)
		{
			if(switchTime<tBin)
			{
				//if(itsDirection==Plus){pSwitchingTimePlus[i] += 1;}
				//else{pSwitchingTimeMinus[i] += 1;}
				probDist[i]+=1;
				if(switchTime<extraSwitchingTimeMax)
				{
					tBin = extraDeltaSwitchT;
					for(i=0;i<extraSwitchingTimeBins;i++)
					{
						if(switchTime<tBin)
						{
							//if(itsDirection==Plus){pSwitchingTimePlusSmall[i] = pSwitchingTimePlusSmall[i] + 1;}
							//else{pSwitchingTimeMinusSmall[i] = pSwitchingTimeMinusSmall[i] + 1;}
							probDistSmall[i]+=1;
							return 0;
						}
						tBin = tBin + extraDeltaSwitchT;
					}
				}
    				return 0;
			}
			tBin = tBin + deltaSwitchT;
		}//end for i
		ASSERT(switchTime>=switchingTimeMax);
		ASSERT(itsTime>tEq);
		//if(itsDirection==Plus){pSwitchingTimePlus[nSwitchingTimeBins] = pSwitchingTimePlus[nSwitchingTimeBins] + 1;}
		//else{pSwitchingTimeMinus[nSwitchingTimeBins] = pSwitchingTimeMinus[nSwitchingTimeBins] + 1;}
		probDist[nSwitchingTimeBins]+=1;
		return 0;
	}//end subroutine measureSwitchingTime

//===========================================================================
	int measureSwitchRelatedDistance(const double& dist, double* probDist, double* probDistSmall)
	{
		int i;
		double xBin;
		double switchDistance;
		switchDistance=dist;
		xBin=switchingDistanceMin+0.5*deltaSwitchX;
		if(switchDistance<xBin)
		{
			probDist[0] += 1;
			return 0;
		}
		xBin +=  deltaSwitchX;
		for(i=1;i<nSwitchingDistanceBins;i++)
		{
			if(switchDistance<xBin)
			{
				probDist[i] = probDist[i] + 1;
				if((switchDistance>extraSwitchingDistanceMin)&&(switchDistance<extraSwitchingDistanceMax))
				{
					xBin = extraSwitchingDistanceMin + extraDeltaSwitchX;
					for(i=0;i<extraSwitchingDistanceBins;i++)
					{
						if(switchDistance<xBin)
						{
							probDistSmall[i] += 1;
							return 0;
						}
						xBin = xBin + extraDeltaSwitchX;
					}
				}
    				return 0;
			}
			xBin = xBin + deltaSwitchX;
		}//end for i
		ASSERT(switchDistance>=switchingDistanceMax-0.5*deltaSwitchX);
		probDist[nSwitchingDistanceBins] +=  1;
		return 0;
	}// end subroutine measureSwitchingDistance
//===========================================================================
/*
	int measureSwitchingDistance()
	{
		int i;
		double xBin;
		double switchDistance;
		switchDistance=itsSwitchingDistance;//-itsSojournDist;//itsWaitingTime*itsVelocity; doesn;t matter because last sojourn was pause, i.e. no motion
		//cout<<"measureSwitchingDistance: "<<itsSwitchingDistance<<endl;
		xBin=switchingDistanceMin+0.5*deltaSwitchX;
		if(switchDistance<xBin)
		{
			pSwitchingDistance[0] = pSwitchingDistance[0] + 1;
			return 0;
		}
		xBin +=  deltaSwitchX;
		for(i=1;i<nSwitchingDistanceBins;i++)
		{
			if(switchDistance<xBin)
			{
				pSwitchingDistance[i] = pSwitchingDistance[i] + 1;
				if((switchDistance>extraSwitchingDistanceMin)&&(switchDistance<extraSwitchingDistanceMax))
				{
					xBin = extraSwitchingDistanceMin + extraDeltaSwitchX;
					for(i=0;i<extraSwitchingDistanceBins;i++)
					{
						if(switchDistance<xBin)
						{
							pSwitchingDistanceSmall[i] = pSwitchingDistanceSmall[i] + 1;
							return 0;
						}
						xBin = xBin + extraDeltaSwitchX;
					}
				}
    				return 0;
			}
			xBin = xBin + deltaSwitchX;
		}//end for i
		ASSERT(switchDistance>=switchingDistanceMax-0.5*deltaSwitchX);
		pSwitchingDistance[nSwitchingDistanceBins] = pSwitchingDistance[nSwitchingDistanceBins] + 1;
		return 0;
	}// end subroutine measureSwitchingDistance
*/
//===========================================================================
	int measureWalkingTime()
	{
		int i;
		double tBin;
		ASSERT(itsKp==0);ASSERT(itsKm==0);
		tBin = deltaWalkT;
		for(i=0;i<nWalkingTimeBins;i++)
		{
			if(itsWalkingTime<tBin)
			{
				pWalkingTime[i] = pWalkingTime[i] + 1;
				if(itsWalkingTime<extraWalkingTimeMax)
				{
					tBin = extraDeltaWalkT;
					for(i=0;i<extraWalkingTimeBins;i++)
					{
						if(itsWalkingTime<tBin)
						{
							pWalkingTimeSmall[i] = pWalkingTimeSmall[i] + 1;
							return 0;
						}
						tBin = tBin + extraDeltaWalkT;
					}
				}
    				return 0;
			}
			tBin = tBin + deltaWalkT;
		}//end for i
		ASSERT(itsWalkingTime>=walkingTimeMax);
		pWalkingTime[nWalkingTimeBins] = pWalkingTime[nWalkingTimeBins] + 1;
		return 0;
	}// end subroutine measureWalk
//===========================================================================
	int measureWalkingDistance()
	{
		int i;
		double xBin;
		ASSERT(itsKp==0);ASSERT(itsKm==0);
		//cout<<"measureWalkingDistance: "<<itsWalkingDistance<<endl;
		xBin=walkingDistanceMin+0.5*deltaWalkX;
		if(itsWalkingDistance<xBin)
		{
			pWalkingDistance[0] = pWalkingDistance[0] + 1;
			return 0;
		}
		xBin += deltaWalkX;
		for(i=1;i<nWalkingDistanceBins;i++)
		{
			if(itsWalkingDistance<xBin)
			{
				pWalkingDistance[i] = pWalkingDistance[i] + 1;
				if((itsWalkingDistance>extraWalkingDistanceMin)&&(itsWalkingDistance<extraWalkingDistanceMax))
				{
					xBin = extraWalkingDistanceMin + extraDeltaWalkX;
					for(i=0;i<extraWalkingDistanceBins;i++)
					{
						if(itsWalkingDistance<xBin)
						{
							pWalkingDistanceSmall[i] = pWalkingDistanceSmall[i] + 1;
							return 0;
						}
						xBin = xBin + extraDeltaWalkX;
					}
				}
    				return 0;
			}
			xBin = xBin + deltaWalkX;
		}//end for i
		ASSERT(itsWalkingDistance>=walkingDistanceMax-0.5*deltaWalkX);
		pWalkingDistance[nWalkingDistanceBins] = pWalkingDistance[nWalkingDistanceBins] + 1;
		return 0;
	}// end subroutine measureWalk
//===========================================================================
};//end cargo class


//===========================================================================
/*
	int calculateDirectionOld()
	{
		int i;
		double tBin;
		int switching,pausing;
		itsSwitchingTime+=itsWaitingTime;
		itsTimeSinceLastPause+=itsWaitingTime;
		itsSwitchingDistance+=itsSojournDist;//itsWaitingTime*itsVelocity;
		switching=0;
		pausing=0;
		//cout.precision(2);
		//cout<<"t = "<<itsTime<<", waitingTime = "<<itsWaitingTime<<", v = "<<itsVelocity<<", oldDir = "<<itsOldDirection<<", direction = "<<itsDirection<<endl;
		//cout<<"time since last pause = "<<itsTimeSinceLastPause<<", switchTime = "<<itsSwitchingTime<<endl;
		// now itsDirection is direction of last state, itsOldDirection is direction of state before last state
		if	(itsVelocity>0)
		{
			if(itsDirection==Zero){itsTimeSinceLastPause=0;}
			if(itsOldDirection==Minus){switching=1;}//cout<<"switching!"<<endl;}
			//else{if(itsTime>itsWaitingTime){ASSERT(itsDirection==Plus);}}
			itsOldDirection=itsDirection; itsDirection=Plus;
		}
		else if(itsVelocity<0)
		{
			if(itsDirection==Zero){itsTimeSinceLastPause=0;}
			if(itsOldDirection==Plus){switching=1;}//cout<<"switching!"<<endl;}
			//else{ASSERT(itsDirection==Minus)}
			itsOldDirection=itsDirection; itsDirection=Minus;
		}
		else
		{
			ASSERT(itsVelocity==0);
			itsOldDirection=itsDirection; itsDirection=Zero;
			pausing=1; //cout<<"pausing!"<<endl;
		}
		//else if	((itsVelocity>(-1e-10))&&(itsVelocity<(1e-10))){ pausing=1; cout<<"pausing!"<<endl;}
		//else		{ASSERT(itsVelocity==0); if(itsDirection!=Zero){switching=1;}   itsDirection=Zero;}
		//cout<<"t = "<<itsTime<<", v = "<<itsVelocity<<", oldDir = "<<itsOldDirection<<", direction = "<<itsDirection<<", switching = "<<switching<<", pausing = "<<pausing<<endl<<endl;
		if(switching==1)
		{
			if(itsTime>=tEq)
			{
				measureSwitchingTime();
				measureSwitchingDistance();
				itsNumberOfSwitches = itsNumberOfSwitches + 1;
			}
			//itsSwitchingTime=itsTime;
			itsSwitchingTime=0;
			itsSwitchingDistance=0;//itsWalkingDistance;
		}
		if(pausing==1)
		{
			if(itsTime>=tEq){measurePauseToPauseTime();}
			//itsTimeSinceLastPause=0;
		}
		return 0;
	}//end subroutine calculateDirection
*/

//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
int Cargo::displayState()const
{
	//char transChar[80];
	//cout.setf(ios::left); cout.setf(ios::showpoint|ios::fixed);cout.width(6);
	cout.precision(4);
	cout<<itsNumberOfCalls<<"  t = "<<itsTime<<", kp = "<<itsKp<<", km = "<<itsKm
		<<", vel = "<<itsVelocity
		<<", waitTime = "<<itsWaitingTime<<", sojournDist = "<<itsSojournDist
		//<<", oldkp = "<<itsOldKp<<", oldkm = "<<itsOldKm
		//<<", state = "<<itsState<<", v = "<<itsVelocity<<", dir = "<<itsDirection
		//<<", timeSinceLastPause = "<<itsTimeSinceLastPause
		//<<", timeSinceLastSwitch = "<<itsSwitchingTime<<endl;
		//<<", walkTime = "<<itsWalkingTime<<", walkDist = "<<itsWalkingDistance
		//<<"  (had: tau = "<<itsWaitingTime<<", trans = "<<itsTransitionType<<")"
		<<endl;
	return 0;
}//end displayState
