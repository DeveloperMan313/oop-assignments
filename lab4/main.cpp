#include "MyStack/MyStack.hpp"
#include <iostream>

void multipliers(int n, MyStack<int> &stack) {
  if (n == 0) {
    stack.push(0);
    return;
  }
  if (n < 0) {
    stack.push(-1);
    n *= -1;
  }
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
  MyStack<int> stack1(stack);
  std::cout << n << eq;
  stack1.printReversed(sep);
  MyStack<int> stack2;
  stack2 = stack1;
  std::cout << n << eq;
  stack2.print(sep);
  return 0;
}
