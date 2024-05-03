#include "./s21_stack.h"

using namespace s21;


template <typename T>
stack<T>::stack(): count(0) {}

template <typename T>
stack<T>::stack(stack<T>::Node* values) {
  tail = values;
  Node* tmp = tail;
  while (tmp->ptr) {
    tmp = tmp->ptr;
    head = tmp;
    count++;
  } //searching for new head
}

template <typename T>
stack<T>::stack(std::initializer_list<T> const &items) {
  for (T i: items) {
    push(i);
  };

  foo(count);
}

// template <typename T>
// stack<T>::stack(const stack& other) {
//   delete_stack(tail);
//   for (size_t i = 0; i < count; i++) {
//     push(other.at(i));
//   }
// }

template <typename T>
stack<T>::stack(const stack<T>& other) {
  if (this == &other) return;
  delete_stack();
  count = 0;
  for (size_t i = 0;i < other.size(); i++) {
    push(other.at(i));
#ifdef DEB  
    std::cout<<i<<" - "<<other.at(i)<<std::endl;
#endif
  }
}


template <typename T>
stack<T>::stack(stack<T>&& other) noexcept{
  if (this == &other) return;

  tail = nullptr;
  count = 0;
  for (size_t i = 0; i < other.size(); i++) {
    push(other.at(i));
  }
  other.clear();
  foo(count);
}

template <typename T>
stack<T>::~stack() {
  delete_stack();
}

template <typename T>
T stack<T>::at(size_t arg) const{
  if (arg >= count) throw std::logic_error("Your index is too big, Senpai");
  Node* tmp = tail;
  for (size_t i = 0; i < arg; i++) {
    tmp = tmp->ptr;
  }
  return tmp->value;
}

template <typename T>
T stack<T>::operator[](size_t arg) const {
  return this->at(arg);
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& other) {
  if (other == this) return *this;
  delete_stack();
  tail = nullptr;
  count = 0;
  for (size_t i = 0; i < other.size(); i++) {
    push(other.at(i));
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& other) {
  // delete_stack(tail);
  if (this == &other) return *this;
  tail = nullptr;
  count = 0;
  for (size_t i = 0; i < other.size(); i++) {
    push(other.at(i));
  }
  other.clear();
  foo(count);
  return *this;
}


// template <typename T>
// void stack<T>::pop() {
//   if (!head || !tail) throw std::logic_error("head is empty");
//   if (tail == head && tail) {
//     delete tail;
//     return;
//   }
//   delete head;
//   head = tail;
//   while (head->ptr) {
//     head = head->ptr;
//   }
//   count--;
// }


template <typename T>
void stack<T>::pop() {
  if (!count) throw std::logic_error("head is empty");
  if (count == 1) delete_stack();
  Node* predposledniy = tail;
  int i = 1;
  while (predposledniy->ptr->ptr) {
    // std::cout<<i<<"\t"<<predposledniy->value<<"\n";
    ++i;
    predposledniy = predposledniy->ptr;
  }
  // std::cout<<i<<"\t"<<predposledniy->value<<"\n\n";
  head = predposledniy;
  predposledniy = predposledniy->ptr;
  delete predposledniy;
  head->ptr = nullptr;
  --count;
}


template <typename T>
void stack<T>::push(T value) {
  Node* new_Node = new Node(value);
  if (!tail) tail = new_Node;
  if (head) {
    head->ptr = new_Node;
    head = head->ptr;
    head->ptr = nullptr;
  } else {
    head = new_Node;
  }
#ifdef DEB  
  std::cout<<"\npushing this value "<<head->value<<std::endl;
#endif
  count++;
  // foo(count);
  // std::cout<<tail<<"\t"<<head<<std::endl;
}

template <typename T>
void stack<T>::clear() {
  delete_stack();
}

template <typename T>
void stack<T>::insert(T value, size_t pos) {
  Node* tmp = tail;
  for(int i = 0; i < pos; i++) {
    tmp = tmp->ptr;
  }
  Node* tmp2 = tmp->ptr;
  tmp = new Node(value);
  tmp->ptr = tmp2;
  count++;
}

// template <typename T>
// void stack<T>::insert_many_back(T* values) {
//   for (auto i : values) {
//     push(i);
//     count++;
//   }
// }

// Node* stack<T>::peek() {return head*}

template <typename T>
T stack<T>::top() const {
  if (0 == count) throw std::logic_error("no such element, sempai");
  return head->value;
}

template <typename T>
void stack<T>::swap(stack<T>& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(count, other.count);
}

template <typename T>
bool stack<T>::empty() { return 0 == count;}

template <typename T>
size_t stack<T>::size() const {
  return count;
}

template <typename T>
void stack<T>::delete_stack() {
  if (count != 0) {
    Node* tmp;
    while(tail->ptr != nullptr) {
      tmp = tail->ptr;
      if (tail) delete tail;
      tail = tmp;
      --count;
    }
    if (head) {
      delete head;
      --count;
    }
  }
}

// template <typename T>
// void stack<T>::delete_stack() {
// while (count) {pop();}
// }

template <typename T>
void stack<T>::printstack() const{
  Node* tmp = tail;
  while (tmp->ptr) {
    std::cout<<tmp->value<<"\n";
    tmp = tmp->ptr;
  }
  std::cout<<tmp->value<<"\n";
}

template <typename T>
void stack<T>::foo(size_t n) const {
  // std::cout<<n<<"\t"<<tail<<"\t"<<head<<"\n";
  n++;
}

template <typename T>
template <class... Args>
void stack<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push(arg);
  }
}

