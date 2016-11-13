
//================================================
//================================================
// transition rates
//================================================
//================================================
long double lambdaFunc(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
//(const int& kp, const int& km)
{
	long double l;
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
//		if(Ftot>=0) // plus motors win, or stall
//		{
			//l=0.0;
//			l=1.0;
			//l = km/(kp+km);
			//l = FdMinus*km/(FsPlus*kp+FdMinus*km);
			//l=1.0;
//		}
//		else // minus motors win
//		{
			//l=0.0;
			//l=0.1;
//			l=1.0;
			//l = kp/(kp+km);
			//l = FdPlus*kp/(FdPlus*kp+FsMinus*km);
			//l=1.0;
//		}
	l = 1.0;
	l=lambda;
	return l;
}


//================================================

long double detachPlus(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
{
	//cout<<" detachPlus with "<<kp<<"  "<<km<<"  ";
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	long double rate,exponent;
	//cout<<" detachPlus with "<<kp<<"  "<<km<<": ";
	if(kp==0) // no motor to detach
	//((kp==0)&&(km==0)) //unbound cargo
	{
		//cout<<"  unbound"<<endl;
		exponent = -1.0;
	}
	else ///if (gamm==0)
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
		if(Ftot>=0) // plus motors win, or stall
		{
			//exponent = FsMinus/FdPlus*km/kp;
			//exponent = FsPlus*km/(kp+km)/FdPlus;
			//exponent = FsPlus*km*(FdMinus/vMinus)/((FsPlus/vPlus)*kp+(FdMinus/vMinus)*km)/FdPlus;
			exponent =
			(lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus)
			*kp*FsPlus
			+
			(1-lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus))
			*km*FsMinus)/kp/FdPlus;
		}
		else // minus motors win
		{
			//exponent = FsPlus/FdPlus;
			//exponent = FsMinus*km/(kp+km)/FdPlus;
			//exponent = FsMinus*km*(FdPlus/vPlus)/((FdPlus/vPlus)*kp+(FsMinus/vMinus)*km)/FdPlus;
			//exponent = ((1-lambda(kp,km))*kp*FsPlus + (lambda(kp,km))*km*FsMinus)/kp/FdPlus;
			exponent =
			((1-lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus))
			*kp*FsPlus
			+
			(lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus))
			*km*FsMinus)/kp/FdPlus;
		}
		//cout<<"exponent = "<<exponent<<endl;
	}
	if(exponent<0)			{rate = 0.0;} 			// no motor to unbind
	else if(exponent>100)	{rate = doubleLimit;}	// transition rate too large
	else 				{rate = kp*epsPlus*exp(exponent);}
	if((kp==1)&&(km==0))	{rate = bPlus*rate;}
	ASSERT(rate>=0);
	//cout<<"rate = "<<rate<<endl;
	return rate;
}

//================================================

long double detachMinus(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
{
	//cout<<" detachMinus with "<<kp<<"  "<<km<<"  ";
	//cout<<" rates: epsP = "<<epsPlus<<", epsMinus = "<<epsMinus
	//	<<", FsPlus = "<<FsPlus<<", FsMinus = "<<FsMinus
	//	<<", FdPlus = "<<FdPlus<<", FdMinus = "<<FdMinus<<endl;
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	long double rate,exponent;
	if(km==0) // no motor to detach
	//((kp==0)&&(km==0)) //unbound cargo
	{
		exponent=-1.0;
		//rate = 0;
	}
	else //if (gamm==0)
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
		if(Ftot>=0) // plus motors win, or stall
		{
			//exponent = FsMinus/FdMinus;
			//exponent = FsPlus*kp/(kp+km)/FdMinus;
			//exponent = FsPlus*kp*(FdMinus/vMinus)/((FsPlus/vPlus)*kp+(FdMinus/vMinus)*km)/FdMinus;
			//exponent = FsPlus*kp*(FdMinus/vMinus)/((FsPlus/vPlus)*kp+(FdMinus/vMinus)*km)/FdMinus;
			exponent = (lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus)
			*kp*FsPlus
			+
			(1-lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus))
			*km*FsMinus)/km/FdMinus;
		}
		else // minus motors win
		{
			//exponent = FsPlus/FdMinus*kp/km;
			//exponent = FsMinus*kp/(kp+km)/FdMinus;
			//exponent = FsMinus*kp*(FdPlus/vPlus)/((FdPlus/vPlus)*kp+(FsMinus/vMinus)*km)/FdMinus;
			//exponent = ((1-lambda(kp,km))*kp*FsPlus + (lambda(kp,km))*km*FsMinus)/km/FdMinus;
			exponent =
			((1-lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus))
			*kp*FsPlus
			+
			(lambdaFunc(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus))
			*km*FsMinus)/km/FdMinus;
		}
		//cout<<"exponent = "<<exponent<<endl;
	}
	//cout<<"kp = "<<kp<<", km = "<<km<<" detachMinus = "<<rate<<endl;
	if(exponent<0)			{rate=0;}
	else if(exponent>300)	{rate=doubleLimit;}//cout<<"ATTENTION! double limit reached!, exponent = "<<exponent<<endl;}
	else 				{rate = km*epsMinus*exp(exponent);}
	if((kp==0)&&(km==1))	{rate = bMinus*rate;}
	ASSERT(rate>=0);
	//cout<<"rate = "<<rate<<endl;
	return rate;
}

//================================================
long double attachPlus(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
{
	//cout<<" attachPlus with "<<kp<<"  "<<km<<"  ";
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	long double rate;
	if ((kp>0)||(km>0)){rate = piPlus*(NpTot-kp);}
	else {rate =  piPlus*NpTot*gPlus;}
	ASSERT(rate>=0);
	//cout<<"rate = "<<rate<<endl;
	return rate;
}
//================================================

long double attachMinus(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
{
	//cout<<" attachMinus with "<<kp<<"  "<<km<<"  ";
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	long double rate;
	if ((kp>0)||(km>0)) {rate =  piMinus*(NmTot-km);}
	else {rate = piMinus*NmTot*gMinus;}
	ASSERT(rate>=0);
	//cout<<"rate = "<<rate<<endl;
	return rate;
}

//================================================

long double velocity(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
// HAS NOT BEEN TESTED!!!!!
{
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	double v;
	if((kp==0)&&(km==0)) //unbound cargo
	{
		v = 0;
	}
	else if(velocChoice==loadSK)
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus - FMinus;
		double gamPlus=gamm*vPlus;
		double gamMinus=gamm*vMinus;
		if(Ftot>=0) // plus motors win, or stall
		{
			if((gamm==0))
			{
				if(FsPlus>0){v = vPlus*(1-FMinus/FPlus);}
				else
				{
					if(FMinus==0){v=vPlus;}
					else{v=0;}
				}
			}
			else{v = vPlus*Ftot/(FPlus+gamPlus);}
			ASSERT(v>=0);ASSERT(v<=vPlus);
		}
		else
		{
			if(gamm==0)
			{
				if(FsMinus>0){v = -vMinus*(1-FPlus/FMinus);}
				else
				{
					if(FPlus==0){v=-vMinus;}
					else{v=0;}
				}
			}
			else {v = vMinus*Ftot/(FMinus+gamMinus);}
			// attention: Ftot is negative!
			ASSERT(v<0);ASSERT(-v<=vMinus);
		}
	}
	else
	{
		ASSERT(velocChoice==blockRL);
		if((kp>0)&&(km>0)){v=0;}
		else if(km==0)
		{
			ASSERT(kp>0);
			if(gamm==0){v = vPlus;}
			else
			{
				double FPlus = FsPlus*kp;
				v = vPlus*(FPlus)/(FPlus+gamm*vPlus);
			}
		}
		else
		{
			ASSERT(kp==0);ASSERT(km>0);
			if(gamm==0){v = -vMinus;}
			else
			{
				double FMinus = FsMinus*km;
				v = -vMinus*(FMinus)/(FMinus+gamm*vMinus);
			}
		}
	}
	return v;
}

//================================================
long double totalOutRate(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
{
	//cout<<" totalOutRate with "<<kp<<"  "<<km<<"  "<<endl;;
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	long double rate;
	rate = attachPlus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus)
		+ attachMinus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus)
		+ detachPlus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus)
		+ detachMinus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,gamm,gPlus,gMinus);
	ASSERT(rate>=0);
	//cout<<"rate = "<<rate<<endl;
	return rate;
}

//================================================
int displayVelocities(const int& NpTot,const int& NmTot,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& gamm,
	const double& gPlus, const double& gMinus)
{
	int kp,km;
	for(kp=0;kp<=NpTot;kp++){for(km=0;km<=NmTot;km++){
	cout<<kp<<"  "<<km<<": vel = "
		<<velocity(Np,Nm,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vMinus,vMinus,gamm,gPlus,gMinus)<<endl;
	}}
	return 0;
}//end displayVelocities
