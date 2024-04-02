#ifndef MECHANISM_HPP
#define MECHANISM_HPP

#include "Node.hpp"

class Mechanism : public Node {
public:
  using Node::Node;

  void show() const override;
};

#endif
