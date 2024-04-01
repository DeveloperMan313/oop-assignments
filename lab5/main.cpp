#include "MySet/MySet.hpp"
#include "MyVector/MyVector.hpp"
#include <iostream>

int main() {
  setlocale(LC_ALL, ".UTF8");
  MySet<int> n1, n2;
  n1.addElement(1);
  n1.addElement(4);
  n1.addElement(5);
  n1.addElement(6);
  n2.addElement(1);
  n2.addElement(2);
  n2.addElement(3);
  n2.addElement(4);
  std::cout << n1 << " + " << n2 << " => " << n1 + n2 << std::endl;
  std::cout << n1 << " * " << n2 << " => " << n1 * n2 << std::endl;
  std::cout << n1 << " - " << n2 << " => " << n1 - n2 << std::endl;
  MyVector<const char *> v("Hello!");
  v.push("Привет!");
  v.push("Привет!");
  v.push("Привет!");
  v.push("Привет!");
  v.push("Привет!");
  std::cout << "Вектор v: " << v << std::endl;
  v.push("Привет!");
  v.push("Привет!");
  v.push("Привет!");
  std::cout << "Вектор v: " << v << std::endl;
  MyVector v1 = v;
  std::cout << "Вектор v1: " << v1 << std::endl;
  v1.clear();
  std::cout << "Вектор v1: " << v1 << std::endl;
  MySet<const char *> s("Yes"), s1, s2;
  s.addElement("Привет!");
  s.addElement("No");
  const char *str = "Hello!";
  s.addElement(str);
  std::cout << "Множество s: " << s << std::endl;
  s1.addElement("Cat");
  s1.addElement("No");
  s1.addElement("Привет!");
  std::cout << "Множество s1: " << s1 << std::endl;
  s2 = s1 - s;
  std::cout << "Множество s2=s1-s: " << s2 << std::endl;
  std::cout << "Множество s1: " << s1 << std::endl;
  std::cout << "Множество s: " << s << std::endl;
  s2 = s - s1;
  std::cout << "Множество s2=s-s1: " << s2 << std::endl;
  std::cout << "Множество s1: " << s1 << std::endl;
  std::cout << "Множество s: " << s << std::endl;
  s2 = s1 + s;
  std::cout << "Множество s2=s1+s: " << s2 << std::endl;
  std::cout << "Множество s1: " << s1 << std::endl;
  std::cout << "Множество s: " << s << std::endl;
  s2 = s1 * s;
  std::cout << "Множество s2=s1*s: " << s2 << std::endl;
  std::cout << "Множество s1: " << s1 << std::endl;
  std::cout << "Множество s: " << s << std::endl;
  MySet s3 = s2;
  std::cout << "Множество s3=s2: " << s3 << std::endl;
  if (s3 == s2) {
    std::cout << "Множество s3=s2\n";
  } else {
    std::cout << "Множество s3!=s2\n";
  }
  if (s3 == s1) {
    std::cout << "Множество s3=s1\n";
  } else {
    std::cout << "Множество s3!=s1\n";
  }
  if (s1 == s3) {
    std::cout << "Множество s1=s3\n";
  } else {
    std::cout << "Множество s1!=s3\n";
  }
  return 0;
}
