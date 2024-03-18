#include "../MyVector/MyVector.hpp"
#include <ostream>

template <typename T> class MySet : private MyVector<T> {
public:
  using MyVector<T>::getSize;

  bool isElement(const T &element) const;

  void addElement(const T &element);

  void deleteElement(const T &element);

  using MyVector<T>::clear;

  using MyVector<T>::operator[];

  using MyVector<T>::operator=;

  void operator+=(const MySet<T> &set);

  void operator-=(const MySet<T> &set);

  void operator*=(const MySet<T> &set);

  MySet<T> operator+(const MySet<T> &set) const;

  MySet<T> operator-(const MySet<T> &set) const;

  MySet<T> operator*(const MySet<T> &set) const;

  bool operator==(const MySet<T> &set) const;

  template <typename U>
  friend std::ostream &operator<<(std::ostream &out, const MySet<U> &set);

private:
  using MyVector<T>::array;
  using MyVector<T>::size;
};
