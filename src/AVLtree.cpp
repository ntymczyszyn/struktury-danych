//
// Created by antalix on 20.04.23.
//

#include "../include/AVLtree.h"

template< class T >
int Node<T>::compareTo(std::unique_ptr<Node<T>>& node2){
    return k.compareTo(node2->k);
}

template< class T >
std::unique_ptr<Node<T>> Node<T>::get_left() const{
    return left;
}

template< class T >
std::unique_ptr<Node<T>> Node<T>::get_right() const{
    return right;
}

// nie wiem co tutaj chciałaś zrobić
template< class T >
T Node<T>::get_value() const{
    return;
}

template<typename T>
AVLtree<T>::AVLtree() {
}
template<typename T>
AVLtree<T>::~AVLtree() {
}
template<typename T>
int AVLtree<T>::height() const {
    if(root == nullptr)
        return 0;
    return root->height;
}
template<typename T>
int AVLtree<T>::size() const {
    return node_count;
}
template<typename T>
bool AVLtree<T>::isEmpty() const {
    return size() == 0;
}
template<typename T>
bool AVLtree<T>::contains(const T &value) {
    return contains(root, value);
}
template<typename T>
bool AVLtree<T>::insert(const T &value) {
    if( value == nullptr) {
        return false;
    }
    if( !contains(root, value)){
        root = insert(root, value);
        node_count++;
        return true;
    }
    return false;
}
template<typename T>
bool AVLtree<T>::remove(const T &value) {
    if(value == nullptr ) {
        return false;
    }
    if(contains(root, value)){
        root = remove(root, value);
        node_count--;
        return true;
    }
    return false;
}
template<typename T>
bool AVLtree<T>::contains(std::unique_ptr<Node<T>> &node, const T &value) {
    if(node == nullptr) {
        return false;
    }
    int cmp = value.compareTo(node->value);
    // get into left sub tree
    if( cmp < 0) {
        return contains(node->left, value);
    }
    // get into  right sub tree
    if( cmp > 0) {
        return contains(node->right, value);
    }
    return true;

}
template<typename T>
auto AVLtree<T>::insert(std::unique_ptr<Node<T>> &node, const T &value) {
    if( node == nullptr) {
        return new Node<T>(value);
    }
    int cmp = value.compareTo(node->value);
    // Insert node in proper sub tree
    if( cmp < 0) {
        node->left = insert(node->left, value);
    }
    else{
        node->right = insert(node->right, value);
    }
    update(node);
    return balance(node);
}
template<typename T>
auto AVLtree<T>::remove(std::unique_ptr<Node<T>> &node, const T &value) {
    if( node == nullptr )
        return nullptr;
    int cmp = value.compareTo(node->value);
    if( cmp < 0){
        node->left = remove(node->left, value);
    }
    else if( cmp > 0){
        node->right = remove(node->right, value);
    }
    else{
        if(node->left == nullptr){
            return node->right;
        }
        else if( node->right == nullptr){
            return node->left;
        }
        else{
            if( node->left->height > node->right->height){
                T successor_value = find_max(node->left);
                node->value = successor_value;
                node->left = remove(node->left, successor_value);
            }
            else{
                T successor_value = find_min(node->left);
                node->value = successor_value;
                node->right = remove(node->right, successor_value);
            }
        }
    }
    update(node);
    return balance(node);
}
template<typename T>
void AVLtree<T>::update(std::unique_ptr<Node<T>> &node) {
    int left_node_height = (node->left = nullptr) ? -1 : node->left->height;
    int right_node_height = (node->right == nullptr) ? -1: node->right->height;
    // Update height
    node->height = 1 + std::max(left_node_height, right_node_height);
    // Update balance factor
    node->bf = right_node_height - left_node_height;
}
template<typename T>
auto AVLtree<T>::balance(std::unique_ptr<Node<T>> &node) {
    // Left balancing sub tree
    if(node->bf == -2){
        if( node->left->bf <= 0 ){
            return left_left_case(node);
        }
        else{
            return left_right_case(node);
        }
    }
    //Right balancing sub tree
    else if( node->bf == 2 ){
        if( node->right->bf >= 0 ){
            return right_right_case(node);
        }
        else{
            return right_left_case(node);
        }
    }
    return node;
}
template<typename T>
auto AVLtree<T>::left_left_case(std::unique_ptr<Node<T>> &node) {
    return right_rotation(node);
}
template<typename T>
auto AVLtree<T>::left_right_case(std::unique_ptr<Node<T>> &node) {
    node->left = left_rotation(node->left);
    return left_left_case(node);
}
template<typename T>
auto AVLtree<T>::right_left_case(std::unique_ptr<Node<T>> &node) {
    node->right = right_rotation(node->right);
    return right_right_case(node);
}
template<typename T>
auto AVLtree<T>::right_right_case(std::unique_ptr<Node<T>> &node) {
    return left_rotation(node);
}
template<typename T>
auto AVLtree<T>::left_rotation(std::unique_ptr<Node<T>> &node) {
    std::unique_ptr<Node<T>> new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    update(node);
    update(new_parent);
    return new_parent;
}
template<typename T>
auto AVLtree<T>::right_rotation(std::unique_ptr<Node<T>> &node) {
    std::unique_ptr<Node<T>> new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    update(node);
    update(new_parent);
    return new_parent;
}
template<typename T>
T AVLtree<T>::find_min(std::unique_ptr<Node<T>> &node) const {
    while( node->left != nullptr)
        node = node->left;
    return node->value;
}
template<typename T>
T AVLtree<T>::find_max(std::unique_ptr<Node<T>> &node) const {
    while( node->right != nullptr)
        node = node->right;
    return node->value;
}