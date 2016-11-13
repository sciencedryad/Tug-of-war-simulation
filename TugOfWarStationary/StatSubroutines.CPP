//================================================================

//int numberOfStates(const int& np, const int& nm) { return (np+1)*(nm+1); }

//================================================================
//long double abs(const long double& x)
//{
//	if(x<0){return -x;}
//	return x;
//}
//================================================================
long double xLnx(const long double& x)
// returns x*Ln(x) with correct limit x=0
{
	//cout.precision(8);cout.setf(ios_base::fixed, ios_base::floatfield);
	//cout<<"x = "<<x<<endl;
	if(x>0){return x*log(x);}
	else if (x<-0.0000001){cout<<"error in xLnx!! Negative argument!"<<endl;exit(8);}
	else {return 0.0;}
}
//================================================================

int index(const int& np, const int& nm)
// index for Master equation, state numbering
{
if(useSymmetry==0){return (nm*(Np + 1) + np);}
else
{
	ASSERT(Np==Nm);ASSERT(np>=nm);
	return ((nm*(2*Np+1-nm))/2 + np);
}
}

//================================================================

int nPlus(const int& ind)
// inverse function of index
{
if(useSymmetry==0){return (ind)%(Np+1);}
else
{
	//cout<<"symmetric index calculation: ";
	int np,j;
	ASSERT(Np==Nm);
	np = ind;
	for(j=0;j<=Np;j++)
	{
		if(np<=(Np-j)){np+=j;break;}
		np -= (Np+1-j) ;
	}
	return np;
}
}

//================================================================

int nMinus(const int& ind)
{
// inverse function of index
if(useSymmetry==0){return  ((ind  - nPlus(ind))/(Np + 1));}
else
{
	int nm,j;
	ASSERT(Np==Nm);
	nm = ind;
	for(j=0;j<=Nm;j++)
	{
		nm -= (Nm+1-j);
		if(nm<0){break;}
	}
	return j;
}
}

//================================================================

//int symmetricIndex(const int& ind)
//{
//return the index of the vertex that is symmetric to ind
//int np = nPlus(ind);
//int nm = nMinus(ind);
//return  index(nm,np);
//}


//================================================================

int normalizeVec(const int& length, double* vec)
// normalizes vector vec of length length to have unit norm=Sum_i vec[i]
{
	int i;
	double norm;
	norm = 0;
	for(i=0;i<length;i++)
	{
		norm = norm + vec[i];
	}
	//cout<<"norm = "<<norm<<endl;
	for(i=0;i<length;i++)
	{
		vec[i] = vec[i]/norm;
	}
	return 0;
}

//================================================================

int calculatePDeltaSigma(double* pStat, double* pDelta, double* pSigma)
// calculates pDelta and pSigma from pStat
{
	int del,sig;
	int delInd;//,sigmaInd;
	int ind;
	int ip,ipMin,ipMax;
	for(del=-Nm;del<=Np;del++)
	{
		delInd = del+Nm;
		pDelta[delInd]=0;
		ipMin=max(0,del);
		ipMax=min(Np,(Nm+del));
		for(ip=ipMin;ip<=ipMax;ip++)
		{
			if(useSymmetry==0)
			{
				ind =index(ip,ip-del);
				pDelta[delInd] += pStat[ind];
			}
			else
			{
				if(del>0){ind =index(ip,ip-del);pDelta[delInd] += pStat[ind]/2;}
				else if(del<0){ind =index(ip-del,ip);pDelta[delInd] += pStat[ind]/2;}
				else {ind =index(ip,ip-del);pDelta[delInd] += pStat[ind];}
			}
			//ind =indVec.GetIndex(ip,ip-del);
		}
	}
	for(sig=0;sig<=(Np+Nm);sig++)
	{
	pSigma[sig]=0;
	ipMin=max(0,sig-Nm);
	ipMax=min(Np,sig);
		for(ip=ipMin;ip<=ipMax;ip++)
		{
			if(useSymmetry==0)
			{
				ind=index(ip,sig-ip);
				pSigma[sig]+= pStat[ind];
			}
			else
			{
				if(2*ip>sig){ind=index(ip,sig-ip);pSigma[sig]+= pStat[ind]/2;}
				else if(2*ip<sig){ind=index(sig-ip,ip);pSigma[sig]+= pStat[ind]/2;}
				else {pSigma[sig]+= pStat[ind];}
			}
			//pSigma[sig]=pSigma[sig] + pStat[indVec.GetIndex(ip,sig-ip)];
		}
	}
	return 0;
}

//================================================================

int findLocalExtrema(const int& listlength, double* liste,
	int& numberOfExtrema,int& numberOfMaxima)
// finds extrema and maxima of list liste of length listlength
// extrema on boundary count
{
	int i;
	double valLeft,valRight,val;
	numberOfExtrema=2; // on boundary is always extremum
	numberOfMaxima=0;
	if(liste[0]>liste[1]){numberOfMaxima = numberOfMaxima + 1;}
	for(i=1;i<(listlength-1);i++)
	{
		valLeft=liste[i-1];
		val=liste[i];
		valRight=liste[i+1];
		if((val>valLeft)&&(val>valRight))
		{
			numberOfExtrema = numberOfExtrema + 1;
			numberOfMaxima = numberOfMaxima + 1;
		}
		if((val<valLeft)&&(val<valRight))
		{
			numberOfExtrema = numberOfExtrema + 1;
		}
	}
	if(liste[listlength-2]<liste[listlength-1]){numberOfMaxima = numberOfMaxima + 1;}

	return 0;
}
//================================================================

int findLocalExtremaPositions(const int& listlength, double* liste,
	int& numberOfExtrema,int& numberOfMaxima, int* maximaPos)
// finds extrema and maxima and their positions of list liste of length listlength
// extrema on boundary count
{
	int i;
	double valLeft,valRight,val;
	numberOfExtrema=2; // on boundary is always extremum
	numberOfMaxima=0;
	//cout<<"findMax, listlength "<<listlength<<endl;
	//for(i=0;i<listlength;i++){cout<<liste[i]<<"  ";}cout<<endl;
	if(liste[0]>=liste[1])
	{
		maximaPos[numberOfMaxima] = 0;
		//cout<<"found no "<<numberOfMaxima<<" val = "<<liste[0]<<"  at  "<<0<<endl;
		numberOfMaxima = numberOfMaxima + 1;
	}
	for(i=1;i<(listlength-1);i++)
	{
		valLeft=liste[i-1];
		val=liste[i];
		valRight=liste[i+1];
		if((val>significance*valLeft)&&(val>significance*valRight))
		{
			maximaPos[numberOfMaxima] = i;
			//cout<<"found no "<<numberOfMaxima<<" val = "<<val<<"  at  "<<i<<endl;
			numberOfExtrema = numberOfExtrema + 1;
			numberOfMaxima = numberOfMaxima + 1;
		}
		if((val*significance<valLeft)&&(val*significance<valRight))
		{
			numberOfExtrema = numberOfExtrema + 1;
		}
	}
	if(liste[listlength-2]<=liste[listlength-1])
	{
		maximaPos[numberOfMaxima] = listlength-1;
		//cout<<"found  no "<<numberOfMaxima<<" val = "<<liste[listlength-1]<<"  at  "<<listlength-1<<endl;
		numberOfMaxima = numberOfMaxima + 1;
	}
	//for(i=0;i<numberOfMaxima;i++){cout<<i<<"  "<<maximaPos[i]<<endl;}
	return 0;
}
//================================================================

int findAbsMaxPos(const int& listlength, double* liste,int& maxPos)
// finds position of absolute maximum of list liste of length listlength
{
	int i;
	double maxVal;
	maxPos=0;maxVal=liste[0];
	//cout<<"finsAbsMaxPos"<<endl;for(i=0;i<listlength;i++){cout<<liste[i]<<endl;}
	for(i=1;i<listlength;i++)
	{
		if(liste[i]>maxVal)
		{
			maxVal=liste[i];
			maxPos=i;
		}
	}
	return 0;
}

//================================================================

/*
int findAbsMax(const int& listlength, long double* liste,long double& max)
{
	int i;
	max=abs(liste[0]);
	//cout<<"finsAbsMaxPos"<<endl;for(i=0;i<listlength;i++){cout<<liste[i]<<endl;}
	for(i=1;i<listlength;i++)
	{
		if((abs(liste[i]))>(abs(max)))
		{
			max=liste[i];
		}
	}
	return 0;
}
*/
//================================================================

int findMax(const int& listlength, long double* liste,long double& max)
{
	int i;
	max=liste[0];
	//cout<<"finsAbsMaxPos"<<endl;for(i=0;i<listlength;i++){cout<<liste[i]<<endl;}
	for(i=1;i<listlength;i++)
	{
		if(liste[i]>max)
		{
			max=liste[i];
		}
	}
	return 0;
}

//================================================================

int calculateAverage(const int& listlength, double* liste, const int& indexOffset,double& average)
// calculate average of list liste of length listlength, using offset indexOffset: <i+indexOffset>
{
	int i;
	average=0;
	for(i=0;i<listlength;i++)
	{
		average = average + (i+indexOffset)*liste[i+indexOffset];
		//cout<<"i = "<<i<<", av = "<<average<<endl;
	}
	return 0;
}

//================================================================
//int findPhaseVal(const int& del, double** matrix, int& maxKp, int& maxKm)//, const int& xdim,const int& ydim, double matrix[ ][ydim], int& maxKp, int& maxKm)
//int findPhaseVal(const int& del,const int& xdim,const int& ydim, double matrix[ ][ydim], int& maxKp, int& maxKm)
int findPhaseVal(const int del,const int xdim,const int ydim, double matrix[ ][ydim], int& maxKp, int& maxKm)
// finds maxima positions maxKp,maxKm of all probabilities in matrix matrix[xdim][ydim] with given delta-value del = np-nm 
{
	int n,nStart,nEnd;
	int ind,maxI;
	double vec[Np+Nm+1];
	nStart=max(0,del);
	nEnd=min(Np,Np+del);
	//cout<<"find max for del = "<<del<<endl;
	ind =0;
	for(n=nStart;n<=nEnd;n++)
	{
		vec[ind]=matrix[n][n-del];
		//cout<<ind<<"  "<<vec[ind]<<endl;
		ind = ind+1;
	}
	findAbsMaxPos(nEnd-nStart+1, vec,maxI);
	//cout<<"length = "<<nEnd-nStart+1<<", maxI = "<<maxI<<endl;
	maxKp=maxI+max(0,del);
	maxKm=maxKp-del;
	return 0;
}

//================================================================
int calculatePStatMat(const int& xdim, const int& ydim,double* pstat, double pstatmat[][ydim])
// calculates stationary state matrix pstatmatrix from stationary state vector pstat
{
		int ind,kp,km;
		for(ind=0;ind<numberOfStates;ind++)
		{
			kp=nPlus(ind);km=nMinus(ind);
			pstatmat[kp][km]=pstat[ind];
			//cout<<"ind = "<<ind<<", pstat = "<<pstat[ind]<<", np, nm = "<<nPlus(ind)<<", "<<nMinus(ind)
			//	<<", pstat = "<<pstatmat[kp][km]<<endl;
		}
		if(useSymmetry==1)
		{
			for(km=0;km<ydim;km++){for(kp=0;kp<km;kp++)
			{
				if(kp!=km){pstatmat[kp][km] = pstatmat[km][kp];}}
			}
		}
	return 0;
}

//================================================================
int isDirectNeighbour(int& kp, int& km, int& kpComp, int& kmComp)
// returns 1 if kp,km is direct neighbour of kpComp,kmComp,
// returns 0 else
{
	//cout<<"test for direct neighbour: ";
	if((kp==kpComp)&&((km==kmComp-1)||(km==kmComp+1))){return 1;}
	else if ((km==kmComp)&&((kp==kpComp-1)||(kp==kpComp+1))){return 1;}
	else {return 0;}
}

//================================================================
int isNeighbour(int& kp, int& km, int& kpComp, int& kmComp)
// returns 1 if kp,km is (direct or diagonal) neighbour of kpComp,kmComp,
// returns 0 else
{
	if(((kp>=kpComp-1)&&(kp<=kpComp+1))&&((km>=kmComp-1)&&(km<=kmComp+1))){return 1;}
//	else if ((kp==kpComp)&&((km>=kmComp-1)||(km<=kmComp+1))){return 1;}
//	else if ((kp==kpComp-1)&&((km>=kmComp-1)||(km<=kmComp+1))){return 1;}
	else {return 0;}
}

//================================================================
int isDiagonalNeighbour(int& kp, int& km, int& kpComp, int& kmComp)
// returns 1 if kp,km is diagonal neighbour of kpComp,kmComp,
// returns 0 else
{
	if((kp==kpComp+1)&&((km==kmComp-1)||(km==kmComp+1))){return 1;}
	else if ((kp==kpComp-1)&&((km==kmComp-1)||(km==kmComp+1))){return 1;}
	else {return 0;}
}

//================================================================
int findMatrixMax(const int& xdim, const int& ydim,double matrix[][ydim],
	int& numberOfMax,int* storeMaxKp,int* storeMaxKm,
	int& onBoundary, int& onDiagonal, int& inMiddle, int& specialTrans)
// finds number of maxima of matrixrix matrix[xdim][ydim]
// stores number of Maxima in numberOfMax, and their positions in storeMaxKp[xdim], storeMaxKm[ydim]
// discards some maxima, see subroutine
// stores how many maxima are onBoundary, onDiagonal, inMiddle
{
	double val,valLeft,valRight,valTop,valDown,valTopLeft,valTopRight,valDownLeft,valDownRight;
	int kp,km,i;
	int newMax;
	//cout<<"mat: "<<endl;for(kp=0;kp<xdim;kp++){for(km=0;km<ydim;km++){cout<<matrix[kp][km]<<"  ";}cout<<endl;}//cout<<endl;
	numberOfMax=0;
	onDiagonal=0;
	onBoundary=0;
	inMiddle=0;
	specialTrans=0;
	for(kp=0;kp<xdim;kp++){for(km=0;km<ydim;km++)
	{
		//====================
		// calculate neighbour values
			val =matrix[kp][km];
			valDownLeft=-1;valDown=-1;valDownRight=-1;
			valLeft=-1;valRight=-1;
			valTopLeft=-1;valTop=-1;valTopRight=-1;
			if(kp-1>=0) //down
			{
				if(km-1>=0){	valDownLeft	=matrix[kp-1][km-1];}
							valDown		=matrix[kp-1][km];
				if(km+1<ydim){	valDownRight	=matrix[kp-1][km+1];}
			}
			if(km-1>=0){		valLeft		=matrix[kp][km-1];}
			if(km+1<ydim){		valRight		=matrix[kp][km+1];}
			if(kp+1<xdim)//top
			{
				if(km-1>=0){	valTopLeft	=matrix[kp+1][km-1];}
							valTop		=matrix[kp+1][km];
				if(km+1<ydim){	valTopRight	=matrix[kp+1][km+1];}
			}
			//cout<<"kp,km = "<<kp<<", "<<km<<", val = "<<val<<", neighbours: "<<endl;
			//cout<<"  "<<valDownLeft<<"  "<<valDown<<"  "<<valDownRight<<endl;
			//cout<<"  "<<valLeft      <<"  "<<val      <<"  "<<valRight       <<endl;
			//cout<<"  "<<valTopLeft<<"  "<<valTop<<"  "<<valTopRight<<endl;
		//====================
		newMax=0;
		if((special10==1)&&(((kp==1)&&(km==0))||((kp==0)&&(km==1)))) // special treatment of maxima at (1,0) and (0,1) (no comarison with diagonal)
		{
			if((val>=valLeft)&&(val>=valRight)&&(val>=valDown)&&(val>=valTop)) // test for maximum
			{
				newMax=1;
			}
		}
		else
		{
		if((val>=valLeft)&&(val>=valRight)&&(val>=valDown)&&(val>=valTop)
			&&(val>=valDownRight)&&(val>=valDownLeft)&&(val>=valTopRight)&&(val>=valTopLeft)) // test for maximum
		{
			newMax=1;
			if(specialDiagonal==1)// only store one maximum near diagonal if directly next to diagonal
			{
				if(km==kp-1)// if maximum near diagonal
				{
					for(i=0;i<numberOfMax;i++)
					{
						if ((storeMaxKm[i]==kp)&&(storeMaxKp[i]==km)){newMax=0;}
					}
					if(kp==1){specialTrans=1;}
				}
				else if(km==kp+1)// if maximum near diagonal
				{
					for(i=0;i<numberOfMax;i++)
					{
						if ((storeMaxKm[i]==kp)&&(storeMaxKp[i]==km)){newMax=0;}
					}
					if(kp==0){specialTrans=1;}
				}
			}
			if(discardSmallMaxima==1)
			{
				if(val<0.000000001){newMax=0;}
			}
		}//end if val...
		}//end else special10
		if(newMax==1)
		{
			//cout<<"found max at kp,km = "<<kp<<", "<<km<<" with val "<<val<<endl;
			storeMaxKp[numberOfMax]=kp;
			storeMaxKm[numberOfMax]=km;
			numberOfMax+=1;
			if(specialDiagonal==1)
			{
				if((kp==km)||(km==kp-1)||(km==kp+1))	{onDiagonal+=1;}
				else if((kp==0)||(km==0))			{onBoundary+=1;}
				else 							{inMiddle+=1;}
			}
			else
			{
				if(kp==km)				{onDiagonal+=1;}
				else if((kp==0)||(km==0))	{onBoundary+=1;}
				else 					{inMiddle+=1;}
			}
			if((kp==0)&&(km==0)){specialTrans=2;}
		}
	}}// end for kp,km
	//cout<<"found "<<numberOfMax<<" maxima!"<<endl;
	//for(kp=0;kp<numberOfMax;kp++)
	//{
	//	cout<<kp+1<<". max at "<<storeMaxKp[kp]<<", "<<storeMaxKm[kp]<<endl;
	//}
	//cout<<"  onDiagonal = "<<onDiagonal<<", onBoundary = "<<onBoundary<<", inMiddle = "<<inMiddle<<endl;
return 0;
}

//================================================================
int renormalizeMatrix(const int& xdim, const int& ydim, double matrix[][ydim],double matRenorm[][ydim/2])
{
	int i,j,kp,km;
	ASSERT(xdim%2==0);ASSERT(ydim%2==0);
	for(i=0;i<xdim/2;i++){for(j=0;j<ydim/2;j++)
	{
		kp=2*i;
		km=2*j;
		matRenorm[i][j] = matrix[kp][km]
			+ matrix[kp+1][km] + matrix[kp][km+1] + matrix[kp+1][km+1];
//		cout<<i<<"  "<<j<<": "<<kp<<"  "<<km<<"  "<<pStatMatrix[kp][km]<<"  "<<pStatMatrixRenorm[i][j]<<endl;
	}}
	return 0;
}

//================================================================
int findPointPos(const int& xdim,const int& ydim,STATES posMat[][ydim])
{
// gives position of point to each point of matrix
	int i,j;
for(i=0;i<=Np;i++){for(j=0;j<=Np;j++)
{
	//cout<<i<<"  "<<j<<": ";
	if		((i>0)&&(i<(xdim-1))&&(j>0)&&(j<(ydim-1))) 	{posMat[i][j]=Middle;}
	else if	((i>0)&&(i<(xdim-1))&&(j==0))				{posMat[i][j]=Left;}
	else if	((i==(xdim-1))&&(j>0)&&(j<(ydim-1)))		{posMat[i][j]=Up;}
	else if	((i>0)&&(i<(xdim-1))&&(j==(ydim-1)))		{posMat[i][j]=Right;}
	else if	((i==0)&&(j>0)&&(j<(ydim-1)))				{posMat[i][j]=Low;}
	else if	((i==0)&&(j==0))						{posMat[i][j]=LLCorner;}
	else if	((i==0)&&(j==(ydim-1)))					{posMat[i][j]=RLCorner;}
	else if	((i==(xdim-1))&&(j==0))					{posMat[i][j]=LUCorner;}
	else if	((i==(xdim-1))&&(j==(ydim-1)))			{posMat[i][j]=RUCorner;}
}}
	return 0;
}






