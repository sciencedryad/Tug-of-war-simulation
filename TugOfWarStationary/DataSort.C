//*******************************************************************
// libraries
//*******************************************************************
#include<iostream.h>
#include<fstream.h>
#include<time.h>
#include<stdlib.h>
//#include<malloc.h>
#include<math.h>
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

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
// MAIN PROGRAM
//*******************************************************************

int main()
{

//*******************************************************************
// PARAMETERS
//*******************************************************************
const int Np=5;
const int Nm=Np;
const int nDelta=Np+Nm+1;
const int deltaOffset=Nm;
char folder[80]="../PhaseDiagN05c/";//"../Test/"; // will be read in from Para.CPP

//*******************************************************************
char dataFile[80];
char outfile[nDelta][80];
ofstream fout[nDelta];
char comment;

const int maxLength=1000;

double data1[maxLength],data2[maxLength],data3[maxLength],data4[maxLength];

int i,j,ind;

char strBuffer;

char ch;

ifstream finData;

//==========================================
sprintf(dataFile,"%s%s",folder,"DeltaChange.dat");

finData.open(dataFile);
	if(!finData) {cout<<"Unable to open file! ";ASSERTperm(0);}
	skip_comments(finData,'#');

ind=0;
while(!finData.eof())
{
	finData>>data1[ind];
	finData>>data2[ind];
	finData>>data3[ind];
	finData>>data4[ind];
	ind=ind+1;
}
ind = ind-1;
cout<<"length of dataFile = "<<ind<<endl;

//for(i=0;i<ind;i++)
//{cout<<i<<"  "<<data1[i]<<"  "<<data2[i]<<"  "<<data3[i]<<"  "<<data4[i]<<"  "<<endl;}

finData.close();

for(i=0;i<nDelta;i++)
{
	sprintf(outfile[i],"%s%s%i%s",folder,"DeltaChange",i-deltaOffset,".dat");
	//cout<<outfile[i]<<endl;;
	fout[i].open(outfile[i]);
	fout[i]<<"# change of delta value from delta = "<<i-deltaOffset<<endl<<"# f    eps"<<endl;
}

for(i=0;i<ind;i++)
{
	for(j=0;j<ind;j++)
	{
		if(data3[i]==(j-deltaOffset)){fout[j]<<data1[i]<<"   "<<data2[i]<<endl;}
	}
}

for(i=0;i<nDelta;i++)
{
	fout[i].close();
}


return 0;
}// end main
