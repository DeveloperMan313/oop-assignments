#include "Mechanism.hpp"
#include <iostream>

void Mechanism::show() const {
  std::cout << "Механизм \"" << this->name << "\" имеет массу " << this->mass
            << " кг" << std::endl;
}
