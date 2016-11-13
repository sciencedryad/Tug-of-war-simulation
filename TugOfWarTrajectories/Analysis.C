//*******************************************************************
// libraries
//*******************************************************************
//#include<iostream.h>
//#include<fstream.h>
//#include<stdlib.h>
//#include<stdlib>
//#include<malloc.h>
//#include<math.h>

#include<iostream>
#include<fstream>
#include<time.h>
#include<cmath>
using namespace std;

//*******************************************************************
// debugging
//*******************************************************************
#define DEBUG
#include "Assert.CPP"

//*******************************************************************
// PARAMETER FILE
//*******************************************************************
#include "AnaPara.CPP"

//*******************************************************************
// MAIN PROGRAM
//*******************************************************************

int main()
{
//char folder[80]="../TugK013f2N20/";//"../Test/"; // will be read in from Para.CPP
char dataFile[80];

int kp,km;
int iTime,n;
double t,p;

double times[numberOfTimes];
double pKpKm[Np+1][Nm+1][numberOfTimes];
int Delta,sigma;

double pDelta[Np+Nm+1][numberOfTimes];
double pSigma[Np+Nm+1][numberOfTimes];

ofstream foutProb;

ASSERT(equilibrationTime<maxTime);

cout<<"Data analysis from folder "<<folder<<endl;


//*******************************************************************
// TIME DEPENDENT ANALYSIS
//*******************************************************************

// READ DATA FILE
cout<<"Time analysis"<<endl;
sprintf(dataFile,"%s%s",folder,"ProbaKpKm.dat");

ifstream finData(dataFile);
	if(!finData) {cout<<"Unable to open file! ";ASSERTperm(0);}

//for(iTime=0; iTime<numberOfTimes;iTime++)
//{
//	finData>>times[iTime];cout<<times[iTime];
//	for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
//	{
//		finData>>pKpKm[kp][km][iTime]; cout<<"  "<<pKpKm[kp][km][iTime];
//	}}// end for kp, for km
//	cout<<endl;
//}//end for i

for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
{
	for(iTime=0; iTime<numberOfTimes;iTime++)
	{
		finData>>times[iTime];
		//cout<<times[iTime];
		finData>>pKpKm[kp][km][iTime];
		//cout<<"  "<<pKpKm[kp][km][iTime]<<endl;;
	}//end for i
	//cout<<endl;
}}// end for kp, for km

finData.close();

char foutProbDeltaFile[80];
sprintf(foutProbDeltaFile,"%s%s",folder,"ProbaDelta.dat");

// INITIALIZE

for(iTime=0; iTime<numberOfTimes;iTime++)
{
	for(n=0;n<=Np+Nm;n++)
	{
		pDelta[n][iTime]=0;
		pSigma[n][iTime]=0;
	}//end for j
}//end for i

// CALCULATE
for(iTime=0; iTime<numberOfTimes;iTime++)
{
	for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
	{
		Delta = kp-km;
		sigma = kp+km;
		pDelta[Delta+Nm][iTime] = pDelta[Delta+Nm][iTime] + pKpKm[kp][km][iTime];
		pSigma[sigma][iTime] = pSigma[sigma][iTime] + pKpKm[kp][km][iTime];
	}}// end for kp, for km
}//end for i

// OUTPUT
foutProb.open(foutProbDeltaFile);
	if(!foutProb) {cout<<"Unable to open file! ";ASSERTperm(0);}

foutProb.setf(ios::left); foutProb.setf(ios::showpoint|ios::fixed);
for(n=0;n<=(Np+Nm);n++)
{
	for(iTime=0; iTime<numberOfTimes;iTime++)
	{
		foutProb.width(1); foutProb.precision(1);
		foutProb<<times[iTime];
		foutProb.width(3); foutProb.precision(3);
		foutProb<<"  "<<pDelta[n][iTime]<<endl;
	}//end for iTime
	foutProb<<endl;
}//end for n

foutProb.close();


//*******************************************************************
// STATIONARY STATE
//*******************************************************************
char foutProbDeltaStatFile[80];
char foutProbSigmaStatFile[80];
sprintf(foutProbDeltaStatFile,"%s%s",folder,"ProbaDeltaStat.dat");
sprintf(foutProbSigmaStatFile,"%s%s",folder,"ProbaSigmaStat.dat");

double timeInterval = maxTime/(1.0*numberOfTimes);
int itEq = int (equilibrationTime/timeInterval) ;

double pDeltaStat[Np+Nm+1];
double pSigmaStat[Np+Nm+1];

cout<<"Stationary state analysis"<<endl;
cout<<"total Time = "<<maxTime<<", equilibration Time = "<<equilibrationTime<<", itEq = "<<itEq
	<<", number of stationary time bins = "<<numberOfTimes-itEq<<endl;

for(n=0;n<=Nm+Np;n++)
{
	pDeltaStat[n]=0;
	pSigmaStat[n]=0;
}//end for n

for(iTime=itEq; iTime<numberOfTimes;iTime++)
{
	for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++)
	{
		Delta = kp - km;
		sigma = kp + km;
		pDeltaStat[Delta+Nm] = pDeltaStat[Delta+Nm] + pKpKm[kp][km][iTime];
		pSigmaStat[sigma] = pSigmaStat[sigma] + pKpKm[kp][km][iTime];
	}}// end for kp, for km
}//end for iTime

 foutProb.open(foutProbDeltaStatFile);
	if(!foutProb) {cout<<"Unable to open file! ";ASSERTperm(0);}
for(n=0;n<=Nm+Np;n++)
{
	pDeltaStat[n] = pDeltaStat[n]/(numberOfTimes-itEq);
	foutProb<<n-Nm<<"  "<<pDeltaStat[n]<<endl;
}//end for n
foutProb.close();

 foutProb.open(foutProbSigmaStatFile);
	if(!foutProb) {cout<<"Unable to open file! ";ASSERTperm(0);}
for(n=0;n<=Nm+Np;n++)
{
	pSigmaStat[n] = pSigmaStat[n]/(numberOfTimes-itEq);
	foutProb<<n<<"  "<<pSigmaStat[n]<<endl;
}//end for n
foutProb.close();

return 0;
}//end main
