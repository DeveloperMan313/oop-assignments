#ifndef MyStack_hpp
#define MyStack_hpp

#include <iostream>

template <class INFO, class FRIEND> class ListNode {
private:
  INFO info;
  ListNode *next;

  ListNode() : next(nullptr) {}

  friend FRIEND;
};

template <class INFO> class MyStack {
public:
  typedef class ListNode<INFO, MyStack<INFO>> Node;
  Node *top;

  MyStack() : top(nullptr) {}

  ~MyStack() {
    while (!this->empty()) {
      this->pop();
    }
  }

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

  void printReversed(const char *sep) { printReversedInner(sep, this->top); }

private:
  void printReversedInner(const char *sep, Node *node, bool outer = true) {
    const INFO info = node->info;
    if (node->next != nullptr) {
      this->printReversedInner(sep, node->next, false);
    }
    std::cout << info;
    if (outer) {
      std::cout << std::endl;
    } else {
      std::cout << sep;
    }
  }
};

#endif
