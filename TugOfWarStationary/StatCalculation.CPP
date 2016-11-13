	//========================================================
	// calculation
	//========================================================
	epsM=epsFactor*epsP;
	FsP=fP*FdM;
	FsM=fFactor*FsP;
	// kinesin like rates for minus direction(!)
		if(useKinesinRates==1){epsM = 1;piM = 5;FdM = 3; FsM = 6;}
	//cout<<endl;
	//cout<<"eps = "<<epsP<<", f = "<<fP<<": "<<endl;
	//cout<<"eps = "<<epsP<<", f = "<<fP<<":  ";
	//initialize matrix
		mat.setRates(epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
		//mat.DisplayMatrix();
		mat.calculateStationaryState(pStat);
		cout.precision(3);cout.setf(ios_base::fixed, ios_base::floatfield);
		//cout<<"  pStat ";for(ind=0;ind<numberOfStates;ind++){cout<<pStat[ind]<<"  ";}cout<<endl;
		calculatePDeltaSigma(pStat, pDelta, pSigma);
		calculatePStatMat(Np+1, Nm+1,pStat, pStatMatrix);
		//cout<<"pStatMat = "<<endl;for(i=0;i<Np+1;i++){for(j=0;j<Nm+1;j++){cout<<pStatMatrix[i][j]<<" ";}cout<<endl;}
		//cout<<"  pDelta ";for(ind=0;ind<=(Np+Nm);ind++){cout<<pDelta[ind]<<"  ";}cout<<endl;
	// calculation of properties
		//findLocalExtrema((Np+Nm+1), pDelta,numberOfExtrema,numberOfMaxima);
		findLocalExtremaPositions((Np+Nm+1), pDelta,numberOfExtrema,numberOfMaxima,maximaPos);
		//cout<<"  numberOfExtrema = "<<numberOfExtrema<<", numberOfMax = "<<numberOfMaxima<<endl;
		//cout<<"  max Positions at delta = ";for(i=0;i<numberOfMaxima;i++){cout<<maximaPos[i]-Nm<<" ";} cout<<endl;
		//cout<<epsP<<"  "<<fP<<"  "<<numberOfMaxima<<endl;
		if(measureBifDiag==1)
		{
			fileNames.itsBifDiagOut<<epsP<<"   "<<fP;
			for(i=0;i<numberOfMaxima;i++)
			{
			fileNames.itsBifDiagOut<<"  "<<maximaPos[i]-Nm;
			}
			fileNames.itsBifDiagOut<<endl;
		}
		findAbsMaxPos((Np+Nm+1), pDelta, maxPos);
			if(maxPos==Nm){sym=1;}else{sym=0;}
		calculateAverage((Np+Nm+1),pSigma,0,sigmaAv);
			if(sigmaAv>sigmaThres){sigmaAboveThres=1;}else{sigmaAboveThres=0;}
		//cout<<"  NumberOfExtrema = "<<numberOfExtrema<<"  NumberOfMaxima = "<<numberOfMaxima<<", sym = "<<sym<<endl;
		//for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){cout<<pStatMatrix[kp][km]<<"  ";}cout<<endl;}cout<<endl;
		maxLarger1Sym=0;maxLarger1US=0;
		for(i=0;i<numberOfMaxima;i++)
		{
			findPhaseVal(maximaPos[i]-Nm,Np+1,Nm+1,pStatMatrix,maxKp,maxKm);
			//findPhaseVal(maximaPos[i]-Nm,pStatMatrix,maxKp,maxKm);
			//cout<<"  del = "<<maximaPos[i]-Nm<<", kp = "<<maxKp<<", km = "<<maxKm;//<<endl;
			if((maxKp>=FPLargerVal)||(maxKm>=FPLargerVal)){if(maximaPos[i]==Nm){maxLarger1Sym=1;}else {maxLarger1US=1;}}
		}
		//cout<<"  max Positions at delta = ";for(i=0;i<numberOfMaxima;i++){cout<<maximaPos[i]-Nm<<" ";}
		//cout<<", larger 1? sym "<<maxLarger1Sym<<", US "<<maxLarger1US;//<<endl;
		if((pStatMatrix[0][0]>pStatMatrix[1][1])||(pStatMatrix[0][0]>pStatMatrix[0][1])||(pStatMatrix[0][0]>pStatMatrix[1][0])){bound=0;}
			else{bound=1;}
		//if(pStatMatrix[0][0]>=0.5){bound=0;}else{bound=1;}
		//if(pStatMatrix[0][0]>pStatMatrix[1][1]){bound=0;}else{bound=1;}
		//cout<<", bound = "<<bound<<endl;
		if(pointMeas==1)
		{
			fileNames.itsPointMaxLocationOut<<fP<<"   "<<epsP/piP<<"  "<<numberOfPointMaxInd
					<<"  "<<onDiagonal<<"  "<<onBoundary<<"  "<<inMiddle<<endl;
			findMatrixMax(Np+1,Nm+1,pStatMatrix,numberOfPointMaxInd,storeKp,storeKm,onBoundary,onDiagonal,inMiddle,specialTrans);
			numberOfPointMax=numberOfPointMaxInd;
			#include "StatMeanValCalc.CPP"
			fileNames.itsMeanValOut<<fP<<"   "<<epsP/piP
			<<"  "<<t<<"  "<<v
			<<"  "<<mat.calculateEntropyProduction((Np+1)*(Nm+1),pStat)<<endl;
		}
	//========================================================
	// find point maxima phase transition
	//========================================================
		if(numberOfPointMax!=numberOfPointMaxOld)
		{
			//cout<<"eps = "<<epsP<<", f = "<<fP<<": "<<endl;
			//cout<<"pointMaxChange"<<endl;
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			//if(fP>(fPOld+0.0000001))
			{
				foundPointMaximaTrans[numberOfPointMaxOld][numberOfPointMax]=1;
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomPoint.CPP"
					}
				}
				else
				{
					fileNames.itsPointMaximaOutfiles[numberOfPointMaxOld][numberOfPointMax]<<fP-fIncr/2<<"   "<<epsP/piP<<endl;
				}
			}
			numberOfPointMaxOld=numberOfPointMax;
		}
	//========================================================
	// find special point phase transition
	//========================================================
		if(specialTrans!=specialTransOld)
		{
			//cout<<"pointMaxChange"<<endl;
//			if(fP>(fPOld+0.0000001))
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			{
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomPointSpecial.CPP"
					}
				}
				else
				{
					fileNames.itsPointMaximaSpecialOut<<fP-fIncr/2<<"   "<<epsP/piP<<endl;
				}
			}
			specialTransOld=specialTrans;
		}
	//========================================================
	// find point maxima phase transition for renormalized matrix
	//========================================================
		//if(renormalize==1)
		//{
		//if(numberOfPointMaxRenorm!=numberOfPointMaxOldRenorm)
		//{
		//	if(fP>(fPOld+0.0000001))
		//	{
		//		foundPointMaximaRenormTrans[numberOfPointMaxOldRenorm][numberOfPointMaxRenorm]=1;
		//		fileNames.itsPointMaximaRenormOutfiles[numberOfPointMaxOldRenorm][numberOfPointMaxRenorm]<<fP-fIncr/2<<"   "<<epsP<<endl;
		//	}
		//	numberOfPointMaxOldRenorm=numberOfPointMaxRenorm;
		//}
		//}
	//========================================================
	// find fixed point phase transition
	//========================================================
/*
		if((numberOfExtrema!=numberOfExtremaOld))
		{
			//cout<<"Phase transition (extrema) from "<<numberOfExtremaOld<<" to "<<numberOfExtrema<<" found at "<<fP<<"   "<<epsP<<endl;
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
//			if(fP>(fPOld+0.0000001))
			{
				foundPhaseExtremaTrans[numberOfExtremaOld][numberOfExtrema]=1;
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomExtr.CPP"
					}
				}
				else
				{
					fileNames.itsPhaseExtremaOutfiles[numberOfExtremaOld][numberOfExtrema]<<fP-fIncr/2<<"   "<<epsP<<endl;
				}
			}
			numberOfExtremaOld=numberOfExtrema;
		}
*/
		if(numberOfMaxima!=numberOfMaximaOld)
		{
//				cout<<"Phase transition (maxima) found at "<<fP<<"   "<<epsP<<endl;
//			if(fP>fPOld+0.00001)
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			{
				foundPhaseMaximaTrans[numberOfMaximaOld][numberOfMaxima]=1;
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomMax.CPP"
					}
				}
				else
				{
				fileNames.itsPhaseMaximaOutfiles[numberOfMaximaOld][numberOfMaxima]<<fP-fIncr/2<<"   "<<epsP/piP<<endl;
				}
//				cout<<"Phase transition (maxima) found at "<<fP<<"   "<<epsP<<endl;
			}
			numberOfMaximaOld=numberOfMaxima;
			for(i=0;i<numberOfMaxima;i++)
			{
				findPhaseVal(maximaPos[i]-deltaOffset,Np+1,Nm+1,pStatMatrix,maxKp,maxKm);
				//findPhaseVal(maximaPos[i]-deltaOffset,pStatMatrix,maxKp,maxKm);
				//if((maxKp==0)||(maxKm==0)){maxLarger1Old[i]=0;}else{maxLarger1Old[i]=1;}
				if(deltaMeas==1){maximaPosOld[i]=maximaPos[i];}
			}
		}
		//else // no maxima number change
		//{
		//========================================================
		// find delta phase transition
		//========================================================
		if(deltaMeas==1)
		{
		for(i=0;i<numberOfMaxima;i++)
		{
			if(maximaPos[i]!=maximaPosOld[i])
			{
//				if(fP>fPOld+0.00001)
				if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
				{
					if(zoomIn==1)
					{
						for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
						{
						#include "StatZoomDelta.CPP"
						}
					}
					else
					{
						fileNames.itsDeltaChangeOut<<fP-fIncr/2<<"   "<<epsP/piP<<endl;
					}
				}
				maximaPosOld[i]=maximaPos[i];
			}
		}
		}// end if(deltaMeas==1)
		//}//end else of if(numberOfMaxima!=numberOfMaximaOld)

	//========================================================
	// find transition to FP larger 1
	//========================================================
/*
		if(maxLarger1Sym!=maxLarger1SymOld)
		{
			//if(fP>(fPOld+0.0000001))
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			{
				//cout<<"SymFP passes 1,1"<<endl;
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomFPLarger1Sym.CPP"
					}
				}
				else
				{
					fileNames.itsFPLarger1SymOut<<(fP-fIncr/2)<<"   "<<epsP<<endl;
				}
			}
			maxLarger1SymOld=maxLarger1Sym;
		}
		if(maxLarger1US!=maxLarger1USOld)
		{
			//if(fP>(fPOld+0.0000001))
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			{
				//cout<<"USFP passes 1,1"<<endl;
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomFPLarger1US.CPP"
					}
				}
				else
				{
					fileNames.itsFPLarger1USOut<<(fP-fIncr/2)<<"   "<<epsP<<endl;
				}
			}
			maxLarger1USOld=maxLarger1US;
		}
*/
	//========================================================
	// find binding transition
	//========================================================
/*
	if(bound!=boundOld)
	{
			//if(fP>(fPOld+0.0000001))
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			{
				//cout<<"USFP passes 1,1"<<endl;
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomBound.CPP"
					}
				}
				else
				{
					fileNames.itsBoundOut<<(fP-fIncr/2)<<"   "<<epsP<<endl;
				}
			}
			boundOld=bound;
	}
*/
	//========================================================
	// find symmetry transition
	//========================================================
		if(sym!=symOld)
		{
//			if(fP>(fPOld+0.0000001))
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			{
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomSym.CPP"
					}
				}
				else
				{
					fileNames.itsSymThresOut<<(fP-fIncr/2)<<"   "<<epsP/piP<<endl;
				}
			}
			symOld=sym;
		}
	//========================================================
	// find sigmaThreshold
	//========================================================
/*
		if(sigmaAboveThres!=sigmaAboveThresOld)
		{
			//if(fP>(fPOld+0.0000001))
			if(((scanEps==1)&&(fP>(fPOld+0.0000001)))||((scanEps==0)&&(epsP>(epsPOld+0.0000001))))
			{
				if(zoomIn==1)
				{
					for(zoomLevel=1;zoomLevel<=zoomDepth;zoomLevel++)
					{
					#include "StatZoomSigmaThres.CPP"
					}
				}
				else
				{
					fileNames.itsSigmaThresOut<<(fP-fIncr/2)<<"   "<<epsP<<endl;
				}
			}
			sigmaAboveThresOld=sigmaAboveThres;
		}
*/
//========================================================
