//****************************************************************
// ZOOM IN
//****************************************************************

if(zoomLevel==1)
{
	nPointMaxLeft=numberOfPointMaxOld;
	if(scanEps==1)
	{
		fPLeft=fPOld;
		fPRight=fP;
		fIncrAct=fIncr;
		fPMiddle = (fPLeft+fPRight)/2;
		fIncrAct=fIncrAct/2;
		mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);	}
	else
	{
		epsPLeft=epsPOld;
		epsPRight=epsP;
		epsIncrAct=epsIncr;
		epsPMiddle = (epsPLeft+epsPRight)/2;
		epsIncrAct=epsIncrAct/2;
		mat.setRates(epsPMiddle,epsFactor*epsPMiddle,piP,piM,fP*FdP,fP*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);	}
}

// calculation of stationary state
	mat.calculateStationaryState(pStat);
	calculatePStatMat(Np+1, Nm+1,pStat, pStatMatrix);
// calculation of properties
	findMatrixMax(Np+1,Nm+1,pStatMatrix,numberOfPointMaxInd,storeKp,storeKm,onBoundary,onDiagonal,inMiddle,specMiddle);

// find phase transition
if(scanEps==1)
{
	if(specMiddle!=specLeft)		{fPRight=fPMiddle;}// nMaxRight=nMaxMiddle;}
	else								{fPLeft  =fPMiddle; specLeft  =specMiddle;}
	if(zoomLevel==zoomDepth)//measure at latest zoom level
	{
		fIncrAct=fIncrAct/2;
		fPMiddle=fPMiddle-fIncrAct;
		fileNames.itsPointMaximaSpecialOut<<fPMiddle<<"   "<<epsP/piP<<endl;
	}
}
else
{
	if(specMiddle!=specLeft)		{epsPRight=epsPMiddle;}// nMaxRight=nMaxMiddle;}
	else								{epsPLeft  =epsPMiddle; specLeft  =specMiddle;}
	if(zoomLevel==zoomDepth)//measure at latest zoom level
	{
		epsIncrAct=epsIncrAct/2;
		epsPMiddle=epsPMiddle-epsIncrAct;
		fileNames.itsPointMaximaSpecialOut<<fP<<"   "<<epsPMiddle/piP<<endl;
	}
}








