#include "mymath/mymath.hpp"
#include "myprint/myprint.hpp"
#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");
  const int a = 10, b = 32;
  std::cout << "Я умею суммировать! Зацени " << a << '+' << b << '=';
  myprint::printInt(mymath::sum(a, b));
  std::cout << std::endl;
  return 0;
}
