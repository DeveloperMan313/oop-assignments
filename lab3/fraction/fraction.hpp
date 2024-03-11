#include <istream>

class Fraction {
public:
  Fraction();

  Fraction(int _numer, unsigned int _denom);

  Fraction(const Fraction &f);

  Fraction(int a);

  Fraction(double a);

  Fraction(const char *str);

  void fromString(const char *str);

  void operator=(const Fraction &f);

  void operator=(double a);

  void operator=(const char *str);

  Fraction operator-() const;

  template <typename T1, typename T2>
  friend Fraction operator+(const T1 &t1, const T2 &t2);

  template <typename T1, typename T2>
  friend Fraction operator-(const T1 &t1, const T2 &t2);

  template <typename T1, typename T2>
  friend Fraction operator*(const T1 &t1, const T2 &t2);

  template <typename T1, typename T2>
  friend Fraction operator/(const T1 &t1, const T2 &t2);

  void operator+=(const Fraction &f);

  void operator-=(const Fraction &f);

  void operator*=(const Fraction &f);

  void operator/=(const Fraction &f);

  friend std::istream &operator>>(std::istream &in, Fraction &f);

  friend std::ostream &operator<<(std::ostream &out, const Fraction &f);

private:
  int numer;
  unsigned int denom;

  void checkDenom();

  void simplify();

  static unsigned int gcd(unsigned int a, unsigned int b);
};
