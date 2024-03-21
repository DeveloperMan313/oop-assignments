#include "Polynomial.hpp"
#include <cstddef>
#include <cstring>
#include <sstream>
#include <stdexcept>

const size_t inputBufSz = 1024;

Polynomial::Polynomial(const Term &t) : isReversed_(false) {
  if (t.coef != 0) {
    this->poly_.push(t);
  }
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
      idx = 0;
      continue;
    }
    this->poly_[idx]->coef += otherTerm.coef;
  }
  const size_t newThisSz = this->poly_.getSize();
  bool removed = false;
  for (size_t i = 0; i < newThisSz; ++i) {
    if (this->poly_[i]->coef == 0) {
      this->poly_.remove(i);
      removed = true;
    }
  }
  if (newThisSz > thisSz || removed) {
    this->poly_.sortUpdateSize();
  }
  return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &p) {
  const size_t thisSz = this->poly_.getSize(), otherSz = p.poly_.getSize();
  const Polynomial thisCopy = *this;
  this->poly_.clear();
  for (size_t i = 0; i < otherSz; ++i) {
    const Term &otherTerm = *p.poly_[i];
    Polynomial polByTerm = thisCopy;
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
  const std::overflow_error overflow("buffer overflow");
  char buf0[inputBufSz], buf[inputBufSz];
  in.getline(buf0, inputBufSz);
  if (in.fail()) {
    throw overflow;
  }
  const size_t sLen = std::strlen(buf0);
  size_t idx = 0;
  const auto checkOverflow = [idx, sLen, overflow] {
    if (idx == sLen) {
      throw overflow;
    }
  };
  for (size_t i = 0; i < sLen; ++i) {
    if (buf0[i] == ' ') {
      continue;
    }
    if (buf0[i] == 'x' &&
        (idx == 0 || buf[idx - 1] == '+' || buf[idx - 1] == '-')) {
      checkOverflow();
      buf[idx] = '1';
      ++idx;
    }
    if (idx > 0 && buf[idx - 1] != '^' && buf0[i] == '-') {
      checkOverflow();
      buf[idx] = '+';
      ++idx;
    }
    checkOverflow();
    buf[idx] = buf0[i];
    ++idx;
  }
  buf[idx] = '\0';
  std::stringstream sstream(buf);
  while (!sstream.eof()) {
    Term term;
    sstream.getline(buf, inputBufSz, '+');
    std::stringstream termStream(buf);
    termStream >> term;
    p += Polynomial(term);
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &p) {
  const size_t pSz = p.poly_.getSize();
  if (pSz == 0) {
    out << 0;
    return out;
  }
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
