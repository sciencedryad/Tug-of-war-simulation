//****************************************************************
// ZOOM IN
//****************************************************************

if(zoomLevel==1)
{
	fPLeft=fPOld;
	fPRight=fP;
	boundLeft=boundOld;
	//boundRight=bound;
}
fPMiddle = (fPLeft+fPRight)/2;
//cout<<"  Zoom level "<<zoomLevel<<" at eps = "<<epsP<<" between f = "<<fPLeft<<" and "<<fPRight<<" at "<<fPMiddle<<endl;
//cout<<"    left "<<maxLarger1SymLeft<<", right "<<maxLarger1SymRight<<endl;
//initialize matrix
	mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	//(epsP,epsM,piP,piM,fPMiddle,fPMiddle,gP,gM);
// calculation of stationary state
	mat.calculateStationaryState(pStat);
	/*mat.rowReduce();mat.GetColumn(numberOfStates-1,pStat);pStat[numberOfStates-1]=-1;if(boundStatesOnly==1){pStat[0]=0;}
	normalizeVec(numberOfStates,pStat);*/
	calculatePDeltaSigma(pStat, pDelta, pSigma);
// calculation of properties
	for(ind=0;ind<numberOfStates;ind++){pStatMatrix[nPlus(ind)][nMinus(ind)]=pStat[ind];}
	if(pStatMatrix[0][0]>pStatMatrix[1][1]){boundMiddle=0;}else{boundMiddle=1;}

// find phase transition
	if((boundMiddle!=boundLeft))	{fPRight=fPMiddle;}//boundRight=boundMiddle;}
	else						{fPLeft  =fPMiddle; boundLeft  =boundMiddle;}
// measure at latest zoom level
if(zoomLevel==zoomDepth)
{
	fIncrAct=fIncr/(2*zoomDepth);
	fileNames.itsBoundOut<<(fPMiddle-fIncrAct/2)<<"   "<<epsP<<endl;
	//cout<<"  fIncrAct  = "<<fIncrAct<<"  symmetry trans at f = "<<(fPMiddle-fIncrAct/2)<<endl;
}







