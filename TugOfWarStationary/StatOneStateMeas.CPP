//===================================================
// Measurements and outputs for one single phase space point: stationary state and its properties
//===================================================

//=========================================
// output of P(Delta)
//=========================================
fileNames.itsPDeltaOut.open(fileNames.itsPDelta);
	if(!fileNames.itsPDeltaOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
fileNames.itsPDeltaOut<<"# Delta   P(Delta)"<<endl;
for(del=-Nm;del<=Np;del++)
{
	fileNames.itsPDeltaOut<<del<<"   "<<pDelta[del+Nm]<<endl;
}
fileNames.itsPDeltaOut.close();

//=========================================
// output of P(n_p,n_m)
//=========================================
fileNames.itsPStatKpKmOut.open(fileNames.itsPStatKpKm);
	if(!fileNames.itsPStatKpKmOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
fileNames.itsPStatKpKmOut<<"# np   nm   P(np,nm)"<<endl;
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
{
	fileNames.itsPStatKpKmOut<<kp<<"  "<<km<<"  "<<pStatMatrix[kp][km]<<"  "<<endl;
}
fileNames.itsPStatKpKmOut<<endl;
}
fileNames.itsPStatKpKmOut.close();

//=========================================
// calculation and output of mean first return time to diagonal (Kac's formula, see Aldous & Fill p. 12 and 21)
// calculation and output of mean distance traveled between returns to diagonal\
// calculation of mean velocity
//=========================================
#include "StatMeanValCalc.CPP"

fileNames.itsMeanValuesOut.open(fileNames.itsMeanValues);
	if(!fileNames.itsMeanValuesOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
/*
fileNames.itsMeanValuesOut<<"# mean return time to diagonal with time on diagonal"<<"   ";
fileNames.itsMeanValuesOut<<"# mean return time to diagonal without time on diagonal"<<"   ";
fileNames.itsMeanValuesOut<<"# mean switching time  "<<"   ";
fileNames.itsMeanValuesOut<<"#  mean pause time"<<endl;
fileNames.itsMeanValuesOut<<"#  mean distance between two returns"<<"   ";
fileNames.itsMeanValuesOut<<"#  mean switching distance "<<endl;
fileNames.itsMeanValuesOut<<tReturn<<"   ";
fileNames.itsMeanValuesOut<<tReturnWithoutPause<<"   ";
fileNames.itsMeanValuesOut<<2*tReturnWithoutPause<<"   ";
fileNames.itsMeanValuesOut<<meanPauseTime<<endl;
fileNames.itsMeanValuesOut<<x<<"   ";
fileNames.itsMeanValuesOut<<2*x<<endl;
*/
fileNames.itsMeanValuesOut.close();


//=========================================
// calculation of mean velocity
//=========================================


//=========================================

//=========================================
// general output
//=========================================
if(generalOutput==1)
{
/*
	sprintf(fileNames.itsGeneralFile,"%s",generalFileName);
	fileNames.itsGeneralFileOut.open(fileNames.itsGeneralFile,ios_base::app);
		if(!fileNames.itsGeneralFileOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
	fileNames.itsGeneralFileOut<<Np<<"  "<<betaPlus<<"  "
		<<2*tReturnWithoutPause<<"   "
		<<2*x<<"  "
		<<v<<"   "
		<<mat.calculateEntropyProduction((Np+1)*(Nm+1),pStat)<<endl;
	fileNames.itsGeneralFileOut.close();
*/
}
