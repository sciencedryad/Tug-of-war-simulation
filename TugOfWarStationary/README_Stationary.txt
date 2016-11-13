Numerical calculation of stationary states of a cargo pulled by two teams of molecular motors performing a tug-of-war. 

------------------------
Research paper
------------------------
MJI Müller, S Klumpp, R Lipowsky
Tug-of-war as a cooperative mechanism for bidirectional cargo transport by molecular motors.
Proceedings of the National Academy of Sciences 105 (12), 4609-4614.

------------------------
Description of code files
------------------------

Main files for usage:
	StatCalc.C	// main file, contains main loop over phase diagram parameters
	StatPara.CPP,ParaStat.CPP // put parameters here 
		(most interesting ones singled out in ParaStat.CPP)

Motor cargo calculation files
	StatMatrixClass.CPP // master class for the transition matrix
	StatIndexClass.CPP // generate matrix indices
	StatIni.CPP // initialization
	StatCalculation.CPP // calculate stationary state
	TransitionRates.CPP // functions for transitions (detach, attach, move etc)

Measurements
    StatOneStateMeas.CPP
    StatMeanValCalc.CPP     
    StatSubroutines.CPP
	StatZoomPoint.CPP, StatZoomPointSpecial.CPP, StatZoomMax.CPP
		StatZoomBound.CPP,StatZoomDelta.CPP,STatZoomExtr.CPP, StatZoomSym.CPP,
		StatZoomSigmaThres.CPP,StatZoomFPLarger1Sym.CPP,StatZoomFPLarger1US.CPP
		// more fine grained calculations in the phase diagram

Other files
	StatDef.CPP //load libraries, subroutines, define types, globals
	Assert.CPP // function used to check stuff	
	VecMatRoutines.CPP, MatInvert.CPP // Matrix calculation stuff
	StatFiles.CPP	// define names for output files

Analysis
	AnaStat.C // analysis
	AnaPara.CPP // parameters for analysis






------------------------
Basic Usage 
------------------------
from terminal with g++ compiler:
	Compile the code: g++ TugOfWar.C -o TugOfWar.exe
	Run the simulation: ./TugOfWar.exe
	With the pre-set parameters, the simulation should run some minutes, 
		and put files into the folder Test/
	Change the parameters: in the file TugPara.CPP

------------------------
Output
------------------------
Output into the folder 'folderName' (e.g. "Test/") in TugPara.CPP.
Program outputs the following files:
	Averages.dat // some trajectory averages
	Para.CPP, Para.dat, Parameters.dat // simulation parameters in different formats
	plotPhaseDiag.gnu // gnuplot file to plot phase diagram
	ProbaDist.dat
	pStatDel.dat	// probability of having kp-km motor difference bound
	ProbaKpKm.dat // probability of having kp plus motors and km minus motors bound
	pStatSig.dat // probability of having kp+km motor sum bound
	pSwitchingDistance.dat //
	pSwitchingTime.dat 
	pVelocity.dat // probability of velocity v
	pWaitingTime.dat
	pWalkingDistance.dat
	pWalkingDistance.dat
	SingleProbTrajectory.dat
	SingleTrajectory.dat // outputs single trajectory



------------------------
Description of code files
------------------------


Files for motor simulation
	TugCargoClass.CPP //class for the cargo with motors
	TugRateClass.CPP 	// class for transitions

Measurements 
	TugMeasure.CPP	// measurement of dynamic properties
	TugMeasureStat.CPP // measurement of stationary state properties
	TugFinish.CPP		// final measurements and output
	TugFinishStatTrajec.CPP // final measurements and output
	TugMeasureSubroutines.CPP // subroutines used in measurements
	TugMeasureSubroutines2.CPP // subroutines used in measurements
	
Other files 
	TugDef.CPP,TugGlobals.CPP //load libraries, subroutines, define types, globals
	TugTimeChange.CPP	// used to simulate binding or unbinding of motors to/from cargo
	RandomMTImproved.CPP // Mersenne Twister Random Number Generator
