#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>
#include "dft.h"

using namespace std;
using namespace fourier;
complex<double> IM = (0, 1);

vector<complex<double>> fourier::transform(vector<double> inp)
{
  vector<complex<double>> freq = {};
  int N = inp.size();
  for (int k = 0; k < N; k++)
  {
    if (k % 100 == 0)
    {
      cout << "k = " << k << endl;
    }
    complex<double> sum = 0;
    for (int n = 0; n < N; n++)
    {
      sum += complex<double>(inp[n], 0) * exp(-IM * complex<double>(2 * M_PI * k * n / N, 0));
    }
    freq.push_back(sum /*/ complex<double>(N, 0)*/);
  }

  return freq;
}

vector<complex<double>> fourier::inv(vector<complex<double>> inp)
{
  vector<complex<double>> bin = {};
  int N = inp.size();

  for (int n = 0; n < N; n++)
  {

    complex<double> sum = 0;
    for (int k = 0; k < N; k++)
    {
      sum += inp[k] * exp(IM * complex<double>(2 * M_PI * k * n / N, 0));
    }

    bin.push_back(sum / complex<double>(N, 0));
  }

  return bin;
}