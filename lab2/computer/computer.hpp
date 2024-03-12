#pragma once

#include <cstddef>
#include <iostream>

class Computer {
public:
  Computer();

  Computer(const char *_name, unsigned int _cpuMHz, unsigned int _ramMB,
           unsigned int _storageGB, double _ageYrs, bool _isOperational);

  Computer(const Computer &computer);

  ~Computer();

  unsigned int cpuMHz, ramMB, storageGB;
  bool isOperational;

  void print() const;

  char *getName() const;

  void setName(const char *_name);

  double getAge() const;

  void setAge(double _ageYrs);

  static void dbPrint();

  static void dbClear();

  static void dbResize(size_t cap);

  static void dbAdd(const Computer &computer);

  static void dbDelete(size_t i);

  static Computer *dbGet(size_t i);

  static size_t dbGetSz();

  static void dbReadFile(const char *fname);

  static void dbWriteFile(const char *fname);

  static void dbSort();

  static size_t idxByName(const char *name);

private:
  char *name;
  double ageYrs;

  static const size_t dbCapInit = 1, dbGrowthFactor = 2;
  static Computer **db;
  static size_t dbCap, dbSize;

  static void dbInit();

  friend bool operator<(const Computer &p1, const Computer &p2);

  friend bool operator==(const Computer &p1, const Computer &p2);

  friend std::istream &operator>>(std::istream &in, Computer &computer);

  friend std::ostream &operator<<(std::ostream &out, const Computer &computer);
};

size_t idxByComputerNameUI(std::istream &in, bool demo);

void editComputer(std::istream &in, bool demo);

void computerMenu(std::istream &in, bool demo);
