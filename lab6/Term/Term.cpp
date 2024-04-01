#include "Term.hpp"
#include <format>
#include <istream>
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
  int coef = 0, power = 0;
  char xSymbol = '\0', powSymbol = '\0';
  in >> coef >> xSymbol >> std::ws;
  if (xSymbol == '+' || in.eof() && (xSymbol == 'x' || xSymbol == '\0')) {
    t.coef = coef;
    if (xSymbol == 'x') {
      t.power = 1;
    } else {
      t.power = 0;
    }
    in.clear();
    return in;
  }
  in >> powSymbol >> power;
  if (xSymbol != 'x' || (powSymbol != '^' && power != 0)) {
    throw std::runtime_error("wrong term format");
  }
  t.coef = coef;
  t.power = power;
  in.clear();
  return in;
}

std::ostream &operator<<(std::ostream &out, const Term &t) {
  if (t.coef == -1) {
    out << '-';
  } else if (t.coef != 1 || t.coef != 0 && t.power == 0) {
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
