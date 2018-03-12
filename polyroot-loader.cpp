#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  int N;
    
  ifstream polytest;
  polytest.open("polytest.txt");
  if (!polytest)
  {
    cerr << "filename: polytest.txt";
    exit(1);
  }
    
  polytest >> N;
    
  double polyO[N]; //original input coefficients
    
  //inputs coefficients
  for (int s = 0; s < N; s++)
    polytest >> polyO[s];  
  //displays polyO's coefficients
  for (int s = 0; s < N; s++)
    cout << polyO[s] << ", ";
  system("PAUSE");

  polytest.close();
  return EXIT_SUCCESS;
}
