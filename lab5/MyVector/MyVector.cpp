#include "MyVector.hpp"
#include <algorithm>
#include <cstddef>
#include <stdexcept>

template <typename T> const size_t MyVector<T>::initCapacity = 1;

template <typename T> const size_t MyVector<T>::resizeFactor = 2;

template <typename T>
MyVector<T>::MyVector() : capacity(0), size(0), removedCnt(0), array(nullptr) {}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &vector) : MyVector<T>() {
  this->copy(vector);
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
  this->array[this->size] = new T(element);
  ++this->size;
  if (this->removedCnt > 0) {
    --this->removedCnt;
  }
}

template <typename T> void MyVector<T>::remove(size_t idx) {
  delete this->array[idx];
  this->array[idx] = nullptr;
  ++this->removedCnt;
}

template <typename T> void MyVector<T>::resize(size_t newCapacity) {
  if (newCapacity < this->size) {
    for (size_t i = newCapacity; i < this->size; ++i) {
      delete this->array[i];
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
    delete this->array[i];
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
    if (el == element) {
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

template <typename T> void MyVector<T>::copy(const MyVector<T> &vector) {
  if (vector.array == nullptr || this->array == vector.array) {
    return;
  }
  this->clear();
  this->capacity = vector.capacity;
  this->size = vector.size;
  this->array = new T *[this->capacity];
  for (size_t i = 0; i < this->size; ++i) {
    this->array[i] = new T(*vector.array[i]);
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

template class MyVector<int>;
