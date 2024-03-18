#include "MySet.hpp"
#include <cstddef>
#include <iostream>

template <typename T> bool MySet<T>::isElement(const T &element) const {
  try {
    this->find(element);
  } catch (...) {
    return false;
  }
  return true;
}

template <typename T> void MySet<T>::addElement(const T &element) {
  if (this->isElement(element)) {
    return;
  }
  this->push(element);
  this->sortUpdateSize();
}

template <typename T> void MySet<T>::deleteElement(const T &element) {
  size_t idx;
  try {
    idx = this->find(element);
  } catch (...) {
    return;
  }
  this->remove(idx);
  this->sortUpdateSize();
}

template <typename T> void MySet<T>::operator+=(const MySet<T> &set) {
  for (size_t i = 0; i < set.size; ++i) {
    this->addElement(*set.array[i]);
  }
}

template <typename T> void MySet<T>::operator-=(const MySet<T> &set) {
  for (size_t i = 0; i < set.size; ++i) {
    this->deleteElement(*set.array[i]);
  }
}

template <typename T> void MySet<T>::operator*=(const MySet<T> &set) {
  for (size_t i = 0; i < this->size; ++i) {
    if (!set.isElement(*this->array[i])) {
      this->remove(i);
    }
  }
  this->sortUpdateSize();
}

template <typename T> MySet<T> MySet<T>::operator+(const MySet<T> &set) const {
  MySet<T> newSet(*this);
  newSet += set;
  return newSet;
}

template <typename T> MySet<T> MySet<T>::operator-(const MySet<T> &set) const {
  MySet<T> newSet(*this);
  newSet -= set;
  return newSet;
}

template <typename T> MySet<T> MySet<T>::operator*(const MySet<T> &set) const {
  MySet<T> newSet(*this);
  newSet *= set;
  return newSet;
}

template <typename T> bool MySet<T>::operator==(const MySet<T> &set) const {
  if (this->size != set.size) {
    return false;
  }
  for (size_t i = 0; i < this->size; ++i) {
    if (*this->array[i] != *set.array[i]) {
      return false;
    }
  }
  return true;
}

template <typename U>
std::ostream &operator<<(std::ostream &out, const MySet<U> &set) {
  out << '{';
  for (size_t i = 0; i < set.size; ++i) {
    out << *set.array[i];
    if (i < set.size - 1) {
      out << ", ";
    }
  }
  out << '}';
  return out;
}

template class MySet<int>;
template std::ostream &operator<<(std::ostream &out, const MySet<int> &set);
