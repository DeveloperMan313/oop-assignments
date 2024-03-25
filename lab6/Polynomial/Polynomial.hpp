#include "../MyVector/MyVector.hpp"
#include "../Term/Term.hpp"
#include <istream>

class Polynomial {
public:
  explicit Polynomial(const Term &t);

  Polynomial(int coef = 0, int power = 0);

  int getDegree() const;

  int getReversed() const;

  void setReversed(bool isReversed);

  Polynomial &operator=(const Polynomial &p);

  Polynomial &operator+=(const Polynomial &p);

  Polynomial &operator*=(const Polynomial &p);

  int operator[](int power) const;

  friend Polynomial operator+(const Polynomial &p1, const Polynomial &p2);

  friend Polynomial operator*(const Polynomial &p1, const Polynomial &p2);

  friend std::istream &operator>>(std::istream &in, Polynomial &p);

  friend std::ostream &operator<<(std::ostream &out, const Polynomial &p);

private:
  MyVector<Term> poly_;
  int degree_;
  bool isReversed_;
};
