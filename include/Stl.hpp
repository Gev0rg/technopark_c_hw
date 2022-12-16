#pragma once

#include <iostream>

template <typename Key, typename Compare>
class Iterator;

template <typename Key, typename Compare = std::less<Key>>
class Stl {
   public:
    using key_type = Key;
    using value_type = Key;
    using size_type = std::size_t;
    using difference_ype = std::ptrdiff_t;
    using key_compare = Compare;
    using value_compare = Compare;
    using reference = Key&;
    using const_reference = const Key&;
    using iterator = Iterator<Key, Compare>;

   private:
    struct Node {
        Key key;

        size_t height;

        Node* left;
        Node* right;

        Node(const_reference key) : key(key), height(1), left(nullptr), right(nullptr) {}
    };

   public:
    Stl() : root(nullptr), treeSize(0), comp(Compare()) {}
    template <class InputIterator>
    Stl(InputIterator first, InputIterator last, const Compare& comp = Compare());
    Stl(const std::initializer_list<Key>& init_list);
    template <typename Cmp = Compare>
    Stl(const Stl<Key, Cmp>& other);
    Stl(const Stl &other);
    Stl& operator=(Stl other);

    ~Stl();

    void insert(const_reference key);
    void erase(const_reference key);

    size_type size() const;
    bool empty() const;

    iterator find(const_reference key) const;
    iterator lower_bound(const_reference key) const;

    iterator begin() const;
    iterator end() const;

    bool operator==(const Stl<Key, Compare> &other) const;
    bool operator!=(const Stl<Key, Compare> &other) const;

   private:
    friend class Iterator<Key, Compare>;

    iterator _find(Node* node, const_reference key) {}
    Node* _insert(Node* node, const_reference key) {}
    Node* _erase(Node* node, const_reference key) {}

    Node* findMin(Node* node);
    Node* removeMin(Node* node);

    size_t getHeight(Node* node) const;
    void fixHeight(Node* node);

    int bFactor(Node* node) const;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balance(Node* node);

    Node *getLeftMost(Node *node) {}
	Node *getRightMost(Node *node) {}

    Node* root;
    size_type treeSize;
    key_compare comp;
};

template <typename Key, typename Compare>
bool Stl<Key, Compare>::operator==(const Stl<Key, Compare> &other) const
{
}

template <typename Key, typename Compare>
bool Stl<Key, Compare>::operator!=(const Stl<Key, Compare> &other) const
{
}

template <typename Key, typename Compare>
template <typename InputIterator>
Stl<Key, Compare>::Stl(InputIterator first, InputIterator last, const Compare& cmp) : comp(cmp)
{
}

template <typename Key, typename Compare>
Stl<Key, Compare>::Stl(std::initializer_list<Key> const &init_list)
{
}

template <typename Key, typename Compare>
template <typename Cmp>
Stl<Key, Compare>::Stl(const Stl<Key, Cmp> &other)
{
}

template <typename Key, typename Compare>
Stl<Key, Compare>::Stl(const Stl &other)
{
}

template <typename Key, typename Compare>
Stl<Key, Compare>::~Stl()
{
}

template <typename Key, typename Compare>
Stl<Key, Compare> &Stl<Key, Compare>::operator=(Stl other)
{
}

template <typename Key, typename Compare>
void Stl<Key, Compare>::insert(const Key &data)
{
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::find(const Key &data) const
{
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::lower_bound(const Key &data) const
{
}

template <typename Key, typename Compare>
void Stl<Key, Compare>::erase(const Key &data)
{
}

template <typename Key, typename Compare>
size_t Stl<Key, Compare>::getHeight(Node *node) const
{
}

template <typename Key, typename Compare>
void Stl<Key, Compare>::fixHeight(Node *node)
{
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node *Stl<Key, Compare>::rotateLeft(Node *node)
{
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node *Stl<Key, Compare>::rotateRight(Node *node)
{
}

template <typename Key, typename Compare>
int Stl<Key, Compare>::bFactor(Node *node) const
{
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node *Stl<Key, Compare>::balance(Node *node)
{
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::begin() const
{
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::end() const
{
}

template <typename Key, typename Compare>
std::size_t Stl<Key, Compare>::size() const
{
}

template <typename Key, typename Compare>
bool Stl<Key, Compare>::empty() const
{
}
