#include "planet.hpp"
#include "../input/input.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>

Planet **Planet::db;
size_t Planet::dbCap, Planet::dbSize;

Planet::Planet()
    : name(nullptr), diameter(0.0), hasLife(false), moonCount(0u) {}

Planet::Planet(const char *_name, double _diameter, bool _hasLife,
               unsigned int _moonCount)
    : name(nullptr), diameter(_diameter), hasLife(_hasLife),
      moonCount(_moonCount) {
  this->setName(_name);
}

Planet::Planet(const Planet &planet)
    : Planet(planet.name, planet.diameter, planet.hasLife, planet.moonCount) {}

Planet::~Planet() { delete[] this->name; }

void Planet::print() const {
  std::cout << "Имя: " << this->name << '\n'
            << "Диаметр, км: " << this->diameter << '\n'
            << "Жизнь: " << this->hasLife << '\n'
            << "Спутники: " << this->moonCount << std::endl;
}

char *Planet::getName() const { return this->name; }

void Planet::setName(const char *_name) {
  delete[] this->name;
  const size_t bufSz = strlen(_name) + 1;
  this->name = new char[bufSz];
  strncpy(this->name, _name, bufSz);
}

double Planet::getDiameter() const { return this->diameter; }

void Planet::setDiameter(double _diameter) {
  if (_diameter >= 0) {
    this->diameter = _diameter;
  }
}

void Planet::dbPrint() {
  if (dbSize == 0) {
    std::cout << "нет записей" << std::endl;
    return;
  }
  for (size_t i = 0; i < dbSize; ++i) {
    const Planet *planetPtr = Planet::dbGet(i);
    if (planetPtr == nullptr) {
      continue;
    }
    planetPtr->print();
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

Planet *Planet::dbGet(size_t i) { return db[i]; }

void Planet::dbInit() {
  dbCap = dbCapInit;
  db = new Planet *[dbCap];
  dbSize = 0;
}

size_t Planet::dbGetSz() { return dbSize; }

void Planet::dbReadFile(const char *fname) {
  std::ifstream file(fname, std::ios::binary);
  if (!file) {
    std::cout << "Ошибка открытия файла" << std::endl;
    return;
  }
  dbClear();
  dbInit();
  Planet planet;
  while (file >> planet) {
    dbAdd(planet);
  }
}

void Planet::dbWriteFile(const char *fname) {
  std::ofstream file(fname, std::ios::binary);
  if (!file) {
    std::cout << "Ошибка открытия файла" << std::endl;
    return;
  }
  file.clear();
  for (size_t i = 0; i < dbSize; ++i) {
    if (db[i] == nullptr) {
      continue;
    }
    file << *db[i] << '\n';
  }
}

void Planet::dbSort() {
  const auto cmp = [](const Planet *p1, const Planet *p2) { return *p2 < *p1; };
  std::sort(db, db + dbSize, cmp);
}

size_t Planet::idxByName(const char *name) {
  const size_t dbSz = Planet::dbGetSz();
  for (size_t i = 0; i < dbSz; ++i) {
    const Planet *planetPtr = Planet::dbGet(i);
    if (planetPtr == nullptr) {
      continue;
    }
    if (strcmp(name, planetPtr->getName()) == 0) {
      return i;
    }
  }
  throw std::invalid_argument("not found");
}

bool operator<(const Planet &p1, const Planet &p2) {
  return p1.diameter < p2.diameter;
}

bool operator==(const Planet &p1, const Planet &p2) {
  return p1.diameter == p2.diameter;
}

std::istream &operator>>(std::istream &in, Planet &planet) {
  char *name = readString(in);
  in >> planet.diameter >> planet.hasLife >> planet.moonCount;
  delete[] planet.name;
  planet.name = name;
  return in;
}

std::ostream &operator<<(std::ostream &out, const Planet &planet) {
  out << planet.name << ' ' << planet.diameter << ' ' << planet.hasLife << ' '
      << planet.moonCount;
  return out;
}

size_t idxByPlanetNameUI(std::istream &in, bool demo) {
  std::cout << "Введите имя планеты:" << std::endl;
  char *name = readString(in);
  if (demo) {
    std::cout << name << std::endl;
  }
  Planet *planetPtr;
  try {
    const size_t idx = Planet::idxByName(name);
    delete[] name;
    return idx;
  } catch (const std::invalid_argument &) {
    std::cout << "Планета не найдена" << std::endl;
    delete[] name;
    throw std::invalid_argument("not found");
  }
}

void editPlanet(std::istream &in, bool demo) {
  Planet *planetPtr;
  try {
    planetPtr = Planet::dbGet(idxByPlanetNameUI(in, demo));
  } catch (const std::invalid_argument &) {
    return;
  }
  Planet &planet = *planetPtr;
  while (true) {
    std::cout << "Выберите параметр для изменения:\n"
                 "1 - имя\n"
                 "2 - диаметр, км\n"
                 "3 - наличие жизни\n"
                 "4 - количество спутников\n"
                 "5 - выйти"
              << std::endl;
    std::cout << inputIndicator;
    int option;
    in >> option;
    if (demo) {
      std::cout << option << std::endl;
    }
    switch (option) {
    case 1: {
      char *newName = readString(in);
      if (demo) {
        std::cout << newName << std::endl;
      }
      planet.setName(newName);
      delete[] newName;
      break;
    }
    case 2: {
      double diameter;
      in >> diameter;
      if (demo) {
        std::cout << diameter << std::endl;
      }
      planet.setDiameter(diameter);
      break;
    }
    case 3:
      in >> planet.hasLife;
      if (demo) {
        std::cout << planet.hasLife << std::endl;
      }
      break;
    case 4:
      in >> planet.moonCount;
      if (demo) {
        std::cout << planet.moonCount << std::endl;
      }
      break;
    case 5:
      return;
    default:
      std::cout << "Неверная опция" << std::endl;
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl;
      continue;
    }
    std::cout << std::endl;
  }
}

void planetMenu(std::istream &in, bool demo) {
  while (true) {
    std::cout << "Выберите действие:\n"
                 "0 - помощь"
              << std::endl;
    const char *help = "1 - прочитать БД из файла\n"
                       "2 - записать БД в файл\n"
                       "3 - отсортировать БД по размеру планет\n"
                       "4 - добавить новый объект в БД\n"
                       "5 - удалить объект из БД\n"
                       "6 - редактировать БД\n"
                       "7 - вывести БД на экран\n"
                       "8 - выйти";
    std::cout << inputIndicator;
    int option;
    in >> option;
    if (demo) {
      std::cout << option << std::endl;
    }
    switch (option) {
    case 0:
      std::cout << help << std::endl;
      break;
    case 1: {
      std::cout << "Введите имя файла" << std::endl;
      char *fname = readString(in);
      if (demo) {
        std::cout << fname << std::endl;
      }
      Planet::dbReadFile(fname);
      delete[] fname;
      break;
    }
    case 2: {
      std::cout << "Введите имя файла" << std::endl;
      char *fname = readString(in);
      if (demo) {
        std::cout << fname << std::endl;
      }
      Planet::dbWriteFile(fname);
      delete[] fname;
      break;
    }
    case 3:
      Planet::dbSort();
      break;
    case 4: {
      std::cout
          << "Введите имя, диаметр в км, наличие жизни, количество спутников"
          << std::endl;
      Planet planet;
      in >> planet;
      if (demo) {
        std::cout << planet << std::endl;
      }
      Planet::dbAdd(planet);
      break;
    }
    case 5:
      try {
        Planet::dbDelete(idxByPlanetNameUI(in, demo));
      } catch (const std::invalid_argument &) {}
      break;
    case 6:
      editPlanet(in, demo);
      break;
    case 7:
      std::cout << "БД планет:" << std::endl;
      Planet::dbPrint();
      break;
    case 8:
      return;
    default:
      std::cout << "Неверная опция" << std::endl;
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl;
      continue;
    }
    std::cout << std::endl;
  }
}
