#pragma once

#include <cstddef>
#include <fstream>

class Planet {
public:
  Planet(const char *_name, double _diameter, bool _hasLife,
         unsigned int _moonCount);

  Planet(const Planet &planet);

  ~Planet();

  char *name;
  double diameter;
  bool hasLife;
  unsigned int moonCount;

  void print();

  static void dbPrint();

  static void dbClear();

  static void dbResize(size_t cap);

  static void dbAdd(const Planet &planet);

  static void dbDelete(size_t i);

  static Planet &dbGet(size_t i);

  static size_t dbGetSz();

private:
  static const size_t dbCapInit = 1, dbGrowthFactor = 2;
  static Planet **db;
  static size_t dbCap, dbSize;

  static void dbInit();
};

std::ifstream &operator>>(std::ifstream &in, Planet &planet);

std::ofstream &operator<<(std::ofstream &out, const Planet &planet);

void addSolarSystem();
