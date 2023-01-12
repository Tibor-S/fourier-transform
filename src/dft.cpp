#include <vector>
#include <complex>
#include "dft.h"

using namespace std;
using namespace Oscilloscope;

vector<complex<double>> DFT::transform(vector<double> inp)
{
  vector<complex<double>> freq = {};
  double N = inp.size();
  for (int k = 0; k < N; k++)
  {
    complex<double> sum = 0;
    for (int n = 0; n < N; n++)
    {
      complex<double> amp(inp[n], 0);
      complex<double> arg(2 * k * n / N, 0);
      sum += amp * exp(-IM * PI * arg);
    }
    freq.push_back(sum);
  }
  return freq;
}

vector<complex<double>> DFT::inv(vector<complex<double>> inp)
{
  vector<complex<double>> bin = {};
  int N = inp.size();

  for (int n = 0; n < N; n++)
  {

    complex<double> sum = 0;
    for (int k = 0; k < N; k++)
    {
      complex<double> arg(2 * M_PI * k * n / N, 0);
      sum += inp[k] * exp(IM * arg);
    }

    bin.push_back(sum / complex<double>(N, 0));
  }

  return bin;
}
