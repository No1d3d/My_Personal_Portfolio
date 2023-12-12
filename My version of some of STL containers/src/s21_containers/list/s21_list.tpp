#ifndef S21_CPP_CONTAINERS_S21_LIST_TPP_
#define S21_CPP_CONTAINERS_S21_LIST_TPP_

#include "s21_list.h"
namespace s21 {

template <typename Value>
list<Value>::list() {
  back_ptr = nullptr;
  front_ptr = nullptr;
}

template <typename Value>
list<Value>::list(type_size n) : list() {
  if (n > 0) {
    for (type_size i = 0; i < n; ++i) {
        push_back(value_type());
    } 
  }
}

template <typename Value>
list<Value>::list(const list& other) : list(){
  Node *current = other.front_ptr;
  while (current) {
    push_back(current->value_);
    current = current->next_;
  }
}

template <typename Value>
list<Value>::list(list&& other) {
  Node_size_ = other.Node_size_;
  back_ptr = other.back_ptr;
  front_ptr = other.front_ptr;
  other.Node_size_ = 0;
  other.back_ptr = nullptr;
  other.front_ptr = nullptr;
}

template <typename Value>
list<Value>::Node::Node(value_type value)
    : value_(value), next_(nullptr), prev_(nullptr) {}

template <typename Value>
void list<Value>::push_front(con_reference Val) {
    Node* new_element = new Node(Val);
    new_element->next_ = front_ptr;
    if (front_ptr != nullptr) {
        front_ptr->prev_ = new_element;
    }
    if (back_ptr == nullptr) {
      back_ptr = new_element;
    }
    front_ptr = new_element;
    Node_size_+=1;
}

template <typename Value>
void list<Value>::push_back(con_reference Val) {
    Node* new_element = new Node(Val);
    new_element->prev_ = back_ptr;
    if (back_ptr != nullptr) {
        back_ptr->next_ = new_element;
    }
    if (front_ptr == nullptr) {
      front_ptr = new_element;
    }
    back_ptr = new_element;
    Node_size_+=1;
}

template <typename Value>
void list<Value>::pop_front() {
    if (front_ptr == nullptr) return;
    Node* ptr = front_ptr->next_;
    if (ptr != nullptr) {
      ptr->prev_ = nullptr;
    } else {
      back_ptr = nullptr;
    }
    delete front_ptr;
    front_ptr = ptr;
    Node_size_-=1;
}

template <typename Value>
void list<Value>::pop_back() {
  if (back_ptr == nullptr) return;
    Node* ptr = back_ptr->prev_;
    if (ptr != nullptr) {
      ptr->next_ = nullptr;
    } else {
      front_ptr = nullptr;
    }
    delete back_ptr;
    back_ptr = ptr;
    Node_size_-=1;
}

template <typename Value>
bool list<Value>::empty() const {
    return this->back_ptr == nullptr;
}

template <typename Value>
void list<Value>::erase(iterator pos) {
   Node *ptr = pos.inter_ptr;
  if (ptr == begin()) {
    pop_front();
  } else if (ptr == end()) {
    pop_back();
  } else {
   ptr->next_->prev_ = ptr->prev_;
   ptr->prev_->next_ = ptr->next_;
   delete ptr;
   this->Node_size_-=1;
  }
}


template <typename Value>
list<Value>::Iterator::Iterator() {
  inter_ptr = nullptr;
}

template <typename Value>
list<Value>::Iterator::Iterator(Node* node) {
    inter_ptr = node;
}

template <typename Value>
typename list<Value>::Iterator& list<Value>::Iterator::operator++() {
  if(this->inter_ptr->next_ != nullptr)
    this->inter_ptr  = this->inter_ptr->next_;
  return *this;
}

template <typename Value>
typename list<Value>::Iterator& list<Value>::Iterator::operator--() {
  if(this->inter_ptr->prev_ != nullptr)
    this->inter_ptr  = this->inter_ptr ->prev_;
  return *this;
}

template <typename Value>
Value &list<Value>::Iterator::operator*() {
    return inter_ptr->value_;
}

template <typename Value>
bool list<Value>::Iterator::operator==(const list<Value>::Iterator &it) {
    return this->inter_ptr == it.inter_ptr;
}

template <typename Value>
bool list<Value>::Iterator::operator!=(const list<Value>::Iterator &it) {
    return this->inter_ptr != it.inter_ptr;
}

template <typename Value>
list<Value>::list(std::initializer_list<value_type> const &items) : list() {
   for (auto i = items.begin(); i != items.end(); ++i) {
    push_back(*i);
   }
}

template <typename Value>
template <class... Args>
void list<Value>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

template <typename Value>
template <class... Args>
void list<Value>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_front(arg);
  }
}

template <typename Value>
typename list<Value>::Iterator list<Value>::insert(iterator pos, con_reference value) {
  if (pos.inter_ptr == begin()) {
    push_front(value);
    pos.inter_ptr = this->front_ptr;
  } else if (pos.inter_ptr == this->end()) {
    push_back(value);
    pos.inter_ptr = this->back_ptr;
  } else {
    Node* this_node = pos.inter_ptr;
    Node* node_node = new Node(value);
    node_node->next_ = this_node;
    node_node->prev_ = this_node->prev_;
    this_node->prev_->next_ = node_node;
    this_node->prev_ = node_node;
    this->Node_size_++;
    return iterator(node_node);
  }
  return pos;
}

template <typename Value>
template <class... Args>
typename list<Value>::Iterator list<Value>::insert_many(con_iterator pos, Args&&... args) {
  for (const auto& arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

}//namespace s21

#endif //S21_CPP_CONTAINERS_S21_LIST_TPP_