#ifndef S21_CPP_CONTAINERS_S21_LIST_H_
#define S21_CPP_CONTAINERS_S21_LIST_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename Value>
class list {
 protected:
  struct Node;

 public:
  class Iterator;
  using value_type = Value;
  using type_size = size_t;
  using reference = value_type&;
  using con_reference = const value_type&;
  using iterator = Iterator;
  using con_iterator = Iterator const;

  list();
  list(type_size n);
  list(const list& other);
  list(list&& other);
  list(std::initializer_list<value_type> const& items);
  ~list() {
    while (Node_size_ > 0) {
      erase(begin());
    }
    back_ptr = nullptr;
  }
  bool empty() const;
  type_size size() { return Node_size_; };
  void erase(iterator pos);
  void push_front(con_reference Val);
  void push_back(con_reference Val);
  void pop_front();
  void pop_back();
  iterator insert(iterator pos, con_reference value);

  template <class... Args>
  void insert_many_back(Args&&... args);
  template <class... Args>
  void insert_many_front(Args&&... args);
  template <class... Args>
  iterator insert_many(con_iterator pos, Args&&... args);

  con_reference front() { return this->front_ptr->value_; };
  con_reference back() { return this->back_ptr->value_; };

  class Iterator {
    friend class list<Value>;

   public:
    Iterator();
    Iterator(Node* node);

    iterator& operator++();
    iterator& operator--();
    reference operator*();

    bool operator==(const iterator& it);
    bool operator!=(const iterator& it);

   protected:
    Node* inter_ptr;
  };

  iterator begin() { return iterator(this->front_ptr); };
  iterator end() { return iterator(this->back_ptr); };
  iterator cbegin() const { return iterator(this->front_ptr); };
  iterator cend() const { return iterator(this->back_ptr); };

  void print() {
    auto size = this->Node_size_;
    // std::cout <<  size << std::endl;
    while (size > 0) {
      int n = this->back_ptr->value_;
      std::cout << n << std::endl;
      this->back_ptr = this->back_ptr->prev_;
      --size;
    }
  }

 protected:
  struct Node {
    Node(value_type value);
    value_type value_;
    Node* next_ = nullptr;
    Node* prev_ = nullptr;
  };

  type_size Node_size_ = 0;
  Node* front_ptr;
  Node* back_ptr;
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_CPP_CONTAINERS_S21_LIST_H_