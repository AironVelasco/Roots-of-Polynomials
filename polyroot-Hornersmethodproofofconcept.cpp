#include <iostream>

using namespace std;

int main()
{
  int order=0;
  double answer=0;
  double root=0;
  double coefficient[21];
  cout <<"Highest Exponent?";
  cin>> order;
  cout <<"Root to Test?";
  cin>> root;
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
          answer=answer*root;
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
