#include "Mechanism.hpp"
#include <cstring>
#include <iostream>

Mechanism::Mechanism() : Node::Node() { this->setMechanismType(""); }

Mechanism::Mechanism(const Mechanism &mechanism) : Node::Node(mechanism) {
  this->setMechanismType(mechanism.mechanismType);
}

Mechanism::Mechanism(const char *name_, double partMass_, double nodeSize_,
                     const char *mechanismType_)
    : Node::Node(name_, partMass_, nodeSize_) {
  if (mechanismType_ == nullptr) {
    this->setMechanismType("");
    return;
  }
  this->setMechanismType(mechanismType_);
}

Mechanism::~Mechanism() { delete[] this->mechanismType; }

void Mechanism::show() const {
  std::cout << "Механизм \"" << this->name << "\" типа \""
            << this->mechanismType << "\" содержит узел, имеющий размер "
            << this->nodeSize << " м и содержащий деталь массой "
            << this->partMass << " кг" << std::endl;
}

void Mechanism::setMechanismType(const char *mechanismType_) {
  if (mechanismType_ == nullptr) {
    throw std::invalid_argument("mechanism type cannot be nullptr");
  }
  delete[] this->mechanismType;
  const size_t bufSz = std::strlen(mechanismType_) + 1;
  this->mechanismType = new char[bufSz];
  std::strncpy(this->mechanismType, mechanismType_, bufSz);
}
