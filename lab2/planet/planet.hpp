#pragma once

#include <cstddef>
#include <iostream>

class Planet {
public:
  Planet();

  Planet(const char *_name, double _diameter, bool _hasLife,
         unsigned int _moonCount);

  Planet(const Planet &planet);

  ~Planet();

  bool hasLife;
  unsigned int moonCount;

  void print() const;

  char *getName() const;

  void setName(const char *_name);

  double getDiameter() const;

  void setDiameter(double _diameter);

  static void dbPrint();

  static void dbClear();

  static void dbResize(size_t cap);

  static void dbAdd(const Planet &planet);

  static void dbDelete(size_t i);

  static Planet *dbGet(size_t i);

  static size_t dbGetSz();

  static void dbReadFile(const char *fname);

  static void dbWriteFile(const char *fname);

  static void dbSort();

  static size_t idxByName(const char *name);

private:
  char *name;
  double diameter;

  static const size_t dbCapInit = 1, dbGrowthFactor = 2;
  static Planet **db;
  static size_t dbCap, dbSize;

  static void dbInit();

  friend bool operator<(const Planet &p1, const Planet &p2);

  friend bool operator==(const Planet &p1, const Planet &p2);

  friend std::istream &operator>>(std::istream &in, Planet &planet);

  friend std::ostream &operator<<(std::ostream &out, const Planet &planet);
};

size_t idxByPlanetNameUI(std::istream &in, bool demo);

void editPlanet(std::istream &in, bool demo);

void planetMenu(std::istream &in, bool demo);
