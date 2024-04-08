#include "Engineering/Device.hpp"
#include "Engineering/Mechanism.hpp"
#include "Engineering/Node.hpp"
#include "Engineering/Part.hpp"
#include <clocale>

int main() {
  setlocale(LC_ALL, ".UTF8");
  [[maybe_unused]] Part part("болт", 0.01);
  [[maybe_unused]] Node node("клапан", 0.02, 0.15);
  [[maybe_unused]] Mechanism mechanism("поршень", 1.5, 0.2, "рычажный");
  [[maybe_unused]] Device device("двигатель", 5, 0.2, "рычажный", 50000.0);
  Part::showList();
  return 0;
}
