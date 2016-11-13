class Rates
{
private:
	double itsAttachPlusMatrix[Np+1][Nm+1];
	double itsAttachMinusMatrix[Np+1][Nm+1];
	double itsDetachPlusMatrix[Np+1][Nm+1];
	double itsDetachMinusMatrix[Np+1][Nm+1];
	double itsTotalRate[Np+1][Nm+1];
	double itsVelocity[Np+1][Nm+1];
	int itsNumberOfDifferentVelocities;
	double itsOccuredVelocity[(Np+1)*(Nm+1)];
	int itsNp,itsNm;
public:
	Rates(){cout<<"Rates Default constructor"<<endl;}//end constructor
	Rates(const int& NpTot,const int& NmTot,
	const double& epsPlus, const double& epsMinus, const double& piPlus, const double& piMinus,
	const double& fPlus, const double& fMinus, const double& betaPlus, const double& betaMinus)
	{
		ASSERT(NpTot<=Np);ASSERT(NmTot<=Nm);
		cout<<"Rate constructor called"<<endl;
		initializeRates(NpTot,NmTot,epsPlus, epsMinus, piPlus,piMinus,FsPlus, FsMinus, FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus, gMinus);
		//cout<<"Rate constructor finished"<<endl;
	}//end constructor
	~Rates()
	{
		cout<<"Rate destructor"<<endl;
	}//end destructor
public:
	double GetAttachPlus(const int& kp, const int& km)const{return itsAttachPlusMatrix[kp][km];};
	double GetAttachMinus(const int& kp, const int& km)const{return itsAttachMinusMatrix[kp][km];};
	double GetDetachPlus(const int& kp, const int& km)const{return itsDetachPlusMatrix[kp][km];};
	double GetDetachMinus(const int& kp, const int& km)const{return itsDetachMinusMatrix[kp][km];};
	double GetTotalRate(const int& kp, const int& km)const{return itsTotalRate[kp][km];};
	double GetVelocity(const int& kp, const int& km)const{return itsVelocity[kp][km];};
	int GetNumberOfDifferentVelocities()const{return itsNumberOfDifferentVelocities;};
	double GetOccuredVelocity(const int& i){return itsOccuredVelocity[i];};
	void DisplayRates()const;
public:
	int initializeRates(const int& NpTot,const int& NmTot, const double& epsP, const double& epsM, const double& piP, const double& piM,
		const double& FsP, const double& FsM, const double& FdP, const double& FdM,
		const double& vP, const double& vM,const double& betaP,const double& betaM, const double& gP, const double& gM)
	{
		int kp,km;
		int i;
		//cout<<"InitializeRates called"<<endl;
		itsNp=NpTot;itsNm=NmTot;
		for(kp=0;kp<=NpTot;kp++)
		{
			for(km=0;km<=NmTot;km++)
			{
				itsVelocity[kp][km] = velocity(NpTot,NmTot,kp, km,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,
						vP,vM,betaP,betaM,gP,gM);
				itsAttachPlusMatrix[kp][km]=attachPlus(NpTot,NmTot,kp, km,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,
						vP,vM,betaP,betaM,gP,gM);
				itsAttachMinusMatrix[kp][km]=attachMinus(NpTot,NmTot,kp, km,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,
						vP,vM,betaP,betaM,gP,gM);
				itsDetachPlusMatrix[kp][km]=detachPlus(NpTot,NmTot,kp, km,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,
						vP,vM,betaP,betaM,gP,gM);
				itsDetachMinusMatrix[kp][km]	=detachMinus(NpTot,NmTot,kp, km,epsP,epsM,piP,piM,FsP,FsM,FdP,FdM,
						vP,vM,betaP,betaM,gP,gM);
				itsTotalRate[kp][km]=itsAttachPlusMatrix[kp][km]  + itsAttachMinusMatrix[kp][km]
					+itsDetachPlusMatrix[kp][km]+itsDetachMinusMatrix[kp][km];
			}
		}
		findDifferentVelocities();
		//cout<<"InitializeRates finished"<<endl;
		return 0;
	}//end initializeRates

	int findDifferentVelocities()
	{
		int kp,km,i;
		int occured;
		itsNumberOfDifferentVelocities = 0;
		for(i=0;i<(itsNp+1)*(itsNm+1);i++){itsOccuredVelocity[i]=0;}
		for(kp=0;kp<=itsNp;kp++)
		{
			for(km=0;km<=itsNm;km++)
			{
				occured=0;
				for(i=0;i<(itsNp+1)*(itsNm+1);i++)
				{
					if((itsVelocity[kp][km]>itsOccuredVelocity[i]-0.00001)&&(itsVelocity[kp][km]<itsOccuredVelocity[i]+0.00001))
						{occured=1;}
				}
				if(occured==0)
				{
					itsNumberOfDifferentVelocities = itsNumberOfDifferentVelocities + 1;
					itsOccuredVelocity[itsNumberOfDifferentVelocities] = itsVelocity[kp][km];
				}
			}
		}
		itsNumberOfDifferentVelocities = itsNumberOfDifferentVelocities + 1; // v = 0 is always value
		//for(i=0;i<(Np+1)*(Nm+1);i++){cout<<i<<"  "<<itsOccuredVelocity[i]<<endl;;}
		orderArray(itsNumberOfDifferentVelocities, itsOccuredVelocity);
		//for(i=0;i<(Np+1)*(Nm+1);i++){cout<<i<<"  "<<itsOccuredVelocity[i]<<endl;;}
		return 0;
	}//end findDifferentVelocities
};//end class Rates

// =====================================================

void Rates::DisplayRates()const
{
	int kp,km;
	cout<<"Np = "<<itsNp<<", Nm = "<<itsNm<<endl;
	cout<<"kp   km   attachPlus  attachMinus  detachPlus  detachMinus  totalRate  velocity"<<endl;
	cout.setf(ios::left); cout.setf(ios::showpoint|ios::fixed);
	for(kp=0;kp<=itsNp;kp++){for(km=0;km<=itsNm;km++)
	{
		cout<<kp<<"    "<<km<<"       "<<itsAttachPlusMatrix[kp][km]<<"           "<<itsAttachMinusMatrix[kp][km]
			<<"          "<<itsDetachPlusMatrix[kp][km]<<"            "<<itsDetachMinusMatrix[kp][km]
			<<"          "<<itsTotalRate[kp][km]<<"        "<<itsVelocity[kp][km]<<endl;
	}}
};//end DisplayRates

