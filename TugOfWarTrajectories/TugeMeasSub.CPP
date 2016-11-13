//================================================================

int insertArray(const int& L, double* data, const int& i, const double x)
// inserts value x to array data[L]
// inserts the value x between data[i-1] and data[i]
// throws away data[L-1]
{
	int n;
	//cout<<"insertArrayCalled"<<endl;
	//for(n=0;n<L;n++){cout<<n<<"   "<<data[n]<<endl;}
	for(n=L-1;n>i;n--) { data[n] = data[n-1]; }
	data[i] = x;
	//cout<<"after insert "<<endl;
	//for(n=0;n<L;n++){cout<<n<<"   "<<data[n]<<endl;}
	//cout<<"leaving insert "<<endl;
	return 0;
}

//================================================================


int orderArray(const int& L,  double* data)
// orders the array data[L]
// orders numbers in ascending order
{
	double goal[L];
	int i,j,n,length;
	int notdone;
	//cout<<"orderArray called"<<endl;
	for(j=0;j<L;j++){goal[j]=data[j];}
	length = 1;
	//for(j=0;j<L;j++){cout<<j<<"   "<<goal[j]<<endl;}
	for(n=1;n<L;n++)
	{
		notdone = 1;
		i = 0;
		while(notdone)
		{
			if(data[n]<goal[i])
			{
				ASSERT(i<L); ASSERT(i<length);
				insertArray(L,goal,i,data[n]);
				length = length + 1;
				notdone = 0;
			}
			i=i+1;
			if(i==length)
			{
				goal[i] = data[n];
				length = length + 1;
				notdone = 0;
			}
		}//end while
		//cout<<"step "<<n<<endl;;
		//for(j=0;j<L;j++){cout<<j<<"   "<<goal[j]<<endl;}
	}
	//cout<<"after ordering:"<<endl;
	//for(j=0;j<L;j++){cout<<j<<"   "<<goal[j]<<endl;}
	for(j=0;j<L;j++){data[j]=goal[j];}
	return 0;
}//end subroutine orderArray

