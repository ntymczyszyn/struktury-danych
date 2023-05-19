//
// Created by antalix on 20.04.23.
//

#include "../include/AVLtree.h"
#include <iostream>
#include <queue>
#include <cmath>
template<typename T>
AVLtree<T>::AVLtree(): root(nullptr) {
}

template<typename T>
AVLtree<T>::~AVLtree() {
}

template<typename T>
int AVLtree<T>::height() const {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

template<typename T>
int AVLtree<T>::size() const {
    return node_count;
}

template<typename T>
bool AVLtree<T>::isEmpty() const {
    return this->size() == 0;
}

template<typename T>
bool AVLtree<T>::contains(const T& value) {
    return contains(root, value);
}

template<typename T>
bool AVLtree<T>::insert(const T& value) {
    if (!contains(root, value)) {
        std::cout << "DODAWANIE " << value << std::endl;
        root = insert(root, value);
        node_count++;
        return true;
    }
    return false;
}

template<typename T>
bool AVLtree<T>::remove(const T& value) {
    if (value == nullptr ) {
        return false;
    }
    if (contains(root, value)) {
        root = remove(root, value);
        node_count--;
        return true;
    }
    return false;
}

template<typename T>
bool AVLtree<T>::contains(Node<T>* node, const T& value) {
    if (node == nullptr) {
        return false;
    }
    T cmp = node->compareTo(value);
    // get into left subtree
    if (cmp > 0) {
        return contains(node->left, value);
    }
    // get into  right subtree
    else if (cmp < 0) {
        return contains(node->right, value);
    }
    else if (cmp == 0) {
        std::cout << "WARTOSC JUZ ISTNIEJE " << value << std::endl;
        return true;
    }
}

template<typename T>
auto AVLtree<T>::insert(Node<T>* node, const T& value) {
    if (node == nullptr) {
        return new Node<T> (value);
    }
    T cmp = node->compareTo(value);
    // Insert node into the proper subtree
    if (cmp > 0) {
        node->left = insert(node->left, value);
    }
    else if (cmp < 0) {
        node->right = insert(node->right, value);
    }
    update(node);
    return balance(node);
}

template<typename T>
auto AVLtree<T>::remove(Node<T>* node, const T& value) {
    if(node == nullptr) {
        return nullptr;
    }
    T cmp = node->compareTo(value);
    if (cmp > 0) {
        node->left = remove(node->left, value);
    }
    else if (cmp < 0) {
        node->right = remove(node->right, value);
    }
    else {
        if (node->left == nullptr) {
            return node->right;
        }
        else if (node->right == nullptr) {
            return node->left;
        }
        else {
            if (node->left->height > node->right->height) {
                T successor_value = find_max(node->left);
                node->value = successor_value;
                node->left = remove(node->left, successor_value);
            }
            else {
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
void AVLtree<T>::update(Node<T>* node) {
    int left_node_height = (node->left == nullptr) ? -1 : node->left->height;
    int right_node_height = (node->right == nullptr) ? -1 : node->right->height;

    node->height = std::max(left_node_height, right_node_height) + 1;

    node->bf = right_node_height - left_node_height;
}

template<typename T>
auto AVLtree<T>::balance(Node<T>* node) {
    // Left subtree is too heavy
    if (node->bf == -2) {
        if (node->left->bf <= 0) {
            return left_left_case(node);
        }
        else {
            return left_right_case(node);
        }
    }
    // Right subtree is too heavy
    else if (node->bf == 2) {
        if (node->right->bf >= 0) {
            return right_right_case(node);
        }
        else {
            return right_left_case(node);
        }
    }
    return node;
}

template<typename T>
auto AVLtree<T>::left_left_case(Node<T>* node) {
    return right_rotation(node);
}

template<typename T>
auto AVLtree<T>::left_right_case(Node<T>* node) {
    node->left = left_rotation(node->left);
    return left_left_case(node);
}

template<typename T>
auto AVLtree<T>::right_left_case(Node<T>* node) {
    node->right = right_rotation(node->right);
    return right_right_case(node);
}

template<typename T>
auto AVLtree<T>::right_right_case(Node<T>* node) {
    return left_rotation(node);
}

template<typename T>
auto AVLtree<T>::left_rotation(Node<T>* node) {
    Node<T>* new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template<typename T>
auto AVLtree<T>::right_rotation(Node<T>* node) {
    Node<T>* new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template<typename T>
T AVLtree<T>::find_min(Node<T>* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node->value;
}

template<typename T>
T AVLtree<T>::find_max(Node<T>* node) const {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node->value;
}

template<typename T>
void AVLtree<T>::displayBinaryTree(Node<T> *root, std::string indent, bool last) {
    if (root == nullptr)
        return;

    std::cout << indent;

    if (last) {
        std::cout << "|_____ ";
        indent += "  ";
    } else {
        std::cout << "|----- ";
        indent += "| ";
    }

    std::cout << root->value << std::endl;

    displayBinaryTree(root->right, indent + "     ", false);
    displayBinaryTree(root->left, indent + "     ", true);

}
