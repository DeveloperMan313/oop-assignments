#include "planet/planet.hpp"
#include <clocale>

int main() {
  setlocale(LC_ALL, ".UTF8");
  addSolarSystem();
  const char *fname = "db.txt";
  Planet::dbWriteFile(fname);
  Planet::dbReadFile(fname);
  Planet::dbPrint();
  Planet::dbClear();
  return 0;
}
