#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Mechanism.hpp"

class Device : public Mechanism {
public:
  Device();

  Device(const Device &device);

  explicit Device(const char *name_, double partMass_ = 0.0,
                  double nodeSize_ = 0.0, const char *mechanismType_ = nullptr,
                  double deviceCost_ = 0.0);

  void show() const override;

protected:
  double deviceCost;
};

#endif
