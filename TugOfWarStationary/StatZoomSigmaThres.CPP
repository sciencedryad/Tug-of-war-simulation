//****************************************************************
// ZOOM IN
//****************************************************************

if(zoomLevel==1)
{
	fPLeft=fPOld;
	fPRight=fP;
	sigmaThresLeft=sigmaAboveThresOld;
	//sigmaThresRight=sigmaAboveThres;
}
fPMiddle = (fPLeft+fPRight)/2;
//cout<<"Zoom level "<<zoomLevel<<"at eps = "<<epsP<<" between f = "<<fPLeft<<" and "<<fPRight<<" at "<<fPMiddle<<endl;

//initialize matrix
	mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	//(epsP,epsM,piP,piM,fPMiddle,fPMiddle,gP,gM);
// calculation of stationary state
	mat.calculateStationaryState(pStat);
	/*mat.rowReduce();	mat.GetColumn(numberOfStates-1,pStat);pStat[numberOfStates-1]=-1;
	if(boundStatesOnly==1){pStat[0]=0;}	normalizeVec(numberOfStates,pStat);*/
	calculatePDeltaSigma(pStat, pDelta, pSigma);
// calculation of properties
	calculateAverage((Np+Nm+1),pSigma,0,sigmaAv);
		if(sigmaAv>sigmaThres){sigmaThresMiddle=1;}else{sigmaThresMiddle=0;}

// find phase transition
	if((sigmaThresMiddle!=sigmaThresLeft))	{fPRight=fPMiddle; }//sigmaThresRight=sigmaThresMiddle;}
	else									{fPLeft  =fPMiddle; sigmaThresLeft  =sigmaThresMiddle;}
// measure at latest zoom level
if(zoomLevel==zoomDepth)
{
	fIncrAct=fIncr/(2*zoomDepth);
	fileNames.itsSigmaThresOut<<(fPMiddle-fIncrAct/2)<<"   "<<epsP<<endl;
	//cout<<"  fIncrAct  = "<<fIncrAct<<"  symmetry trans at f = "<<(fPMiddle-fIncrAct/2)<<endl;
}







