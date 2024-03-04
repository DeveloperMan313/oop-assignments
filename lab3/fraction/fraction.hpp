#include <istream>

class Fraction {
public:
  Fraction();

  Fraction(int _numer, unsigned int _denom);

  explicit Fraction(const char *str);

  void fromString(const char *str);

  friend std::istream &operator>>(std::istream &in, Fraction &fraction);

  friend std::ostream &operator<<(std::ostream &out, const Fraction &fraction);

private:
  int numer;
  unsigned int denom;
};
