#ifndef MECHANISM_HPP
#define MECHANISM_HPP

#include "Node.hpp"

class Mechanism : public Node {
public:
  Mechanism();

  Mechanism(const Mechanism &mechanism);

  explicit Mechanism(const char *name_, double partMass_ = 0.0,
                     double nodeSize_ = 0.0,
                     const char *mechanismType_ = nullptr);

  ~Mechanism() override;

  void show() const override;

protected:
  char *mechanismType;

  void setMechanismType(const char *mechanismType_);
};

#endif
