#ifndef S21_CPP_CONTAINERS_SET_H_
#define S21_CPP_CONTAINERS_SET_H_

#include "../Tree/AVLTree.h"
#include "../vector/s21_vector.h"
namespace s21 {
template <typename Key>
class set : public AVLTree<Key, Key> {
  // protected:
  //   struct Node;
 public:
  using key_type = Key;
  using value_type = Key;
  using iterator = typename AVLTree<Key, Key>::iterator;
  using const_iterator = typename AVLTree<Key, Key>::ConIterator;
  using size_type = size_t;

  set() : AVLTree<Key, Key>(){};
  set(std::initializer_list<value_type> const &items);
  set(const set &other) : AVLTree<Key, Key>(other){};
  set(set &&other) noexcept : AVLTree<Key, Key>(std::move(other)){};
  set &operator=(set &&other) noexcept;
  set &operator=(const set &other);
  ~set() = default;

  /*
  struct Node {
      Node(Key key);
      Node(Key key, Node* parent);
      Key key_;
      Node* left_ = nullptr;
      Node* right_ = nullptr;
      Node* parent_ = nullptr;
      int height_ = 0;
      friend class AVLTree<Key, Key>;
  };

  Node* root_;
  void FreeNode(Node* node);
  Node* CopyTree(Node* node, Node* parent);
  void SwapValue(Node* a, Node* b);
  void RightRotate(Node* node);
  void LeftRotate(Node* node);
  void Balance(Node* node);
  int GetBalance(Node* node);
  int GetHeight(Node* node);
  void SetHeight(Node* node);
  static Node* GetMin(Node* node);
  static Node* GetMax(Node* node);
  bool RecInsert(Node* node, const Key& key);
  Node* RecDelete(Node* node, Key key);
  size_t RecSize(Node* node);
  Node* RecFind(Node* node, const Key& key);
*/
};
};  // namespace s21

#include "s21_set.tpp"

#endif  // S21_CPP_CONTAINERS_SET_H_
