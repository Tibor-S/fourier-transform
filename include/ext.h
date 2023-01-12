#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace Oscilloscope
{
  template <typename T>
  void vecToFile(std::string path, std::vector<T> vec)
  {
    std::ofstream file;

    file.open(path);
    for (T el : vec)
    {
      file << el << std::endl;
    }
    file.close();
  };
}