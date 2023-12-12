#include "s21_multiset.h"
#include <iostream>

namespace s21 {
template <typename Key>
multiset<Key>::multiset(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i < items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(multiset &&other) noexcept {
  if (this != &other) {
    AVLTree<Key, Key>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(const multiset &other) {
  if (this != &other) {
    AVLTree<Key, Key>::operator=(other);
  }
  return *this;
}


}  // namespace s21