#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Mechanism.hpp"

class Device : public Mechanism {
public:
  using Mechanism::Mechanism;

  void show() const override;
};

#endif
