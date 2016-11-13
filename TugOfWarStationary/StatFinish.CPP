//******************************************************************
// TIME MEASUREMENT
//******************************************************************
time (&time2); // set time2 to current time (in sec since 1970)
timeUsed = difftime(time2,time1);

//******************************************************************
// OUTPUT
//******************************************************************
fileNames.openFinalFiles();

// found phase transitions
//fileNames.itsFoundPhaseExtremaTransOut<<"# found phase transitions(extrema) from  "<<endl
//	<<"FP to FP  number"<<endl;
fileNames.itsFoundPhaseMaximaTransOut<<"# found phase transitions(maxima) from  "<<endl
	<<"FP to FP  number"<<endl;
fileNames.itsFoundPointMaximaTransOut<<"# found point max phase transitions from  "<<endl
	<<"max to max  number"<<endl;
//fileNames.itsFoundPointMaximaRenormTransOut<<"# found point max phase transitions renormalized from  "<<endl
//	<<"max to max  number"<<endl;
cout<<"found phase transition from FP "<<endl<<"ini    to    fin"<<endl;
//for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
//{
//	if (foundPhaseExtremaTrans[i][j]==1)
//	{
//		fileNames.itsFoundPhaseExtremaTransOut<<i<<"      "<<j<<endl;
//		//iExtrEnd=i;jExtrEnd=j;
//		cout<<"ext: "<<i<<"      "<<j<<endl;
//	}
//	else {remove(fileNames.itsPhaseExtrema[i][j]);}
//}}
for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
{
	if (foundPhaseMaximaTrans[i][j]==1)
	{
		fileNames.itsFoundPhaseMaximaTransOut<<i<<"      "<<j<<endl;
		//iMaxEnd=i;jMaxEnd=j;
		cout<<"max: "<<i<<"      "<<j<<endl;
	}
	else {remove(fileNames.itsPhaseMaxima[i][j]);}
}}
for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
{
	if (foundPointMaximaTrans[i][j]==1)
	{
		fileNames.itsFoundPointMaximaTransOut<<i<<"      "<<j<<endl;
		iPMaxEnd=i;jPMaxEnd=j;
		cout<<"pma: "<<i<<"      "<<j<<endl;
	}
	else {remove(fileNames.itsPointMaxima[i][j]);}
}}
//for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
//{
//	if (foundPointMaximaRenormTrans[i][j]==1)
//	{
//		fileNames.itsFoundPointMaximaRenormTransOut<<i<<"      "<<j<<endl;
//		iPMaxEndRenorm=i;jPMaxEndRenorm=j;
//		cout<<"ren: "<<i<<"      "<<j<<endl;
//	}
//	else {remove(fileNames.itsPointMaximaRenorm[i][j]);}
//}}

//cout<<"IPMAxEnd "<<iPMaxEnd<<"  "<<jPMaxEnd<<endl;
//=========================================
//gnufile
//=========================================
fileNames. itsGnuPointPhaseDiagOut<<"reset"<<endl<<endl
	<<"#set terminal postscript enhanced color"<<endl
	<<"#set output \"PhaseDiagN"<<Np<<".eps\""<<endl
	<<"set terminal x11"<<endl<<endl
	<<"set title \"N = "<<Np<<"\""<<endl
	<<"set xlabel \"f\""<<endl<<"set ylabel \"K\""<<endl<<endl;

fileNames. itsGnuPointPhaseDiagOut<<"plot[0:][0:]\\"<<endl;
for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
{
	//cout<<i<<"  "<<j<<"foundPOintMaximaTrans = "<<foundPointMaximaTrans[i][j]<<endl;
	if (foundPointMaximaTrans[i][j]==1)
	{
	//	if((i==iPMaxEnd)&&(j==jPMaxEnd))
	//	{fileNames. itsGnuPointPhaseDiagOut<<"\"PointMaximaFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"point max "<<i<<" to "<<j<<"\" w p"<<endl;}
	//	else
		{fileNames. itsGnuPointPhaseDiagOut<<"\"PointMaximaFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"point max "<<i<<" to "<<j<<"\" w p,\\"<<endl;}
	}
}}
fileNames.itsGnuPointPhaseDiagOut<<"\"PointMaximaSpecial.dat\" u 1:2 t \"special trans\" w p"<<endl;
fileNames. itsGnuPointPhaseDiagOut<<endl;

//fileNames. itsGnuPointPhaseDiagOut<<"#plot[0:][0:]\\"<<endl;
//for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
//{
//	//cout<<i<<"  "<<j<<"foundPOintMaximaTrans = "<<foundPointMaximaTrans[i][j]<<endl;
//	if (foundPointMaximaRenormTrans[i][j]==1)
//	{
//		if((i==iPMaxEndRenorm)&&(j==jPMaxEndRenorm))
//		{fileNames. itsGnuPointPhaseDiagOut<<"\"PointMaximaRenormFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"point max ren "<<i<<" to "<<j<<"\" w p"<<endl;}
//		else
//		{fileNames. itsGnuPointPhaseDiagOut<<"\"PointMaximaRenormFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"point max ren "<<i<<" to "<<j<<"\" w p,\\"<<endl;}
//	}
//}}
fileNames. itsGnuPointPhaseDiagOut<<endl;

fileNames. itsGnuPhaseDiagOut<<"reset"<<endl<<endl
	<<"#set terminal postscript enhanced color"<<endl
	<<"#set output \"PhaseDiagN"<<Np<<".eps\""<<endl
	<<"set terminal x11"<<endl<<endl
	<<"set title \"N = "<<Np<<"\""<<endl
	<<"set xlabel \"f\""<<endl<<"set ylabel \"K\""<<endl<<endl;

fileNames. itsGnuPhaseDiagOut<<"plot[0:][0:]\\"<<endl;
for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
{
	if (foundPhaseMaximaTrans[i][j]==1)
	{
		{fileNames. itsGnuPhaseDiagOut<<"\"PhaseMaximaFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"FPmax "<<i<<" to "<<j<<"\" w p,\\"<<endl;}
	}
}}
fileNames. itsGnuPhaseDiagOut<<"\"\" not w p ps 0"<<endl<<endl;

fileNames. itsGnuPhaseDiagOut<<"#plot[0:][0:]\\"<<endl;
//for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
//{
//	if (foundPhaseExtremaTrans[i][j]==1)
//	{
		//if((i==iExtrEnd)&&(j==jExtrEnd))
		//{fileNames. itsGnuPhaseDiagOut<<"\"PhaseExtremaFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"FPext "<<i<<" to "<<j<<"\" w p"<<endl;}
		//else
//		{fileNames. itsGnuPhaseDiagOut<<"\"PhaseExtremaFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"FPext "<<i<<" to "<<j<<"\" w p,\\"<<endl;}
//	}
//}}
//fileNames. itsGnuPhaseDiagOut<<endl<<"# ";
for(i=0;i<maxFP;i++){for(j=0;j<maxFP;j++)
{
	if (foundPhaseMaximaTrans[i][j]==1)
	{
		//if((i==iMaxEnd)&&(j==jMaxEnd))
		//{fileNames. itsGnuPhaseDiagOut<<"\"PhaseMaximaFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"FPmax "<<i<<" to "<<j<<"\" w p"<<endl;}
		//else
		{fileNames. itsGnuPhaseDiagOut<<"\"PhaseMaximaFP"<<i<<"to"<<j<<".dat\" u 1:2 t \"FPmax "<<i<<" to "<<j<<"\" w l,\\"<<endl;}
	}
}}
fileNames. itsGnuPhaseDiagOut<<"\"symmetryChange.dat\" u 1:2 t \"Symmetry change\" w l"<<endl;

//fileNames. itsGnuPhaseDiagOut<<endl<<"# plot\\"<<endl
//	<<"\"FPLarger1Sym.dat\" u 1:2 t \"Sym FP passes "<<FPLargerVal<<" \" w p,\\"<<endl
//	<<"\"FPLarger1US.dat\"   u 1:2 t \"Unsym FP passes "<<FPLargerVal<<"\" w p"<<endl;


fileNames. itsGnuPhaseDiagOut<<endl<<"# plot\\"<<endl
	<<"\"symmetryChange.dat\" u 1:2 t \"Symmetry change\" w lp,\\"<<endl;
//	<<"\"sigmaThreshold.dat\" u 1:2 t \"<sig>="<<sigmaThres<<"\" w lp"<<endl;

// PARAMETER output
fileNames.itsParaFileOut<<"Parameters of tug of war simulation in folder "<<fileNames.folder<<endl;
fileNames.itsParaFileOut<<"Np = "<<Np<<", Nm = "<<Nm<<endl;
fileNames.itsParaFileOut<<"epsP = "<<epsPlus<<", epsM = "<<epsMinus<<", piP = "<<piPlus<<", piM = "<<piMinus
	<<" => KP = "<<epsPlus/piMinus<<",  KM = "<<epsMinus/piMinus<<endl;
fileNames.itsParaFileOut<<"FsP = "<<FsPlus<<", FsM = "<<FsMinus<<", FdP = "<<FdPlus<<", FdM = "<<FdMinus
	<<" => fP = "<<FsPlus/FdMinus<<", fM = "<<FsMinus/FdPlus<<endl;
fileNames.itsParaFileOut<<"gPlus = "<<gPlus<<", gMinus = "<<gMinus<<endl;
fileNames.itsParaFileOut<<"vP = "<<vPlus<<"vM ="<<vMinus<<", velocityModel = ";
	if(velocChoice==loadSK){fileNames.itsParaFileOut<<"loadSK";}
	else if(velocChoice==blockRL){fileNames.itsParaFileOut<<"blockRL";}
	else {fileNames.itsParaFileOut<<"undefined";}
	fileNames.itsParaFileOut<<", betaPlus = "<<betaPlus<<", betaMinus = "<<betaMinus<<endl;
fileNames.itsParaFileOut<<"epsFactor = "<<epsFactor<<", fFactor = "<<fFactor<<endl;
if(zoomIn==1){fileNames.itsParaFileOut<<"zoomDepth  = "<<zoomDepth<<endl;}
fileNames.itsParaFileOut<<"bound states only: ";
	if(boundStatesOnly==1){fileNames.itsParaFileOut<<" yes";} else{fileNames.itsParaFileOut<<" no";}
fileNames.itsParaFileOut<<", use balancing: ";
	if(useBalancing==1){fileNames.itsParaFileOut<<"yes";}	else {fileNames.itsParaFileOut<<"no";}
fileNames.itsParaFileOut<<", doubleLimit = "<<doubleLimit<<endl;
fileNames.itsParaFileOut<<", useSymmetry = ";
	if(useSymmetry==1){fileNames.itsParaFileOut<<"yes";}	else {fileNames.itsParaFileOut<<"no";}
fileNames.itsParaFileOut<<", boundStatesOnly = ";
	if(boundStatesOnly==1){fileNames.itsParaFileOut<<"yes";}else {fileNames.itsParaFileOut<<"no";}
fileNames.itsParaFileOut<<endl;
fileNames.itsParaFileOut<<"epsStart = "<<epsStart<<", epsEnd = "<<epsEnd<<", epsIncrement = "<<epsIncr<<endl
	<<"fStart = "<<fStart<<", fEnd = "<<fEnd	<<", fIncrement = "<<fIncr<<endl;
fileNames.itsParaFileOut<<" used time = "<<timeUsed<<" sec"<<" = "<<timeUsed/60<<" min"<<" = "<<timeUsed/3600<<" h"<<endl;


fileNames.itsParaDatOut<<Np<<endl<<Nm<<endl;
fileNames.itsParaDatOut<<epsPlus<<endl<<epsMinus<<endl<<piPlus<<endl<<piMinus<<endl
	<<FsPlus<<endl<<FsMinus<<endl<<FdPlus<<endl<<FdMinus<<endl<<vPlus<<endl<<vMinus<<endl<<betaPlus<<betaMinus<<endl
	<<gPlus<<endl<<gMinus<<endl;

fileNames.closeFinalFiles();

//******************************************************************
// CLOSE FILES
//******************************************************************

fileNames.closePermanentFiles();

cout<<"output to folder "<<fileNames.folder<<endl;
cout<<"used time: "<<timeUsed<<" sec"
		<<" = "<<timeUsed/60<<" min"
		<<" = "<<timeUsed/3600<<" h"<<endl;

