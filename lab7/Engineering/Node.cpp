#include "Node.hpp"
#include <iostream>

Node::Node() : Part::Part(), nodeSize(0.0) {}

Node::Node(const Node &node) : Part::Part(node), nodeSize(node.nodeSize) {}

Node::Node(const char *name_, double partMass_, double nodeSize_)
    : Part::Part(name_, partMass_) {
  if (nodeSize_ < 0.0) {
    throw std::invalid_argument("node size cannot be negative");
  }
  this->nodeSize = nodeSize_;
}

void Node::show() const {
  std::cout << "Узел \"" << this->name << "\" имеет размер " << this->nodeSize
            << " м и содержит деталь массой " << this->partMass << " кг"
            << std::endl;
}
