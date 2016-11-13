//cout<<"Doing parameter change at time t = "<<t<<endl;
//=================================
// Change of total number of available motors
ASSERT(NpChange<=Np);ASSERT(NpChange<=Nm);
cargoMotors.SetCargoRates(NpChange,NmChange,
epsPlus,epsMinus,piPlus,piMinus,FsPlus,FsMinus,FdPlus,FdMinus,vPlus,vMinus,betaPlus,betaMinus,gPlus,gMinus);

//=================================
tChanged=1;
