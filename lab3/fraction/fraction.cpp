#include "fraction.hpp"
#include <cstddef>
#include <sstream>

const size_t bufSz = 64;

Fraction::Fraction() : numer(1), denom(1u) {}

Fraction::Fraction(int _numer, unsigned int _denom)
    : numer(_numer), denom(_denom) {}

Fraction::Fraction(const char *str) : Fraction() { this->fromString(str); }

void Fraction::fromString(const char *str) {
  bool hasWhole = false;
  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (str[i] == ' ') {
      hasWhole = true;
      break;
    }
  }
  std::stringstream sstream(str);
  int wholePart = 0;
  if (hasWhole) {
    sstream >> wholePart;
  }
  char buf[bufSz];
  sstream.getline(buf, sizeof(buf), '/');
  this->numer = std::stoi(buf);
  sstream >> this->denom;
  if (wholePart < 0) {
    this->numer *= -1;
  }
  this->numer += wholePart * static_cast<int>(this->denom);
}

std::istream &operator>>(std::istream &in, Fraction &fraction) {
  char buf[bufSz];
  in >> buf;
  fraction.fromString(buf);
  return in;
}

std::ostream &operator<<(std::ostream &out, const Fraction &fraction) {
  return out << fraction.numer << '/' << fraction.denom;
}
