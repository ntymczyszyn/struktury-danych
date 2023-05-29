//
// Created by Natalia on 18.05.2023.
//

#include "../include/Node_S.h"


// NODE IMPLEMENTATION

template< class T >
Node_S<T>::Node_S(const T& keeey): k(keeey){
    left = nullptr;
    right = nullptr;
    up = nullptr;
    down = nullptr;
}

template< class T > //TODO usuwanie wskaznikow
Node_S<T>::~Node_S(){
    // delete node;
}

// compare values of element in the list/nodes
template< class T >
int Node_S<T>::compare_keys(Node_S<T>* node2){
    return this->k - node2->k;
}

// Find node of specified key in List -> searching for the key value in List
template< class T >
Node_S<T>* Node_S<T>::find(Node_S<T>* found){
    if(right!=nullptr && found->compare_keys(right) >= 0 ) {// czy tylko >
        return right->find(found);
    }
    else if(down != nullptr) {
        return down->find(found);
    }
    return this;
}

// Insert Node
template< class T >
void Node_S<T>::insert_node(Node_S<T>* node2, Node_S<T>* lower, int insert_height, int distance){
    if (height <= insert_height) {
        node2->left = this;
        node2->right = right;
        node2->down = lower;
        if(right != nullptr) {
            right->left = node2;
        }
        right = node2;
        if (lower != nullptr)
            lower->up = node2;
        node2->height = height;
        node2->left_distance = distance;
        if(node2->right != nullptr) {
            node2->right->left_distance -= node2->left_distance - 1;
        }
        Node_S<T>* temp = this;
        while (temp->up == nullptr) {
            distance += temp->left_distance;
            if(temp->left == nullptr)
                break;
            temp = temp->left;
        }
        if(temp->up != nullptr) {
            temp = temp->up;
            temp->height++;   //potrzebne??
            temp->insert_node(node2, node2->down, insert_height, distance); //może tak byc??
        }
        //delete temp;
    }
    else {
        Node_S<T>* temp = this;
        temp->right->left_distance++;
        // wyznaczanie odległości na każdej z wysokości od kolejnych elementów
        while (temp->left != nullptr or temp->up != nullptr) {
            while (temp->up == nullptr) {
                temp = temp->left;
            }
            temp = temp->up;
            temp->right->left_distance++;
        }
        //delete temp; //można tak?
    }
}

// Remove Node
template< class T >
void Node_S<T>::remove_node(Node_S<T>* node2){
    Node_S<T>* temp = this;
    while (temp->up != nullptr) {
        temp->left->right = temp->right;
        temp->right->left = temp->left;
        temp->right->left_distance += temp->left_distance - 1;
        temp = temp->up;
    }
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    temp->right->left_distance += temp->left_distance - 1;
    while (temp->left != nullptr or temp->up != nullptr) {
        while (temp->up == nullptr) {
            temp = temp->left;
        }
        temp = temp->up;
        temp->right->left_distance--;
    }
    delete node2; //chyba tak bedzie giit
}
