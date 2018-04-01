#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <complex>
#include <fstream>
#include <iomanip>
using namespace std;
int precision_error_flag;
int order;
double *a;
double *b;
double *c;
double *d;
double *e;

void find_poly_roots(int n)
{
		double r,s,dn,dr,ds,drn,dsn,eps;
	int i,iter;

	r = s = 0;
	dr = 1.0;
	ds = 0;
	eps = 1e-14;
	iter = 1;

	while ((fabs(dr)+fabs(ds)) > eps) {
		if ((iter % 200) == 0) {
			r=(double)rand()/16000.;
		}
		if ((iter % 500) == 0) {
			eps*=10.0;
			precision_error_flag=1;
			std::cout<<"Loss of precision\n";
		}
		b[1] = a[1] - r;
		c[1] = b[1] - r;

		for (i=2;i<=n;i++){
			b[i] = a[i] - r * b[i-1] - s * b[i-2];
			c[i] = b[i] - r * c[i-1] - s * c[i-2];
		}
		dn=c[n-1] * c[n-3] - c[n-2] * c[n-2];
		drn=b[n] * c[n-3] - b[n-1] * c[n-2];
		dsn=b[n-1] * c[n-1] - b[n] * c[n-2];

		if (fabs(dn) < 1e-16) {
			dn = 1;
			drn = 1;
			dsn = 1;
		}
		dr = drn / dn;
		ds = dsn / dn;

		r += dr;
		s += ds;
		iter++;
	}
	for (i=0;i<n-1;i++)
		a[i] = b[i];
	a[n] = s;
	a[n-1] = r;
}


int main(int argc, char *argv[])
{
  std::cout << std::fixed;
    std::cout << std::setprecision(6);
    int n;
    //-----------------------------
    ifstream polytest;
    string faradon;
  if (argv)
  {
      cout <<"filename?";
      cin >> faradon;
      polytest.open(faradon.c_str());
  }
  else
  {
        cout << argv[1] << endl;
        polytest.open(argv[1]);
  }
  while (!polytest)
  {
    cout << "Filename?";
    cin >> faradon;
    polytest.open(faradon.c_str());
  }

  polytest >> order;
  a= new double[order+1];
    b= new double[order+1];
      c= new double[order+1];
        d= new double[order+1];
        e= new double[order+1];

  //inputs coefficients
  for (int i=0;i<=order;i++){
		//std::cout <<"a("<<order<<")=";
		polytest >> a[order-i];
		e[order-i]=a[order-i];
	}
    //-------------------------------------------------
//	int i,n;//order=0;
	double tmp;
/*
	while ((order < 2)){
		std::cout <<"Polynomial order (2-X): ";
		std::cin>>order;
	}

	std::cout <<"Enter coefficients from the lowest order to the highest order\n";
	for (i=0;i<=order;i++){
		std::cout <<"a("<<order<<")=";
		std::cin >> a[order-i];
		e[order-i]=a[order-i];
	}*/
	for (int v=0; v<=order; v++)
  {
    std::cout <<a[v]<<std::endl;
  }
			tmp=a[0];
			a[0]=1.0;
			d[0]=1.0;

	for (int p=1; p<=order; p++)
  {
    	a[p]/=tmp;
		d[p]=a[p];
  }

	b[0]=c[0]=1.0;
	n=order;
	precision_error_flag=0;
	while (n > 2) {
		find_poly_roots(n);
				n-=2;
	}
	std::cout <<"The quadratic factors are:\n";

	for (int i=order; i>=2; i-=2) /* print quadratics */
		std::cout <<"t^2  +  "<<a[i-1]<<"t  +  "<<a[i]<<"\n";
	if ((n % 2) == 1)
		std::cout <<"The linear term is: \nt  +  "<<a[1]<<"\n";

	complex<double> factr[order];
    complex<double> x[2];
    int f=0;
    for (int l=order; l>=2; l-=2)
    {
    x[0]= (a[l-1]*a[l-1]-4*a[l])/4;
    x[0]= sqrt(x[0]);
    x[0]= x[0];
    x[0]+= -a[l-1]/2;
    factr[f]=x[0];
    f++;
    //cout << x[0]<<endl;
    x[1]= (a[l-1]*a[l-1]-4*a[l])/4;
    x[1]= sqrt(x[1]);
    x[1]= (-a[l-1]/2)-x[1];
   // cout << x[1]<<endl;
    factr[f]=x[1];
    f++;
    }
    if (order%2==1)
    factr[f]=-a[1];
    for (int i=0; i<=f-1; i++)
    {
        cout <<factr[i]<<endl;
    }
    if (order%2==1)
        cout <<factr[f]<<endl;

complex<double> answer[order+1];
     // answer={0,0};
      for (int j=0; j<order;j++)
      {

    for (int i=0; i<order+1;i++)
  {

   // cout << "Horner Step:" << i+1<<endl;
    answer[j]=answer[j]+e[i];
    //cout <<"Before Root Answer:" <<answer<<endl;
    if (i!=order)
    {
          answer[j]=answer[j]*factr[j];
   //           cout <<"After Root Answer:" <<answer<<endl;
    }
    else
    {
      break;
    }
  }
  //cout <<"---------------------------"<<endl;
  //cout <<"Final Answer:" <<answer;
  //answer={0,0};
  //cout <<endl;
      }

       ofstream saveFile ("Results.txt");

  saveFile << "Polynomial:" << endl;

  for (int ox=0; ox< order; ox++)
  {
    saveFile << e[ox] << "x^" <<order-ox <<" + " ;
    cout << e[ox] << "x^" <<order-ox <<" + " ;
  }
  saveFile << e[order] << endl;
  cout << e[order] << endl;

  saveFile << endl;

  saveFile << "Roots:" << endl;

  for (int i=0; i<=f-1; i++)
  {
    saveFile << factr[i] << endl;
  }
  if (order%2==1)
  {
    saveFile <<factr[f] << endl;
  }
  saveFile << endl;

  saveFile << "Evaluating polynomial at identified roots:" << endl;
  for (int kxi=0; kxi < f; kxi++)
  {
    cout << factr[kxi] <<" = " <<answer[kxi] << endl;
    saveFile << factr[kxi] << " = " << answer[kxi] << endl;
  }
  if (order%2==1)
  {
    saveFile <<factr[f] << " = " << answer[f] << endl;
  }
  saveFile.close();

  return 0;
}
