#ifndef NODE_HPP
#define NODE_HPP

#include "Part.hpp"

class Node : public Part {
public:
  using Part::Part;

  void show() const override;
};

#endif
