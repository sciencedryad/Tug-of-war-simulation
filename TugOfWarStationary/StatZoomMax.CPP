//****************************************************************
// ZOOM IN
//****************************************************************

if(zoomLevel==1)
{
	nMaxLeft=numberOfMaximaOld;
	if(scanEps==1)
	{
		fPLeft=fPOld;
		fPRight=fP;
		fIncrAct=fIncr;
		fPMiddle = (fPLeft+fPRight)/2;
		fIncrAct=fIncrAct/2;
		mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	}
	else
	{
		epsPLeft=epsPOld;
		epsPRight=epsP;
		epsIncrAct=epsIncr;
		epsPMiddle = (epsPLeft+epsPRight)/2;
		epsIncrAct=epsIncrAct/2;
		mat.setRates(epsPMiddle,epsFactor*epsPMiddle,piP,piM,fP*FdP,fP*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	}
}
// calculation of stationary state
	mat.calculateStationaryState(pStat);
	calculatePDeltaSigma(pStat, pDelta, pSigma);
// calculation of properties
	findLocalExtrema((Np+Nm+1), pDelta,nExtrMiddle,nMaxMiddle);

// find phase transition
if(scanEps==1)
{
	if((nMaxMiddle!=nMaxLeft))	{fPRight=fPMiddle;}// nMaxRight=nMaxMiddle;}
	else							{fPLeft  =fPMiddle; nMaxLeft  =nMaxMiddle;}
	if(zoomLevel==zoomDepth)//measure at latest zoom level
	{
		fIncrAct=fIncrAct/2;
		fPMiddle=fPMiddle-fIncrAct;
		fileNames.itsPhaseMaximaOutfiles[numberOfMaximaOld][numberOfMaxima]<<fPMiddle<<"   "<<epsP/piP<<endl;
	}
}
else
{
	if((nMaxMiddle!=nMaxLeft))	{epsPRight=epsPMiddle;}// nMaxRight=nMaxMiddle;}
	else								{epsPLeft  =epsPMiddle; nMaxLeft  =nMaxMiddle;}
	if(zoomLevel==zoomDepth)//measure at latest zoom level
	{
		epsIncrAct=epsIncrAct/2;
		epsPMiddle=epsPMiddle-epsIncrAct;
		fileNames.itsPhaseMaximaOutfiles[numberOfMaximaOld][numberOfMaxima]<<fP<<"   "<<epsPMiddle/piP<<endl;
	}
}








