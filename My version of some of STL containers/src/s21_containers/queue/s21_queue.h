#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace s21 {

template <typename T>
class queue {
 private:
  struct Node;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue();
  queue(Node* values);
  queue(std::initializer_list<T> const& items);
  queue(const queue<T>& other);
  queue(queue<T>&& other) noexcept;
  ~queue();

  value_type at(size_t arg) const;
  value_type operator[](size_t arg) const;
  void pop();
  void push(T value);
  void push_range(std::initializer_list<T> const& items);
  void insert(T value, size_t pos);

  T& front();
  T& back();

  T top() const;
  void swap(queue& aim);
  void clear();
  bool empty();
  size_t size() const;

  queue& operator=(const queue& other);
  queue& operator=(queue&& other);
  bool operator==(const queue& other);

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  Node* head = nullptr;
  Node* tail = nullptr;
  size_t count = 0;
  void delete_queue();

  struct Node {
    value_type value;
    Node* ptr;
    Node(value_type val) : value(val), ptr(nullptr){};
  };
};

};  // namespace s21

#include "s21_queue.tpp"

#endif  // _QUEUE_H_
