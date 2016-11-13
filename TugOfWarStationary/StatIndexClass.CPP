class IndexVec
{
private:
	int itsIndex[Np+1][Nm+1];
	int nPlus[numberOfStates];
	int nMinus[numberOfStates];
public:
	IndexVec()
	{
	int np,nm,ind;
	cout<<"IndexVec Constructor"<<endl;
	for(nm=0;nm<=Nm;nm++){for(np=0;np<=Np;np++)
	{
		if(useSymmetry==0){itsIndex[np][nm]=(nm*(Np + 1) + np);}
		else {if(np>=nm){itsIndex[np][nm] = ((nm*(2*Np+1-nm))/2 + np);}}
	}}
	DisplayIndex();
	}//end constructor
public:
	int GetIndex(const int& np, const int& nm)const{return itsIndex[np][nm];}
	void DisplayIndex()const
	{
		int np,nm;
		for(nm=0;nm<=Nm;nm++){for(np=0;np<=Np;np++)
		{
			cout<<", useSymmetry = ";
				if(useSymmetry==1){cout<<"yes";}
				else {cout<<"no";}cout<<endl;
			if(useSymmetry==0){cout<<"np,nm = "<<np<<","<<nm<<"=> ind = "<<itsIndex[np][nm]<<endl;}
			else {if(np>=nm){cout<<"np,nm = "<<np<<","<<nm<<"=> ind = "<<itsIndex[np][nm]<<endl;}}
		}}
	}
};//end class index

//IndexVec indVec;
