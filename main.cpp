#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

#define MAX_TERMS 21
int precision_error_flag;
int order;
double *a;
double *b;
double *c;
double *d;

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


int main()
{
	int i,n;//order=0;
	double tmp;

	while ((order < 2)){
		std::cout <<"Polynomial order (2-X): ";
		std::cin>>order;
	}
  a= new (std::nothrow) double[order+1];
    b= new (std::nothrow) double[order+1];
      c= new (std::nothrow) double[order+1];
        d= new (std::nothrow) double[order+1];
	std::cout <<"Enter coefficients from the lowest order to the highest order\n";
	for (i=0;i<=order;i++){
		std::cout <<"a("<<order<<")=";
		std::cin >> a[order-i];
	}
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

	for (i=order; i>=2; i-=2) /* print quadratics */
		std::cout <<"t^2  +  "<<a[i-1]<<"t  +  "<<a[i]<<"\n";
	if ((n % 2) == 1)
		std::cout <<"The linear term is: \nt  +  "<<a[1]<<"\n";
}
