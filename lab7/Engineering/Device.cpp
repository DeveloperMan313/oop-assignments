#include "Device.hpp"
#include <iostream>

void Device::show() const {
  std::cout << "Изделие \"" << this->name << "\" имеет массу " << this->mass
            << " кг" << std::endl;
}
