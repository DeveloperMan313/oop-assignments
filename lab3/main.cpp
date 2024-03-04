#include "fraction/fraction.hpp"
#include <clocale>
#include <iostream>

int main() {
  setlocale(LC_ALL, ".UTF8");
  Fraction f("-2 1/4");
  std::cout << f << std::endl;
  return 0;
}
