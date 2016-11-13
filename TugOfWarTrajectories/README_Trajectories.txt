Simulation of trajectories of a cargo pulled by two teams of molecular motors performing a tug-of-war. 

------------------------
Research paper
------------------------
MJI Müller, S Klumpp, R Lipowsky
Tug-of-war as a cooperative mechanism for bidirectional cargo transport by molecular motors.
Proceedings of the National Academy of Sciences 105 (12), 4609-4614.

------------------------
Basic Usage 
------------------------
from terminal with g++ compiler:
	Compile the code: g++ TugOfWar.C -o TugOfWar.exe
	Run the simulation: ./TugOfWar.exe
	With the pre-set parameters, the simulation should run some minutes, 
		and put files into the folder Test/
	Change the parameters: in the file TugPara.CPP

Analysis: 
	Put the folder in AnaPara.CPP
	g++ Analysis.C -o ana.exe
	Run ./ana.exe
	
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

Main files for usage:
	TugOfWar.C	// main file, contains main loop over trajectories
	TugPara.CPP // file with main simulation parameters

Files for motor simulation
	TugCargoClass.CPP //class for the cargo with motors
	TransitionRates.CPP // functions for transitions (detach, attach, move etc)
	TugRateClass.CPP 	// class for transitions
	TugIni.CPP	// initialization

Measurements 
	TugMeasure.CPP	// measurement of dynamic properties
	TugMeasureStat.CPP // measurement of stationary state properties
	TugFinish.CPP		// final measurements and output
	TugFinishStatTrajec.CPP // final measurements and output
	TugMeasureSubroutines.CPP // subroutines used in measurements
	TugMeasureSubroutines2.CPP // subroutines used in measurements
	
Other files 
	TugDef.CPP,TugGlobals.CPP //load libraries, subroutines, define types, globals
	TugFiles.CPP	// define names for output files
	TugTimeChange.CPP	// used to simulate binding or unbinding of motors to/from cargo
	TugReInitialize.CPP // used to re-initialize measurements if desired
	Assert.CPP // function used to check stuff	
	RandomMTImproved.CPP // Mersenne Twister Random Number Generator

Analysis.C // trajectory analysis
	// uses parameters (especially folder) given in AnaPara.CPP
 AnaPara.CPP // analysis parameters