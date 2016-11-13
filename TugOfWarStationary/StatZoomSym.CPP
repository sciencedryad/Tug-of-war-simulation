//****************************************************************
// ZOOM IN
//****************************************************************

if(zoomLevel==1)
{
	fPLeft=fPOld;
	fPRight=fP;
	symLeft=symOld;
	//symRight=sym;
}
fPMiddle = (fPLeft+fPRight)/2;
//cout<<"Zoom level "<<zoomLevel<<"at eps = "<<epsP<<" between f = "<<fPLeft<<" and "<<fPRight<<" at "<<fPMiddle<<endl;

//initialize matrix
	mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	//(epsP,epsM,piP,piM,fPMiddle,fPMiddle,gP,gM);
// calculation of stationary state
	mat.calculateStationaryState(pStat);
	/*mat.rowReduce();	mat.GetColumn(numberOfStates-1,pStat);
	pStat[numberOfStates-1]=-1;	if(boundStatesOnly==1){pStat[0]=0;}	normalizeVec(numberOfStates,pStat);*/
	calculatePDeltaSigma(pStat, pDelta, pSigma);
// calculation of properties
	findAbsMaxPos((Np+Nm+1), pDelta, maxPos);
		if(maxPos==Nm){symMiddle=1;}else{symMiddle=0;}

// find phase transition
	if((symMiddle!=symLeft))	{fPRight=fPMiddle; }//symRight=symMiddle;}
	else						{fPLeft  =fPMiddle; symLeft  =symMiddle;}
// measure at latest zoom level
if(zoomLevel==zoomDepth)
{
	fIncrAct=fIncr/(2*zoomDepth);
	fileNames.itsSymThresOut<<(fPMiddle-fIncrAct/2)<<"   "<<epsP/piP<<endl;
	//cout<<"  fIncrAct  = "<<fIncrAct<<"  symmetry trans at f = "<<(fPMiddle-fIncrAct/2)<<endl;
}







