//****************************************************************
// FILE NAMES
//****************************************************************

class MakeFileNames
{
public:
	//static char folder[80]; // folder name
	char folder[80];
	char itsParaFile[80];
	char itsParaDat[80];
	char itsGeneralFile[80]; // general file to be opened by many simulations!
//phase Boundary files
//	char itsPhaseExtrema[maxFP][maxFP][80];
	char itsPhaseMaxima[maxFP][maxFP][80];
	char itsPointMaxima[maxFP][maxFP][80];
	char itsPointMaximaSpecial[80];
//	char itsPointMaximaRenorm[maxFP][maxFP][80];
//	char itsFoundPhaseExtremaTrans[80];
	char itsFoundPhaseMaximaTrans[80];
	char itsFoundPointMaximaTrans[80];
//	char itsFoundPointMaximaRenormTrans[80];
	char itsPointMaxLocation[80];
	char itsGnuPhaseDiag[80];
	char itsGnuPointPhaseDiag[80];
//	char itsSigmaThres[80];
	char itsSymThres[80];
//	char itsFPLarger1Sym[80];
//	char itsFPLarger1US[80];
//	char itsBound[80];
	//char itsPointProp[80];
	char itsBifDiag[80];
	char itsDeltaChange[80];
	char itsPDelta[80];
	char itsPSigma[80];
	char itsPStatKpKm[80];
	char itsMeanValues[80];
	char itsMeanVal[80];
	ofstream itsParaFileOut;
	ofstream itsParaDatOut;
	ofstream itsGeneralFileOut;
//	ofstream itsPhaseExtremaOutfiles[maxFP][maxFP];
	ofstream itsPhaseMaximaOutfiles[maxFP][maxFP];
	ofstream itsPointMaximaOutfiles[maxFP][maxFP];
	ofstream itsPointMaximaSpecialOut;
//	ofstream itsPointMaximaRenormOutfiles[maxFP][maxFP];
//	ofstream itsFoundPhaseExtremaTransOut;
	ofstream itsFoundPhaseMaximaTransOut;
	ofstream itsFoundPointMaximaTransOut;
//	ofstream itsFoundPointMaximaRenormTransOut;
	ofstream itsPointMaxLocationOut;
	ofstream itsGnuPhaseDiagOut;
	ofstream itsGnuPointPhaseDiagOut;
//	ofstream itsSigmaThresOut;
	ofstream itsSymThresOut;
//	ofstream itsFPLarger1SymOut;
//	ofstream itsFPLarger1USOut;
//	ofstream itsBoundOut;
	//ofstream itsPointPropOut;
	ofstream itsBifDiagOut;
	ofstream itsDeltaChangeOut;
	ofstream itsPDeltaOut;
	ofstream itsPSigmaOut;
	ofstream itsPStatKpKmOut;
	ofstream itsMeanValuesOut;
	ofstream itsMeanValOut;
public:
	MakeFileNames(){cout<<"MakeFileNames constructor called "<<endl;}
	MakeFileNames(char* foldername)
	{
		sprintf(folder,"%s",foldername);
		cout<<"MakeFileNames constructor called with folder "<<folder<<endl;
		//cout<<"folder = "<<folder<<endl;
	}
	~MakeFileNames()	{cout<<"MakeFileNames destructor called"<<endl;}
public: //subroutines
	void openPermanentFiles()
	{
		int iniFP,finFP;
		for(iniFP=0;iniFP<maxFP;iniFP++){for(finFP=0;finFP<maxFP;finFP++)
		{
//			sprintf(itsPhaseExtrema[iniFP][finFP],"%s%s%i%s%i%s",folder,"PhaseExtremaFP",iniFP,"to",finFP,".dat");
			sprintf(itsPhaseMaxima[iniFP][finFP],"%s%s%i%s%i%s",folder,"PhaseMaximaFP",iniFP,"to",finFP,".dat");
			sprintf(itsPointMaxima[iniFP][finFP],"%s%s%i%s%i%s",folder,"PointMaximaFP",iniFP,"to",finFP,".dat");
			//sprintf(itsPointMaximaRenorm[iniFP][finFP],"%s%s%i%s%i%s",folder,"PointMaximaRenormFP",iniFP,"to",finFP,".dat");
//			itsPhaseExtremaOutfiles[iniFP][finFP].open(itsPhaseExtrema[iniFP][finFP]);
//				if(!itsPhaseExtremaOutfiles[iniFP][finFP]) {cout<<"Unable to open file! ";ASSERTperm(0);}
			itsPhaseMaximaOutfiles[iniFP][finFP].open(itsPhaseMaxima[iniFP][finFP]);
				if(!itsPhaseMaximaOutfiles[iniFP][finFP]) {cout<<"Unable to open file! ";ASSERTperm(0);}
			itsPointMaximaOutfiles[iniFP][finFP].open(itsPointMaxima[iniFP][finFP]);
				if(!itsPointMaximaOutfiles[iniFP][finFP]) {cout<<"Unable to open file! ";ASSERTperm(0);}
			//itsPointMaximaRenormOutfiles[iniFP][finFP].open(itsPointMaximaRenorm[iniFP][finFP]);
			//	if(!itsPointMaximaRenormOutfiles[iniFP][finFP]) {cout<<"Unable to open file! ";ASSERTperm(0);}
//			itsPhaseExtremaOutfiles[iniFP][finFP]<<"# Phase boundaries where number of fixed points (extrema) changes from "
//				<<iniFP<<" to "<<finFP<<endl<<"# f          eps"<<endl;
			itsPhaseMaximaOutfiles[iniFP][finFP]<<"# Phase boundaries where number of fixed points (maxima) changes from "
				<<iniFP<<" to "<<finFP<<endl
				<<"# f          eps"<<endl;
			itsPointMaximaOutfiles[iniFP][finFP]<<"# Phase boundaries where number of maxima points of pStatMatrix changes from "
				<<iniFP<<" to "<<finFP<<endl
				<<"# f          eps"<<endl;
			//itsPointMaximaRenormOutfiles[iniFP][finFP]<<"# Phase boundaries where number of maxima points of pStatMatrixRenorm changes from "
			//	<<iniFP<<" to "<<finFP<<endl
			//	<<"# f          eps"<<endl;
		}}
		sprintf(itsPointMaximaSpecial,"%s%s",folder,"PointMaximaSpecial.dat");
		itsPointMaximaSpecialOut.open(itsPointMaximaSpecial);
			if(!itsPointMaximaSpecialOut){cout<<"Unable to open file! ";ASSERTperm(0);}
		itsPointMaximaSpecialOut<<"# Phase boundaries where number of maxima points of pStatMatrix changes from "
				<<" (1,1) to (1,0)"<<endl
				<<"# f          eps"<<endl;
		sprintf(itsPointMaxLocation,"%s%s",folder,"PointMaxLoc.dat");
		itsPointMaxLocationOut.open(itsPointMaxLocation);
			if(!itsPointMaxLocationOut){cout<<"Unable to open file! ";ASSERTperm(0);}
		itsPointMaxLocationOut<<"#Location of point max"<<endl
		//	<<"#=1 on boundary, =2 on boundary and diagonal, =3 on diagonal, =4 neither on diagonal nor on boundary"<<endl;
		<<"# eps  f   numberOfMax   numberOnDiag   numberOnBoundary  numberInMiddle"<<endl;
//		sprintf(itsSigmaThres,"%s%s",folder,"sigmaThreshold.dat");
//		itsSigmaThresOut.open(itsSigmaThres);
//			if(!itsSigmaThresOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
//		itsSigmaThresOut<<"# Boundary where <sigma> = <n+ + n-> passes threshold "<<sigmaThres<<endl<<"# f          eps"<<endl;
		sprintf(itsSymThres,"%s%s",folder,"symmetryChange.dat");
		itsSymThresOut.open(itsSymThres);
			if(!itsSymThresOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		itsSymThresOut<<"# Boundary where symmetric fixed point is no longer absolute probability maximum "<<endl<<"# f          eps"<<endl;
//		sprintf(itsFPLarger1Sym,"%s%s",folder,"FPLarger1Sym.dat");
//		itsFPLarger1SymOut.open(itsFPLarger1Sym);
//			if(!itsFPLarger1SymOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
//		itsFPLarger1SymOut<<"# Boundary where symmetric fixed point passes 1,1 "<<endl<<"# f          eps"<<endl;
//		sprintf(itsFPLarger1US,"%s%s",folder,"FPLarger1US.dat");
//		itsFPLarger1USOut.open(itsFPLarger1US);
//			if(!itsFPLarger1USOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
//		itsFPLarger1USOut<<"# Boundary where unsymmetric fixed point passes 1,1 "<<endl<<"# f          eps"<<endl;
//		sprintf(itsBound,"%s%s",folder,"BoundOrNot.dat");
//		itsBoundOut.open(itsBound);
//			if(!itsBoundOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
//		itsBoundOut<<"# Boundary where pStat(0,0)=p(1,1)"<<endl<<"# f          eps"<<endl;
		//sprintf(itsPointProp,"%s%s",folder,"PointProperties.dat");
		//itsPointPropOut.open(itsPointProp);
		//	if(!itsPointPropOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		sprintf(itsBifDiag,"%s%s",folder,"BifurcationDiag.dat");
		itsBifDiagOut.open(itsBifDiag);
			if(!itsBifDiagOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		sprintf(itsDeltaChange,"%s%s",folder,"DeltaChange.dat");
		itsDeltaChangeOut.open(itsDeltaChange);
			if(!itsDeltaChangeOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		itsDeltaChangeOut<<"# boundary where maximum delta changes value"<<endl<<"# f          eps      delta   |delta|"<<endl;
		sprintf(itsPDelta,"%s%s",folder,"pDeltaStat.dat");
		sprintf(itsPSigma,"%s%s",folder,"pSigmaStat.dat");
		sprintf(itsPStatKpKm,"%s%s",folder,"pStatKpKm.dat");
		sprintf(itsMeanValues,"%s%s",folder,"meanValuesSingle.dat");
		sprintf(itsMeanVal,"%s%s",folder,"meanVal.dat");
		itsMeanValOut.open(itsMeanVal);
			if(!itsMeanValOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
			itsMeanValOut<<"# f  K  t(switch)  v(av)    sigma (entropy production)"<<endl;
	}
	void closePermanentFiles()
	{
		int iniFP,finFP;
		for(iniFP=0;iniFP<maxFP;iniFP++){for(finFP=0;finFP<maxFP;finFP++)
		{
//			itsPhaseExtremaOutfiles[iniFP][finFP].close();
			itsPhaseMaximaOutfiles[iniFP][finFP].close();
			itsPointMaximaOutfiles[iniFP][finFP].close();
			//itsPointMaximaRenormOutfiles[iniFP][finFP].close();
		}}
		itsPointMaximaSpecialOut.close();
		itsPointMaxLocationOut.close();
//		itsSigmaThresOut.close();
		itsSymThresOut.close();
//		itsFPLarger1SymOut.close();
//		itsFPLarger1USOut.close();
//		itsBoundOut.close();
		//itsPointPropOut.close();
		itsBifDiagOut.close();
		itsDeltaChangeOut.close();
		//remove(itsFoundPhaseExtremaTrans);
		itsMeanValOut.close();
	}
	void openFinalFiles()
	{
		sprintf(itsParaFile,"%s%s",folder,"Parameters.dat");
		sprintf(itsParaDat,"%s%s",folder,"Para.dat");
//		sprintf(itsFoundPhaseExtremaTrans,"%s%s",folder,"FoundExtremaPhaseTrans.dat");
		sprintf(itsFoundPhaseMaximaTrans,"%s%s",folder,"FoundMaximaPhaseTrans.dat");
		sprintf(itsFoundPointMaximaTrans,"%s%s",folder,"FoundPointMaxPhaseTrans.dat");
		//sprintf(itsFoundPointMaximaRenormTrans,"%s%s",folder,"FoundPointMaxRenormPhaseTrans.dat");
		sprintf(itsGnuPhaseDiag,"%s%s",folder,"plotPhaseDiag.gnu");
		sprintf(itsGnuPointPhaseDiag,"%s%s",folder,"plotPointPhaseDiag.gnu");
		itsParaFileOut.open(itsParaFile);
			if(!itsParaFileOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		itsParaDatOut.open(itsParaDat);
			if(!itsParaDatOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
//		itsFoundPhaseExtremaTransOut.open(itsFoundPhaseExtremaTrans);
//			if(!itsFoundPhaseExtremaTransOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		itsFoundPhaseMaximaTransOut.open( itsFoundPhaseMaximaTrans);
			if(!itsFoundPhaseMaximaTransOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		itsFoundPointMaximaTransOut.open(itsFoundPointMaximaTrans);
			if(!itsFoundPointMaximaTransOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		//itsFoundPointMaximaRenormTransOut.open( itsFoundPointMaximaRenormTrans);
		//	if(!itsFoundPointMaximaRenormTransOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		itsGnuPhaseDiagOut.open(itsGnuPhaseDiag);
			if(!itsGnuPhaseDiagOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
		itsGnuPointPhaseDiagOut.open(itsGnuPointPhaseDiag);
			if(!itsGnuPointPhaseDiagOut) {cout<<"Unable to open file! ";ASSERTperm(0);}
	}
	void closeFinalFiles()
	{
		itsParaFileOut.close();
		itsParaDatOut.close();
//		itsFoundPhaseExtremaTransOut.close();
		itsFoundPhaseMaximaTransOut.close();
		itsFoundPointMaximaTransOut.close();
		//itsFoundPointMaximaRenormTransOut.close();
		itsGnuPhaseDiagOut.close();
		itsGnuPointPhaseDiagOut.close();
	}
};//end class makeFiles
//char MakeFileNames::folder[80]="../Test/";
//char MakeFileNames::folder[80]="../Test/";//"../PhaseDiagN05c/";//"../PhaseDiagSkew/";//"../RunLengthMeas/";//"../PhaseDiagN10b2/";//"../Trajec N05";//"../PhaseDiagN10b/";//"../PhaseDiagSkew/";//"../PhaseDiagN10Bif/";
//char MakeFileNames::folder[80]="../PhaseDiagN10/";


