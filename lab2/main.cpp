#include "planet/planet.hpp"
#include <clocale>
#include <iostream>

int main() {
  setlocale(LC_ALL, ".UTF8");
  planetMenu(std::cin, false);
  Planet::dbClear();
  return 0;
}
