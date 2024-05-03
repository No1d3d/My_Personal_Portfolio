#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

#include <algorithm>
#include <stdexcept>

namespace s21 {

template <typename T>
class stack {
 private:
  struct Node;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack();
  stack(Node* values);
  stack(std::initializer_list<T> const& items);
  stack(const stack& other);
  stack(stack&& other) noexcept;

  ~stack();

  void printstack() const;
  value_type at(size_t arg) const;
  value_type operator[](size_t arg) const;

  void pop();
  void push(T value);
  void push_range(std::initializer_list<T> const& items);
  // Node* peek();
  T top() const;
  void swap(stack& aim);
  void clear();
  bool empty();
  size_t size() const;

  stack& operator=(const stack& other);
  stack& operator=(stack&& other);
  template <class... Args>
  void insert_many_front(Args&&... args);
  // Iterator begin();
  // Iterator end();
  // void assign(size_t count, const T& value);

 private:
  Node* head = nullptr;
  Node* tail = nullptr;
  size_t count = 0;

  void delete_stack();
  void insert(T value, size_t pos);

  void foo(size_t n) const;

  struct Node {
    value_type value;
    Node* ptr;
    Node(value_type val) : value(val), ptr(nullptr){};
  };
};

};  // namespace s21

#include "s21_stack.tpp"

#endif  // _STACK_H_
