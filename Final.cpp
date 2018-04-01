#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <complex>
#include <fstream>
#include <iomanip>

using namespace std;
int precisionErrorFlag;
int polyOrder;
int numRoots;
complex<double> *roots;
complex<double> *rootsEval;
double *coeff;
double *b;
double *c;
double *e;

//Function to get the absolute value of a double
double dabs(double x)
{
  if (x >= 0)
  {
    return x;
  }
  else
  {
    return -x;
  }
}

//Function to acqire the roots of the polynomial
void findQuadraticTerms(int n)
{
  double r,s,dn,dr,ds,drn,dsn,eps;
	int i,iter;

	r = s = 0;
	dr = 1.0;
	ds = 0;
	eps = 1e-300;
	iter = 1;

	while ((dabs(dr)+dabs(ds)) > eps)
  {
		if ((iter % 200) == 0)
		{
			r=(double)rand()/16000.;
		}
		if ((iter % 500) == 0)
		{
			eps*=10.0;
			precisionErrorFlag=1;
			cout<<"Loss of precision\n";
		}
		b[1] = coeff[1] - r;
		c[1] = b[1] - r;

		for (i=2;i<=n;i++)
    {
			b[i] = coeff[i] - r * b[i-1] - s * b[i-2];
			c[i] = b[i] - r * c[i-1] - s * c[i-2];
		}
		dn=c[n-1] * c[n-3] - c[n-2] * c[n-2];
		drn=b[n] * c[n-3] - b[n-1] * c[n-2];
		dsn=b[n-1] * c[n-1] - b[n] * c[n-2];

		if (dabs(dn) < 1e-16)
    {
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
  {
		coeff[i] = b[i];
  }
	coeff[n] = s;
	coeff[n-1] = r;
}

void inputFile(int argc, char *argv[])
{
  cout << fixed;
  cout << setprecision(6);

  ifstream polytest;
  string filename;

  if (argc < 2)
  {
    cout <<"Please enter the filename: ";
    cin >> filename;
    polytest.open(filename.c_str());
  }
  else
  {
    polytest.open(argv[1]);
  }

  while (!polytest)
  {
    cout << "Please enter the filename: ";
    cin >> filename;
    polytest.open(filename.c_str());
  }

  polytest >> polyOrder;
  coeff = new double[polyOrder+1];
  b = new double[polyOrder+1];
  c = new double[polyOrder+1];
  e = new double[polyOrder+1];

  //inputs coefficients
  for (int i=0;i<=polyOrder;i++)
  {
		polytest >> coeff[polyOrder-i];
		e[polyOrder-i]=coeff[polyOrder-i];
	}
	polytest.close();
}

// Function to save the results to a text file
void saveToFile()
{
  //Opens the file which will be used to store the results
  ofstream saveFile ("Results.txt");

  //Asks the User to set the number of decimals places for the results
  int setPrec;
  cout << "How many decimal places would you like to have: ";
  cin >> setPrec;

  //Sets how precise the results would be based on the user's input
  saveFile << fixed << setprecision(setPrec) << endl;

  //Saves the Polynomial entered at the start
  saveFile << "Polynomial:" << endl;

  for (int i=0; i< polyOrder; i++)
  {
    saveFile << e[i] << "x^" << polyOrder-i <<" + " ;
  }
  saveFile << e[polyOrder] << endl;

  //Saves the roots of the polynomial
  saveFile << endl << "Roots:" << endl;

  for (int i=0; i<=numRoots-1; i++)
  {
    saveFile << roots[i] << endl;
  }
  if (polyOrder%2==1)
  {
    saveFile << roots[numRoots] << endl;
  }

  //Saves the evaluated value of the polynomial using the acquired roots
  saveFile << endl << "Evaluating polynomial at identified roots:" << endl;
  for (int i=0; i < numRoots; i++)
  {
    saveFile << roots[i] << " = " << rootsEval[i] << endl;
  }
  if (polyOrder%2==1)
  {
    saveFile <<roots[numRoots] << " = " << rootsEval[numRoots] << endl;
  }
  saveFile.close();
}

//Function which outputs the inputted polynomial, the roots of the 
//polynomial, and the evaluated values of the acquired polynomial
void outputToConsole()
{
  cout << "Polynomial:" << endl;
  for (int i=0; i< polyOrder; i++)
  {
    cout << e[i] << "x^" << polyOrder-i <<" + " ;
  }
  cout << e[polyOrder] << endl;

  cout << endl << "Roots: " << endl;
  for (int i=0; i<=numRoots-1; i++)
  {
    cout << roots[i] << endl;
  }
  if (polyOrder%2==1)
  {
    cout << roots[numRoots] << endl;
  }

  cout << endl << "Evaluating polynomial at identified roots:" << endl;
  for (int i=0; i < numRoots; i++)
  {
    cout << roots[i] <<" = " << rootsEval[i] << endl;
  }
  cout << endl;
}

//Function to find the root of a polynomial given its order and coefficients
void findRoot()
{
  double tmp;
  tmp=coeff[0];
  coeff[0]=1.0;

	for (int p=1; p<=polyOrder; p++)
  {
    coeff[p]/=tmp;
  }

	b[0]=c[0]=1.0;
  int numQuad = polyOrder;
	precisionErrorFlag=0;
	while (numQuad > 2)
  {
		findQuadraticTerms(numQuad);
    numQuad -= 2;
	}

	roots = new complex<double>[polyOrder];
  complex<double> x[2];
  numRoots=0;
  for (int l=polyOrder; l>=2; l-=2)
  {
    x[0]= (coeff[l-1]*coeff[l-1]-4*coeff[l])/4;
    x[0]= sqrt(x[0]);
    x[0]= x[0];
    x[0]+= -coeff[l-1]/2;
    roots[numRoots]=x[0];
    numRoots++;
    x[1]= (coeff[l-1]*coeff[l-1]-4*coeff[l])/4;
    x[1]= sqrt(x[1]);
    x[1]= (-coeff[l-1]/2)-x[1];
    roots[numRoots]=x[1];
    numRoots++;
  }
  if (polyOrder%2==1)
  {
    roots[numRoots]=-coeff[1];
  }
}

//Function which evaluates the roots acquired in findRoots to determine if they are indeed roots of the polynomial
void evalRoots()
{
  rootsEval = new complex<double>[polyOrder+1];
  for (int j=0; j<polyOrder;j++)
  {
    for (int i=0; i<polyOrder+1;i++)
    {
      // cout << "Horner Step:" << i+1<<endl;
      rootsEval[j]=rootsEval[j]+e[i];
      //cout <<"Before Root Answer:" <<answer<<endl;
      if (i!=polyOrder)
      {
        rootsEval[j]=rootsEval[j]*roots[j];
        //cout <<"After Root Answer:" <<answer<<endl;
      }
      else
      {
        break;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  //Opens input file
  inputFile(argc, argv);

  //Finds the root
  findRoot();

  //Horner Step? evaluates the solved roots
  evalRoots();

  //Ouputs the results to the console
  outputToConsole();

  //Asks the user if they would like to save the results to a text file
  char save;
  cout << "Would you like to save the results to a text file? (Y/N)" << endl;
  cin >> save;
  if (save == 'Y')
  {
    //Saves the results to a text file
    saveToFile();
  }

  return 0;
}

