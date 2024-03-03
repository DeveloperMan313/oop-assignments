#include "computer/computer.hpp"
#include "input/input.hpp"
#include "planet/planet.hpp"
#include <clocale>
#include <iostream>
#include <limits>
#include <sstream>

void mainMenu(std::istream &in, bool demo) {
  while (true) {
    std::cout << "Выберите тип объектов:\n"
                 "1 - планеты\n"
                 "2 - компьютеры\n"
                 "3 - выйти"
              << std::endl;
    std::cout << inputIndicator;
    int option;
    in >> option;
    if (demo) {
      std::cout << option << std::endl;
    }
    switch (option) {
    case 1:
      planetMenu(in, demo);
      break;
    case 2:
      computerMenu(in, demo);
      break;
    case 3:
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

void run(bool demo) {
  if (demo) {
    std::cout << "Демонстрационный режим. Чтобы перейти в интерактивный режим, "
                 "запустите с аргументом i."
              << std::endl;
    const char *demoInput =
        "1 0 7 4 Меркурий 4878 0 0 7 4 Венера 12104 0 0 7 2 db.txt 5 Меркурий "
        "7 1 db.txt 7 4 Марс 6786 1 2 7 0 6 Марс 1 Марс_2100 2 6790 3 1 4 3 5 "
        "7 3 7 8 3";
    std::stringstream demoStream(demoInput);
    mainMenu(demoStream, true);
  } else {
    mainMenu(std::cin, false);
  }
  Planet::dbClear();
  Computer::dbClear();
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, ".UTF8");
  const bool interactive = argc > 1 && argv[1][0] == 'i';
  run(!interactive);
  return 0;
}
