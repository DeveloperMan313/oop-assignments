#include "computer.hpp"
#include "../input/input.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>

Computer **Computer::db;
size_t Computer::dbCap, Computer::dbSize;

Computer::Computer()
    : name(nullptr), cpuMHz(0u), ramMB(0u), storageGB(0u), ageYrs(0.0),
      isOperational(false) {}

Computer::Computer(const char *_name, unsigned int _cpuMHz, unsigned int _ramMB,
                   unsigned int _storageGB, double _ageYrs, bool _isOperational)
    : name(nullptr), cpuMHz(_cpuMHz), ramMB(_ramMB), storageGB(_storageGB),
      ageYrs(_ageYrs), isOperational(_isOperational) {
  this->setName(_name);
}

Computer::Computer(const Computer &computer)
    : Computer(computer.name, computer.cpuMHz, computer.ramMB,
               computer.storageGB, computer.ageYrs, computer.isOperational) {}

Computer::~Computer() { delete[] this->name; }

void Computer::print() const {
  std::cout << "Имя: " << this->name << '\n'
            << "Частота CPU, МГц: " << this->cpuMHz << '\n'
            << "Объём RAM, МБ: " << this->ramMB << '\n'
            << "Объём хранилища, ГБ: " << this->storageGB << '\n'
            << "Возраст, лет: " << this->ageYrs << '\n'
            << "В рабочем состоянии: " << this->isOperational << std::endl;
}

char *Computer::getName() const { return this->name; }

void Computer::setName(const char *_name) {
  delete[] this->name;
  const size_t bufSz = strlen(_name) + 1;
  this->name = new char[bufSz];
  strncpy(this->name, _name, bufSz);
}

double Computer::getAge() const { return this->ageYrs; }

void Computer::setAge(double _ageYrs) {
  if (_ageYrs >= 0) {
    this->ageYrs = _ageYrs;
  }
}

void Computer::dbPrint() {
  bool found = false;
  for (size_t i = 0; i < dbSize; ++i) {
    const Computer *computerPtr = Computer::dbGet(i);
    if (computerPtr == nullptr) {
      continue;
    }
    found = true;
    computerPtr->print();
    if (i < dbSize - 1) {
      std::cout << '\n';
    }
  }
  if (!found) {
    std::cout << "нет записей" << std::endl;
  }
}

void Computer::dbClear() {
  for (size_t i = 0; i < dbSize; ++i) {
    delete db[i];
  }
  delete[] db;
  db = nullptr;
}

void Computer::dbResize(size_t cap) {
  if (cap < dbSize) {
    return;
  }
  Computer **dbNew = new Computer *[cap];
  for (size_t i = 0; i < dbSize; ++i) {
    dbNew[i] = new Computer(*db[i]);
  }
  dbClear();
  db = dbNew;
  dbCap = cap;
}

void Computer::dbAdd(const Computer &computer) {
  if (db == nullptr) {
    dbInit();
  }
  Computer *computerCopy = new Computer(computer);
  for (size_t i = 0; i < dbSize; ++i) {
    if (db[i] == nullptr) {
      db[i] = computerCopy;
      return;
    }
  }
  if (dbSize == dbCap) {
    dbResize(dbCap * dbGrowthFactor);
  }
  db[dbSize] = computerCopy;
  ++dbSize;
}

void Computer::dbDelete(size_t i) {
  if (i >= dbSize) {
    return;
  }
  delete db[i];
  db[i] = nullptr;
}

Computer *Computer::dbGet(size_t i) { return db[i]; }

void Computer::dbInit() {
  dbCap = dbCapInit;
  db = new Computer *[dbCap];
  dbSize = 0;
}

size_t Computer::dbGetSz() { return dbSize; }

void Computer::dbReadFile(const char *fname) {
  std::ifstream file(fname, std::ios::binary);
  if (!file) {
    std::cout << "Ошибка открытия файла" << std::endl;
    return;
  }
  dbClear();
  dbInit();
  Computer computer;
  while (file >> computer) {
    dbAdd(computer);
  }
}

void Computer::dbWriteFile(const char *fname) {
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

void Computer::dbSort() {
  const auto cmp = [](const Computer *p1, const Computer *p2) {
    return *p2 < *p1;
  };
  std::sort(db, db + dbSize, cmp);
}

size_t Computer::idxByName(const char *name) {
  const size_t dbSz = Computer::dbGetSz();
  for (size_t i = 0; i < dbSz; ++i) {
    const Computer *computerPtr = Computer::dbGet(i);
    if (computerPtr == nullptr) {
      continue;
    }
    if (strcmp(name, computerPtr->getName()) == 0) {
      return i;
    }
  }
  throw std::invalid_argument("not found");
}

bool operator<(const Computer &p1, const Computer &p2) {
  return p1.cpuMHz < p2.cpuMHz;
}

bool operator==(const Computer &p1, const Computer &p2) {
  return p1.cpuMHz == p2.cpuMHz;
}

std::istream &operator>>(std::istream &in, Computer &computer) {
  char *name = readString(in);
  double ageYrs;
  in >> computer.cpuMHz >> computer.ramMB >> computer.storageGB >> ageYrs >>
      computer.isOperational;
  delete[] computer.name;
  computer.name = name;
  computer.setAge(ageYrs);
  return in;
}

std::ostream &operator<<(std::ostream &out, const Computer &computer) {
  out << computer.name << ' ' << computer.cpuMHz << ' ' << computer.ramMB << ' '
      << computer.storageGB << ' ' << computer.ageYrs << ' '
      << computer.isOperational;
  return out;
}

size_t idxByComputerNameUI(std::istream &in, bool demo) {
  std::cout << "Введите имя компьютера:" << std::endl;
  char *name = readString(in);
  if (demo) {
    std::cout << name << std::endl;
  }
  try {
    const size_t idx = Computer::idxByName(name);
    delete[] name;
    return idx;
  } catch (const std::invalid_argument &) {
    std::cout << "Компьютер не найден" << std::endl;
    delete[] name;
    throw std::invalid_argument("not found");
  }
}

void editComputer(std::istream &in, bool demo) {
  Computer *computerPtr;
  try {
    computerPtr = Computer::dbGet(idxByComputerNameUI(in, demo));
  } catch (const std::invalid_argument &) {
    return;
  }
  Computer &computer = *computerPtr;
  while (true) {
    std::cout << "Выберите параметр для изменения:\n"
                 "1 - имя\n"
                 "2 - частота CPU, МГц\n"
                 "3 - объём RAM, МБ\n"
                 "4 - объём хранилища, ГБ\n"
                 "5 - возраст, лет\n"
                 "6 - в рабочем состоянии\n"
                 "7 - выйти"
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
      computer.setName(newName);
      delete[] newName;
      break;
    }
    case 2:
      in >> computer.cpuMHz;
      if (demo) {
        std::cout << computer.cpuMHz << std::endl;
      }
      break;
    case 3:
      in >> computer.ramMB;
      if (demo) {
        std::cout << computer.ramMB << std::endl;
      }
      break;
    case 4:
      in >> computer.storageGB;
      if (demo) {
        std::cout << computer.storageGB << std::endl;
      }
      break;
    case 5: {
      double ageYrs;
      in >> ageYrs;
      if (demo) {
        std::cout << ageYrs << std::endl;
      }
      computer.setAge(ageYrs);
      break;
    }
    case 6:
      in >> computer.isOperational;
      if (demo) {
        std::cout << computer.isOperational << std::endl;
      }
      break;
    case 7:
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

void computerMenu(std::istream &in, bool demo) {
  while (true) {
    std::cout << "Выберите действие:\n"
                 "0 - помощь"
              << std::endl;
    const char *help = "1 - прочитать БД из файла\n"
                       "2 - записать БД в файл\n"
                       "3 - отсортировать БД по частоте процессоров\n"
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
      Computer::dbReadFile(fname);
      delete[] fname;
      break;
    }
    case 2: {
      std::cout << "Введите имя файла" << std::endl;
      char *fname = readString(in);
      if (demo) {
        std::cout << fname << std::endl;
      }
      Computer::dbWriteFile(fname);
      delete[] fname;
      break;
    }
    case 3:
      Computer::dbSort();
      break;
    case 4: {
      std::cout << "Введите имя, частоту CPU в МГц, объём RAM в МБ, объём "
                   "хранилища в ГБ, возраст в годах, в рабочем ли состоянии"
                << std::endl;
      Computer computer;
      in >> computer;
      if (demo) {
        std::cout << computer << std::endl;
      }
      Computer::dbAdd(computer);
      break;
    }
    case 5:
      try {
        Computer::dbDelete(idxByComputerNameUI(in, demo));
      } catch (const std::invalid_argument &) {}
      break;
    case 6:
      editComputer(in, demo);
      break;
    case 7:
      std::cout << "БД компьютеров:" << std::endl;
      Computer::dbPrint();
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
