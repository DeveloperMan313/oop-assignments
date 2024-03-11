#ifndef MyStack_hpp
#define MyStack_hpp

#include <iostream>

template <class INFO, class FRIEND> class ListNode {
private:
  INFO info;
  ListNode *next;

  ListNode() : info(), next(nullptr) {}

  friend FRIEND;
};

template <class INFO> class MyStack {
public:
  typedef class ListNode<INFO, MyStack<INFO>> Node;
  Node *top;

  MyStack() : top(nullptr) {}

  MyStack(const MyStack<INFO> &stack) : MyStack() { *this = stack; }

  ~MyStack() { this->clear(); }

  bool empty() { return top == nullptr; }

  void push(INFO info) {
    Node *newTop = new Node;
    newTop->info = info;
    newTop->next = this->top;
    this->top = newTop;
  }

  void pop() {
    Node *newTop = this->top->next;
    delete this->top;
    this->top = newTop;
  }

  void clear() {
    while (!this->empty()) {
      this->pop();
    }
  }

  INFO topInfo() { return this->top->info; }

  void print(const char *sep) {
    Node *node = this->top;
    while (node != nullptr) {
      std::cout << node->info;
      node = node->next;
      if (node != nullptr) {
        std::cout << sep;
      }
    }
    std::cout << std::endl;
  }

  void printReversed(const char *sep) {
    MyStack<INFO> stack;
    Node *node = this->top;
    while (node != nullptr) {
      stack.push(node->info);
      node = node->next;
    }
    while (!stack.empty()) {
      std::cout << stack.topInfo();
      stack.pop();
      if (stack.top != nullptr) {
        std::cout << sep;
      }
    }
    std::cout << std::endl;
  }

  void operator=(const MyStack<INFO> &stack) {
    if (this->top == stack.top) {
      return;
    }
    this->clear();
    MyStack<INFO> temp;
    Node *node = stack.top;
    while (node != nullptr) {
      temp.push(node->info);
      node = node->next;
    }
    node = temp.top;
    while (node != nullptr) {
      this->push(node->info);
      node = node->next;
    }
  }
};

#endif
