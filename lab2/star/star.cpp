#include "star.hpp"
#include "../input/input.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>

Star **Star::db;
size_t Star::dbCap, Star::dbSize;

Star::Star() : name(nullptr), diameter(0.0), mass(1.0), temp(0.0) {}

Star::Star(const char *_name, double _diameter, bool _mass, unsigned int _temp)
    : name(nullptr) {
  this->setName(_name);
  this->diameter = _diameter;
  this->mass = _mass;
  this->temp = _temp;
}

Star::Star(const Star &star)
    : Star(star.name, star.diameter, star.mass, star.temp) {}

Star::~Star() { delete[] this->name; }

void Star::print() const {
  std::cout << "Название: " << this->name << '\n'
            << "Диаметр: " << this->diameter << '\n'
            << "Масса: " << this->mass << '\n'
            << "Температура: " << this->temp << std::endl;
}

char *Star::getName() const { return this->name; }

void Star::setName(const char *_name) {
  delete[] this->name;
  const size_t bufSz = strlen(_name) + 1;
  this->name = new char[bufSz];
  strncpy(this->name, _name, bufSz);
}

double Star::getMass() { return this->mass; }

void Star::setMass(double _mass) {
  if (_mass > 0) {
    this->mass = _mass;
  }
}

double Star::getTemp() { return this->temp; }

void Star::setTemp(double _temp) {
  if (_temp >= 0) {
    this->temp = _temp;
  }
}

double Star::getDiameter() { return this->diameter; }

void Star::setDiameter(double _diameter) {
  if (_diameter >= 0) {
    this->diameter = _diameter;
  }
}

void Star::dbPrint() {
  for (size_t i = 0; i < dbSize; ++i) {
    const Star *starPtr = Star::dbGet(i);
    if (starPtr == nullptr) {
      continue;
    }
    starPtr->print();
    if (i < dbSize - 1) {
      std::cout << '\n';
    }
  }
}

void Star::dbClear() {
  for (size_t i = 0; i < dbSize; ++i) {
    delete db[i];
  }
  delete[] db;
  db = nullptr;
}

void Star::dbResize(size_t cap) {
  if (cap < dbSize) {
    return;
  }
  Star **dbNew = new Star *[cap];
  for (size_t i = 0; i < dbSize; ++i) {
    dbNew[i] = new Star(*db[i]);
  }
  dbClear();
  db = dbNew;
  dbCap = cap;
}

void Star::dbAdd(const Star &star) {
  if (db == nullptr) {
    dbInit();
  }
  Star *starCopy = new Star(star);
  for (size_t i = 0; i < dbSize; ++i) {
    if (db[i] == nullptr) {
      db[i] = starCopy;
      return;
    }
  }
  if (dbSize == dbCap) {
    dbResize(dbCap * dbGrowthFactor);
  }
  db[dbSize] = starCopy;
  ++dbSize;
}

void Star::dbDelete(size_t i) {
  if (i >= dbSize) {
    return;
  }
  delete db[i];
  db[i] = nullptr;
}

Star *Star::dbGet(size_t i) { return db[i]; }

void Star::dbInit() {
  dbCap = dbCapInit;
  db = new Star *[dbCap];
  dbSize = 0;
}

size_t Star::dbGetSz() { return dbSize; }

void Star::dbReadFile(const char *fname) {
  std::ifstream file(fname, std::ios::binary);
  if (!file) {
    std::cout << "Ошибка открытия файла" << std::endl;
    return;
  }
  dbClear();
  dbInit();
  Star star;
  while (file >> star) {
    dbAdd(star);
  }
}

void Star::dbWriteFile(const char *fname) {
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

void Star::dbSort() {
  const auto cmp = [](const Star *p1, const Star *p2) { return *p2 < *p1; };
  std::sort(db, db + dbSize, cmp);
}

size_t Star::idxByName(const char *name) {
  const size_t dbSz = Star::dbGetSz();
  for (size_t i = 0; i < dbSz; ++i) {
    const Star *starPtr = Star::dbGet(i);
    if (starPtr == nullptr) {
      continue;
    }
    if (strcmp(name, starPtr->getName()) == 0) {
      return i;
    }
  }
  throw std::invalid_argument("not found");
}

bool operator<(const Star &p1, const Star &p2) {
  return p1.diameter < p2.diameter;
}

bool operator==(const Star &p1, const Star &p2) {
  return p1.diameter == p2.diameter;
}

std::istream &operator>>(std::istream &in, Star &star) {
  char *name = readString(in);
  in >> star.diameter >> star.mass >> star.temp;
  delete[] star.name;
  star.name = name;
  return in;
}

std::ostream &operator<<(std::ostream &out, const Star &star) {
  out << star.name << ' ' << star.diameter << ' ' << star.mass << ' '
      << star.temp;
  return out;
}

size_t idxByStarNameUI(std::istream &in, bool demo) {
  std::cout << "Введите имя звезды:" << std::endl;
  char *name = readString(in);
  if (demo) {
    std::cout << name << std::endl;
  }
  Star *starPtr;
  try {
    const size_t idx = Star::idxByName(name);
    delete[] name;
    return idx;
  } catch (const std::invalid_argument &) {
    std::cout << "Звезда не найдена" << std::endl;
    delete[] name;
    throw std::invalid_argument("not found");
  }
}

void editStar(std::istream &in, bool demo) {
  Star *starPtr;
  try {
    starPtr = Star::dbGet(idxByStarNameUI(in, demo));
  } catch (const std::invalid_argument &) {
    return;
  }
  Star &star = *starPtr;
  while (true) {
    std::cout << "Выберите параметр для изменения:\n"
                 "1 - имя\n"
                 "2 - диаметр\n"
                 "3 - масса\n"
                 "4 - температура\n"
                 "5 - отменить изменение"
              << std::endl;
    int option;
    in >> option;
    switch (option) {
    case 1: {
      char *newName = readString(in);
      if (demo) {
        std::cout << newName << std::endl;
      }
      star.setName(newName);
      delete[] newName;
      break;
    }
    case 2: {
      double diameter;
      in >> diameter;
      if (demo) {
        std::cout << diameter << std::endl;
      }
      star.setDiameter(diameter);
      break;
    }
    case 3: {
      double mass;
      in >> mass;
      star.setMass(mass);
      if (demo) {
        std::cout << star.getMass() << std::endl;
      }
      break;
    }
    case 4: {
      double temp;
      in >> temp;
      star.setTemp(temp);
      if (demo) {
        std::cout << star.getTemp() << std::endl;
      }
      break;
    }
    case 5:
      return;
    default:
      std::cout << "Неверная опция" << std::endl;
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl;
      continue;
    }
    break;
  }
}

void starMenu(std::istream &in, bool demo) {
  while (true) {
    std::cout << "Выберите действие:\n"
                 "1 - прочитать БД из файла\n"
                 "2 - записать БД в файл\n"
                 "3 - отсортировать БД по размеру планет\n"
                 "4 - добавить новый объект в БД\n"
                 "5 - удалить объект из БД\n"
                 "6 - редактировать БД\n"
                 "7 - вывести БД на экран\n"
                 "8 - выйти"
              << std::endl;
    int option;
    in >> option;
    switch (option) {
    case 1: {
      char *fname = readString(in);
      if (demo) {
        std::cout << fname << std::endl;
      }
      Star::dbReadFile(fname);
      delete[] fname;
      break;
    }
    case 2: {
      char *fname = readString(in);
      if (demo) {
        std::cout << fname << std::endl;
      }
      Star::dbWriteFile(fname);
      delete[] fname;
      break;
    }
    case 3:
      Star::dbSort();
      break;
    case 4: {
      Star star;
      in >> star;
      if (demo) {
        std::cout << star << std::endl;
      }
      Star::dbAdd(star);
      break;
    }
    case 5: {
      try {
        Star::dbDelete(idxByStarNameUI(in, demo));
      } catch (const std::invalid_argument &) {}
      break;
    }
    case 6:
      editStar(in, demo);
      break;
    case 7:
      Star::dbPrint();
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
