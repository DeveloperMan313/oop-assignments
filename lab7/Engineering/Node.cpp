#include "Node.hpp"
#include <iostream>

void Node::show() const {
  std::cout << "Узел \"" << this->name << "\" имеет массу " << this->mass
            << " кг" << std::endl;
}
