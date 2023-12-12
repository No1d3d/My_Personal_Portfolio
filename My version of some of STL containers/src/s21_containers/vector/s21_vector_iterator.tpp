#ifndef S21_CPP_CONTAINERS_VECTOR_ITERATOR_TPP_
#define S21_CPP_CONTAINERS_VECTOR_ITERATOR_TPP_

namespace s21 {

template <typename T>
vector<T>::VectorIterator::VectorIterator(iterator_pointer ptr) : ptr_(ptr) {}

template <typename T>
typename vector<T>::reference vector<T>::VectorIterator::operator*() {
    return *ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
    VectorIterator tmp(*this);
    ++ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
    VectorIterator tmp(*this);
    --ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator++() {
    ++ptr_;
    return *this;
}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator--() {
    --ptr_;
    return *this;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator &other) const {
    return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator &other) const {
    return ptr_ != other.ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(
    int n) const {
    VectorIterator tmp(*this);
    for (int i = 0; i < n; i++) {
        tmp++;
    };
    return tmp;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(
    int n) const {
    VectorIterator tmp(*this);
    for (int i = 0; i < n; i++) {
        tmp--;
    };
    return tmp;
}

template <typename T>
ptrdiff_t vector<T>::VectorIterator::operator-(
    const VectorIterator &other) const {
    return ptr_ - other.ptr_;
}

template <typename T>
vector<T>::ConstVectorIterator::ConstVectorIterator(const_iterator_pointer ptr)
    : ptr_(ptr) {}

template <typename T>
typename vector<T>::const_reference vector<T>::ConstVectorIterator::operator*()
    const {
    return *ptr_;
}

template <typename T>
typename vector<T>::ConstVectorIterator
vector<T>::ConstVectorIterator::operator++(int) {
  ConstVectorIterator tmp(*this);
    ++ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::ConstVectorIterator
vector<T>::ConstVectorIterator::operator--(int) {
  ConstVectorIterator tmp(*this);
    --ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::ConstVectorIterator &
vector<T>::ConstVectorIterator::operator++() {
    ++ptr_;
    return *this;
}

template <typename T>
typename vector<T>::ConstVectorIterator &
vector<T>::ConstVectorIterator::operator--() {
    --ptr_;
    return *this;
}

template <typename T>
bool vector<T>::ConstVectorIterator::operator==(
    const ConstVectorIterator &other) const {
    return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::ConstVectorIterator::operator!=(
    const ConstVectorIterator &other) const {
    return ptr_ != other.ptr_;
}

template <typename T>
typename vector<T>::ConstVectorIterator
vector<T>::ConstVectorIterator::operator+(int n) const {
    ConstVectorIterator tmp(*this);
    for (int i = 0; i < n; i++) {
        tmp++;
    };
    return tmp;
}

template <typename T>
typename vector<T>::ConstVectorIterator
vector<T>::ConstVectorIterator::operator-(int n) const {
    ConstVectorIterator tmp(*this);
    for (int i = 0; i < n; i++) {
        tmp--;
    };
    return tmp;
}

template <typename T>
ptrdiff_t vector<T>::ConstVectorIterator::operator-(
    const ConstVectorIterator &other) const {
    return ptr_ - other.ptr_;
}

}  // namespace s21

#endif // S21_CPP_CONTAINERS_VECTOR_ITERATOR_TPP_