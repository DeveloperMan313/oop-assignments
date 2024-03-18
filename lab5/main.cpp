#include "MySet/MySet.hpp"
#include <iostream>

int main() {
  MySet<int> s1;
  s1.addElement(1);
  s1.addElement(4);
  s1.addElement(5);
  s1.addElement(6);
  MySet<int> s2;
  s2.addElement(1);
  s2.addElement(2);
  s2.addElement(3);
  s2.addElement(4);
  std::cout << s1 << " + " << s2 << " => " << s1 + s2 << std::endl;
  std::cout << s1 << " * " << s2 << " => " << s1 * s2 << std::endl;
  std::cout << s1 << " - " << s2 << " => " << s1 - s2 << std::endl;
  return 0;
}
