//****************************************************************
// ZOOM IN
//****************************************************************

if(zoomLevel==1)
{
	fPLeft=fPOld;
	fPRight=fP;
	maxPosLeft=maximaPosOld[i];
	//maxPosRight=maximaPos[i];
	fIncrAct=fIncr;
}
fPMiddle = (fPLeft+fPRight)/2;
fIncrAct=fIncrAct/2;
//cout<<"  Zoom level "<<zoomLevel<<" between f = "<<fPLeft<<" and "<<fPRight<<" at "<<fPMiddle<<endl;

//initialize matrix
	mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	//(epsP,epsM,piP,piM,fPMiddle,fPMiddle,gP,gM);
// calculation of stationary state
	mat.calculateStationaryState(pStat);
	/*mat.rowReduce();	mat.GetColumn(numberOfStates-1,pStat);
	pStat[numberOfStates-1]=-1;	if(boundStatesOnly==1){pStat[0]=0;}	normalizeVec(numberOfStates,pStat);*/
	calculatePDeltaSigma(pStat, pDelta, pSigma);
// calculation of properties
	//findLocalExtrema((Np+Nm+1), pDelta,nExtrMiddle,nMaxMiddle);
	findLocalExtremaPositions((Np+Nm+1), pDelta,nExtrMiddle,nMaxMiddle,maximaPosMiddle);
	maxPosMiddle=maximaPosMiddle[i];

// find phase transition
	if((maxPosMiddle!=maxPosLeft))	{fPRight=fPMiddle; }//maxPosRight=maxPosMiddle;}
	else						{fPLeft  =fPMiddle; maxPosLeft  =maxPosMiddle;}
// measure at latest zoom level
if(zoomLevel==zoomDepth)
{
	fIncrAct=fIncrAct/2;
	fileNames.itsDeltaChangeOut<<(fPMiddle-fIncrAct)<<"   "<<epsP/piP<<"   "
		<<maximaPosOld[i]-deltaOffset<<"    "<<abs(maximaPosOld[i]-deltaOffset)<<endl;
	//<<maxPosMiddle-deltaOffset<<"    "<<abs(maxPosMiddle-deltaOffset)<<endl;
//	cout<<"fIncrAct  = "<<fIncrAct<<"  phase trans at f = "<<fPMiddle-fIncrAct/2<<endl;
}







