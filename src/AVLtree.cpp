//
// Created by antalix on 20.04.23.
//

#include "../include/AVLtree.h"

template<typename T>
AVLtree<T>::AVLtree() {
}
template<typename T>
AVLtree<T>::~AVLtree() {
}
template<typename T>
int AVLtree<T>::height() const {
    return 0;
}
template<typename T>
int AVLtree<T>::size() const {
    return 0;
}
template<typename T>
bool AVLtree<T>::isEmpty() const {
    return false;
}
template<typename T>
bool AVLtree<T>::contains(const T &value) {
    return false;
}
template<typename T>
bool AVLtree<T>::insert(const T &value) {
    return false;
}
template<typename T>
bool AVLtree<T>::remove(const T &value) {
    return false;
}
template<typename T>
bool AVLtree<T>::contains(std::unique_ptr<Node<T>> &node, const T &value) {
    return false;
}
template<typename T>
auto AVLtree<T>::insert(std::unique_ptr<Node<T>> &node, const T &value) {
    return nullptr;
}
template<typename T>
auto AVLtree<T>::remove(std::unique_ptr<Node<T>> &node, const T &value) {
    return nullptr;
}
template<typename T>
void AVLtree<T>::update(std::unique_ptr<Node<T>> &node) {
}
template<typename T>
auto AVLtree<T>::balance(std::unique_ptr<Node<T>> &node) {
    return nullptr;
}
template<typename T>
auto AVLtree<T>::leftLeftCase(std::unique_ptr<Node<T>> &node) {
    return nullptr;
}
template<typename T>
auto AVLtree<T>::leftRightCase(std::unique_ptr<Node<T>> &node) {
    return nullptr;
}
template<typename T>
auto AVLtree<T>::rightLeftCase(std::unique_ptr<Node<T>> &node) {
    return nullptr;
}
template<typename T>
auto AVLtree<T>::rightRightCase(std::unique_ptr<Node<T>> &node) {
    return nullptr;
}
template<typename T>
auto AVLtree<T>::leftRotation(std::unique_ptr<Node<T>> &node) {
    return nullptr;
}
template<typename T>
auto AVLtree<T>::rightRotation(std::unique_ptr<Node<T>> &node) {
    return nullptr;
}
template<typename T>
T AVLtree<T>::findMin(std::unique_ptr<Node<T>> &node) const {
    return nullptr;
}
template<typename T>
T AVLtree<T>::findMax(std::unique_ptr<Node<T>> &node) const {
    return nullptr;
}