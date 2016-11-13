// measure stationary state probabilities

actualKp = cargoMotors.GetOldKp();
actualKm = cargoMotors.GetOldKm();
//del = actualKp - actualKm;
//sig = actualKp + actualKm;
waitTime = cargoMotors.GetWaitingTime();

//numberOfStatSteps = numberOfStatSteps + 1;
integrateTimeStat += waitTime;
distanceStat +=  fabs(cargoMotors.GetSojournDist());//abs(cargoMotors.GetWalkingDistance());
//if(cargoMotors.GetOldDirection()==Zero){pausingTimeStat+=waitTime;}

//cout<<"time "<<t<<", integrateTimeStat ="<< integrateTimeStat<<", sojournDist = "<<fabs(cargoMotors.GetSojournDist())<<", distanceStat = "<<distanceStat <<endl;

pStatKpKm[actualKp][actualKm] = pStatKpKm[actualKp][actualKm] + waitTime;

//pStatDel[del+Nm] = pStatDel[del+Nm] + waitTime;
//pStatSig[sig] = pStatSig[sig] + waitTime;

//cout<<"Step "<<numberOfStatSteps<<", t = "<<t
//	<<", kp = "<<actualKp<<", km = "<<actualKm<<", del = "<<del<<", sig = "<<sig<<", pdel = "<<pStatDel[del+Nm]<<endl;
