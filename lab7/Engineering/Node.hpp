#ifndef NODE_HPP
#define NODE_HPP

#include "Part.hpp"

class Node : public Part {
public:
  Node();

  Node(const Node &node);

  explicit Node(const char *name_, double partMass_ = 0.0,
                double nodeSize_ = 0.0);

  void show() const override;

protected:
  double nodeSize;
};

#endif
