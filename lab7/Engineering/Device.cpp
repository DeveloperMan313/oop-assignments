#include "Device.hpp"
#include <iostream>

Device::Device() : Mechanism::Mechanism(), deviceCost(0.0) {}

Device::Device(const Device &device)
    : Mechanism::Mechanism(device), deviceCost(device.deviceCost) {}

Device::Device(const char *name_, double partMass_, double nodeSize_,
               const char *mechanismType_, double deviceCost_)
    : Mechanism::Mechanism(name_, partMass_, nodeSize_, mechanismType_) {
  if (deviceCost < 0.0) {
    throw std::invalid_argument("device cost cannot be negative");
  }
  this->deviceCost = deviceCost_;
}

void Device::show() const {
  std::cout << "Изделие \"" << this->name
            << "\", стоимость производства которого " << this->deviceCost
            << " руб., содержит механизм типа \"" << this->mechanismType
            << "\", содержащий узел, имеющий размер " << this->nodeSize
            << " м и содержащий деталь массой " << this->partMass << " кг"
            << std::endl;
}
