#include "planet.hpp"
#include <cstddef>
#include <iostream>
#include <string.h>

Planet **Planet::db;
size_t Planet::dbCap, Planet::dbSize;

Planet::Planet(const char *_name, double _diameter, bool _hasLife,
               unsigned int _moonCount) {
  this->name = new char[strlen(_name) + 1];
  strcpy(this->name, _name);
  this->diameter = _diameter;
  this->hasLife = _hasLife;
  this->moonCount = _moonCount;
}

Planet::Planet(const Planet &planet)
    : Planet(planet.name, planet.diameter, planet.hasLife, planet.moonCount) {}

Planet::~Planet() { delete[] this->name; }

void Planet::print() {
  std::cout << "Название: " << this->name << '\n'
            << "Диаметр: " << this->diameter << '\n'
            << "Жизнь: " << this->hasLife << '\n'
            << "Спутники: " << this->moonCount << std::endl;
}

void Planet::dbPrint() {
  for (size_t i = 0; i < dbSize; ++i) {
    Planet::dbGet(i).print();
    if (i < dbSize - 1) {
      std::cout << '\n';
    }
  }
}

void Planet::dbClear() {
  for (size_t i = 0; i < dbSize; ++i) {
    delete db[i];
  }
  delete[] db;
  db = nullptr;
}

void Planet::dbResize(size_t cap) {
  if (cap < dbSize) {
    return;
  }
  Planet **dbNew = new Planet *[cap];
  for (size_t i = 0; i < dbSize; ++i) {
    dbNew[i] = new Planet(*db[i]);
  }
  dbClear();
  db = dbNew;
  dbCap = cap;
}

void Planet::dbAdd(const Planet &planet) {
  if (db == nullptr) {
    dbInit();
  }
  Planet *planetCopy = new Planet(planet);
  for (size_t i = 0; i < dbSize; ++i) {
    if (db[i] == nullptr) {
      db[i] = planetCopy;
      return;
    }
  }
  if (dbSize == dbCap) {
    dbResize(dbCap * dbGrowthFactor);
  }
  db[dbSize] = planetCopy;
  ++dbSize;
}

void Planet::dbDelete(size_t i) {
  if (i >= dbSize) {
    return;
  }
  delete db[i];
}

Planet &Planet::dbGet(size_t i) { return *db[i]; }

void Planet::dbInit() {
  dbCap = dbCapInit;
  db = new Planet *[dbCap];
  dbSize = 0;
}

size_t Planet::dbGetSz() { return dbSize; }

std::ifstream &operator>>(std::ifstream &in, Planet &planet) {
  in >> planet.name >> planet.diameter >> planet.hasLife >> planet.moonCount;
  return in;
}

std::ofstream &operator<<(std::ofstream &out, const Planet &planet) {
  out << planet.name << ' ' << planet.diameter << ' ' << planet.hasLife << ' '
      << planet.moonCount << std::endl;
  return out;
}

void addSolarSystem() {
  Planet::dbAdd(Planet("Меркурий", 4878.0, false, 0));
  Planet::dbAdd(Planet("Венера", 12104.0, false, 0));
  Planet::dbAdd(Planet("Земля", 12774.0, true, 1));
  Planet::dbAdd(Planet("Марс", 6786.0, true, 2));
  Planet::dbAdd(Planet("Юпитер", 142796.0, false, 16));
  Planet::dbAdd(Planet("Сатурн", 120000.0, false, 17));
  Planet::dbAdd(Planet("Уран", 51108.0, false, 5));
  Planet::dbAdd(Planet("Нептун", 49600.0, false, 2));
  Planet::dbAdd(Planet("Плутон", 2280.0, false, 1));
}
