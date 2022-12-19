
#include <complex>
#include <vector>

#ifndef dft
#define dft
namespace fourier
{
  std::vector<std::complex<double>> transform(std::vector<double> inp);
  std::vector<std::complex<double>> inv(std::vector<std::complex<double>> inp);
}

#endif // dft.h