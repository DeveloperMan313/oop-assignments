#include <istream>

class Polynomial;

class Term {
public:
  int coef, power;

  Term(int coef_ = 0, int power_ = 0);

  friend Polynomial;
};

Term operator+(const Term &t1, const Term &t2);

bool operator==(const Term &t1, const Term &t2);

bool operator<(const Term &t1, const Term &t2);

std::istream &operator>>(std::istream &in, Term &t);

std::ostream &operator<<(std::ostream &out, const Term &t);
