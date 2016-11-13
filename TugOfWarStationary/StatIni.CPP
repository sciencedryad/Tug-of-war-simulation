//******************************************************************
// declare variables
//******************************************************************

time_t time1,time2;		//time measurement variables
double timeUsed=0;	//time difference

double epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,gP,gM;	// rates
double fP;

// stationary probabilities
double pStat[numberOfStates]; 	// stationary state vector, uses index numbering
double pDelta[Nm+Np+1];		// probability of del = n+ - n-, index offset byset=Nm, i.e. delind=del+Nm
const int deltaOffset=Nm;
double pSigma[Nm+Np+1];		// probability vector of sig = n+ + n-

// measurement variables
int numberOfExtrema,numberOfMaxima;
int numberOfExtremaOld,numberOfMaximaOld;
int specialTrans,specialTransOld,specialTransInd;
int foundPhaseExtremaTrans[maxFP][maxFP],foundPhaseMaximaTrans[maxFP][maxFP];
double sigmaAv;
int maxPos,maxPosLeft,maxPosMiddle;//,maxPosRight;
double fPOld,epsPOld;
int sym,symOld;
int sigmaAboveThres,sigmaAboveThresOld;;

// zoom in variables
int zoomLevel;
double fPMiddle,fPLeft,fPRight;
double epsPMiddle,epsPLeft,epsPRight;
double fIncrAct,epsIncrAct;
int nExtrMiddle,nExtrLeft;//nExtrRight;;
int nMaxMiddle,nMaxLeft;//nMaxRight;
int nPointMaxMiddle,nPointMaxLeft;//nMaxRight;
int symMiddle,symLeft;//,symRight;
int sigmaThresLeft,sigmaThresMiddle;//sigmaThresRight;
int specLeft,specMiddle;

//point measure variables
double pStatMatrix[Np+1][Nm+1];
STATES pointPos[Np+1][Nm+1];
//double val;
int numberOfPointMax,numberOfPointMaxOld,numberOfPointMaxInd;
int foundPointMaximaTrans[maxFP][maxFP];
int storeKp[maxFP],storeKm[maxFP];
//int storeMaxType;
int onBoundary,onDiagonal,inMiddle;
//point measure variables
//double pStatMatrixRenorm[renormNp][renormNm];
//STATES pointPosRenorm[renormNp][renormNm];
//int numberOfPointMaxRenorm,numberOfPointMaxOldRenorm,numberOfPointMaxIndRenorm;
//int foundPointMaximaRenormTrans[maxFP][maxFP];
//int storeKpRenorm[maxFP],storeKmRenorm[maxFP];
//double pStatDiagVec[numberOfStates];

int maxKp,maxKm;
int maximaPos[maxFP], maximaPosOld[maxFP],maximaPosMiddle[maxFP];
int maxLarger1Sym,maxLarger1SymOld;
int maxLarger1US,maxLarger1USOld;
int maxLarger1SymLeft,maxLarger1SymMiddle;//,maxLarger1SymRight;
int maxLarger1USLeft,maxLarger1USMiddle;//,maxLarger1USRight;

int bound,boundOld;
int boundLeft,boundMiddle;//,boundRight

// dummy variables
int del;//,delInd,sig;
int i,j,kp,km,ind;
//int iExtrEnd,jExtrEnd;
//int iMaxEnd,jMaxEnd;
int iPMaxEnd,jPMaxEnd;
int iPMaxEndRenorm,jPMaxEndRenorm;
//char filename[80];
double t,x,v,vAct;
double tReturn,tReturnWithoutPause,pDiag,meanPauseTime;

double tauPlus,tauMinus,tauPause,tSwitchPlusMinus,tSwitchMinusPlus;
double xPlus,xMinus,xSwitchPlusMinus,xSwitchMinusPlus;

double pL,pP,pR;
double omPR,omLP,omPL;

//******************************************************************
// rates setting
//******************************************************************
//epsP=0.1;
//fP=1.;
//piP=1.;
//gP=1.;
//epsM=epsP;
//fM=fP;
//piM=piP;
//gM=gP;

//******************************************************************
// initialize time measurement
//******************************************************************
time (&time1); // set time1 to current time (in sec since 1970)

//******************************************************************
// open out files
//******************************************************************
//MakeFileNames fileNames(2);
MakeFileNames fileNames(folderName);
fileNames.openPermanentFiles();
//cout<<fileNames.folder<<endl;

//******************************************************************
// initialize variables
//******************************************************************

for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
{
	foundPhaseExtremaTrans[i][j]=0;
	foundPhaseMaximaTrans[i][j]=0;
	foundPointMaximaTrans[i][j]=0;
	//foundPointMaximaRenormTrans[i][j]=0;
}}

findPointPos(Np+1,Nm+1,pointPos);
//for(i=0;i<=Np;i++){for(j=0;j<=Np;j++){	if(pointPos2[i][j]!=pointPos[i][j]){cout<<"ERROR in pointPos"<<endl;}}}

//findPointPos(renormNp,renormNm,pointPosRenorm);
//for(i=0;i<=renormNp;i++){for(j=0;j<=renormNp;j++){	if(pointPosRenorm2[i][j]!=pointPosRenorm[i][j]){cout<<"ERROR in pointPos"<<endl;}}}

//GammaClass gamma;
//cout<<"NumberOfDifferentGamma = "<<gamma.GetNumberOfDifferentGamma()<<endl;

//******************************************************************
// parameter output
//******************************************************************
cout<<"Rate parameters: epsStart = "<<epsStart<<", epsEnd = "<<epsEnd<<", fStart = "<< fStart<<", fEnd = "<< fEnd
	<<", epsIncr = "<<epsIncr<<", fIncr = "<<fIncr<<endl;
//cout<<"Parameters = "<<
cout<<"use balancing: ";
	if(useBalancing==1){cout<<"yes";}
	else {cout<<"no";}
cout<<", use discarding: ";
	if(useDiscardRates==1){cout<<"yes";}
	else {cout<<"no";}
cout<<", double limit = "<<doubleLimit;
cout<<", useSymmetry = ";
	if(useSymmetry==1){cout<<"yes";}
	else {cout<<"no";}
cout<<", boundStatesOnly = ";
	if(boundStatesOnly==1){cout<<"yes";}
	else {cout<<"no";}
cout<<", zoomIn = ";
	if(zoomIn==1){cout<<"yes";}
	else {cout<<"no";}
cout<<", specialDiagonal = ";
	if(specialDiagonal==1){cout<<"yes";}
	else {cout<<"no";}
cout<<endl;

//******************************************************************
// ASSERTs
//******************************************************************
ASSERT((zoomIn==1)||(zoomIn==0));
ASSERT((pointMeas==1)||(pointMeas==0));

