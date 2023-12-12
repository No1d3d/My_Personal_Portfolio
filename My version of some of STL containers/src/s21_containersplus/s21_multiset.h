#ifndef S21_CPP_CONTAINERS_SET_H_
#define S21_CPP_CONTAINERS_SET_H_

#include "../s21_containers/Tree/AVLTree.h"
//#include "../vector/s21_vector.h"
#include <vector>
namespace s21 {
    template <typename Key>
    class multiset : public AVLTree<Key, Key> {



        public:
        using key_type = Key;
        using value_type = Key;
        using iterator = typename AVLTree<Key, Key>::iterator;
        using con_iterator = typename AVLTree<Key, Key>::ConIterator;
        using size_type = size_t;

        multiset() : AVLTree<Key, Key>(){};
        multiset(std::initializer_list<value_type> const &items);
        multiset(const multiset &other) : AVLTree<Key, Key>(other){};
        multiset(multiset &&other) noexcept : AVLTree<Key, Key>(std::move(other)){};
        multiset &operator=(multiset &&other) noexcept;
        multiset &operator=(const multiset &other);
        ~multiset() = default;

        std::pair<iterator, bool> insert(const value_type &value) {
        return this->multiinsert(value);
        }

    };
};

#include "s21_multiset.tpp"

#endif //S21_CPP_CONTAINERS_SET_H_
