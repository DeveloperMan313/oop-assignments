#include "planet.hpp"
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

Planet **Planet::db;
size_t Planet::dbCap, Planet::dbSize;

Planet::Planet()
    : name(nullptr), diameter(0.0), hasLife(false), moonCount(0u) {}

Planet::Planet(const char *_name, double _diameter, bool _hasLife,
               unsigned int _moonCount)
    : name(nullptr) {
  this->setName(_name);
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

char *Planet::getName() const { return this->name; }

void Planet::setName(const char *_name) {
  delete[] this->name;
  const size_t bufSz = strlen(_name) + 1;
  this->name = new char[bufSz];
  strcpy_s(this->name, bufSz, _name);
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
  db[i] = nullptr;
}

Planet &Planet::dbGet(size_t i) { return *db[i]; }

void Planet::dbInit() {
  dbCap = dbCapInit;
  db = new Planet *[dbCap];
  dbSize = 0;
}

size_t Planet::dbGetSz() { return dbSize; }

void Planet::dbReadFile(const char *fname) {
  dbClear();
  std::ifstream file(fname, std::ios::binary);
  Planet planet;
  while (file >> planet) {
    dbAdd(planet);
  }
}

void Planet::dbWriteFile(const char *fname) {
  std::ofstream file(fname, std::ios::binary);
  file.clear();
  for (size_t i = 0; i < dbSize; ++i) {
    if (db[i] == nullptr) {
      continue;
    }
    file << *db[i];
  }
}

std::ifstream &operator>>(std::ifstream &in, Planet &planet) {
  const size_t pos = in.tellg();
  size_t nameLen;
  for (size_t i = 0;; ++i) {
    char c;
    if (!in.get(c) || c == ' ') {
      nameLen = i;
      break;
    }
  }
  in.seekg(pos);
  char *_name = new char[nameLen + 1];
  in >> _name >> planet.diameter >> planet.hasLife >> planet.moonCount;
  planet.setName(_name);
  delete[] _name;
  return in;
}

std::ofstream &operator<<(std::ofstream &out, const Planet &planet) {
  out << planet.getName() << ' ' << planet.diameter << ' ' << planet.hasLife
      << ' ' << planet.moonCount << std::endl;
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
