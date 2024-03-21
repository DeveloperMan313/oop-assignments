#include "Polynomial/Polynomial.hpp"
#include <clocale>
#include <iostream>

int main() {
  setlocale(LC_ALL, ".UTF8");
  Polynomial p1, p2;
  std::cout << "Введите полином p1" << std::endl;
  std::cin >> p1;
  std::cout << "Введите полином p2" << std::endl;
  std::cin >> p2;
  std::cout << std::endl;
  std::cout << "p1 = " << p1 << std::endl;
  std::cout << "p2 = " << p2 << std::endl;
  std::cout << "p1 + p2 = " << p1 + p2 << std::endl;
  std::cout << "p1 * p2 = " << p1 * p2 << std::endl;
  return 0;
}
