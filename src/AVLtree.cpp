//
// Created by antalix on 20.04.23.
//

#include "../include/AVLtree.h"

template< class T >
int Node<T>::compareTo(std::unique_ptr<Node<T>>& node2){
    return k -node2->k;
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
    return value;
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
        root = insert(std::move(root), value);
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
        root = remove(std::move(root), value);
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
        node->left = insert(std::move(node->left), value);
    }
    else{
        node->right = insert(std::move(node->right), value);
    }
    update(node);
    return balance(std::move(node));
}
template<typename T>
auto AVLtree<T>::remove(std::unique_ptr<Node<T>> &node, const T &value) {
    if( node == nullptr )
        return nullptr;
    int cmp = value.compareTo(node->value);
    if( cmp < 0){
        node->left = remove(std::move(node->left), value);
    }
    else if( cmp > 0){
        node->right = remove(std::move(node->right), value);
    }
    else{
        if(node->left == nullptr){
            return std::move(node->right);
        }
        else if( node->right == nullptr){
            return std::move(node->left);
        }
        else{
            if( node->left->height > node->right->height){
                T successor_value = find_max(node->left);
                node->value = successor_value;
                node->left = remove(std::move(node->left), successor_value);
            }
            else{
                T successor_value = find_min(node->left);
                node->value = successor_value;
                node->right = remove(std::move(node->right), successor_value);
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
            return left_left_case(std::move(node));
        }
        else{
            return left_right_case(std::move(node));
        }
    }
    //Right balancing sub tree
    else if( node->bf == 2 ){
        if( node->right->bf >= 0 ){
            return right_right_case(std::move(node));
        }
        else{
            return right_left_case(std::move(node));
        }
    }
    return node;
}
template<typename T>
auto AVLtree<T>::left_left_case(std::unique_ptr<Node<T>> &node) {
    return right_rotation(std::move(node));
}
template<typename T>
auto AVLtree<T>::left_right_case(std::unique_ptr<Node<T>> &node) {
    node->left = left_rotation(std::move(node->left));
    return left_left_case(std::move(node));
}
template<typename T>
auto AVLtree<T>::right_left_case(std::unique_ptr<Node<T>> &node) {
    node->right = right_rotation(std::move(node->right));
    return right_right_case(std::move(node));
}
template<typename T>
auto AVLtree<T>::right_right_case(std::unique_ptr<Node<T>> &node) {
    return left_rotation(std::move(node));
}
template<typename T>
auto AVLtree<T>::left_rotation(std::unique_ptr<Node<T>> &node) {
    std::unique_ptr<Node<T>> new_parent = std::move(node->right);
    node->right = std::move(new_parent->left);
    new_parent->left = std::move(node);
    update(node);
    update(new_parent);
    return new_parent;
}
template<typename T>
auto AVLtree<T>::right_rotation(std::unique_ptr<Node<T>> &node) {
    std::unique_ptr<Node<T>> new_parent = std::move(node->left);
    node->left = std::move(new_parent->right);
    new_parent->right = std::move(node);
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



template<typename T>
void AVLtree<T>::show_tree( std::unique_ptr<Node<T>>& node){
    if(node != nullptr){
        show_tree(node->left);
        std::cout <<node->value<<" ";
        show_tree(node->right);
    }
}