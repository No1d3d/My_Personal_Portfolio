#ifndef S21_CPP_CONTAINERS_VECTOR_ITERATOR_H_
#define S21_CPP_CONTAINERS_VECTOR_ITERATOR_H_

namespace s21 {

template <typename T>
class vector<T>::VectorIterator {
 public:
  VectorIterator() = default;
  VectorIterator(iterator_pointer ptr);

  reference operator*();
  VectorIterator operator++(int);
  VectorIterator operator--(int);
  VectorIterator& operator++();
  VectorIterator& operator--();
  bool operator==(const VectorIterator& other) const;
  bool operator!=(const VectorIterator& other) const;
  VectorIterator operator+(int n) const;
  VectorIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorIterator& other) const;

 private:
  iterator_pointer ptr_;
};

template <typename T>
class vector<T>::ConstVectorIterator : public VectorIterator {
 public:
  ConstVectorIterator() = default;
  ConstVectorIterator(const_iterator_pointer ptr);

  const_reference operator*() const;
  ConstVectorIterator operator++(int);
  ConstVectorIterator operator--(int);
  ConstVectorIterator& operator++();
  ConstVectorIterator& operator--();
  bool operator==(const ConstVectorIterator& other) const;
  bool operator!=(const ConstVectorIterator& other) const;
  ConstVectorIterator operator+(int n) const;
  ConstVectorIterator operator-(int n) const;
  ptrdiff_t operator-(const ConstVectorIterator& other) const;

 private:
  const_iterator_pointer ptr_;
};

}  // namespace s21

#include "s21_vector_iterator.tpp"

#endif  // S21_CPP_CONTAINERS_VECTOR_ITERATOR_H_