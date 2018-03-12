#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  int N;
  double r, s;
    
  ifstream polytest;
  polytest.open("polytest.txt");
  if (!polytest)
  {
    cerr << "filename: polytest.txt";
    exit(1);
  }
    
  polytest >> N;
    
  double polyA[N]; //original input coefficients
    
  //inputs coefficients
  for (int t = 0; t < N; t++)
    polytest >> polyA[t];  
  //displays polyA's coefficients
  for (int t = 0; t < N; t++)
    cout << polyA[t] << ", ";
  polytest.close();
  
  //set initial values for r and s
  r = polyA[N]/polyA[N-1];
  s = polyA[N-1]/polyA[N-2];
  
  double polyB[N];
  
  polyB[N] = polyA[N];
  polyB[N-1] = polyA[N-1] + r*polyB[N];
  for (int t = N-2; t > 0; t--)
  {
    polyB[t] = polyA[t] + r*polyB[t+1] + s*polyB[t+2];
  }  
  
  //displays polyB's coefficients
  for (int t = 0; t < N; t++)
    cout << polyB[t] << ", ";  
  system("PAUSE");
  return EXIT_SUCCESS;
}
