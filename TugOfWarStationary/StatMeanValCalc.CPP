//=========================================
//cout<<"set switch states"<<endl;
mat.setSwitchStates(switchStatesChoice);

//=========================================
//=========================================
// calculation of switch times via sojourn times
// exact, but works only if the pausing state between the two moving states is disconnected
//=========================================
cout<<"======================================="<<endl;
cout<<"calculation of switch times via sojourn times in L,R,P"<<endl;
mat.calculateSwitchTimesViaSojournTimes(pStat,tauPause,tauPlus,tauMinus,tSwitchPlusMinus,tSwitchMinusPlus,
xPlus,xMinus,xSwitchPlusMinus,xSwitchMinusPlus);

	cout.precision(4);
	cout<<"single plus run time = tauL = "<<tauPlus<<", distance = "<<xPlus<<endl;
	cout<<"single minus run time = tauR = "<<tauMinus<<", distance = "<<xMinus<<endl;
	cout<<"pause time = tauP = "<<tauPause<<endl;
	cout<<"long L run time = switch time L->R = tauL = "<<tSwitchPlusMinus<<", distance = "<<xSwitchPlusMinus<<endl;
	cout<<"long R run time = switch time R->L = tauR = "<<tSwitchMinusPlus<<", distance = "<<xSwitchMinusPlus<<endl;

//=========================================
// calculation of switch time via collapse of target state + matrix Inversion
// always only approximate redsult, but works in any case
//=========================================
/*
cout<<"======================================="<<endl;

cout<<"calculation of switch time via collapse + matrix Inversion"<<endl;
mat.calculateSwitchTimesViaInversion(pStat,tSwitchMinusPlus);
cout<<"long R run time = switch time R->L = tauR = "<<tSwitchMinusPlus<<endl;

*/
//=========================================
// calculation and output of mean first return time to diagonal (Kac's formula, see Aldous & Fill p. 12 and 21)
// calculation and output of mean distance traveled between returns to diagonal
// calculation of mean velocity
// only works of the pausing state is the diagonal!!!!!
//=========================================
/*
cout<<"======================================="<<endl;
cout<<"calculation of switching time via Kac's formula"<<endl;
pDiag=0;
tReturn=0;
meanPauseTime=0;
j=min(Np,Nm);

for(kp=0;kp<=j;kp++)
{
	pDiag+=pStatMatrix[kp][kp];
	tReturn+=pStatMatrix[kp][kp]*totalOutRate(Np,Nm,kp,kp,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	//meanPauseTime+=pStatMatrix[kp][kp]/totalOutRate(Np,Nm,kp,kp,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
	meanPauseTime+=pStatMatrix[kp][kp]*totalOutRate(Np,Nm,kp,kp,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM);
}
tReturn = (1.0/tReturn);
//meanPauseTime/=pDiag;
meanPauseTime=pDiag/meanPauseTime;

tReturnWithoutPause = tReturn - meanPauseTime;
//displayVelocities(Np,Nm,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,gamm,gP,gM);
x=0;
v=0;
t=tReturn;
//sum=(1-pDiag)/2;
for(kp=0;kp<=Np;kp++){for(km=0;km<=Nm;km++){
	vAct=velocity(Np,Nm,kp,km,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,vP,vM,betaPlus,betaMinus,gP,gM)*pStatMatrix[kp][km];
	v+=fabs(vAct);
	x+=fabs(vAct)*t;
}}

cout<<" proba of zero vel state "<<pDiag<<endl;
cout<<"# mean return time to diagonal with time on diagonal = "<<tReturn<<endl;
cout<<"# mean return time to diagonal without time on diagonal = "<<tReturnWithoutPause<<endl;
cout<<"# mean switching time with pause = "<<2*tReturn<<endl;
cout<<"# mean switching time without pause = "<<2*tReturnWithoutPause+meanPauseTime<<endl;
cout<<"#  mean pause time = "<<meanPauseTime<<endl;
cout<<endl;
//x/=sum;
//cout<<"mean distance between two returns = "<<x<<"  x2 -> "<<2*x<<endl;
cout<<"======================================="<<endl;
*/
//================================================


