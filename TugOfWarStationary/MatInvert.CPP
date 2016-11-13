//============================================
//============================================
// subroutines for matrix inversion, from numerical recipes in C
//============================================
//============================================

#define NRANSI
//#include "nrutil.h"
#define TINY 1.0e-20;

void ludcmp(double **a, int n, int *indx, double *d)
{
	int i,imax,j,k;
	double big,dum,sum,temp;
	double *vv;
	vv=vector(1,n);
	*d=1.0;
	for (i=1;i<=n;i++) {
		big=0.0;
		for (j=1;j<=n;j++)
			if ((temp=fabs(a[i][j])) > big) big=temp;
		if (big == 0.0) {cout<<"Singular matrix in routine ludcmp"<<endl;}
		vv[i]=1.0/big;
	}
	for (j=1;j<=n;j++) {
		for (i=1;i<j;i++) {
			sum=a[i][j];
			for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
		}
		big=0.0;
		for (i=j;i<=n;i++) {
			sum=a[i][j];
			for (k=1;k<j;k++)
				sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
			if ( (dum=vv[i]*fabs(sum)) >= big) {
				big=dum;
				imax=i;
			}
		}
		if (j != imax) {
			for (k=1;k<=n;k++) {
				dum=a[imax][k];
				a[imax][k]=a[j][k];
				a[j][k]=dum;
			}
			*d = -(*d);
			vv[imax]=vv[j];
		}
		indx[j]=imax;
		if (a[j][j] == 0.0) a[j][j]=TINY;
		if (j != n) {
			dum=1.0/(a[j][j]);
			for (i=j+1;i<=n;i++) a[i][j] *= dum;
		}
	}
	free_vector(vv,1,n);
}
#undef TINY
#undef NRANSI


//============================================

void lubksb(double **a, int n, int *indx, double b[])
{
	int i,ii=0,ip,j;
	double sum;

	for (i=1;i<=n;i++) {
		ip=indx[i];
		sum=b[ip];
		b[ip]=b[i];
		if (ii)
			for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
		else if (sum) ii=i;
		b[i]=sum;
	}
	for (i=n;i>=1;i--) {
		sum=b[i];
		for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
		b[i]=sum/a[i][i];
	}
}

//============================================

void matrixInvert(double ** a, int n)
// inverts matrix a[1..n][1..n], and gives this inverse back as a (thus a is destroyed)
// attention: a has indices 1..n in both arguments!
// if a matrix of the form mat[0..n-1][0..n-1] is to be inverted, use the following:
// a=convert_matrix(&mat[0][0],1,n,1,n); // converts the matrix mat to the matrix a
// free_convert_matrix(a,1,n,1,n);  // deletes a
// attention: original matrices (a, mat) are destroyed!
{
int  *indx; indx=ivector(1,n);
double d;
double *col; col=vector(1,n);
int i,j;

double **y;y=matrix(1,n,1,n);

//cout<<"matrixInvert"<<endl;
//for(i=1;i<=n;i++){for(j=1;j<=n;j++){
//cout<<a[i][j]<<"  ";}cout<<endl;}cout<<endl;

ludcmp(a, n,  indx,&d);

//for(i=1;i<=n;i++){for(j=1;j<=n;j++){
//cout<<a[i][j]<<"  ";}cout<<endl;}cout<<endl;

for(j=1;j<=n;j++)
{
	for(i=1;i<=n;i++){col[i]=0.0;}
	col[j]=1.0;
	lubksb(a,n,indx,col);
	for(i=1;i<=n;i++){y[i][j]=col[i];}
}

for(j=1;j<=n;j++){for(i=1;i<=n;i++){a[i][j]=y[i][j];}}

//for(i=1;i<=n;i++){for(j=1;j<=n;j++){
//cout<<a[i][j]<<"  ";}cout<<endl;}cout<<endl;

free_vector(col,1,n);
free_ivector(indx,1,n);
free_matrix(y,1,n,1,n);

}