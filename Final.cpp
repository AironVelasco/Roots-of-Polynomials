#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <complex>
#include <fstream>
#include <iomanip>

using namespace std;
int precisionChangeFlag;
int polyOrder;
int numRoots;
complex<double> *roots;
complex<double> *rootsEval;
double *quadCoeff;
double *b;
double *c;
double *inputCoeff;

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

//Function to acquire the roots of the polynomial
void findQuadraticTerms(int n)
{
  double r,s,dn,dr,ds,drn,dsn,precision;
	int iter;

	r = s = 0;
	dr = 1.0;
	ds = 0;
	precision = 1e-300;
	iter = 1;

	while ((dabs(dr)+dabs(ds)) > precision)
  {
    /*This if statement makes it so that if the remainders do not converge after
    500 iterations and adjusts the precision of convergence to 1 exponent
    higher.*/
		if ((iter % 500) == 0)
		{
			precision*=10.0;
			precisionChangeFlag=1;
		}
		/* The current r is accounted for to adjust the quadratic coefficients*/
		b[1] = quadCoeff[1] - r;
		c[1] = b[1] - r;
    /*This for loop makes the synthetic division required to operate
    Bairstow's Method. The first one deflates the polynomial to an order 2
    less than the original. The second adds or subtracts the
    residuals. */
		for (int i=2;i<=n;i++)
    {
			b[i] = quadCoeff[i] - r * b[i-1] - s * b[i-2];
			c[i] = b[i] - r * c[i-1] - s * c[i-2];
		}
		/* The change in value for the guess coefficients are computed for
		iteratively such that the values for the change in r (signified by dr) and
		the change in s (signified by ds) is very small and negligible. */
		dn=c[n-1] * c[n-3] - c[n-2] * c[n-2];
		drn=b[n] * c[n-3] - b[n-1] * c[n-2];
		dsn=b[n-1] * c[n-1] - b[n] * c[n-2];

		dr = drn / dn;
		ds = dsn / dn;

    /* The change is then added to create a more precise guess. The hope is
    that changing the values according to dr will give a closer answer. */
		r += dr;
		s += ds;
		iter++;
	}
	/* If the values for r and s (which represent r and s in x^2+rx+s) pass the
	test, the values of r and s are said to be coefficients of one quadratic
	factor that contains the root */
	for (int i=0;i<n-1;i++)
  {
		quadCoeff[i] = b[i];
  }
	quadCoeff[n] = s;
	quadCoeff[n-1] = r;
}

//Function to find the root of a polynomial given its order and coefficients
void findRoot()
{
  double tmp;
  tmp=quadCoeff[0];
  quadCoeff[0]=1.0;

	for (int p=1; p<=polyOrder; p++)
  {
    quadCoeff[p]/=tmp;
  }

	b[0]=c[0]=1.0;
  int numQuad = polyOrder;
	precisionChangeFlag=0;
	while (numQuad > 2)
  {
		findQuadraticTerms(numQuad);
    numQuad -= 2;
	}

	roots = new complex<double>[polyOrder];
  complex<double> quadRoots[2];
  numRoots=0;
  for (int l=polyOrder; l>=2; l-=2)
  {
    //This code does the quadratic formula for both + and - cases.
    quadRoots[0]= (quadCoeff[l-1]*quadCoeff[l-1]-4*quadCoeff[l])/4;
    quadRoots[0]= sqrt(quadRoots[0]);
    quadRoots[0]= quadRoots[0];
    quadRoots[0]+= -quadCoeff[l-1]/2;
    roots[numRoots]=quadRoots[0];
    numRoots++;
    quadRoots[1]= (quadCoeff[l-1]*quadCoeff[l-1]-4*quadCoeff[l])/4;
    quadRoots[1]= sqrt(quadRoots[1]);
    quadRoots[1]= (-quadCoeff[l-1]/2)-quadRoots[1];
    roots[numRoots]=quadRoots[1];
    numRoots++;
  }
  /*If the polynomial is of an odd order, a linear term is expected. Since the
  leading coefficient was normalized to 1, the linear term is given as -a
  (assuming the linear eqn is of the form "x-a")*/
  if (polyOrder%2==1)
  {
    roots[numRoots]=-quadCoeff[1];
  }
}

//Function that sets the precision of the console and
//acquires the input polynomial from a given text file
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
  quadCoeff = new double[polyOrder+1];
  b = new double[polyOrder+1];
  c = new double[polyOrder+1];
  inputCoeff = new double[polyOrder+1];

  //inputs coefficients
  for (int i=0;i<=polyOrder;i++)
  {
		polytest >> quadCoeff[polyOrder-i];
		inputCoeff[polyOrder-i]=quadCoeff[polyOrder-i];
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
    saveFile << inputCoeff[i] << "x^" << polyOrder-i <<" + " ;
  }
  saveFile << inputCoeff[polyOrder] << endl;

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
    saveFile << "f" << roots[i] << " = " << rootsEval[i] << endl;
  }
  if (polyOrder%2==1)
  {
    saveFile << "f" << roots[numRoots] << " = " << rootsEval[numRoots] << endl;
  }
  saveFile.close();
}

//Function which outputs the input polynomial, the roots of the
//polynomial, and the evaluated values of the acquired polynomial
void outputToConsole()
{
  cout << "Polynomial:" << endl;
  for (int i=0; i< polyOrder; i++)
  {
    cout << inputCoeff[i] << "x^" << polyOrder-i <<" + " ;
  }
  cout << inputCoeff[polyOrder] << endl;

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
    cout << "f" << roots[i] << " = " << rootsEval[i] << endl;
  }
  if (polyOrder%2==1)
  {
    cout << "f" << roots[numRoots] << " = " << rootsEval[numRoots] << endl;
  }
  cout << endl;
}

//Function which evaluates the roots acquired in findRoots to determine
//if they are indeed roots of the polynomial
void evalRoots()
{
  rootsEval = new complex<double>[polyOrder+1];
  for (int j=0; j<polyOrder;j++)
  {
    for (int i=0; i<polyOrder+1;i++)
    {
      rootsEval[j]=rootsEval[j]+inputCoeff[i];
      if (i!=polyOrder)
      {
        rootsEval[j]=rootsEval[j]*roots[j];
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

