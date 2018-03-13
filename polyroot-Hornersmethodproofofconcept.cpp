#include <iostream>
#include <complex>

using namespace std;

int main()
{
  int order=0;
  complex<double> answer=(0,0);
  double rootr=0;
  double rooti=0;
  complex<double> acroot;
  double coefficient[21];
  cout <<"Highest Exponent?";
  cin>> order;
  cout <<"Root to Test?";
  cin>> rootr;
  cin>>rooti;
  acroot = {rootr,rooti}g;
  cout <<endl<< acroot;
  for (int i=0; i<order+1;i++)
  {
    cin >> coefficient[i];
  }
  for (int i=0; i<order+1;i++)
  {
    cout << "Horner Step:" << i+1<<endl;
    answer=answer+coefficient[order-i];
    cout <<"Before Root Answer:" <<answer<<endl;
    if (i!=order)
    {
          answer=answer*acroot;
              cout <<"After Root Answer:" <<answer<<endl;
    }
    else
    {
      break;
    }
  }
  cout <<"---------------------------"<<endl;
  cout <<"Final Answer:" <<answer;
}
