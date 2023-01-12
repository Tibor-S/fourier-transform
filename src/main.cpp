#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>
#include "dft.h"
#include "audioin.h"
#include "ext.h"
// #include "interface.h"
using namespace std;
using namespace Oscilloscope;

double sample(double x, vector<double> freq)
{
  double s = 0;
  for (int f = 0; f < freq.size(); f++)
  {
    s += freq[f] * sin(f * 2 * M_PI * x);
  }

  return s;
}

int main()
{
  srand(time(0));
  ofstream file;

  Oscilloscope::DFT dft;

  int N = 1000;
  int nF = 1;
  int div = 10;
  vector<double> oFreq = {};
  for (int i = 0; i < N / div; i++)
  {
    if (i >= nF)
    {
      oFreq.push_back(1);
      nF = rand() % (N / div - 1) + i + 1;
    }
    else
    {
      oFreq.push_back(0);
    }
  }

  vector<double> inp = {};
  for (double f = 0; f < N; f++)
  {
    double x = f / N;
    inp.push_back(sample(x, oFreq));
  }

  vector<complex<double>> freq = dft.transform(inp);
  vector<double> realFreq = {};
  vector<double> imagFreq = {};

  for (complex<double> f : freq)
  {
    realFreq.push_back(real(f));
    imagFreq.push_back(imag(f));
  }

  vecToFile("org_freq.txt", oFreq);
  vecToFile("ext_complex_freq.txt", freq);
  vecToFile("ext_real_freq.txt", realFreq);
  vecToFile("ext_imag_freq.txt", imagFreq);
  vecToFile("inp.txt", inp);
  vecToFile("ext_complex_inv.txt", dft.inv(freq));

  cout << micin();

  // cout << window();

  return 0;
}