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

        size_t getHeight;

        // для AVL-дерева
        Node* left;
        Node* right;
        Node* parent;

        // для удобного итерирования
        Node* next;
        Node* prev;

        Node(const_reference key) : key(key), getHeight(1), left(nullptr), right(nullptr) {}

        ~Node() { left = right = parent = next = prev = nullptr; }
    };

   public:
    Stl() : root(nullptr), first(nullptr), last(nullptr), _size(0), comp(Compare()) {}
    template <class InputIterator>
    Stl(InputIterator first, InputIterator last, const Compare& comp = Compare());
    Stl(const std::initializer_list<Key>& init_list);
    template <typename Cmp = Compare>
    Stl(const Stl<Key, Cmp>& other);
    Stl(const Stl& other);
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

    bool operator==(const Stl<Key, Compare>& other) const;
    bool operator!=(const Stl<Key, Compare>& other) const;

   private:
    friend class Iterator<Key, Compare>;

    Node* _find(Node* node, const_reference key) const;
    Node* _lower_bound(Node* node, const_reference key) const;
    Node* _insert(Node* node, const_reference key);
    Node* _erase(Node* node, const_reference key);

    Node* findMin(Node* node);
    Node* removeMin(Node* node);

    size_t getHeight(Node* node) const;
    void fixHeight(Node* node);

    int bFactor(Node* node) const;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balance(Node* node);

    static Node* getLeftMost(Node* node);
    static Node* getRightMost(Node* node);

    void deleteStl(Node* node);

    Node* prevFind(Node* node);
    Node* nextFind(Node* node);

    Node* root;
    Node* first;
    Node* last;

    size_type _size;
    key_compare comp;
};

template <typename Key, typename Compare>
template <typename InputIterator>
Stl<Key, Compare>::Stl(InputIterator first, InputIterator last, const Compare& cmp) : root(nullptr), first(nullptr), last(nullptr), _size(0), comp(cmp) {
    while (first != last) {
        insert(*first);
        ++first;
    }
}

template <typename Key, typename Compare>
Stl<Key, Compare>::Stl(std::initializer_list<Key> const& init_list) : root(nullptr), first(nullptr), last(nullptr), _size(0), comp(Compare()) {
    for (auto&& elem : init_list) {
        insert(elem);
    }
}

template <typename Key, typename Compare>
template <typename Cmp>
Stl<Key, Compare>::Stl(const Stl<Key, Cmp>& other) : root(nullptr), first(nullptr), last(nullptr), _size(0), comp(Compare()) {
    for (auto elem : other) {
        std::cout << elem;
        insert(elem);
    }
}

template <typename Key, typename Compare>
Stl<Key, Compare>::Stl(const Stl& other) : root(nullptr), first(nullptr), last(nullptr), _size(0), comp(Compare()) {
    for (auto elem : other) {
        insert(elem);
    }
}

template <typename Key, typename Compare>
Stl<Key, Compare>::~Stl() {
    deleteStl(root);
}

template <typename Key, typename Compare>
void Stl<Key, Compare>::deleteStl(Node* node) {
    if (!node) return;
    deleteStl(node->left);
    deleteStl(node->right);
    delete node;
}

template <typename Key, typename Compare>
Stl<Key, Compare>& Stl<Key, Compare>::operator=(Stl other) {
    std::swap(root, other.root);
    std::swap(first, other.first);
    std::swap(last, other.last);
    std::swap(comp, other.comp);
    std::swap(_size, other._size);
    return *this;
}

template <typename Key, typename Compare>
bool Stl<Key, Compare>::operator==(const Stl<Key, Compare>& other) const {
    auto iteratorOther = other.begin();
    for (auto it = begin(); it != end(); ++it) {
        if (*iteratorOther != *it) {
            return false;
        }
        iteratorOther++;
    }
    return true;
}

template <typename Key, typename Compare>
bool Stl<Key, Compare>::operator!=(const Stl<Key, Compare>& other) const {
    return !(*this == other);
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::begin() const {
    if (!root) {
        return end();
    }
    return Iterator<Key, Compare>(first, root);
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::end() const {
    return Iterator<Key, Compare>(nullptr, root, true);
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::_lower_bound(Node* node, const_reference key) const {
    Node* result = nullptr;
    while (node) {
        if (comp(node->key, key)) {
            node = node->right;
        } else {
            result = node;
            node = node->left;
        }
    }
    return result;
}

template <typename Key, typename Compare>
void Stl<Key, Compare>::insert(const Key& key) {
    if (_find(root, key)) {
        return;
    }

    root = _insert(root, key);
    auto ptrNode = _find(root, key);

    if (!first || comp(ptrNode->key, first->key)) {
        first = ptrNode;
    }

    if (!last || comp(last->key, ptrNode->key)) {
        last = ptrNode;
    }

    ptrNode->prev = prevFind(ptrNode);
    if (ptrNode->prev) {
        ptrNode->prev->next = ptrNode;
    }

    ptrNode->next = nextFind(ptrNode);
    if (ptrNode->next) {
        ptrNode->next->prev = ptrNode;
    }
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::prevFind(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (node->left) {
        node = node->left;
        return getRightMost(node);
    } else {
        Node* neededParent = node->parent;
        while (neededParent && neededParent->right != node) {
            node = neededParent;
            neededParent = node->parent;
        }
        return neededParent;
    }
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::nextFind(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (node->right) {
        node = node->right;
        return getLeftMost(node);
    } else {
        Node* neededParent = node->parent;
        while (neededParent && neededParent->left != node) {
            node = neededParent;
            neededParent = node->parent;
        }
        return neededParent;
    }
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::_insert(Node* node, const_reference key) {
    if (!node) {
        _size++;
        return new Node(key);
    }

    if (comp(key, node->key)) {
        node->left = _insert(node->left, key);
        node->left->parent = node;
    } else if (comp(node->key, key)) {
        node->right = _insert(node->right, key);
        node->right->parent = node;
    }

    return balance(node);
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::find(const Key& key) const {
    auto tmp = _find(root, key);
    return tmp ? Iterator<Key, Compare>(tmp, root) : end();
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::_find(Node* node, const_reference key) const {
    if (!node) {
        return nullptr;
    }
    if (comp(key, node->key)) {
        return _find(node->left, key);
    } else if (comp(node->key, key)) {
        return _find(node->right, key);
    }
    return node;
}

template <typename Key, typename Compare>
Iterator<Key, Compare> Stl<Key, Compare>::lower_bound(const Key& key) const {
    auto tmp = _lower_bound(root, key);
    return tmp ? Iterator<Key, Compare>(tmp, root) : end();
}

template <typename Key, typename Compare>
void Stl<Key, Compare>::erase(const Key& key) {
    auto ptrNode = _find(root, key);
    if (ptrNode) {
        auto prevNode = prevFind(ptrNode);
        auto nextNode = nextFind(ptrNode);

        if (prevNode || nextNode) {
            if (prevNode && nextNode) {
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
            } else if (!prevNode) {
                nextNode->prev = nullptr;
            } else {
                prevNode->next = nullptr;
            }
        }

        root = _erase(root, key);
        first = getLeftMost(root);
        --_size;
    }
}

template <typename Key, typename Compare>
size_t Stl<Key, Compare>::getHeight(Node* node) const {
    return node ? node->getHeight : 0;
}

template <typename Key, typename Compare>
void Stl<Key, Compare>::fixHeight(Node* node) {
    node->getHeight = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::rotateLeft(Node* node) {
    if (!node) {
        return nullptr;
    }

    Node* rightNode = node->right;
    node->right = rightNode->left;
    if (rightNode->left) {
        rightNode->left->parent = node;
    }
    rightNode->left = node;
    rightNode->parent = node->parent;
    node->parent = rightNode;

    fixHeight(node);
    fixHeight(rightNode);

    return rightNode;
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::rotateRight(Node* node) {
    if (!node) {
        return nullptr;
    }

    Node* leftNode = node->left;
    node->left = leftNode->right;
    if (leftNode->right) {
        leftNode->right->parent = node;
    }
    leftNode->right = node;
    leftNode->parent = node->parent;
    node->parent = leftNode;

    fixHeight(leftNode);
    fixHeight(node);

    return leftNode;
}

template <typename Key, typename Compare>
int Stl<Key, Compare>::bFactor(Node* node) const {
    return static_cast<int>(getHeight(node->right)) - static_cast<int>(getHeight(node->left));
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::balance(Node* node) {
    fixHeight(node);
    int bf = bFactor(node);

    if (bf == 2) {
        if (bFactor(node->right) < 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    } else if (bf == -2) {
        if (bFactor(node->left) > 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    return node;
}

template <typename Key, typename Compare>
std::size_t Stl<Key, Compare>::size() const {
    return _size;
}

template <typename Key, typename Compare>
bool Stl<Key, Compare>::empty() const {
    return _size == 0;
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::getLeftMost(Node* node) {
    if (!node) {
        return nullptr;
    }
    while (node->left) {
        node = node->left;
    }
    return node;
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::getRightMost(Node* node) {
    if (!node) {
        return nullptr;
    }
    while (node->right) {
        node = node->right;
    }
    return node;
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::_erase(Node* node, const_reference key) {
    if (!node) {
        return nullptr;
    }

    if (comp(key, node->key)) {
        node->left = _erase(node->left, key);
        if (node->left) {
            node->right->parent = node;
        }
    } else if (comp(node->key, key)) {
        node->right = _erase(node->right, key);
        if (node->right) {
            node->right->parent = node;
        }
    } else {
        Node* left = node->left;
        Node* right = node->right;

        if (!right) {
            delete node;
            return left;
        }

        Node* minNode = findMin(right);
        minNode->right = removeMin(right);
        if (minNode->right) {
            minNode->right->parent = minNode;
        }
        minNode->left = left;
        if (minNode->left) {
            minNode->left->parent = minNode;
        }
        minNode->parent = node->parent;
        delete node;

        return balance(minNode);
    }
    return balance(node);
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::findMin(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (!node->left) {
        return node;
    }

    return findMin(node->left);
}

template <typename Key, typename Compare>
typename Stl<Key, Compare>::Node* Stl<Key, Compare>::removeMin(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (!node->left) {
        return node->right;
    }

    node->left = removeMin(node->left);

    return balance(node);
}
