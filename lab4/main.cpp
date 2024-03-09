#include "MyStack/MyStack.hpp"
#include <iostream>

void multipliers(int n, MyStack<int> &stack) {
  int k = 2;
  while (n > 1) {
    while (n % k > 0) {
      ++k;
    }
    n /= k;
    stack.push(k);
  }
}

int main() {
  const int n = 3960;
  const char *eq = " = ";
  const char *sep = " * ";
  MyStack<int> stack;
  multipliers(n, stack);
  std::cout << n << eq;
  stack.print(sep);
  std::cout << n << eq;
  stack.printReversed(sep);
  return 0;
}
