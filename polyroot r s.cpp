#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool ErrorCheck(double a, double da, double e)
{
  if ((abs(a/da)*100)<e)
    return 1;
  else
    return 0;
}

int main(int argc, char *argv[])
{
  int N, M;
  double r, s, dr, ds, pr, ps, e;
  //set error
  e = 0.01;
    
  ifstream polytest;
  polytest.open("polytest.txt");
  if (!polytest)
  {
    cerr << "filename: polytest.txt";
    exit(1);
  }
    
  polytest >> M;
  N=M+1;
  
  double polyA[N]; //original input coefficients
  double polyB[N];  
  double polyC[M];  
  //inputs coefficients
  for (int t = M; t >= 0; t--)
    polytest >> polyA[t];  
  polytest.close();
  
  //set initial values for r and s
  r = 0.5;
  s = -0.5;
  do
  {
  pr = r;
  ps = s;
  //display r & s
  cout << "r = " << r << endl;
  cout << "s = " << s << endl;
  
  //B coefficients
  if (N>2)
  {
    polyB[N] = polyA[N];
    polyB[N-1] = polyA[N-1] + r*polyB[N];
    for (int t = N-2; t >= 0; t--)
      polyB[t] = polyA[t] + r*polyB[t+1] + s*polyB[t+2];
  }
  //C coefficients
  polyC[M] = polyB[N];
  polyC[M-1] = polyB[N-1] + r*polyC[M];
  for (int t = M-2; t >= 0; t--)
    polyC[t] = polyB[t+1] + r*polyC[t+1] + s*polyC[t+2];
  //displays polyA's coefficients
  for (int t = M; t >= 0; t--)
    cout << polyA[t] << ", ";
  cout << endl;  
  //displays polyB's coefficients
  for (int t = M; t >= 0; t--)
    cout << polyB[t] << ", ";  
  cout << endl;
  //displays polyC's coefficients
  for (int t = M-1; t >= 0; t--)
    cout << polyC[t] << ", ";  
  cout << endl;  
  //solving dr & ds
  dr = ((-polyB[1]*polyC[1])+(polyB[0]*polyC[2]))/((polyC[1]*polyC[1])-(polyC[0]*polyC[2]));
  ds = (-polyB[0]-(polyC[0]*dr))/polyC[1];
  cout << "dr = " << dr << endl;
  cout << "ds = " << ds << endl;
  //adjusting r & s
  r += dr;
  s += ds;
  cout << "\n \n \n";
  }
  while(pr!=r && ps!=s);
  //cout << "Trying Synthetic Division \n";
  //syndiv();
  system("PAUSE");
  return EXIT_SUCCESS;
}
