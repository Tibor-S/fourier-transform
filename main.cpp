#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>
#include "dft.h"
using namespace std;

double sample(double x, vector<double> freq)
{
  double s = 0;
  for (int f = 0; f < freq.size(); f++)
  {
    s += freq[f] * sin(f * 2 * M_PI * x);
  }

  return s;
}

template <typename T>
void vecToFile(string path, vector<T> vec, bool log = false)
{
  ofstream file;
  if (log)
  {
    cout << "Writing to " << path << endl;
  }
  file.open(path);
  for (T el : vec)
  {
    file << el << endl;
  }
  file.close();
}

int main()
{
  srand(time(0));
  ofstream file;

  int N = 100;
  int nF = 1;
  vector<double> oFreq = {};
  for (int i = 0; i < N / 2; i++)
  {
    if (i >= nF)
    {
      oFreq.push_back(1);
      nF = rand() % (N / 2 - 1) + i + 1;
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
  vector<complex<double>> freq = fourier::transform(inp);
  vector<double> realFreq = {};
  vector<double> imagFreq = {};

  for (complex<double> f : freq)
  {
    realFreq.push_back(real(f));
    imagFreq.push_back(imag(f));
  }

  vecToFile("org_freq.txt", oFreq, true);
  vecToFile("ext_complex_freq.txt", freq, true);
  vecToFile("ext_real_freq.txt", realFreq, true);
  vecToFile("ext_imag_freq.txt", imagFreq, true);
  vecToFile("inp.txt", inp, true);
  vecToFile("ext_complex_inv.txt", fourier::inv(freq), true);

  // cout << "Writing to ext_complex_freq" << endl;
  // file.open("ext_complex_freq.txt");
  // for (complex<double> f : freq)
  // {
  //   file << "complex(" << real(f) << ", " << imag(f) << ")" << endl;
  // }
  // file.close();

  // cout << "Writing to ext_real_freq" << endl;
  // file.open("ext_real_freq.txt");
  // for (complex<double> f : freq)
  // {
  //   file << real(f) << endl;
  // }
  // file.close();

  // cout << "Writing to ext_imag_freq" << endl;
  // file.open("ext_imag_freq.txt");
  // for (complex<double> f : freq)
  // {
  //   file << imag(f) << endl;
  // }
  // file.close();

  // cout << "Writing to inp" << endl;
  // file.open("inp.txt");
  // for (double y : inp)
  // {
  //   file << y << endl;
  // }
  // file.close();

  // cout << "Writing to ext_complex_inv" << endl;
  // file.open("ext_complex_inv.txt");
  // for (complex<double> z : inv(freq))
  // {
  //   file << z << endl;
  // }
  // file.close();
  return 0;
}