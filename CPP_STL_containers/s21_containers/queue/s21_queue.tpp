#include "./s21_queue.h"

using namespace s21;

// template <typename T>
// bool queue<T>::operator==(const queue<T>& other) {
//   if (count != other.size()) return false;
//   for (size_t i = 0; i < count; i++) {
//     if (at(i) != other.at(i)) {
//       return false;
//     }
//   }
//   return true;
// }

template <typename T>
queue<T>::queue() {}

template <typename T>
queue<T>::queue(queue<T>::Node* values) {
  tail = values;
  Node* tmp = tail;
  while (tmp->ptr) {
    count++;
    tmp = tmp->ptr;
    head = tmp;
  }
}
  

template <typename T>
queue<T>::queue(std::initializer_list<T> const &items) {
  for (T i: items) {
    push(i);
  };
}

template <typename T>
queue<T>::queue(const queue<T>& other) {
if (this == &other) return;
  delete_queue();
  count = 0;
  for (size_t i = 0;i < other.size(); i++) {
    push(other.at(i));
  }
}

template <typename T>
queue<T>::queue(queue&& other) noexcept {
  if (this == &other) return;
  tail = nullptr;
  count = 0;
  for (size_t i = 0; i < other.size(); i++) {
    push(other.at(i));
  }
  other.clear();
}

template <typename T>
queue<T>::~queue(){
  delete_queue();
}


template <typename T>
T& queue<T>::front() {
  if (head == nullptr || tail == nullptr) throw std::logic_error("queue is empty");
  return (tail->value);
}

template <typename T>
T& queue<T>::back() {
  if (head == nullptr || tail == nullptr) throw std::logic_error("queue is empty");
  return (head->value);
}

template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& other) {
  if (other == *this) return *this;
  delete_queue();
  tail = nullptr;
  count = 0;
  for (size_t i = 0; i < other.size(); i++) {
    push(other.at(i));
  }
  return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue<T>&& other) {
  // delete_queue(tail);
  if (this == &other) return *this;
  tail = nullptr;
  count = 0;
  for (size_t i = 0; i < other.size(); i++) {
    push(other.at(i));
  }
  other.clear();
  return *this;
}

template <typename T>
bool queue<T>::operator==(const queue<T>& other) {
  if (count != other.size()) return false;
  for (size_t i = 0; i < count; i++) {
    if (at(i) != other.at(i)) {
      return false;
    }
  }
  return true;
}

template <typename T>
void queue<T>::delete_queue() {
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

template <typename T>
void queue<T>::pop() {
  if (!count) throw std::logic_error("Pop is not possible, Senpai");
  if (count == 1) {
    delete_queue();
  } else {
    Node* tmp = tail;
    tail = tail->ptr;
    delete tmp;
    --count;
  }
}

template <typename T>
T queue<T>::at(size_t arg) const{
  if (arg >= count) throw std::logic_error("Your index is too big, Senpai");
  Node* tmp = tail;
  for (size_t i = 0; i < arg; i++) {
    tmp = tmp->ptr;
  }
  return tmp->value;
}

template <typename T>
T queue<T>::operator[](size_t arg) const {
  return this->at(arg);
}


template <typename T>
void queue<T>::push(T value) {
  Node* new_Node = new Node(value);
  if (!tail) tail = new_Node;
  if (head) {
    head->ptr = new_Node;
    head = head->ptr;
    head->ptr = nullptr;
  } else {
    head = new_Node;
  }

  count++;
  // std::cout<<tail<<"\t"<<head<<std::endl;
}

template <typename T>
void queue<T>::clear() {
  delete_queue();
}

template <typename T>
void queue<T>::insert(T value, size_t pos) {
  Node* tmp = tail;
  for(int i = 0; i < pos; i++) {
    tmp = tmp->ptr;
  }
  Node* tmp2 = tmp->ptr;
  tmp = new Node(value);
  tmp->ptr = tmp2;
  count++;
}

template <typename T>
T queue<T>::top() const {
  if (0 == count) throw std::logic_error("no such element, sempai");
  return head->value;
}

template <typename T>
void queue<T>::swap(queue<T>& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(count, other.count);
}

template <typename T>
bool queue<T>::empty() { return 0 == count;}

template <typename T>
size_t queue<T>::size() const {
  return count;
}

template <typename T>
template <class... Args>
void queue<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    Node* new_node = new Node(arg);
    new_node->value = arg;
    new_node->ptr = tail;
    tail = new_node;
    count++;
  }
}