#pragma once

#include "Stl.hpp"

template <typename Key, typename Compare>
class Iterator {
   public:
    using key_type = Key;
    using value_type = Key;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using value_compare = Compare;
    using reference = Key &;
    using const_reference = const Key &;
    using pointer = Key *;
    using const_pointer = const Key *;
    using iterator_category = std::bidirectional_iterator_tag;

    Iterator() = default;
    Iterator(typename Stl<Key, Compare>::Node *node, typename Stl<Key, Compare>::Node *root,
             bool after_end = false, bool before_begin = false)
        : node(node), root(root), beforeBegin(before_begin), afterEnd(after_end) {}

    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);

    const_reference operator*();
    const_pointer operator->();

    bool operator==(const Iterator &);
    bool operator!=(const Iterator &);

   private:
    typename Stl<Key, Compare>::Node *node = nullptr;
    typename Stl<Key, Compare>::Node *root = nullptr;

    bool beforeBegin = false;
    bool afterEnd = false;
};

template <typename Key, typename Compare>
Iterator<Key, Compare> &Iterator<Key, Compare>::operator++() {
    if (node) {
        node = node->next;
        if (!node) {
            afterEnd = true;
        }
    } else if (beforeBegin) {
        node = Stl<Key, Compare>::getLeftMost(root);
        beforeBegin = false;
    }
    return *this;
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Iterator<Key, Compare>::operator++(int) {
    Iterator<Key, Compare> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename Key, typename Compare>
Iterator<Key, Compare> &Iterator<Key, Compare>::operator--() {
    if (node) {
        node = node->prev;
        if (!node) {
            beforeBegin = true;
        }
    } else if (afterEnd) {
        node = Stl<Key, Compare>::getRightMost(root);
        afterEnd = false;
    }
    return *this;
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Iterator<Key, Compare>::operator--(int) {
    Iterator<Key, Compare> tmp(*this);
    --(*this);
    return tmp;
}

template <typename Key, typename Compare>
const Key &Iterator<Key, Compare>::operator*() {
    if (!node) {
        throw("attempt to use operator* to nullptr");
    }

    return node->key;
}

template <typename Key, typename Compare>
const Key *Iterator<Key, Compare>::operator->() {
    if (!node) {
        throw("attempt to use operator-> to nullptr");
    }

    return &(node->key);
}

template <typename Key, typename Compare>
bool Iterator<Key, Compare>::operator==(const Iterator<Key, Compare> &other) {
    return node == other.node;
}

template <typename Key, typename Compare>
bool Iterator<Key, Compare>::operator!=(const Iterator<Key, Compare> &other) {
    return !(*this == other);
}
