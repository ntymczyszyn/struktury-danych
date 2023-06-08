#ifndef STRUKTURY_DANYCH_AVLTREE_H
#define STRUKTURY_DANYCH_AVLTREE_H

#include "../src/AVLNode.cpp"
#include "AVLNode.h"
#include <string>

template < typename T>
class AVLtree {
public:
    AVLtree();
    ~AVLtree();

    AVLNode<T>* root;
    int nodeCount;
    int height() const;
    int size() const;
    bool find(const T& value);
    bool insert(const T& value);
    bool remove(const T& value);
    void displayBinaryTree(AVLNode<T> *root, std::string indent, bool last);

private:
    friend class AVLNode<T>;  // <-nie jestem pewna czy ma być

    bool find(AVLNode<T>* node, const T& value);
    auto insert(AVLNode<T>* node, const T& value);
    AVLNode<T>* remove(AVLNode<T>* node, const T& value);

    void update(AVLNode<T>* node);
    auto balance(AVLNode<T>* node);
    auto leftLeftCase(AVLNode<T>* node);
    auto leftRightCase(AVLNode<T>* node);
    auto rightLeftCase(AVLNode<T>* node);
    auto rightRightCase(AVLNode<T>* node);
    auto leftRotation(AVLNode<T>* node);
    auto rightRotation(AVLNode<T>* node);
    AVLNode<T>* findMin(AVLNode<T>* node) const;
    AVLNode<T>* findMax(AVLNode<T>* node) const;
};


















// TODO: add iterator class
// TODO: add printing function
// TODO: add validation function

#endif //STRUKTURY_DANYCH_AVLTREE_H
