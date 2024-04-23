#include "Part.hpp"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

Part *Part::dllTop = nullptr;

Part::Part() : name(nullptr), partMass(0.0), prev(nullptr), next(nullptr) {
  this->setName("");
  this->dllAdd();
}

Part::Part(const Part &part) : name(nullptr), prev(nullptr), next(nullptr) {
  this->setName(part.name);
  this->partMass = part.partMass;
  this->dllAdd();
}

Part::Part(const char *name_, double partMass_)
    : name(nullptr), prev(nullptr), next(nullptr) {
  if (partMass_ < 0.0) {
    throw std::invalid_argument("part mass cannot be negative");
  }
  this->setName(name_);
  this->partMass = partMass_;
  this->dllAdd();
}

Part::~Part() {
  this->dllRemove();
  delete[] this->name;
}

void Part::dllAdd() {
  if (this->prev != nullptr) {
    return;
  }
  if (Part::dllTop == nullptr) {
    Part::dllTop = this;
    return;
  }
  Part *partPtr = Part::dllTop;
  while (partPtr->next != nullptr) {
    partPtr = partPtr->next;
  }
  partPtr->next = this;
  this->prev = partPtr;
}

void Part::dllRemove() {
  if (this->prev == nullptr) {
    return;
  }
  if (Part::dllTop == this) {
    Part::dllTop = nullptr;
  }
  this->prev->next = this->next;
  if (this->next != nullptr) {
    this->next->prev = this->prev;
  }
  this->prev = this->next = nullptr;
}

void Part::show() const {
  std::cout << "Деталь \"" << this->name << "\" имеет массу " << this->partMass
            << " кг" << std::endl;
}

void Part::showList() {
  Part *partPtr = Part::dllTop;
  while (partPtr != nullptr) {
    partPtr->show();
    partPtr = partPtr->next;
  }
}

void Part::setName(const char *name_) {
  if (name_ == nullptr) {
    throw std::invalid_argument("name cannot be nullptr");
  }
  delete[] this->name;
  const size_t bufSz = std::strlen(name_) + 1;
  this->name = new char[bufSz];
  std::strncpy(this->name, name_, bufSz);
}
