//****************************************************************
// ZOOM IN
//****************************************************************

if(zoomLevel==1)
{
	fPLeft=fPOld;
	fPRight=fP;
	maxLarger1USLeft=maxLarger1USOld;
	//maxLarger1USRight=maxLarger1US;
}
fPMiddle = (fPLeft+fPRight)/2;
//cout<<"  Zoom level "<<zoomLevel<<" at eps = "<<epsP<<" between f = "<<fPLeft<<" and "<<fPRight<<" at "<<fPMiddle<<endl;

//initialize matrix
	mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	//(epsP,epsM,piP,piM,fPMiddle,fPMiddle,gP,gM);
// calculation of stationary state
	mat.calculateStationaryState(pStat);
	/*mat.rowReduce();	mat.GetColumn(numberOfStates-1,pStat;
	pStat[numberOfStates-1]=-1;	if(boundStatesOnly==1){pStat[0]=0;}	normalizeVec(numberOfStates,pStat);*/
	calculatePDeltaSigma(pStat, pDelta, pSigma);
// calculation of properties
	findLocalExtremaPositions((Np+Nm+1), pDelta,nExtrMiddle,nMaxMiddle,maximaPos);
	for(ind=0;ind<numberOfStates;ind++){pStatMatrix[nPlus(ind)][nMinus(ind)]=pStat[ind];}
	maxLarger1USMiddle=0;
	for(i=0;i<nMaxMiddle;i++)
	{
		findPhaseVal(maximaPos[i]-Nm,Np+1,Nm+1,pStatMatrix,maxKp,maxKm);
		if((maxKp>=FPLargerVal)||(maxKm>=FPLargerVal)){if(maximaPos[i]!=Nm){maxLarger1USMiddle=1;}}
	}
	//cout<<"    max Positions at delta = ";for(i=0;i<nMaxMiddle;i++){cout<<maximaPos[i]-Nm<<" ";}
	//cout<<", larger 1? us "<<maxLarger1US<<", US "<<maxLarger1US<<endl;

// find phase transition
	if((maxLarger1USMiddle!=maxLarger1USLeft))	{fPRight=fPMiddle;}// maxLarger1USRight=maxLarger1USMiddle;}
	else						{fPLeft  =fPMiddle; maxLarger1USLeft  =maxLarger1USMiddle;}
// measure at latest zoom level
if(zoomLevel==zoomDepth)
{
	fIncrAct=fIncr/(2*zoomDepth);
	fileNames.itsFPLarger1USOut<<(fPMiddle-fIncrAct/2)<<"   "<<epsP<<endl;
	//cout<<"  fIncrAct  = "<<fIncrAct<<"  trans at f = "<<(fPMiddle-fIncrAct/2)<<endl;
}







