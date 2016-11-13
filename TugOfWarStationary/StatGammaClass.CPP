class GammaClass
{
private:
	int itsNumberOfDifferentGamma;
	int itsGammaIndex[Np+1][Nm+1];
public:
	GammaClass(){calculateDifferentGamma();}
	~GammaClass(){}
public:
	int GetNumberOfDifferentGamma()const{return itsNumberOfDifferentGamma;}
private:
	void calculateDifferentGamma()
	{
		int i,j,gamInd;
		itsNumberOfDifferentGamma=2;
		gamInd=0;
		cout<<itsNumberOfDifferentGamma<<endl;
		for(i=1;i<=Np;i++){for(j=1;j<=Nm;j++)
		{
			if((i%j==0)&&(j!=1))
			{}
			else if ((j%i==0)&&(i!=1))
			{}
			else
			{
				
				itsNumberOfDifferentGamma = itsNumberOfDifferentGamma + 1;
			}
			//cout<<i<<"  "<<j<<": numGam = "<<itsNumberOfDifferentGamma<<endl;
		}}
		//cout<<"Np*Nm+2 = "<<Np*Nm+2<<endl;
	}

};//end class


