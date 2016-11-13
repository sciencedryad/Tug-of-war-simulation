#include "StatDef.CPP"

int main()
{

cout<<"Calculation of stationary state for Np = "<<Np<<", Nm = "<<Nm<<" (number of states = "<<numberOfStates<<")"<<endl;
#include "StatIni.CPP"

//======================================
// initialization step
//======================================
cout<<"Initialization step"<<endl;
	// rates
		epsP=epsStart;
		epsM=epsFactor*epsP;
		piP=piPlus;
		piM=piMinus;
		FdP=FdPlus;
		FdM=FdMinus;
		FsP=fStart*FdM;
		FsM=fFactor*FsP;
		vP=vPlus;
		vM=vMinus;
		gP=gPlus;
		gM=gMinus;
		fP=fStart;
// kinesin like rates for minus direction(!)
		if(useKinesinRates==1){epsM = 1;piM = 5;FdM = 3; FsM = 6;}
// start
		fPOld=fP;epsPOld=epsP;
		if(useDiscardRates)
		{
			//ASSERT(doubleLimit>exp(2*FsP/FdM));
			//ASSERT(doubleLimit>exp(2*FsM/FdP));
		}
	//initialize matrix
		//cout<<"Initialize matrix"<<endl;
		//cout<<"KStart = "<<KStart<<", epsStart = "<<epsStart<<endl;
		//cout<<"using parameters: "<<"epsP = "<<epsP<<", epsM = "<<epsM<<", piP = "<<piP<<", piM = "<<piM
		//	<<", FsP =  "<<FsP<<", FsM = "<<FsM<<", FdP = "<<FdP<<", FdM =  "<<FdM
		//	<<", vP = "<<vP<<", vM = "<<vM<<", betaP = "<<betaPlus<<", betaM = "<<betaMinus<<", gP = "<<gP<<", gM = "<<gM<<endl;
		MasterMatrix mat(epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
		cout<<"Rates at start:"<<endl;mat.DisplayRates();
		cout<<"Matrix at start:"<<endl;mat.DisplayMatrix();
		//cout<<"Large rates at start:"<<endl;mat.DisplayLargeRates();
		//cout<<"Do calculation"<<endl;
		mat.calculateStationaryState(pStat);
		calculatePDeltaSigma(pStat, pDelta, pSigma);
		calculatePStatMat(Np+1, Nm+1,pStat, pStatMatrix);
		//cout<<"numberOfDiscardedStates = "<<mat.GetNumberOfDiscardedStates()
		//	<<" from overall "<<numberOfStates<<" states"<<endl;
		cout.setf(ios_base::fixed, ios_base::floatfield);cout.precision(5);
		//cout<<"pStat = ";for(i=0;i<numberOfStates;i++){cout<<pStat[i]<<"  ";}cout<<endl;
		//cout<<"calculate pDelta and Sigma"<<endl;
		cout.precision(3);
		//cout<<"  pDelta = "; for(del=-Nm;del<=Np;del++){cout<<pDelta[del+Nm]<<"  ";}cout<<endl;
	// calculation of properties
		//findLocalExtrema((Np+Nm+1), pDelta,numberOfExtremaOld,numberOfMaximaOld);
		findLocalExtremaPositions((Np+Nm+1), pDelta,numberOfExtremaOld,numberOfMaximaOld,maximaPos);
			numberOfMaxima = numberOfMaximaOld;
			numberOfExtrema = numberOfExtremaOld;
		calculateAverage((Np+Nm+1),pSigma,0,sigmaAv);
	 		if(sigmaAv>sigmaThres){sigmaAboveThresOld=1;}else{sigmaAboveThresOld=0;}
		findAbsMaxPos((Np+Nm+1), pDelta, maxPos);
			if(maxPos==Nm){symOld=1;}else{symOld=0;}
		cout.precision(4);
		cout<<"pStatMatrix"<<endl;for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){cout<<pStatMatrix[kp][km]<<"  ";}cout<<endl;}cout<<endl;
		//findPhaseVal(0,Np+1,Nm+1, pStatMatrix, maxKp,maxKm);
		//cout<<"  numberOfExtrema = "<<numberOfExtrema<<", numberOfMax = "<<numberOfMaxima<<endl;
		//cout<<"  max Positions at delta = ";for(i=0;i<numberOfMaxima;i++){cout<<maximaPos[i]-Nm<<" ";} cout<<endl;
		//cout<<"  p(Delta=0) = "<<pDelta[Nm]<<", 1/p(Delta=0) = "<<1/pDelta[Nm]<<endl;
		//cout<<"  prob of boundary = "<<pDelta[0]<<", 1/p(Delta=Np) = "<<1/pDelta[0]<<endl;
		//cout<<"  max on diagonal at np = "<<maxKp<<", nm = "<<maxKm
		//	<<" with prob "<<pStatMatrix[maxKp][maxKm]<<", 1/p(this max) = "<<1/pStatMatrix[maxKp][maxKm]<<endl;
		maxLarger1SymOld=0;maxLarger1USOld=0;
		for(i=0;i<numberOfMaxima;i++)
		{
			findPhaseVal(maximaPos[i]-Nm,Np+1,Nm+1,pStatMatrix,maxKp,maxKm);
			//findPhaseVal(maximaPos[i]-Nm,pStatMatrix,maxKp,maxKm);
			if((maxKp>=FPLargerVal)||(maxKm>=FPLargerVal)){if(maximaPos[i]==Nm){maxLarger1SymOld=1;}else {maxLarger1USOld=1;}}
			//cout<<"maxKP and Km = "<<maxKp<<"   "<<maxKm<<endl;
		}
		maxLarger1Sym=maxLarger1SymOld;
		maxLarger1US=maxLarger1USOld;
		//cout<<"FP larger 1? sym "<<maxLarger1Sym<<", US "<<maxLarger1US<<endl;
		if((pStatMatrix[0][0]>pStatMatrix[1][1])||(pStatMatrix[0][0]>pStatMatrix[0][1])||(pStatMatrix[0][0]>pStatMatrix[1][0])){bound=0;}
			else{bound=1;}
		//if(pStatMatrix[0][0]>=pStatMatrix[1][1]){bound=0;}else{bound=1;}
		//if(pStatMatrix[0][0]>0.5){bound=0;}else{bound=1;}
		boundOld = bound;
		if(pointMeas==1)
		{
			findMatrixMax(Np+1,Nm+1,pStatMatrix,numberOfPointMaxInd,storeKp,storeKm,onBoundary,onDiagonal,inMiddle,specialTrans);
			numberOfPointMax=numberOfPointMaxInd;
			//# include "StatPointMeasure.CPP"
			numberOfPointMaxOld=numberOfPointMax;
			specialTransOld=specialTrans;
			//numberOfPointMaxOldRenorm=numberOfPointMaxRenorm;
		}
//		findLocalExtremaMatrix(numberOfStates, pStat,numberOfExtrema,numberOfMaxima);
		if(deltaMeas==1)
		{
			for(i=0;i<numberOfMaxima;i++){maximaPosOld[i]=maximaPos[i];}
		}
	// special measurement for only one state in phase state (in this case initial state)
	//mat.DisplayRates();
	# include "StatOneStateMeas.CPP"

//======================================
// phase diagram loop
//======================================
cout<<"Phase diagram loop"<<endl;
if(scanEps==1)
{
	for(epsP=epsStart;epsP<=epsEnd+0.0000001;)
	{
	for(fP=fStart;fP<=fEnd+0.0000001;)
	{
		#include "StatCalculation.CPP"
		fPOld=fP;
		fP=fP+fIncr;
	}
	epsP=epsP+epsIncr;
	}
}
else
{
	ASSERT(scanEps==0);
	for(fP=fStart;fP<=fEnd+0.0000001;)
	{
	for(epsP=epsStart;epsP<=epsEnd+0.0000001;)
	{
		#include "StatCalculation.CPP"
		epsPOld=epsP;
		epsP=epsP+epsIncr;
	}
	fP=fP+fIncr;
	}
}

cout<<"Finishing"<<endl;
#include "StatFinish.CPP"

return 0;
}// end main
