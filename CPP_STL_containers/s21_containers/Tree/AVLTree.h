#ifndef S21_CPP_CONTAINERS_AVLTREE_H_
#define S21_CPP_CONTAINERS_AVLTREE_H_

#include <iostream>
#include <limits>

template <typename Key, typename Value>
class AVLTree {
 protected:
  struct Node;

 public:
  class Iterator;
  class ConIterator;
  using key_type = Key;
  using value_type = Value;
  using reference = value_type&;
  using con_reference = const value_type&;
  using iterator = Iterator;
  using con_iterator = ConIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node* node, Node* prev_node = nullptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator& it);
    friend class AVLTree<Key, Value>;
    bool operator!=(const iterator& it);

    
   protected:
    Node* iter_node;
    Node* iter_prev_node;
    Node* MoveFW(Node* node);
    Node* MoveBW(Node* node);
  };

  class ConIterator {
   public:
    ConIterator() : Iterator(){};
    con_reference operator*() const { return Iterator::operator*(); };
  };

  AVLTree();
  AVLTree(const AVLTree& other);
  AVLTree(AVLTree&& other) noexcept;
  ~AVLTree();
  AVLTree& operator=(AVLTree&& other) noexcept;
  AVLTree& operator=(const AVLTree& other);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const Key& key);
  std::pair<iterator, bool> multiinsert(const Key& key);
  void erase(iterator pos);
  void swap(AVLTree& other);
  void merge(AVLTree& other);
  bool contains(const Key& key);
  iterator lower_bound(value_type value);
  iterator upper_bound(value_type value);
  iterator find(const Key& key);

 protected:
  struct Node {
    Node(Key key, value_type value);
    Node(Key key, value_type value, Node* parent);
    Key key_;
    value_type value_;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node* parent_ = nullptr;
    int height_ = 0;
    friend class AVLTree<Key, Value>;
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
  bool RecInsert(Node* node, const Key& key, Value value);
   bool RecmultInsert(Node* node, const Key& key, Value value);
  Node* RecDelete(Node* node, Key key);
  size_t RecSize(Node* node);
  Node* RecFind(Node* node, const Key& key);
};

#include "AVLTree.tpp"

#endif  // S21_CPP_CONTAINERS_AVLTREE_H_