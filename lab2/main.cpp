#include "planet/planet.hpp"
#include <clocale>

int main() {
  setlocale(LC_ALL, "Russian");
  addSolarSystem();
  Planet::dbPrint();
  Planet::dbClear();
  return 0;
}
