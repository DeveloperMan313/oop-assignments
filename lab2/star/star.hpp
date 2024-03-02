#pragma once

#include <cstddef>
#include <iostream>

class Star {
public:
  Star();

  Star(const char *_name, double _diameter, bool _mass, unsigned int _temp);

  Star(const Star &star);

  ~Star();

  void print() const;

  char *getName() const;

  void setName(const char *_name);

  double getMass();

  void setMass(double _mass);

  double getTemp();

  void setTemp(double _temp);

  double getDiameter();

  void setDiameter(double _diameter);

  static void dbPrint();

  static void dbClear();

  static void dbResize(size_t cap);

  static void dbAdd(const Star &star);

  static void dbDelete(size_t i);

  static Star *dbGet(size_t i);

  static size_t dbGetSz();

  static void dbReadFile(const char *fname);

  static void dbWriteFile(const char *fname);

  static void dbSort();

  static size_t idxByName(const char *name);

private:
  char *name;
  double diameter, mass, temp;

  static const size_t dbCapInit = 1, dbGrowthFactor = 2;
  static Star **db;
  static size_t dbCap, dbSize;

  static void dbInit();

  friend bool operator<(const Star &p1, const Star &p2);

  friend bool operator==(const Star &p1, const Star &p2);

  friend std::istream &operator>>(std::istream &in, Star &star);

  friend std::ostream &operator<<(std::ostream &out, const Star &star);
};

size_t idxByStarNameUI(std::istream &in, bool demo);

void editStar(std::istream &in, bool demo);

void starMenu(std::istream &in, bool demo);
