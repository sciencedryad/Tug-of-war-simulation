class MasterMatrix
{
private:
	double itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
		itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus;
	long double itsMatrixElement[numberOfStates][numberOfStates];
	long double itsTransitionElement[numberOfStates][numberOfStates]; // indices are correct, not swapped
	// itsMatrixElement[i][j] = omega_{j->i}     for i!=j      (Attention: indices swapped!)
	// itsMatrixElement[i][i] = -sum_j omega_{j->i}
	// itsMatrixElement gets diagonalized
	// itsTransitionElement[i][j] = omega_{i->j} (indices are not swapped, and matrix always stays same)
	long double itsBalanceMatrixDiag[numberOfStates];
	double itsVelocity[numberOfStates];
	int itsNumberOfDiscardedStates;			// number of discarded states
	points itsSwappedPoints[numberOfStates]; // points that are swapped because of discarded states
	//int itsDiscardedElementIndex[numberOfStates]; // index of state to be discarded because of too high out rate
	//int itsDiscardedElementDestination[numberOfStates]; // end point of the large out rate
	SWITCHSTATES itsSwitchState[numberOfStates]; // partitions state space into states L,R,P for switching
	int itsLdim,itsRdim,itsPdim;
public:
	//MasterMatrix()
	//{
	//	cout<<"MasterMatrix constructor called"<<endl;
		//initializeRates();
	//}//end constructor
	MasterMatrix(const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
		const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
		const double& vPlus,const double& vMinus,const double& betaPlus, const double& betaMinus,
		const double& gPlus, const double& gMinus)
	{
		setRates(epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,
		vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus);
	}//end constructor
 //~MasterMatrix()
//	{
//		//cout<<"MasterMatrix destructor"<<endl;
//	}//end destructor
public:
double GetMatrixElement(const int& i, const int& j)const{return itsMatrixElement[i][j];}
double GetTransitionElement(const int& i, const int& j)const{return itsTransitionElement[i][j];}
int GetRow(const int& i, double* row)const
{
	int j;
	for(j=0;j<numberOfStates;j++)
	{
		row[j]=itsMatrixElement[i][j];
	}
	return 0;
}
int GetColumn(const int& j, double* col)const
{
	int i;
	for(i=0;i<numberOfStates;i++)
	{
		col[i]=itsMatrixElement[i][j];
	}
	return 0;
}
int GetNumberOfDiscardedStates()const{return itsNumberOfDiscardedStates;}
int GetActualDimension()const{return numberOfStates - itsNumberOfDiscardedStates;}
int setRates(const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
		const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
		const double& vPlus,const double& vMinus,const double& betaPlus, const double& betaMinus,
		const double& gPlus, const double& gMinus)
	{
		int i,j;
		itsEpsPlus=epsPlus;
		itsEpsMinus=epsMinus;
		itsPiPlus=piPlus;
		itsPiMinus=piMinus;
		itsFsPlus=FsPlus;
		itsFsMinus=FsMinus;
		itsFdPlus=FdPlus;
		itsFdMinus=FdMinus;
		itsvPlus=vPlus;
		itsvMinus=vMinus;
		itsBetaPlus=betaPlus;
		itsBetaMinus=betaMinus;
		itsgPlus=gPlus;
		itsgMinus=gMinus;
		if(useSymmetry==0){initializeMatrixElements();}
		else {ASSERT(useSymmetry==1); initializeSymmetricMatrixElements();}
		for(i=0;i<numberOfStates;i++){for(j=0;j<numberOfStates;j++)
		{
			itsTransitionElement[i][j] = itsMatrixElement[j][i];
		}}
		return 0;
	}
//======================================
int calculateStationaryState(double* pStat)
{
	int i,ind;
	int actualDimension;
	double dummy;
	//cout<<"Calculate stationary state start:: "<<endl;;DisplayMatrix();
	// discard large out rates
		//cout<<"Discard rates"<<endl;
		if(useDiscardRates==1){discardStatesWithLargeOutRate();}//cout<<"After DiscardRates: "<<endl;DisplayMatrix();}
			// adjust rates in order to discard states with large out rate
			// shuffle all discarded states to right and low corner of matrix and remember shuffling
		//cout<<"shuffled: ";//for(i=0;i<itsNumberOfDiscardedStates;i++){cout<<itsSwappedPoints[i].point1<<" <-> "<<itsSwappedPoints[i].point2<<"  ";}cout<<endl;
		actualDimension = numberOfStates - itsNumberOfDiscardedStates;
		//CheckNorm();
	// balance matrix
		//cout<<"Balance"<<endl;
		if(useBalancing==1){balance();}//cout<<"After balance"<<endl;DisplayMatrix();}
	// row reduction
		//cout<<"RowReduce"<<endl;
		rowReduce(actualDimension); // row reducing
		//cout<<"After row reduce"<<endl;DisplayMatrix();
	// stationary state vector
		//cout<<"Find stationary state vector"<<endl;
		for(i=0;i<actualDimension-1;i++){pStat[i]=itsMatrixElement[i][actualDimension-1];}
		pStat[actualDimension-1]=-1;
		///cout<<"pStat = "; for(i=0;i<numberOfStates;i++){cout<<pStat[i]<<"  ";}cout<<endl;
		//cout<<"Debalance"<<endl;
		if(useBalancing==1){debalance(pStat);} // debalancing
		for(i=actualDimension;i<numberOfStates;i++){pStat[i]=0;}
		//cout<<"pStat = "; for(i=0;i<numberOfStates;i++){cout<<pStat[i]<<"  ";}cout<<endl;
		//cout<<"Swapping back"<<endl;
		if(useDiscardRates==1)
		{
			//cout<<"number of discarded States = "<<itsNumberOfDiscardedStates<<endl;
			for(ind=itsNumberOfDiscardedStates-1;ind>=0;ind--)
			{
				if(itsSwappedPoints[ind].point1>itsSwappedPoints[ind].point2)
					{ASSERT(pStat[itsSwappedPoints[ind].point1]<=0.00001);}
				//cout<<ind<<": reshuffle states "<<itsSwappedPoints[ind].point1<<" <-> "<<itsSwappedPoints[ind].point2<<endl;
				dummy = pStat[itsSwappedPoints[ind].point1];//cout<<"dummy = "<<dummy<<endl;
				pStat[itsSwappedPoints[ind].point1] = pStat[itsSwappedPoints[ind].point2];
				pStat[itsSwappedPoints[ind].point2] = dummy;
				//cout<<"pStat = "; for(i=0;i<numberOfStates;i++){cout<<i<<"  "<<pStat[i]<<endl;}cout<<endl;
			}
		}
	// bound or not ?
		if(boundStatesOnly==1){pStat[0]=0;}
	// normalize
		normalizeVec(numberOfStates,pStat);
	return 0;
}//end subroutine calculateStationaryState
//======================================
double calculateEntropyProduction(const int& dim,double* pStat)
{
	int i,j;
	double sigma,jijLeft,jijRight,omij,omji;
	double sigma2=0.0;
	sigma=0.0;
	for(i=0;i<dim;i++)for(j=0;j<i;j++)
	{
		omij=itsTransitionElement[i][j];
		omji=itsTransitionElement[j][i];
		jijLeft=pStat[i]*omij;  // attention: swapped indices!!
		jijRight=pStat[j]*omji;
		if((omij>0)&&(omji>0))
		{
			sigma+= (jijLeft - jijRight)*log(omij/omji);
			sigma2+=(jijLeft - jijRight)*log(jijLeft/jijRight);
		}
		else
		{
			ASSERT((jijLeft==0)&&(jijRight==0));
//			if(omij<=0.000001){ASSERT((jijLeft==0)&&(jijRight==0));}
//			if(omji<=0.000001){ASSERT((jijLeft==0)&&(jijRight==0));}
		}
		//cout<<"i,j = "<<i<<", "<<j
		//	<<"; pstat[i] = "<<pStat[i]<<", om[i,j] = "<<omij<<": p[i]*om[i,j] = "<<jijLeft
		//	<<"; pstat[j] = "<<pStat[j]<<", om[j,i] = "<<omji<<", p[j]*om[j,i] = "<<jijRight
		//	<<",      sigma = "<<sigma<<endl;
	}
	//cout<<"sigma = "<<sigma<<endl;
	//cout<<"sigma2 = "<<sigma2<<endl;
	return sigma;
}//end subroutine calculateEntropyProduction
//======================================
void setSwitchStates(const int& switchStatesChoice)
{
	int i,kp,km;
	itsLdim=0;itsRdim=0;itsPdim=0;
	//cout<<"switchStateChoice = "<<switchStatesChoice<<endl;
	for(i=0;i<numberOfStates;i++)
	{
		kp=nPlus(i);km=nMinus(i);
		 if(switchStatesChoice==0)	// determine according to velocity
		 {
			if(itsVelocity[i]<-doubleZero){itsSwitchState[i]=R;itsRdim++;}
			else if (itsVelocity[i]>doubleZero){itsSwitchState[i]=L;itsLdim++;}
			else {ASSERT(itsVelocity[i]==0); itsSwitchState[i]=P;itsPdim++; }
		}
		else if (switchStatesChoice==1) // select diagonal as P
			if(kp==km){itsSwitchState[i]=P;itsPdim++;}
			else if (kp>km){itsSwitchState[i]=L;itsLdim++;}
			else {itsSwitchState[i]=R;itsRdim++;}
		else if(switchStatesChoice==2) // select boundaries as L and R
		{
			if((kp==0)&&(km>0)){itsSwitchState[i]=R;itsRdim++;}
			else if ((km==0)&&(kp>0)){itsSwitchState[i]=L;itsLdim++;}
			else {itsSwitchState[i]=P;itsPdim++;}
		}
		else	{cout<<"Error: switch state choice incorrect"<<endl;exit(8);}
		//cout<<"i = "<<i<<", kp,km = "<<kp<<", "<<km<<", velocity = "<<itsVelocity[i]<<", state = "<<itsSwitchState[i]<<endl;
	}
}// end subroutine setSwitchStates
//======================================
void calculateSwitchTimesViaSojournTimes(double* pStat,
double& tauP, double& tauL, double& tauR,
double& tauSwitchLR,double& tauSwitchRL,
double& xL, double& xR, double& xSwitchLR, double& xSwitchRL)
// calculates mean sojourn times in P,L,R and mean switching times L <-> R, all via sojourn times
// works only if P is disconnected
// tauP = single pause time, tauL = single plus run time, tauR = single minus run time
// tauSwitchLR = switching time from plus to minus, including end pause (but not start pause)
// tauSwitchRL = switching time from minus to plus, including end pause (but not start pause)
// xL = mean plus run distance, xR = mean minus run distance
// xSwitchLR = switching distance from plus to minus, is only correct if there is either no pausing state of if there is a line of pausing states (like diag)
// xSwitchRL = switching distance from minus to plus, same
{
	//double tauP,tauR,tauL;
	//double tauSwitchLR,tauSwitchRL;
	//double xR,xL,xSwitchLR,xSwitchRL;


	double pR,pL,pP;
	double jL,jR,jP;
	double jLR,jRL;
	double jLPi[itsPdim],jRPi[itsPdim],jPiL[itsPdim],jPiR[itsPdim],pPi[itsPdim];
	int i,j,PInd;
	double Jij,Jji;
	double tauLandP,jLandP,tauRandP,jRandP;

	double jLP,jPL,jRP,jPR;

	cout.precision(4);
	// determine probabilities of P,L,R
	pR=0;pL=0;pP=0;
	for(i=0;i<numberOfStates;i++)
	{
		if(itsSwitchState[i]==P){pP+=pStat[i];}
		else	if(itsSwitchState[i]==L){pL+=pStat[i];}
		else	{ASSERT(itsSwitchState[i]==R);pR+=pStat[i];}
	}
	//cout<<"pP,pL,pR = "<<pP<<", "<<pL<<", "<<pR<<endl;

	// determine sojourn times for P,R,L
	jP=0;jR=0;jL=0;jLR=0;jRL=0;
	 jLP=0;jPL=0;jRP=0;jRP=0;
	for(i=0;i<numberOfStates;i++){for(j=0;j<numberOfStates;j++)
	{
		Jij = pStat[i]*itsTransitionElement[i][j];
		if((itsSwitchState[i]==L)&&(itsSwitchState[j]!=L)){jL+=Jij;}
		if((itsSwitchState[i]==R)&&(itsSwitchState[j]!=R)){jR+=Jij;}
		if((itsSwitchState[i]==P)&&(itsSwitchState[j]!=P)){jP+=Jij;}
		if((itsSwitchState[i]==L)&&(itsSwitchState[j]==R)){jLR+=Jij;}
		if((itsSwitchState[i]==R)&&(itsSwitchState[j]==L)){jRL+=Jij;}

		if((itsSwitchState[i]==R)&&(itsSwitchState[j]==P)){jRP+=Jij;}
		if((itsSwitchState[i]==L)&&(itsSwitchState[j]==P)){jLP+=Jij;}
		if((itsSwitchState[i]==P)&&(itsSwitchState[j]==R)){jPR+=Jij;}
		if((itsSwitchState[i]==P)&&(itsSwitchState[j]==L)){jPL+=Jij;}
	}}
	tauL=pL/jL;
	tauR=pR/jR;
	tauP=pP/jP;
	//cout<<"single L run time = tauL = "<<tauL<<endl;
	//cout<<"single R run time = tauR = "<<tauR<<endl;
	//cout<<"pause time = tauP = "<<tauP<<endl;


	// calculate switching times
	for(i=0;i<itsPdim;i++){jPiL[i]=0;jPiR[i]=0;jLPi[i]=0;jRPi[i]=0;}
	PInd=0;
	for(i=0;i<numberOfStates;i++)
	{
		if(itsSwitchState[i]==P)
		{
			pPi[PInd]=pStat[i];
			for(j=0;j<numberOfStates;j++)
			{
				Jij = pStat[i]*itsTransitionElement[i][j];
				Jji = pStat[j]*itsTransitionElement[j][i];
				if(itsSwitchState[j]==L){jPiL[PInd]+=Jij;jLPi[PInd]+=Jji;}
				if(itsSwitchState[j]==R){jPiR[PInd]+=Jij;jRPi[PInd]+=Jji;}
			}
			PInd++;
		}
	}//end for i
	ASSERT(PInd==itsPdim);
	tauLandP=pL;jLandP=jLR;
	tauRandP=pR;jRandP=jRL;
	for(i=0;i<itsPdim;i++)
	{
		tauLandP+=pPi[i]*jLPi[i]/(jLPi[i]+jRPi[i]);
		tauRandP+=pPi[i]*jRPi[i]/(jLPi[i]+jRPi[i]);
		jLandP+=jLPi[i]*jPiR[i]/(jPiR[i]+jPiL[i]);
		jRandP+=jRPi[i]*jPiL[i]/(jPiR[i]+jPiL[i]);
	}
	tauSwitchLR = tauLandP/jLandP;
	tauSwitchRL = tauRandP/jRandP;
	//cout<<"tauSwitchLR = "<<tauSwitchLR<<endl;
	//cout<<"tauSwitchRL = "<<tauSwitchRL<<endl;

	// calculate run distances
	xL=0;xR=0;xSwitchLR=0;xSwitchRL=0;
	for(i=0;i<numberOfStates;i++)
	{
		if(itsSwitchState[i]==L){xL+=tauL*itsVelocity[i]*pStat[i];xSwitchLR+=tauSwitchLR*itsVelocity[i]*pStat[i];}
		if(itsSwitchState[i]==R){xR+=tauR*itsVelocity[i]*pStat[i];xSwitchRL+=tauSwitchRL*itsVelocity[i]*pStat[i];}
	}
	xL=xL/pL;
	xR=xR/pR;
	//xSwitchLR=xSwitchLR/(pL+pP);
	//xSwitchRL=xSwitchRL/(pR+pP);
	xSwitchLR = jLR/jL*xL;
	xSwitchRL = jRL/jR*xR;
	for(i=0;i<itsPdim;i++)
	{
		//cout<<"xSwitchLR = "<<xSwitchLR<<endl;
		xSwitchLR+=jLPi[i]/jL*(jPiL[i]+jPiR[i])/jPiR[i] * xL;
		xSwitchRL+=jRPi[i]/jR*(jPiL[i]+jPiR[i])/jPiL[i] * xR;
	}
	//cout<<"xSwitchLR = "<<xSwitchLR<<endl;
	//cout<<"xSwitchRL = "<<xSwitchRL<<endl;
	//cout<<"fLR = "<<jLR/jL<<", fLP = "<<jLP/jL<<", fPL = "<<jPL/jP<<endl;
	//xSwitchLR  = jLR/jL*xL + jLP/jL*jP/jPR*xL;
	//xSwitchRL  = jRL/jR*xR + jRP/jR*jP/jPL*xR;
	//cout<<"xSwitchLR = "<<xSwitchLR<<endl;
	//cout<<"xSwitchRL = "<<xSwitchRL<<endl;

	//cout<<"single L run time =  "<<tauL<<", distance = "<<xL<<endl;
	//cout<<"single R run time =  "<<tauR<<", distance = "<<xR<<endl;
	//cout<<"long L run time = switch time L->R = tauL = "<<tauSwitchLR<<", distance = "<<xSwitchLR<<endl;
	//cout<<"long R run time = switch time R->L = tauR = "<<tauSwitchRL<<", distance = "<<xSwitchRL<<endl;

}// end subroutine calculateSojournTimes
//======================================
double calculateSwitchTimesViaInversion(double* pStat,
double& switchTime)
// calculates the switch times via state collapse and matrix inversion
// attention: only use after setSwitchStates(), because otherwise the subsets L and R will be undefined!!!
{
	//double switchTime;
	double timeInP;
	int dimStar;
	double **omegaStar;
	double *pStar;
	int *indexStar;
	double pL,pR,pP;
	int i,j,m,n;
	double** zMat;

// collapse the subset L onto a single state
// the new Markov process gets the ending 'star', and the new collapsed state is put at its end
// the new process has dimStar=numberOfStates-Ldim states
// new stationary state: pStar[i] = p[i] for i \notin L, pStar[dimStar]=\sum_{j\in L} p[j]
// new transition matrix: omegaStar[i][j] calculated. The rates involving the new state are omegaStar[dimStar][j] and omegaStar[i][dimStar]
// in order to use the new state with matrix inversion, all indices are started at 1 and not at 0
	//cout.precision(7);
	dimStar=numberOfStates-itsLdim+1;
	omegaStar=matrix(1,dimStar,1,dimStar);
	indexStar=ivector(1,dimStar);
	pStar=vector(1,dimStar);
	//for(i=0;i<numberOfStates;i++){cout<<i<<"    ";}cout<<endl;
	//for(i=0;i<numberOfStates;i++){cout<<nPlus(i)<<","<<nMinus(i)<<"   ";}cout<<endl;
	//for(i=0;i<numberOfStates;i++){cout<<pStat[i]<<" ";}cout<<endl;
	pL=0;pR=0;pP=0;
	m=1;
	for(i=0;i<numberOfStates;i++)
	{
		if(itsSwitchState[i]==L){pL+=pStat[i];indexStar[dimStar]=i;}
		else
		{
			if(itsSwitchState[i]==R){pR+=pStat[i];}
			else{ASSERT(itsSwitchState[i]==P); pP+=pStat[i];}
			pStar[m]=pStat[i];
			indexStar[m]=i;
			m++;
		}
	}
	ASSERT(m==dimStar);
	pStar[m]=pL;
	//for(m=1;m<=dimStar;m++){cout<<pStar[m]<<" ";}cout<<endl;
	//for(m=1;m<=dimStar;m++){cout<<indexStar[m]<<"    ";}cout<<endl;
	//cout<<endl;
	//for(i=0;i<numberOfStates;i++){for(j=0;j<numberOfStates;j++)
	//	{cout<<itsTransitionElement[i][j]<<" ";}cout<<endl;}cout<<endl;
	for(m=1;m<dimStar;m++){for(n=1;n<dimStar;n++)
	{
		i=indexStar[m];j=indexStar[n];
		omegaStar[m][n] =itsTransitionElement[i][j];
	}}
	//for(m=1;m<dimStar;m++){for(n=1;n<dimStar;n++)
	//{cout<<omegaStar[m][n]<<" ";}cout<<endl;}cout<<endl;

	for(m=1;m<dimStar;m++)
	{
		i=indexStar[m];
		omegaStar[m][dimStar]=0;
		omegaStar[dimStar][m]=0;
		for(j=0;j<=numberOfStates;j++)
		{
			if(itsSwitchState[j]==L)
			{
				omegaStar[m][dimStar]+=itsTransitionElement[i][j];
				omegaStar[dimStar][m]+=itsTransitionElement[j][i]*pStat[j];
			}
		}
		omegaStar[dimStar][m]/=pL;
	}
	omegaStar[dimStar][dimStar]=0;
	for(i=0;i<numberOfStates;i++){for(j=0;j<numberOfStates;j++)
	{
		if((itsSwitchState[i]==L)&&(itsSwitchState[j]!=L)){omegaStar[dimStar][dimStar]+=pStat[i]*itsTransitionElement[i][j];}
	}}
	omegaStar[dimStar][dimStar]/=(-pL);

	//for(m=1;m<=dimStar;m++){for(n=1;n<=dimStar;n++)
	//{cout<<omegaStar[m][n]<<" ";}cout<<endl;}cout<<endl;

// calculate first passage times
	zMat=matrix(1,dimStar,1,dimStar);
	for(m=1;m<=dimStar;m++){for(n=1;n<=dimStar;n++)
	{
//		zMat[i+1][j+1] = pStat[j] - mat.GetTransitionElement(j,i);
		zMat[m][n] = pStar[n] - omegaStar[n][m];
	}}
	matrixInvert(zMat,dimStar);

	//cout<<"first passage matrix = "<<endl;
	//for(m=1;m<=dimStar;m++){for(n=1;n<=dimStar;n++)
	//	{cout<<(zMat[m][m]-zMat[m][n])/pStar[m]<<"  ";}cout<<endl;}
		// this is time from n to m

// retransform to the original indices
	switchTime=0;
	timeInP=0;
	for(n=1;n<=dimStar;n++)
	{
		i=indexStar[n];
		if(itsSwitchState[i]==R)
		{
			//cout<<" time to L from "<<i
			//<<"  ("<<nPlus(i)<<", "<<nMinus(i)<<")"<<" is "
			//<<(zMat[dimStar][dimStar]-zMat[dimStar][n])/pStar[dimStar]
			//<<" without pause "<<(zMat[dimStar][dimStar]-zMat[dimStar][n])/pStar[dimStar] + 1/omegaStar[n][n]/pStar[n]*pR
			//<<"  with prob "<<pStat[i]/pR<<endl;
			switchTime+=(zMat[dimStar][dimStar]-zMat[dimStar][n])/pStar[dimStar]*pStar[n];
			//switchTime+=((zMat[dimStar][dimStar]-zMat[dimStar][n])/pStar[dimStar] + 1/omegaStar[n][n]/pStar[n]*pR)*pStar[n]/pR;
			//cout<<"   total out rate = "<<(-1)*omegaStar[n][n]<<endl;
		}
		if(itsSwitchState[i]==P)
		{
			timeInP-=pStar[n]*omegaStar[n][n];
			//cout<<i<<", P: "<<nPlus(i)<<", "<<nMinus(i)<<": "<<omegaStar[n][n]<<", p = "<<pStar[n]<<endl;
		}
	}
	timeInP=pP/timeInP;
	switchTime/=pR;
	cout.precision(5);
	//cout<<"pP, pL, pR = "<<pP<<", "<<pL<<", "<<pR<<endl;
	//cout<<"time in P = "<<timeInP<<endl;
	//cout<<"passageTime = "<<switchTime<<endl;
// free all the vectors and matrices used in this routine
	free_matrix(omegaStar,1,dimStar,1,dimStar);
	free_ivector(indexStar,1,dimStar);
	free_vector(pStar,1,dimStar);
	free_matrix(zMat,1,dimStar,1,dimStar);

	return switchTime;
}//end subroutine calculateSwitchTime
//======================================
void DisplayMatrix()const;
void DisplayRates()const;
void DisplayLargeRates()const;
void CheckNorm()const;
//======================================
//======================================
private:
int rowReduce(const int& actDim)
{
int i,i2;
int j;
//int j;
long double c;
//cout<<"Function rowReduce called"<<endl;DisplayMatrix();
//cout<<"ROWREDUCE called for dimension "<<actDim<<endl;
for(i=0;i<(actDim-1);i++)
{
	//cout<<"Step number "<<i<<endl;
	//DisplayMatrix();cout<<endl;
	if(itsMatrixElement[i][i]==0){cout<<"ERROR! Zero matrix element! at FsPlus  = "<<itsFsPlus<<", epsPlus = "<<itsEpsPlus
		<<", discardedStates: "<<itsNumberOfDiscardedStates<<", i = "<<i<<endl;exit(8);}
	c = 1./itsMatrixElement[i][i];//cout<<"c = "<<c<<endl;
	multiplyRow(i,c);
	for(i2=0;i2<(actDim-1);i2++)
	{
		if((itsMatrixElement[i2][i]!=0)&&(i2!=i))
		{
			//cout<<"Work   on row "<<i2<<": ";
			//for(j=0;j<numberOfStates;j++){cout<<itsMatrixElement[i2][j]<<"  ";};cout<<endl;
			c =-itsMatrixElement[i2][i];
			//cout<<", c = "<<c<<endl;
			//ASSERT(i2>=0);ASSERT(i2<(numberOfStates-1));
			//ASSERT(i>=0);ASSERT(i<(numberOfStates-1));
			addFirstMultipliedRowToSecondRow(c,i,i2); // full row reduce
			//addFirstMultipliedRowToSecondRowOnlyRightColumns(c,i,i2); // not full row reduce
			//cout<<"Worked on row "<<i2<<": ";for(j=0;j<numberOfStates;j++){cout<<itsMatrixElement[i2][j]<<"  ";};cout<<endl;
		//DisplayMatrix();cout<<endl;
		}
	}
	//DisplayMatrix();cout<<endl;
}//end for i
//cout<<"Finish"<<endl;DisplayMatrix();cout<<endl;
//DisplayMatrix();
return 0;
}//end rowReduce
//======================================
int balance()
// routine to balance the matrix A = itsMatrixElements[][]
// produces balanced D^{-1} A D  (i.e. matrix equivalent to A, but having reduced matrix norm, thereby reducing the error in the following
// see Numerical recipes in C++, chapter 11.5
{
int i,j;//,m,n;
long double c,r,f;
long double g,s;
int last;
double gamma;
const double RADIX = numeric_limits<double>::radix;
double sqrdx = RADIX*RADIX;
int actualDimension;
gamma = 0.98;//1.0; // skip step if no substantial reduction
//cout<<"RADIX = "<<RADIX<<endl; (is equal to 2 for MPIKG local computer)
	//cout<<"Diagonal elements before balance:"<<endl;
	//for(i=0;i<actualDimension;i++){cout<<itsMatrixElement[i][i]<<endl;}
actualDimension=GetActualDimension();
//actualDimension=numberOfStates;
//cout<<"Balancing matrix with actualDimension "<<actualDimension<<endl;
for(i=0;i<actualDimension;i++){itsBalanceMatrixDiag[i]=1.0;}// initialize diagnoal balancing matrix
// divide rows so that diagonal elements are equal to 1 (because balancing will not affect diagonals)
	for(i=0;i<actualDimension;i++)
	{
		c =1/ itsMatrixElement[i][i];
		for(j=0;j<actualDimension;j++){itsMatrixElement[i][j] *= c;}
	}
//cout<<"after row division"<<endl;DisplayMatrix();
// balancing
last=0;
while(last==0)
{
	last =1;
	//cout<<"loop"<<endl;
	for(i=0;i<actualDimension;i++)
	{
		c = 0.0;
		r = 0.0;
		for(j=0;j<actualDimension;j++)
		{
			if(j!=i)
			{
				c += fabs(itsMatrixElement[j][i]);	// column norm
				r += fabs(itsMatrixElement[i][j]);	// row norm
			}
		}
		//cout<<"i = "<<i<<", row norm = "<<r<<",  column norm = "<<c<<", sqrt(quotient) = "<<sqrt(r/c)<<endl;//DisplayMatrix();
		//ASSERT(r>0);ASSERT(c>0);
		if((r!=0.0)&&(c!=0.0))
		{
			//cout<<"i = "<<i<<", row norm = "<<r<<",  column norm = "<<c
			//<<", quotient = "<<r/c<<", f  = "<<f<<", crit = "<<(c*f+r/f)/(c+r)<<endl;
			//f = sqrt(r/c);
			// calculation of f = sqrt(r/c), but int floating point arithmetics
				g = r/RADIX;
				f = 1.0;
				s=c+r;
				while(c<g)
				{
					f *= RADIX;
					c*= sqrdx;
				}
				g = r*RADIX;
				while(c>g)
				{
					f /= RADIX;
					c /=sqrdx;
				}
			//if((c*f+r/f)<gamma*(c+r)) // condition for finishing if f = sqrt(r/c) directly
			if ((c+r)/f<gamma*s) // condition for finishing if f = sqrt(r/c) approximately via floating point arithmetics
			{
				//cout<<"similarity transform for "<<i<<" with f = "<<f<<endl;
				ASSERT(f>0);
				last =0;
				itsBalanceMatrixDiag[i] *=f;
				g=1.0/f;
				for(j=0;j<actualDimension;j++)
				{
					//itsMatrixElement[i][j] = itsMatrixElement[i][j]/f; // modify ith column
						//itsMatrixElement[j][i] = itsMatrixElement[j][i]*f; // modify ith row
					itsMatrixElement[i][j] *=g; // modify ith column
					itsMatrixElement[j][i] *= f; // modify ith row
				}
				//DisplayMatrix();
			}// end if criterium for skipping and exiting
		}//end if r!=0 and c!=0
	}//end i
	//cout<<"After balance step"<<endl;DisplayMatrix();
}//end while last
	//cout<<"After balance step"<<endl;DisplayMatrix();
	//cout<<"diag mat "<<endl;for(i=0;i<actualDimension;i++){cout<<itsBalanceMatrixDiag[i]<<"  ";}cout<<endl;
	//cout<<"Diagonal elements after balance:"<<endl;for(i=0;i<actualDimension;i++){cout<<itsMatrixElement[i][i]<<endl;}
return 0;
}//end balance
//======================================
int debalance(double* vec)
{
	int i;
	int actualDimension;
	actualDimension = GetActualDimension();
	//actualDimension=numberOfStates;
	//cout<<"Debalancing with actualDimension "<<actualDimension<<endl;
	for(i=0;i<actualDimension;i++)
	{
		vec[i] *= (double)itsBalanceMatrixDiag[i];
	}
	return 0;
}//end debalance
//======================================
//======================================
private:
int multiplyRow(const int& i, const long double& c)
{
	int j;
	for(j=0;j<numberOfStates;j++)
	{
		itsMatrixElement[i][j] = c*itsMatrixElement[i][j];
	}
	return 0;
}//end multiplyColumn
//======================================
int multiplyColumn(const int& i, const long double& c)
{
	int j;
	for(j=0;j<numberOfStates;j++)
	{
		itsMatrixElement[j][i] = c*itsMatrixElement[j][i];
	}
	return 0;
}//end multiplyColumn
//======================================
int addFirstToSecondRow(const int& i1, const int& i2)
{
	int j;
	for(j=0;j<numberOfStates;j++)
	{
		itsMatrixElement[i2][j] = itsMatrixElement[i2][j] +  itsMatrixElement[i1][j];
	}
	return 0;
}//addFirstToSecondRow
//======================================
int addFirstMultipliedRowToSecondRow(const long double& fac,const int& i1, const int& i2)
{
	int j;
	ASSERT(i1>=0);ASSERT(i1<numberOfStates);
	ASSERT(i2>=0);ASSERT(i2<numberOfStates);
	//cout<<"called addRow with fac = "<<fac<<endl;
	//cout<<"called addRow "<<"["<<i2<<"] + "<<fac<<" x ["<<i1<<"] "<<endl;
	for(j=0;j<numberOfStates;j++)
	{
		//cout<<j<<"  "<<itsMatrixElement[i2][j]<<" changed to ";
		//itsMatrixElement[i2][j] = itsMatrixElement[i2][j];
		//itsMatrixElement[i2][j] = itsMatrixElement[i2][j] +  fac*itsMatrixElement[i1][j];
		itsMatrixElement[i2][j] +=  fac*itsMatrixElement[i1][j];
		//if(abs(itsMatrixElement[i2][j])<doubleLowLimit){itsMatrixElement[i2][j]=0;}
		//cout<<a<<" + "<<b<<" = "<<c<<" = "<<itsMatrixElement[i2][j]<<endl;
	}
	return 0;
}//addFirstMultipliedRowToSecondRow
//======================================
int addFirstMultipliedRowToSecondRowOnlyRightColumns(const long double& fac,const int& i1, const int& i2)
{
	int j;
	ASSERT(i1>=0);ASSERT(i1<numberOfStates);
	ASSERT(i2>=0);ASSERT(i2<numberOfStates);
	//cout<<"called addRow with fac = "<<fac<<endl;
	//cout<<"called addRow "<<"["<<i2<<"] + "<<fac<<" x ["<<i1<<"] "<<endl;
	for(j=i1;j<numberOfStates;j++)
	{
		//cout<<j<<"  "<<itsMatrixElement[i2][j]<<" changed to ";
		//itsMatrixElement[i2][j] = itsMatrixElement[i2][j];
		//itsMatrixElement[i2][j] = itsMatrixElement[i2][j] +  fac*itsMatrixElement[i1][j];
		itsMatrixElement[i2][j] +=  fac*itsMatrixElement[i1][j];
		//if(abs(itsMatrixElement[i2][j])<doubleLowLimit){itsMatrixElement[i2][j]=0;}
		//cout<<a<<" + "<<b<<" = "<<c<<" = "<<itsMatrixElement[i2][j]<<endl;
	}
	return 0;
}//addFirstMultipliedRowToSecondRowOnlyRightColumns
//======================================
int SwapRows(const int& row1, const int& row2, const int& actDim)
// swaps  rows of row1 <-> row2
{
	int j;
	long double dummy;//[actDim];
	//cout<<"SwapRows called for "<<row1<<" <-> "<<row2<<", actual working dimension is "<<actDim<<endl;
	if(row1==row2){return 0;}
	for(j=0;j<actDim;j++)
	{
		dummy = itsMatrixElement[row1][j];
		itsMatrixElement[row1][j] = itsMatrixElement[row2][j];
		 itsMatrixElement[row2][j] = dummy;
	}
	//DisplayMatrix();
	return 0;
}
//======================================
int SwapColumns(const int& col1, const int& col2, const int& actDim)
// swaps  columns of col1 <-> col2
{
	int i;
	long double dummy;//[actDim];
	//cout<<"SwapColumns called for "<<col1<<" <-> "<<col2<<", actual working dimension is "<<actDim<<endl;
	if(col1==col2){return 0;}
	for(i=0;i<actDim;i++)
	{
		dummy = itsMatrixElement[i][col1];
		itsMatrixElement[i][col1] = itsMatrixElement[i][col2];
		 itsMatrixElement[i][col2] = dummy;
	}
	//DisplayMatrix();
	return 0;
}
//======================================
int discardStatesWithLargeOutRate()
{
	int m,n;
	int x,y;
	int i;
	long double max;
	int lookForElement,foundElement,discardSymmetricState;
	int actualDimension;
	itsNumberOfDiscardedStates = 0;
	actualDimension=numberOfStates;
	ASSERT(useDiscardRates==1);
	//cout<<"Discard states called"<<endl;
	//DisplayMatrix();cout<<endl;
	lookForElement = 0;
	//CheckNorm();
	while(lookForElement==0)
	{
		foundElement=0;
		for(x=0;x<actualDimension;x++)
		{
			for(y=0;y<actualDimension;y++)
			{
				//cout<<"x = "<<x<<", y = "<<y<<endl;
				//if((x!=y)&&(abs(itsMatrixElement[x][y])>=doubleLimit)) // if rate from y to x is very large
				if((x!=y)&&(itsMatrixElement[x][y]>=doubleLimit)) // if rate from y to x is very large
				{
					//cout<<"marked element "<<y<<" because of transition to element "<<x
					//	<<" (trans from "<<nPlus(y)<<","<<nMinus(y)<<" to "<<nPlus(x)<<","<<nMinus(x)<<")"
					//	<<" with value "<<itsMatrixElement[x][y]<<endl;
					max = itsMatrixElement[x][y];
					for(i=0;i<actualDimension;i++)
					{
						//cout<<"neighbour "<<i<<" with rate "<< itsMatrixElement[i][y];
						if(itsMatrixElement[i][y]>max)
						{
							max = itsMatrixElement[i][y];
							x = i;
							//cout<<" is larger"<<endl;
						}
						//else {cout<<endl;}
					}
					foundElement=1;
					itsSwappedPoints[itsNumberOfDiscardedStates].point1=y; // point to be discarded
					itsSwappedPoints[itsNumberOfDiscardedStates].point2=x; // target of large transition
					break;
				}
			}// end for y
			if(foundElement==1){break;}
		}//end for x
		if(foundElement==1)
		{
			// shuffle rates in order to discard state y:
				//cout<<"attribute rates into "<<y<<" to "<<x<<endl;
				makeDiscardMatrix(itsSwappedPoints[itsNumberOfDiscardedStates],actualDimension);
				//DisplayMatrix();
			// swap discarded state to end of matrix:
				//cout<<"swap "<<y<<" and "<< actualDimension-1<<endl;
				itsSwappedPoints[itsNumberOfDiscardedStates].point2=actualDimension-1;	// swapped state
				SwapRows(y,actualDimension-1,actualDimension);
				SwapColumns(y,actualDimension-1,actualDimension);
				//cout<<"after swapping states "<<y<<" <-> "<<actualDimension-1<<endl;DisplayMatrix();
			// set numbers saying that point has been discarded:
				itsNumberOfDiscardedStates+=1;
				actualDimension = numberOfStates - itsNumberOfDiscardedStates;
				//CheckNorm();
		}
		else
		{
			lookForElement=1; // total for loop without large rate => stop
		}
		//DisplayMatrix();cout<<endl;
	}// end while lookForElement
	return 0;
}
//======================================
int makeDiscardMatrix(points& discardState, const int& actDim)
{
	int x,y,m;
	x = discardState.point1;
	y = discardState.point2;
	//cout<<"MakeDiscardMatrix called for state "<<x<<" because of transition to state "<<y
	//	<<", actual working dimension is "<<actDim<<", result: "<<endl;
	for(m=0;m<actDim;m++)
	{
		//if((m!=x)&&(m!=y))
		//{
			itsMatrixElement[y][m] += itsMatrixElement[x][m];
		//}
	}
	//DisplayMatrix();
	return 0;
}

//======================================
//======================================
int initializeMatrixElements()
{
	int indx,indy;
	int kp1,km1,kp2,km2;
	itsNumberOfDiscardedStates =0;
	//double v1,v2;
	//double limit=10e10;
	//cout<<"number of States "<<numberOfStates<<endl;
	kp2=Np;km2=1;
	long double largestElement =detachMinus(Np,Nm,kp2,km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
	//cout<<"Largest Element  = "<<largestElement<<endl;
	for(indx=0;indx<numberOfStates;indx++){
	for(indy=0;indy<numberOfStates;indy++){
 		kp2=nPlus(indx);     // final state
		km2=nMinus(indx); // final state
 		kp1=nPlus(indy);	 // initial state
		km1=nMinus(indy);  // initial state
		//cout<<"matrixIndices = "<<indx<<"  "<<indy<<" => trans from state "<<kp1<<"  "<<km1<<" to "<<kp2<<"  "<<km2;
		itsVelocity[indx]=velocity(Np,Nm,kp2,km2,
			itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
			itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
		if(kp2==kp1)
		{
			if         (km2==(km1+1))
			{
				itsMatrixElement[indx][indy] =
					attachMinus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
				//cout<<" attachMinus   ";
			}
			else if (km2==(km1 -1))
			{
				itsMatrixElement[indx][indy] =
					detachMinus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);

				//cout<<" detachMinus   ";
			}
			else if (km2==km1)//&&(kp1==km1))
			{
				 itsMatrixElement[indx][indy] =
					-(attachPlus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus))
					-(detachPlus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus))
					-(attachMinus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus))
					-(detachMinus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus));
				//cout<<" diagonal      ";
			}
			else
			{
				itsMatrixElement[indx][indy] =0.0;
				//cout<<" kp=fixed else ";
			}
		}//end if kp2==kp1
		else if(km2==km1)
		{
			if         (kp2==(kp1+1))
			{
				itsMatrixElement[indx][indy] =
					attachPlus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
				//cout<<" attachPlus    ";
			}
			else if (kp2==(kp1 -1))
			{
				itsMatrixElement[indx][indy] =
					detachPlus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
				//cout<<" detachPlus    ";
			}
			else
			{
				itsMatrixElement[indx][indy] =0.0;
			}
		}//end if km2==km1
		else
		{
			itsMatrixElement[indx][indy] =0.0;
		}
		//cout<<"   matEl = "<<itsMatrixElement[indx][indy]<<endl;
		//if((limitChoice==1)&&(itsMatrixElement[indx][indy]>doubleLimit)){itsMatrixElement[indx][indy] = doubleLimit;}
	//itsMatrixElement[indx][indy]=itsMatrixElement[indx][indy]/largestElement;
	}}//end for indx,for indy
	return 0;
	}//end initializeMatrixElements
//======================================
int initializeSymmetricMatrixElements()
{
	int indx,indy;
	int kp1,km1,kp2,km2;
	itsNumberOfDiscardedStates =0;
	//cout<<"number of States "<<numberOfStates<<endl;
	//for(km1=0;km1<=Nm;km1++){for(kp1=0;kp1<=Np;kp1++){
	//	if(kp1>=km1){indx  = index(kp1,km1);
	//	cout<<"np,nm = "<<kp1<<","<<km1<<" => ind = "<<indx	<<" => np,nm = "<<nPlus(indx)<<","<<nMinus(indx)<<endl;}}}
	kp2=Np;km2=1;
	for(indx=0;indx<numberOfStates;indx++){
	for(indy=0;indy<numberOfStates;indy++){
 		kp2=nPlus(indx);     // final state
		km2=nMinus(indx); // final state
 		kp1=nPlus(indy);	 // initial state
		km1=nMinus(indy);  // initial state
		ASSERT(kp1>=km1);ASSERT(kp2>=km2);
		//cout<<"matrixIndices = "<<indx<<"  "<<indy<<" => trans from state "<<kp1<<"  "<<km1<<" to "<<kp2<<"  "<<km2;
		itsVelocity[indx]=velocity(Np,Nm,kp2,km2,
			itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
			itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
		if(kp2==kp1)
		{
			if         (km2==(km1+1))
			{
				itsMatrixElement[indx][indy] =
					attachMinus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
				if(kp1==km1){cout<<"Error! Diagonal element should not exist"<<endl;}
				//cout<<" attachMinus   ";
			}
			else if (km2==(km1 -1))
			{
				itsMatrixElement[indx][indy] =
					detachMinus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
				if(kp1==km1){itsMatrixElement[indx][indy]*=2;}
				//cout<<" detachMinus   ";
			}
			else if (km2==km1)//&&(kp1==km1))
			{
				 itsMatrixElement[indx][indy] =
					-(attachPlus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus))
					-(detachPlus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus))
					-(attachMinus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus))
					-(detachMinus(Np,Nm,kp2, km2,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus));
				//cout<<" diagonal      ";
			}
			else
			{
				itsMatrixElement[indx][indy] =0.0;
				//cout<<" kp=fixed else ";
			}
		}//end if kp2==kp1
		else if(km2==km1)
		{
			if         (kp2==(kp1+1))
			{
				itsMatrixElement[indx][indy] =
					attachPlus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
				if(kp1==km1){itsMatrixElement[indx][indy]*=2;}
				//cout<<" attachPlus    ";
			}
			else if (kp2==(kp1 -1))
			{
				itsMatrixElement[indx][indy] =
					detachPlus(Np,Nm,kp1, km1,
						itsEpsPlus,itsEpsMinus,itsPiPlus,itsPiMinus,itsFsPlus,itsFsMinus,itsFdPlus,itsFdMinus,
						itsvPlus,itsvMinus,itsBetaPlus,itsBetaMinus,itsgPlus,itsgMinus);
				if(kp1==km1){cout<<"ERROR, diagonal off-rate that should not exist!"<<endl;}
				//cout<<" detachPlus    ";
			}
			else
			{
				itsMatrixElement[indx][indy] =0.0;
			}
		}//end if km2==km1
		else
		{
			itsMatrixElement[indx][indy] =0.0;
		}
		//cout<<"   matEl = "<<itsMatrixElement[indx][indy]<<endl;
		//if((limitChoice==1)&&(itsMatrixElement[indx][indy]>doubleLimit)){itsMatrixElement[indx][indy] = doubleLimit;}
		//itsMatrixElement[indx][indy]=itsMatrixElement[indx][indy]/largestElement;
	}}//end for indx,for indy
	//CheckNorm();
	return 0;
	}//end initializeSymmetricMatrixElements

};//end class MasterMatrix

// =====================================================
// =====================================================
// =====================================================
void MasterMatrix::DisplayMatrix()const
{
	int i,j;
//	cout<<"kp   km   attachPlus  attachMinus  detachPlus  detachMinus  totalRate  velocity"<<endl;
	cout.setf(ios::left);
	cout.setf(ios::showpoint|ios::fixed);
	cout.precision(3);
	//cout.precision(1);
	for(i=0;i<numberOfStates;i++)
	{
		cout<<" ";
		for(j=0;j<numberOfStates;j++)
		{
		//cout.setf(ios_base::scientific, ios_base::floatfield);
		cout.setf(ios_base::fixed, ios_base::floatfield);cout.precision(2);
		//cout.precision(3);cout.setf(ios_base::fixed, ios_base::floatfield);
		cout<<itsMatrixElement[i][j]<<"  ";
		}
		cout<<endl;
	}
}//end DisplayMatrix
// =====================================================
void MasterMatrix::DisplayRates()const
{
	int indx,indy;
	int kp1,km1,kp2,km2;
	//double v1,v2;
	cout.precision(3);
	cout<<"number of States "<<numberOfStates<<endl;
	for(indx=0;indx<numberOfStates;indx++){
	for(indy=0;indy<numberOfStates;indy++){
 		kp2=nPlus(indx);     // final state
		km2=nMinus(indx); // final state
 		kp1=nPlus(indy);	 // initial state
		km1=nMinus(indy);  // initial state
				if(kp2==kp1)
		{
			if         (km2==(km1+1))
			{
				cout<<"matrixIndices = "<<indx<<"  "<<indy<<" => trans from state "<<kp1<<"  "<<km1<<" to "<<kp2<<"  "<<km2;
				cout<<" attachMinus   ";
				cout<<"   matEl = "<<itsMatrixElement[indx][indy]<<endl;
				//if(itsMatrixElement[indx][indy]>doubleLimit){cout<<"LARGE MATRIX ELEMENT!!!"<<endl;}
			}
			else if (km2==(km1 -1))
			{
				cout<<"matrixIndices = "<<indx<<"  "<<indy<<" => trans from state "<<kp1<<"  "<<km1<<" to "<<kp2<<"  "<<km2;
				cout<<" detachMinus   ";
				cout<<"   matEl = "<<itsMatrixElement[indx][indy]<<endl;
				//if(itsMatrixElement[indx][indy]>doubleLimit){cout<<"LARGE MATRIX ELEMENT!!!"<<endl;}
			}
			else if (km2==km1)
			{
				cout<<"matrixIndices = "<<indx<<"  "<<indy<<" => trans from state "<<kp1<<"  "<<km1<<" to "<<kp2<<"  "<<km2;
				cout<<" diagonal      ";
				cout<<"   matEl = "<<itsMatrixElement[indx][indy]<<endl;
				//if(itsMatrixElement[indx][indy]>doubleLimit){cout<<"LARGE MATRIX ELEMENT!!!"<<endl;}
			}
			else					{}
		}//end if kp2==kp1
		else if(km2==km1)
		{
			if         (kp2==(kp1+1))
			{
				cout<<"matrixIndices = "<<indx<<"  "<<indy<<" => trans from state "<<kp1<<"  "<<km1<<" to "<<kp2<<"  "<<km2;
				cout<<" attachPlus    ";
				cout<<"   matEl = "<<itsMatrixElement[indx][indy]<<endl;
				//if(itsMatrixElement[indx][indy]>doubleLimit){cout<<"LARGE MATRIX ELEMENT!!!"<<endl;}
			}
			else if (kp2==(kp1 -1))
			{
				cout<<"matrixIndices = "<<indx<<"  "<<indy<<" => trans from state "<<kp1<<"  "<<km1<<" to "<<kp2<<"  "<<km2;
				cout<<" detachPlus    ";
				cout<<"   matEl = "<<itsMatrixElement[indx][indy]<<endl;
				//if(itsMatrixElement[indx][indy]>doubleLimit){cout<<"LARGE MATRIX ELEMENT!!!"<<endl;}
			}
			else					{}
		}//end if km2==km1
		else	{}
	}}
}//end DisplayRates
// =====================================================
void MasterMatrix::DisplayLargeRates()const
{
	int indx,indy;
	int kp1,km1,kp2,km2;
	//double v1,v2;
	cout<<"limit set to "<<doubleLimit<<endl;
	for(indx=0;indx<numberOfStates;indx++){
	for(indy=0;indy<numberOfStates;indy++){
 		kp2=nPlus(indx);     // final state
		km2=nMinus(indx); // final state
 		kp1=nPlus(indy);	 // initial state
		km1=nMinus(indy);  // initial state
		if(itsMatrixElement[indx][indy]>=doubleLimit)
		{cout<<"trans from element "<<indy<<" to "<<indx<<", i.e. from state "<<kp1<<" "<<km1<<" to "<<kp2<<" "<<km2<<": matrixEl =  "<<itsMatrixElement[indx][indy]<<" is larger than limit"<<endl;}
	}}
}//end DisplayLargeRates
// =====================================================
void MasterMatrix::CheckNorm()const
{
	int x,y;
	int actualDimension;
	double sum;
	actualDimension = GetActualDimension();
	cout<<"CheckNorm called with actual Dimension = "<<actualDimension<<endl;
	for(y=0;y<actualDimension;y++)
	{
		sum = 0;
		for(x=0;x<actualDimension;x++)
		{
			sum+=itsMatrixElement[x][y];
			//cout<<"x = "<<x<<", y = "<<y<<", sum = "<<sum<<endl;
		}
		if((sum>=0.000001)||(sum<=-0.0000001)){cout<<"  Attention! Matrix is not a W-Matrix! for column "<<y
			<<", sum = "<<sum<<endl;}//exit(8);}
	}
}//end CheckNorm
// =====================================================






//======================================
/*int checkDiscard(const int& i)
{
	int j,discard;
	discard=0;
	if(useDiscardRates==1)
	{
		for(j=0;j<itsNumberOfDiscardedStates;j++)
		{
//			if(itsDiscardedElementIndex[j]==i){discard=1;}
		}
	}
	return discard;
}
*/

//======================================
/*
int makeDiscardRates()
// set rates to effective rates, discarding the elements marked in itsDiscardedElementIndex
{
	int i,j;
	int x,y;
	cout<<"number of states to be discarded =  "<<itsNumberOfDiscardedStates<<endl;
	for(i=0;i<itsNumberOfDiscardedStates;i++)
	{
		//x = itsDiscardedElementIndex[i];
		//y = itsDiscardedElementDestination[i];
		ASSERT(x!=y);
		cout<<"discard element "<<x<<" because of transition to "<<y<<endl;;
		for(j=0;j<numberOfStates;j++)
		{
//			if((j!=x)&&(j!=y))
//			{
//				itsMatrixElement[y][j] += itsMatrixElement[x][j];
//			}
			//itsMatrixElement[j][j] -= itsMatrixElement[x][j] + itsMatrixEle;
		}
	DisplayMatrix();cout<<endl;
	}
return 0;
}
*/
