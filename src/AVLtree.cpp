#include "../include/AVLtree.h"
#include <iostream>

template<typename T>
AVLtree<T>::AVLtree(): root(nullptr), nodeCount(0) {
}

template<typename T>
AVLtree<T>::~AVLtree() {
    AVLNode<T>* toDelete{};
    while(root != nullptr){
        toDelete = findMin(root);
        //std::cout << "Removing " << toDelete->value << std::endl;
        remove(toDelete->value);
        //displayBinaryTree(root, "", true);
    }
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
    return nodeCount;
}

template<typename T>
bool AVLtree<T>::find(const T& value) {
    return find(root, value);
}

template<typename T>
bool AVLtree<T>::insert(const T& value) {
    if (!find(root, value)) {
        std::cout << "DODAWANIE " << value << std::endl;
        root = insert(root, value);
        nodeCount++;
        return true;
    }
    return false;
}

template<typename T>
bool AVLtree<T>::remove(const T& value) {
    if (find(root, value)) {
        root = remove(root, value);
        nodeCount--;
        return true;
    }
    return false;
}

template<typename T>
bool AVLtree<T>::find(AVLNode<T>* node, const T& value) {
    if (node == nullptr) {
        return false;
    }
    T cmp = node->compareTo(value);

    if (cmp < 0) {
        return find(node->left, value);
    }
    else if (cmp > 0) {
        return find(node->right, value);
    }
    else if (cmp == 0) {
        std::cout << "WARTOSC JUZ ISTNIEJE " << value << std::endl;
        return true;
    }
    return false; //nie wiem czy potrzebne i musi być, ale nie ma warningów
}

template<typename T>
auto AVLtree<T>::insert(AVLNode<T>* node, const T& value) {
    if (node == nullptr) {
        return new AVLNode<T> (value);
    }
    T cmp = node->compareTo(value);

    if (cmp < 0) {
        node->left = insert(node->left, value);
    }
    else if (cmp > 0) {
        node->right = insert(node->right, value);
    }
    update(node);
    return balance(node);
}

template<typename T>
AVLNode<T>* AVLtree<T>::remove(AVLNode<T>* node, const T& value) {
    if(node == nullptr) {
        return nullptr;
    }
    T cmp = node->compareTo(value);
    if (cmp < 0) {
        node->left = remove(node->left, value);
    }
    else if (cmp > 0) {
        node->right = remove(node->right, value);
    }
    else {
        if (node->left == nullptr) {
            AVLNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            AVLNode<T>* temp = node->left;
            delete node;
            return temp;
        }
        else {
            if (node->left->height > node->right->height) {
                AVLNode<T>* temp = findMax(node->left);
                node->value = temp->value;
                node->left = remove(node->left, temp->value);
            }
            else {
                AVLNode<T>* temp = findMin(node->right); // Find the minimum value node in the right subtree
                node->value = temp->value; // Replace the node's value with the found node's value
                node->right = remove(node->right, temp->value);  // Remove the found node from the subtree
            }
        }
    }
    update(node);
    return balance(node);
}

template<typename T>
void AVLtree<T>::update(AVLNode<T>* node) {
    int left_node_height = (node->left == nullptr) ? -1 : node->left->height;
    int right_node_height = (node->right == nullptr) ? -1 : node->right->height;

    node->height = std::max(left_node_height, right_node_height) + 1;

    node->bf = right_node_height - left_node_height;
}

template<typename T>
auto AVLtree<T>::balance(AVLNode<T>* node) {
    // Left subtree is too heavy
    if (node->bf == -2) {
        if (node->left->bf <= 0) {
            return leftLeftCase(node);
        }
        else {
            return leftRightCase(node);
        }
    }
    // Right subtree is too heavy
    else if (node->bf == 2) {
        if (node->right->bf >= 0) {
            return rightRightCase(node);
        }
        else {
            return rightLeftCase(node);
        }
    }
    return node;
}

template<typename T>
auto AVLtree<T>::leftLeftCase(AVLNode<T>* node) {
    return rightRotation(node);
}

template<typename T>
auto AVLtree<T>::leftRightCase(AVLNode<T>* node) {
    node->left = leftRotation(node->left);
    return leftLeftCase(node);
}

template<typename T>
auto AVLtree<T>::rightLeftCase(AVLNode<T>* node) {
    node->right = rightRotation(node->right);
    return rightRightCase(node);
}

template<typename T>
auto AVLtree<T>::rightRightCase(AVLNode<T>* node) {
    return leftRotation(node);
}

template<typename T>
auto AVLtree<T>::leftRotation(AVLNode<T>* node) {
    AVLNode<T>* new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template<typename T>
auto AVLtree<T>::rightRotation(AVLNode<T>* node) {
    AVLNode<T>* new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template<typename T>
AVLNode<T>* AVLtree<T>::findMin(AVLNode<T>* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename T>
AVLNode<T>* AVLtree<T>::findMax(AVLNode<T>* node) const {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template<typename T>
void AVLtree<T>::displayBinaryTree(AVLNode<T>* root, std::string indent, bool last) {
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
