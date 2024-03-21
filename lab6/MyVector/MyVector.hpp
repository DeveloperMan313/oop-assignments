#include <cstddef>

template <typename T> class MyVector {
public:
  MyVector();

  MyVector(const MyVector<T> &vector);

  ~MyVector();

  size_t getCapacity() const;

  size_t getSize() const;

  void push(const T &element);

  void remove(size_t idx);

  void resize(size_t newCapacity);

  void clear();

  void sort();

  void sortUpdateSize();

  size_t find(const T &element) const;

  T *operator[](size_t idx) const;

  void operator=(const MyVector<T> &vector);

protected:
  T **array;
  size_t size;

private:
  size_t capacity, removedCnt;

  void copy(const MyVector<T> &vector);

  static const size_t initCapacity, resizeFactor;

  static bool cmpWithNullptrs(const T *lhs, const T *rhs);

  static bool cmp(const T *lhs, const T *rhs);
};
