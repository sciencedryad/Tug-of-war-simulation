//================================================
//================================================
// transition rates
//================================================
//================================================

long double detachPlus(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus, const double& betaPlus, const double& betaMinus,
	const double& gPlus, const double& gMinus)
{
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	long double rate,exponent;
	//cout<<" detachPlus with "<<kp<<"  "<<km<<": ";
	if(kp==0) // no motor to detach
	{
		exponent = -1.0;
	}
	else if(km==0)
	{
		exponent =0.0;
	}
	else
/*
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
		if(Ftot>=0){exponent = FsPlus/FdPlus;}
		else	{exponent = FsMinus*km/FdPlus/kp;}
	}
*/
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
		double gammaP,gammaM;
			if(Ftot>=0)
			{
				if(betaMinus>=doubleZero)
				{
					gammaP=FsPlus/vPlus;
					gammaM=1/betaMinus;
					exponent = km/(kp*gammaP+km*gammaM) * (gammaM*FsPlus + gammaP*FsMinus) / FdPlus;
				}
				else
				{
					exponent = FsPlus/FdPlus;
				}
			}
			else
			{
				if(betaPlus>=doubleZero)
				{
					gammaM=FsMinus/vMinus;
					gammaP=1/betaPlus;
					exponent = km/(kp*gammaP+km*gammaM) * (gammaM*FsPlus + gammaP*FsMinus) / FdPlus;
				}
				else
				{
					exponent = FsMinus/FdPlus * km/kp;
				}
			}
	}
	//cout<<"exponent = "<<exponent<<endl;
	if(exponent<=-doubleZero){rate = 0.0;} 			// no motor to unbind
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
	const double& vPlus,const double& vMinus,const double& betaPlus, const double& betaMinus,
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
	}
	else if(kp==0)
	{
		exponent=0.0;
	}
	else
/*
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
		if(Ftot>=0){exponent = FsPlus*kp/FdMinus/km;}
		else	{exponent = FsMinus/FdMinus;}
	}
*/
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
		double gammaP,gammaM;
		if(Ftot>=0)
		{
				if(betaMinus>=doubleZero)
				{
					gammaP=FsPlus/vPlus;
					gammaM=1/betaMinus;
					exponent = kp/(kp*gammaP+km*gammaM) * (gammaM*FsPlus + gammaP*FsMinus) / FdMinus;
				}
				else
				{
					exponent = FsPlus*kp/km/FdMinus;
				}
		}
		else
		{
			if(betaPlus>=0.000000001)
			{
					gammaM=FsMinus/vMinus;
					gammaP=1/betaPlus;
					exponent = kp/(kp*gammaP+km*gammaM) * (gammaM*FsPlus + gammaP*FsMinus) / FdMinus;
			}
			else
			{
				exponent = FsMinus/FdMinus;
			}
		}
		//cout<<"exponent = "<<exponent<<endl;
	}

	//cout<<"kp = "<<kp<<", km = "<<km<<" detachMinus = "<<rate<<endl;
	if(exponent<=-doubleZero)			{rate=0;}
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
	const double& vPlus,const double& vMinus,const double& betaPlus, const double& betaMinus,
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
	const double& vPlus,const double& vMinus,const double& betaPlus, const double& betaus,
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
	const double& vPlus,const double& vMinus,const double& betaPlus, const double& betaMinus,
	const double& gPlus, const double& gMinus)
{
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	double v;
	if((kp==0)&&(km==0)) //unbound cargo
	{
		v = 0;
	}
	else
	{
		double FPlus = FsPlus*kp;
		double FMinus = FsMinus*km;
		double Ftot = FPlus-FMinus;
		if(Ftot>=0)// plus motors win
		{
			if(km==0)						{v = vPlus;}
			else if(betaMinus>=doubleZero)	{v = vPlus*Ftot/(FPlus+km*vPlus/betaMinus);}
			else							{v =0.;}
		}
		else//minus motors win
		{
			if(kp==0)						{v = -vMinus;}
			else if(betaPlus>=doubleZero) 	{v = vMinus*Ftot/(FMinus+kp*vMinus/betaPlus);}
			else							{v=0.;}
		}
	}
	return v;
}

//================================================
long double totalOutRate(const int& NpTot,const int& NmTot, const int& kp,const int& km,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& betaPlus,const double& betaMinus,
	const double& gPlus, const double& gMinus)
{
	//cout<<" totalOutRate with "<<kp<<"  "<<km<<"  "<<endl;;
	ASSERT(kp>=0); ASSERT(km>=0);ASSERT(kp<=NpTot);ASSERT(km<=NmTot);
	long double rate;
	rate =
attachPlus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus)
		+ attachMinus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus)
		+ detachPlus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus)
		+ detachMinus(NpTot,NmTot,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus);
	ASSERT(rate>=0);
	//cout<<"rate = "<<rate<<endl;
	return rate;
}

//================================================
int displayVelocities(const int& NpTot,const int& NmTot,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& FsPlus, const double& FsMinus, const double& FdPlus, const double& FdMinus,
	const double& vPlus,const double& vMinus,const double& betaPlus,const double& betaMinus,
	const double& gPlus, const double& gMinus)
{
	int kp,km;
	for(kp=0;kp<=NpTot;kp++){for(km=0;km<=NmTot;km++){
	cout<<kp<<"  "<<km<<": vel = "
		<<velocity(Np,Nm,kp,km,epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vMinus,vMinus,betaPlus,betaMinus,gPlus,gMinus)<<endl;
	}}
	return 0;
}//end displayVelocities
