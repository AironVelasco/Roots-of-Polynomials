#include <cstdlib>
#include <iostream>
#include <complex>

using namespace std;


int main(int argc, char *argv[])
{
    complex<double> x[2];
    double b,c;
    cin >> b;
    cin>>c;
    x[0]= (b*b-4*c)/4;
    x[0]= sqrt(x[0]);
    x[0]= x[0];
    x[0]+= -b/2;
    cout << x[0];
    x[1]= (b*b-4*c)/4;
    x[1]= sqrt(x[1]);
    x[1]= (-b/2)-x[1];
    cout << x[1];

}
