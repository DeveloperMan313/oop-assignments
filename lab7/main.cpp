#include "Engineering/Device.hpp"
#include "Engineering/Mechanism.hpp"
#include "Engineering/Node.hpp"
#include "Engineering/Part.hpp"
#include <clocale>

int main() {
  setlocale(LC_ALL, ".UTF8");
  [[maybe_unused]] Part part("болт", 0.01);
  [[maybe_unused]] Node node("клапан", 0.02);
  [[maybe_unused]] Mechanism mechanism("винт", 1.5);
  [[maybe_unused]] Device device("часы", 0.2);
  Part::showList();
  return 0;
}
