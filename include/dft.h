
#include <complex>
#include <vector>
#define _USE_MATH_DEFINES

namespace Oscilloscope
{
  class DFT
  {
  public:
    std::vector<std::complex<double>> transform(std::vector<double> inp);
    std::vector<std::complex<double>> inv(std::vector<std::complex<double>> inp);

  private:
    std::complex<double> IM = std::complex<double>(0, 1);
    std::complex<double> PI = std::complex<double>(M_PI, 0);
  };
}
