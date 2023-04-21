//
// Created by antalix on 20.04.23.
//

#ifndef STRUKTURY_DANYCH_AVLTREE_H
#define STRUKTURY_DANYCH_AVLTREE_H

#include <memory>
template <typename T>
class Node {
public:
    Node(const T& value);
    ~Node();
    std::unique_ptr<T> left;
    std::unique_ptr<T> right;
    T value;
    int height;
    int bf; // balance factor

    // getters - for display
    std::unique_ptr<Node<T>> getLeft() const;
    std::unique_ptr<Node<T>> getRight() const;
    T getValue() const;
};

template < typename T>
class AVLtree {
public:
    AVLtree();
    ~AVLtree();
    std::unique_ptr<Node<T>> root;
    int nodeCount;
    int height() const;
    int size() const;
    bool isEmpty() const;
    bool contains(const T& value);
    bool insert(const T& value);
    bool remove(const T& value);
private:
    bool contains(std::unique_ptr<Node<T>>& node, const T& value);
    auto insert(std::unique_ptr<Node<T>>& node, const T& value);
    auto remove(std::unique_ptr<Node<T>>& node, const T& value);

    void update(std::unique_ptr<Node<T>>& node);
    auto balance(std::unique_ptr<Node<T>>& node);
    auto leftLeftCase(std::unique_ptr<Node<T>>& node);
    auto leftRightCase(std::unique_ptr<Node<T>>& node);
    auto rightLeftCase(std::unique_ptr<Node<T>>& node);
    auto rightRightCase(std::unique_ptr<Node<T>>& node);
    auto leftRotation(std::unique_ptr<Node<T>>& node);
    auto rightRotation(std::unique_ptr<Node<T>>& node);
    T findMin(std::unique_ptr<Node<T>>& node) const;
    T findMax(std::unique_ptr<Node<T>>& node) const;
};
// TODO: add iterator class
// TODO: add printing function
// TODO: add validation function

#endif //STRUKTURY_DANYCH_AVLTREE_H
