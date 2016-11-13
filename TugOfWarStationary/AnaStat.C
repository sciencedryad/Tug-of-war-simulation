//*******************************************************************
// libraries
//*******************************************************************
// #include<iostream.h>
// #include<fstream.h>
// #include<time.h>
// #include<stdlib.h>
// #include<math.h>

#include<iostream>
#include<fstream>
#include<time.h>
#include<cmath>
using namespace std;


//*******************************************************************
// comment skipping in in files
//*******************************************************************
#include <string> // Header for STL strings.
#define and &&
#define or ||
#define not !

using namespace std;

// Define skip_comments function.
int skip_comments(ifstream& file, char mark)
{
//   This function skips the all the lines at the start of the specified
//   file that begin with the specified character.  The file must already
//   be open when this funciton is called.  Error checking not yet
//   included.
	const int MAX_CHARS = 100; // This is the maximum characters per line.
   	while (file.peek() == mark) {file.ignore(MAX_CHARS, '\n');}
	return 0;
}


//*******************************************************************
// debugging
//*******************************************************************
#define DEBUG
#include "Assert.CPP"

//*******************************************************************
// PARAMETER FILE
//*******************************************************************
#include "AnaPara.CPP"

//*******************************************************************
// MAIN PROGRAM
//*******************************************************************

int main()
{
//char folder[80]="../TugK013f2N20/";//"../Test/"; // will be read in from Para.CPP
char dataFile[80];
char comment;

int kp,km,del,sig;

double pDelStat[Np+Nm+1];

ifstream finData;

//==========================================
sprintf(dataFile,"%s%s",folder,"PStatDel.dat");

finData.open(dataFile);
	if(!finData) {cout<<"Unable to open file! ";ASSERTperm(0);}
	skip_comments(finData,'#');

for(del=-Nm;del<=Np;del++)
{
	finData>>kp;
	finData>>pDelStat[del+Nm];
	cout<<kp<<"  "<<pDelStat[del+Nm]<<endl;
}
finData.close();

return 0;
}//end main
