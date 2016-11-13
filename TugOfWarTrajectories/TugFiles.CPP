//****************************************************************
// FILE NAMES
//****************************************************************

class MakeFileNames
{
public:
// folder name
	//static char folder[80];
	char folder[80];
// general files
	static char parameterFile[80];
	static char paraFile[80];
	static char singleProbaTrajectoryFile[80];
	static char singleTrajectoryFile[80];
	static char pKpKmFile[80];
	static char pDistFile[80];
	static char pWaitingTimeFile[80];
	static char pVelocityFile[80];
	static char pWalkingTimeFile[80];
	static char pSwitchingTimeFile[80];
	static char pSwitchingTimeLogFile[80];
	static char pWalkingDistanceFile[80];
	static char pSwitchingDistanceFile[80];
	static char pSwitchingDistanceLogFile[80];
	static char pStatKpKmFile[80];
	static char pStatDelFile[80];
	static char pStatSigFile[80];
	char itsGnuPhaseDiag[80];
	ofstream itsGnuPhaseDiagOut;
	char itsMeans[80];
	ofstream itsMeansOut;
	char itsPara[80];
	ofstream itsParaOut;
	char itsParaDat[80];
	ofstream itsParaDatOut;
	char itsTrajectoryFiles[trajectoryNMax][80];
	ofstream itsTrajectoryOut[trajectoryNMax];
public:
	MakeFileNames(char* foldername)
	{
		sprintf(folder,"%s",foldername);
		//cout<<"MakeFileNames constructor called with folder "<<folder<<endl;
		//cout<<"folder = "<<folder<<endl;
	}
	~MakeFileNames()	{}//cout<<"MakeFileNames destructor called"<<endl;}

public:
	void makeNames()
	{
		int i;
		sprintf(parameterFile,"%s%s",folder,"Parameters.dat");
		sprintf(paraFile,"%s%s",folder,"Para.CPP");
		cout<<paraFile<<endl;
		sprintf(singleProbaTrajectoryFile,"%s%s",folder,"SingleProbTrajectory.dat");
		sprintf(singleTrajectoryFile,"%s%s",folder,"SingleTrajectory.dat");
		sprintf(pKpKmFile,"%s%s",folder,"ProbaKpKm.dat");
		sprintf(pDistFile,"%s%s",folder,"ProbaDist.dat");
		sprintf(pWaitingTimeFile,"%s%s",folder,"pWaitingTime.dat");
		sprintf(pVelocityFile,"%s%s",folder,"pVelocity.dat");
		sprintf(pWalkingTimeFile,"%s%s",folder,"pWalkingTime.dat");
		sprintf(pSwitchingTimeFile,"%s%s",folder,"pSwitchingTime.dat");
		sprintf(pSwitchingTimeLogFile,"%s%s",folder,"pSwitchingTimeLog.dat");
		sprintf(pWalkingDistanceFile,"%s%s",folder,"pWalkingDistance.dat");
		sprintf(pSwitchingDistanceFile,"%s%s",folder,"pSwitchingDistance.dat");
		sprintf(pSwitchingDistanceLogFile,"%s%s",folder,"pSwitchingDistanceLog.dat");
		sprintf(pStatKpKmFile,"%s%s",folder,"PStatKpKm.dat");
		sprintf(pStatDelFile,"%s%s",folder,"pStatDel.dat");
		sprintf(pStatSigFile,"%s%s",folder,"pStatSig.dat");
		for(i=0;i<trajectoryNMax;i++)
		{
			sprintf(itsTrajectoryFiles[i],"%s%s%i%s",folder,"Trajectory",i+1,".dat");
		}
	}
	void openPermanentFiles()
	{
		int i;
		if(writeAllTrajectories==1)
		{
			for(i=0;i<trajectoryNMax;i++){itsTrajectoryOut[i].open(itsTrajectoryFiles[i]);}
		}
	}
	void closePermanentFiles()
	{
		int i;
		if(writeAllTrajectories==1)
		{
			for(i=0;i<trajectoryNMax;i++){itsTrajectoryOut[i].close();}
		}
	}
	void openFinalFiles()
	{
		//cout<<"openFinalFiles called"<<endl;
		sprintf(itsGnuPhaseDiag,"%s%s",folder,"plotPhaseDiag.gnu");
		itsGnuPhaseDiagOut.open(itsGnuPhaseDiag);
			if(!itsGnuPhaseDiagOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		sprintf(itsPara,"%s%s",folder,"Parameters.dat");
		itsParaOut.open(itsPara);
			if(!itsParaOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		sprintf(itsParaDat,"%s%s",folder,"Para.dat");
		itsParaDatOut.open(itsParaDat);
			if(!itsParaDatOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		sprintf(itsMeans,"%s%s",folder,"Averages.dat");
		itsMeansOut.open(itsMeans);
			if(!itsMeansOut) {cout<<"Unable to open file! ";ASSERTperm(0);}

	}
	void closeFinalFiles()
	{
		itsGnuPhaseDiagOut.close();
		itsParaOut.close();
		itsParaDatOut.close();
		itsMeansOut.close();
	}
};//end class makeFiles
//char MakeFileNames::folder[80]="../Test2/";//"../TrajecN10MoveBlock2/";//"../RunLengthMeas/";//"../TrajN01US/";
char MakeFileNames::parameterFile[80]="Parameters.dat";
char MakeFileNames::paraFile[80]="Para.CPP";
char MakeFileNames::singleProbaTrajectoryFile[80]="SingleProbTrajectory.dat";
char MakeFileNames::singleTrajectoryFile[80]="SingleTrajectory.dat";
char MakeFileNames::pKpKmFile[80]="ProbaKpKm.dat";
char MakeFileNames::pDistFile[80]="ProbaDist.dat";
char MakeFileNames::pWaitingTimeFile[80]="pWaitingTime.dat";
char MakeFileNames::pVelocityFile[80]="pVelocity.dat";
char MakeFileNames::pWalkingTimeFile[80]="pWalkingTime.dat";
char MakeFileNames::pSwitchingTimeFile[80]="pSwitchingTime.dat";
char MakeFileNames::pSwitchingTimeLogFile[80]="pSwitchingTimeLog.dat";
char MakeFileNames::pWalkingDistanceFile[80]="pWalkingDistance.dat";
char MakeFileNames::pSwitchingDistanceFile[80]="pSwitchingDistance.dat";
char MakeFileNames::pSwitchingDistanceLogFile[80]="pSwitchingDistanceLog.dat";
char MakeFileNames::pStatKpKmFile[80]="PStatKpKm.dat";
char MakeFileNames::pStatDelFile[80]="PStatDel.dat";
char MakeFileNames::pStatSigFile[80]="PStatSig.dat";

