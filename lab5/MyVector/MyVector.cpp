#include "MyVector.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

template <typename T> const size_t MyVector<T>::initCapacity = 1;

template <typename T> const size_t MyVector<T>::resizeFactor = 2;

template <typename T>
MyVector<T>::MyVector() : capacity(0), size(0), removedCnt(0), array(nullptr) {}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &vector) : MyVector<T>() {
  this->copy(vector);
}

template <typename T> MyVector<T>::MyVector(const T &element) : MyVector<T>() {
  this->push(element);
}

template <typename T> MyVector<T>::~MyVector() { this->clear(); }

template <typename T> size_t MyVector<T>::getCapacity() const {
  return this->capacity;
}

template <typename T> size_t MyVector<T>::getSize() const { return this->size; }

template <typename T> void MyVector<T>::push(const T &element) {
  if (this->array == nullptr) {
    this->capacity = MyVector<T>::initCapacity;
    this->array = new T *[this->capacity];
  }
  if (this->size == this->capacity) {
    this->resize(this->capacity * MyVector<T>::resizeFactor);
  }
  this->array[this->size] = MyVector<T>::copyElement(element);
  ++this->size;
  if (this->removedCnt > 0) {
    --this->removedCnt;
  }
}

template <typename T> void MyVector<T>::remove(size_t idx) {
  MyVector<T>::deleteElement(this->array[idx]);
  this->array[idx] = nullptr;
  ++this->removedCnt;
}

template <typename T> void MyVector<T>::resize(size_t newCapacity) {
  if (newCapacity < this->size) {
    for (size_t i = newCapacity; i < this->size; ++i) {
      MyVector<T>::deleteElement(this->array[i]);
    }
    this->size = newCapacity;
  }
  T **newArray = new T *[newCapacity];
  for (size_t i = 0; i < this->size; ++i) {
    newArray[i] = this->array[i];
  }
  delete[] this->array;
  this->array = newArray;
  this->capacity = newCapacity;
}

template <typename T> void MyVector<T>::clear() {
  for (size_t i = 0; i < this->size; ++i) {
    MyVector<T>::deleteElement(this->array[i]);
  }
  delete[] this->array;
  this->array = nullptr;
  this->capacity = 0;
  this->size = 0;
  this->removedCnt = 0;
}

template <typename T> void MyVector<T>::sort() {
  std::sort(this->array, this->array + this->size,
            MyVector<T>::cmpWithNullptrs);
}

template <typename T> void MyVector<T>::sortUpdateSize() {
  this->sort();
  this->size -= this->removedCnt;
  this->removedCnt = 0;
}

template <typename T> size_t MyVector<T>::find(const T &element) const {
  long long l = -1, r = this->size;
  while (r - l > 1) {
    size_t m = static_cast<size_t>(l + (r - l) / 2);
    if (this->array[m] == nullptr) {
      throw std::runtime_error("met nullptr while searching");
    }
    const T &el = *this->array[m];
    if (MyVector<T>::eq(&el, &element)) {
      return m;
    }
    if (MyVector<T>::cmp(&el, &element)) {
      l = m;
    } else {
      r = m;
    }
  }
  throw std::invalid_argument("not found");
}

template <typename T> T *MyVector<T>::operator[](size_t idx) const {
  if (idx >= this->size) {
    throw std::out_of_range("index out of range");
  }
  return this->array[idx];
}

template <typename T> void MyVector<T>::operator=(const MyVector<T> &vector) {
  this->copy(vector);
}

template <typename U>
std::ostream &operator<<(std::ostream &out, const MyVector<U> &vector) {
  out << '[';
  for (size_t i = 0; i < vector.size; ++i) {
    out << *vector.array[i];
    if (i < vector.size - 1) {
      out << ", ";
    }
  }
  out << ']';
  return out;
}

template <typename T> bool MyVector<T>::eq(const T *lhs, const T *rhs) {
  return *lhs == *rhs;
}

template <>
bool MyVector<const char *>::eq(const char *const *lhs,
                                const char *const *rhs) {
  return std::strcmp(*lhs, *rhs) == 0;
}

template <typename T> void MyVector<T>::copy(const MyVector<T> &vector) {
  if (this->array == vector.array) {
    return;
  }
  this->clear();
  if (vector.array == nullptr) {
    return;
  }
  this->capacity = vector.capacity;
  this->size = vector.size;
  this->array = new T *[this->capacity];
  for (size_t i = 0; i < this->size; ++i) {
    this->array[i] = MyVector<T>::copyElement(*vector.array[i]);
  }
}

template <typename T>
bool MyVector<T>::cmpWithNullptrs(const T *lhs, const T *rhs) {
  if (lhs == nullptr) {
    return false;
  }
  if (rhs == nullptr) {
    return true;
  }
  return MyVector<T>::cmp(lhs, rhs);
}

template <typename T> bool MyVector<T>::cmp(const T *lhs, const T *rhs) {
  return *lhs < *rhs;
}

template <>
bool MyVector<const char *>::cmp(const char *const *lhs,
                                 const char *const *rhs) {
  return std::strcmp(*lhs, *rhs) < 0;
}

template <typename T> T *MyVector<T>::copyElement(const T &element) {
  return new T(element);
}

template <>
const char **MyVector<const char *>::copyElement(const char *const &str) {
  const size_t strSz = std::strlen(str) + 1;
  char **newStr = new char *;
  *newStr = new char[strSz];
  std::strncpy(*newStr, str, strSz);
  return const_cast<const char **>(newStr);
}

template <typename T> void MyVector<T>::deleteElement(const T *element) {}

template <>
void MyVector<const char *>::deleteElement(const char *const *strPtr) {
  delete[] *strPtr;
  delete strPtr;
}

template class MyVector<int>;
template std::ostream &operator<<(std::ostream &out,
                                  const MyVector<int> &vector);
template class MyVector<const char *>;
template std::ostream &operator<<(std::ostream &out,
                                  const MyVector<const char *> &vector);
