//================================================================
//WRITE CONFIGURATION for film
//================================================================
void writeConfig(const int& fileNumber)
{
char configFile[80]; //file for configuration output

double x;

sprintf(configFile,"%s%s%04i%s","/tmp/Film/","config",fileNumber,".pov");

ofstream foutConfig(configFile);
if(!foutConfig) {cout<<"Unable to open file! ";ASSERTperm(0);}
foutConfig<<"#include \"/usr/people/fornax/mmueller/Povray/povDefTrajec.inc\""<<endl;
x=cargoMotors.GetWalkingDistance();
		foutConfig<<"object { cargo translate <"<<x<<", 0, 0 > }"<<endl;
foutConfig.close();
return;
}//end subroutine writeConfig

