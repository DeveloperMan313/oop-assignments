#include "Fraction/Fraction.hpp"
#include <clocale>
#include <iostream>

int main() {
  setlocale(LC_ALL, ".UTF8");
  std::cout << "Введите дробь: \n";
  Fraction z;
  std::cin >> z;
  std::cout << "z=" << z << std::endl;
  Fraction fr1(10, 14), fr2;
  std::cout << "fr2=" << fr2 << std::endl;
  std::cout << "fr1=" << fr1 << std::endl;
  Fraction fr = "-1 4/8";
  std::cout << "fr=" << fr << std::endl;
  Fraction x(z), y;
  std::cout << "x=" << x << std::endl;
  double dbl = -1.25;
  Fraction f = dbl;
  std::cout << "f=" << f << std::endl;
  y = x + z;
  std::cout << "y=" << y << std::endl;
  y += x;
  f += dbl / 2;
  std::cout << "f=" << f << std::endl;
  y = x + dbl;
  std::cout << "y=" << y << std::endl;
  y = dbl + y;
  std::cout << "y=" << y << std::endl;
  y += dbl;
  std::cout << "y=" << y << std::endl;
  int i = 5;
  y += i;
  std::cout << "y=" << y << std::endl;
  y = i + x;
  std::cout << "y=" << y << std::endl;
  y = x + i;
  std::cout << "y=" << y << std::endl;
  y += dbl + i + x;
  std::cout << "y=" << y << std::endl;
  return 0;
}
