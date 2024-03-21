#include "Polynomial.hpp"
#include <cstddef>
#include <cstring>
#include <sstream>

const size_t inputBufSz = 1024;

Polynomial::Polynomial(const Term &t) : isReversed_(false) {
  this->poly_.push(t);
}

Polynomial::Polynomial(int coef, int power) : Polynomial(Term(coef, power)) {}

int Polynomial::getDegree() const { return this->degree_; }

int Polynomial::getReversed() const { return this->isReversed_; }

void Polynomial::setReversed(bool isReversed) {
  this->isReversed_ = isReversed;
}

Polynomial &Polynomial::operator=(const Polynomial &p) {
  this->poly_ = p.poly_;
  this->degree_ = p.degree_;
  return *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &p) {
  size_t idx = 0;
  const size_t thisSz = this->poly_.getSize(), otherSz = p.poly_.getSize();
  for (size_t i = 0; i < otherSz; ++i) {
    const Term &otherTerm = *p.poly_[i];
    while (idx < thisSz && this->poly_[idx]->power != otherTerm.power) {
      ++idx;
    }
    if (idx == thisSz) {
      this->poly_.push(Term(otherTerm));
      continue;
    }
    this->poly_[idx]->coef += otherTerm.coef;
  }
  if (idx == thisSz) {
    this->poly_.sort();
  }
  return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &p) {
  const size_t thisSz = this->poly_.getSize(), otherSz = p.poly_.getSize();
  for (size_t i = 0; i < otherSz; ++i) {
    const Term &otherTerm = *p.poly_[i];
    Polynomial polByTerm = *this;
    for (size_t j = 0; j < thisSz; ++j) {
      polByTerm.poly_[j]->coef *= otherTerm.coef;
      polByTerm.poly_[j]->power += otherTerm.power;
    }
    *this += polByTerm;
  }
  return *this;
}

int Polynomial::operator[](size_t power) const {
  const size_t thisSz = this->poly_.getSize();
  for (size_t i = 0; i < thisSz; ++i) {
    if (this->poly_[i]->power == power) {
      return this->poly_[i]->coef;
    }
  }
  return 0;
}

Polynomial operator+(const Polynomial &p1, const Polynomial &p2) {
  return Polynomial(p1) += p2;
}

Polynomial operator*(const Polynomial &p1, const Polynomial &p2) {
  return Polynomial(p1) *= p2;
}

std::istream &operator>>(std::istream &in, Polynomial &p) {
  char buf[inputBufSz];
  in.getline(buf, inputBufSz);
  const size_t sLen = std::strlen(buf);
  size_t idx = 0;
  for (size_t i = 0; i < sLen; ++i) {
    if (buf[i] != ' ') {
      if (buf[i] == 'x' &&
          (idx == 0 || buf[idx - 1] == '+' || buf[idx - 1] == '-')) {
        buf[idx] = '1';
        ++idx;
      }
      buf[idx] = buf[i];
      ++idx;
    }
  }
  buf[idx] = '\0';
  std::stringstream sstream(buf);
  while (!sstream.eof()) {
    Term term;
    sstream >> term >> std::ws;
    p += Polynomial(term);
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &p) {
  const size_t pSz = p.poly_.getSize();
  for (size_t i = 0; i < pSz; ++i) {
    const Term &term = (p.isReversed_) ? *p.poly_[i] : *p.poly_[pSz - i - 1];
    if (term.coef == 0) {
      continue;
    }
    const int sign = (term.coef >= 0) ? 1 : -1;
    if (i != 0) {
      out << ' ' << ((sign == 1) ? '+' : '-') << ' ';
    } else if (sign == -1) {
      out << '-';
    }
    out << Term(sign * term.coef, term.power);
  }
  return out;
}
