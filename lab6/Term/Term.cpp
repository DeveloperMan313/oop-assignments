#include "Term.hpp"
#include <format>
#include <stdexcept>

Term::Term(int coef_, int power_) : coef(coef_), power(power_) {}

Term operator+(const Term &t1, const Term &t2) {
  if (t1.power != t2.power) {
    throw std::logic_error("cannot add terms with different powers");
  }
  return Term(t1.coef + t2.coef, t1.power);
}

bool operator==(const Term &t1, const Term &t2) {
  return t1.coef == t2.coef && t1.power == t2.power;
}

bool operator<(const Term &t1, const Term &t2) {
  if (t1.power != t2.power) {
    return t1.power < t2.power;
  }
  return t1.coef < t2.coef;
}

std::istream &operator>>(std::istream &in, Term &t) {
  int coef, power;
  char xSymbol = '\0', powSymbol = '\0';
  in >> coef >> xSymbol >> powSymbol >> power;
  if (in.eof() && xSymbol == '\0' && powSymbol == '\0') {
    t.coef = coef;
    t.power = 0;
    return in;
  }
  if (xSymbol != 'x' || powSymbol != '^') {
    throw std::runtime_error("wrong term format");
  }
  t.coef = coef;
  t.power = power;
  return in;
}

std::ostream &operator<<(std::ostream &out, const Term &t) {
  if (t.coef == -1) {
    out << '-';
  } else if (t.coef != 1) {
    out << t.coef;
  }
  if (t.power != 0) {
    out << "x";
    if (t.power != 1) {
      out << '^' << t.power;
    }
  }
  return out;
}
