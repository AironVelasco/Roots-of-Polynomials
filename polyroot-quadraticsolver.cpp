#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

double nroot(double a, double b, double c)
{
    double real=-b/(2*a);
    if ((b*b-(4*a*c))>=0)
    {
        real-=((sqrt(b*b - (4*a*c)))/(2*a));
    }
    return real;
}

double rroot(double a, double b, double c)
{
    double real=-b/(2*a);
    if ((b*b-(4*a*c))>=0)
    {
        real+=((sqrt(b*b - (4*a*c)))/(2*a));
    }
    return real;
}


double iroot(double a, double b, double c)
{
    double imag=0;
    if ((b*b-(4*a*c))<0)
    {
        imag=sqrt(abs((b*b - (4*a*c))))/(2*a);
        return imag;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    double a,b,c;
    double real, i1, i2, r2;
    cin>> a;
    cin >> b;
    cin>>c;
    real=rroot(a,b,c);
    r2=nroot(a,b,c);
    i1=iroot(a,b,c);
    i2=-iroot(a,b,c);
    if (i1!=0)
    {
     cout << "R:" <<real<<"I1:" <<i1<<"I2:"<<i2;
    }
    else
    {
        cout <<"R:" <<real<<"R:"<<r2;
    }

}
