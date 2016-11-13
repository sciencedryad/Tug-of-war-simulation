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
	}
	else
	{
		epsPLeft=epsPOld;
		epsPRight=epsP;
		epsIncrAct=epsIncr;
	}
}

if(scanEps==1)
{
	fPMiddle = (fPLeft+fPRight)/2;
	fIncrAct=fIncrAct/2;
	mat.setRates(epsP,epsM,piP,piM,fPMiddle*FdP,fPMiddle*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
}
else
{
	epsPMiddle = (epsPLeft+epsPRight)/2;
	epsIncrAct=epsIncrAct/2;
	mat.setRates(epsPMiddle,epsFactor*epsPMiddle,piP,piM,fP*FdP,fP*FdP,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
}

//cout<<"   epsPLeft, Middle, Right = "<<zoomLevel<<": "<<epsPLeft<<", "<<epsPMiddle<<", "<<epsPRight<<endl;
// calculation of stationary state
	mat.calculateStationaryState(pStat);
	calculatePStatMat(Np+1, Nm+1,pStat, pStatMatrix);
// calculation of properties
	findMatrixMax(Np+1,Nm+1,pStatMatrix,numberOfPointMaxInd,storeKp,storeKm,onBoundary,onDiagonal,inMiddle,specialTransInd);
	nPointMaxMiddle=numberOfPointMaxInd;

// find phase transition
if(scanEps==1)
{
	if((nPointMaxMiddle!=nPointMaxLeft))	{fPRight=fPMiddle;}// nMaxRight=nMaxMiddle;}
	else								{fPLeft  =fPMiddle; nPointMaxLeft  =nPointMaxMiddle;}
	if(zoomLevel==zoomDepth)//measure at latest zoom level
	{
		fIncrAct=fIncrAct/2;
		fPMiddle=fPMiddle-fIncrAct;
		fileNames.itsPointMaximaOutfiles[numberOfPointMaxOld][numberOfPointMax]<<fPMiddle<<"   "<<epsP/piP<<endl;
	}
}
else
{
	if((nPointMaxMiddle!=nPointMaxLeft))	{epsPRight=epsPMiddle;}// nMaxRight=nMaxMiddle;}
	else								{epsPLeft  =epsPMiddle; nPointMaxLeft  =nPointMaxMiddle;}
	if(zoomLevel==zoomDepth)//measure at latest zoom level
	{
		epsIncrAct=epsIncrAct/2;
		epsPMiddle=epsPMiddle-epsIncrAct;
		fileNames.itsPointMaximaOutfiles[numberOfPointMaxOld][numberOfPointMax]<<fP<<"   "<<epsPMiddle/piP<<endl;
		//cout<<"  writing "<<epsPMiddle<<endl;
	}
}







