#include "fraction.hpp"
#include <cmath>
#include <cstddef>
#include <cstring>
#include <sstream>
#include <variant>

const size_t bufSz = 64;

Fraction::Fraction() : numer(1), denom(1u) {}

Fraction::Fraction(int _numer, unsigned int _denom)
    : numer(_numer), denom(_denom) {
  this->simplify();
}

Fraction::Fraction(const Fraction &f) : numer(f.numer), denom(f.denom) {}

Fraction::Fraction(int a) : Fraction(a, 1u) {}

Fraction::Fraction(double a) : Fraction(0, 1u) {
  const int sign = (a >= 0) ? 1 : -1;
  a = std::abs(a);
  while (a != 0) {
    const int wholePart = static_cast<int>(a);
    this->numer += wholePart;
    a = (a - static_cast<double>(wholePart)) * 10;
    this->numer *= 10;
    this->denom *= 10;
  }
  this->numer *= sign;
  this->simplify();
}

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
  this->simplify();
}

void Fraction::operator=(const Fraction &f) {
  this->numer = f.numer;
  this->denom = f.denom;
}

void Fraction::operator=(double a) { *this = Fraction(a); }

void Fraction::operator=(const char *str) { *this = Fraction(str); }

Fraction Fraction::operator-() const {
  return Fraction(-this->numer, this->denom);
}

template <typename T1, typename T2>
Fraction operator+(const T1 &t1, const T2 &t2) {
  const Fraction f1(t1), f2(t2);
  const int lcd = f1.denom * f2.denom / Fraction::gcd(f1.denom, f2.denom);
  const int toLcd1 = lcd / f1.denom;
  const int toLcd2 = lcd / f2.denom;
  return Fraction(f1.numer * toLcd1 + f2.numer * toLcd2, lcd);
}

template <typename T1, typename T2>
Fraction operator-(const T1 &t1, const T2 &t2) {
  const Fraction f1(t1), f2(t2);
  return f1 + -f2;
}

template <typename T1, typename T2>
Fraction operator*(const T1 &t1, const T2 &t2) {
  const Fraction f1(t1), f2(t2);
  return Fraction(f1.numer * f2.numer, f1.denom * f2.denom);
}

template <typename T1, typename T2>
Fraction operator/(const T1 &t1, const T2 &t2) {
  const Fraction f1(t1), f2(t2);
  return Fraction(f1.numer * f2.denom, f1.denom * f2.numer);
}

void Fraction::operator+=(const Fraction &f) { *this = *this + f; }

void Fraction::operator-=(const Fraction &f) { *this = *this - f; }

void Fraction::operator*=(const Fraction &f) { *this = *this * f; }

void Fraction::operator/=(const Fraction &f) { *this = *this / f; }

std::istream &operator>>(std::istream &in, Fraction &f) {
  char buf[bufSz];
  in >> buf;
  const size_t len = std::strlen(buf);
  bool hasSlash = false;
  for (size_t i = 0; i < len; ++i) {
    if (buf[i] == '/') {
      hasSlash = true;
      break;
    }
  }
  if (!hasSlash) {
    in.getline(static_cast<char *>(buf) + len, bufSz - len);
  }
  f.fromString(buf);
  return in;
}

std::ostream &operator<<(std::ostream &out, const Fraction &f) {
  int numer = f.numer;
  const int wholePart = numer / static_cast<int>(f.denom);
  if (wholePart != 0) {
    out << wholePart;
    numer = std::abs(numer) % f.denom;
  }
  if (numer > 0) {
    out << ' ' << numer << '/' << f.denom;
  }
  return out;
}

void Fraction::simplify() {
  const int gcd = Fraction::gcd(std::abs(this->numer), this->denom);
  this->numer /= gcd;
  this->denom /= gcd;
}

unsigned int Fraction::gcd(unsigned int a, unsigned int b) {
  while (a * b != 0) {
    if (a >= b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  return (a != 0) ? a : b;
}

static void instantiate() {
  std::variant<Fraction, int, double> x, y;
  std::visit(
      []<typename T, typename U>(T x, U y) {
        if constexpr (!std::is_same_v<T, U>) {
          Fraction f;
          f = x + y;
          f = x - y;
          f = x * y;
          f = x / y;
        }
      },
      x, y);
}
