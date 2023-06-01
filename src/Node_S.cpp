//
// Created by Natalia on 18.05.2023.
//

#include "../include/Node_S.h"
#include <limits>

// NODE IMPLEMENTATION
template<class T>
Node_S<T>::Node_S():k(std::numeric_limits<int>::min()), left(nullptr), right(nullptr), up(nullptr), down(nullptr){
}

template< class T >
Node_S<T>::Node_S(const T& keeey): k(keeey), left(nullptr), right(nullptr), up(nullptr), down(nullptr){
}

template< class T > //TODO usuwanie wskaznikow
Node_S<T>::~Node_S(){
    // delete node;
}

// compare values of element in the list/nodes
template< class T >
int Node_S<T>::compare_keys(Node_S<T>* node2){
    if(this->k >= 0 and node2->k >= 0) {
        return this->k - node2->k;
    }
    else if(this->k < 0 and node2->k >= 0) {
        return -1;
    }
    else if(this->k >= 0 and node2->k < 0) {
        return 1;
    }
    else {
        return this->k - node2->k;
    }
}

// Find node of specified key in List -> searching for the less key value in List (element before)
template< class T >
Node_S<T>* Node_S<T>::find(Node_S<T>* found){
    if(right!=nullptr and found->compare_keys(right) > 0 ) {
        return right->find(found);
    }
    else if(down != nullptr) {
        return down->find(found);
    }
    return this;
}

// Update distance between nodes
template<class T>
void Node_S<T>::update_distance(Node_S<T>* temp, Node_S<T>* node2) {
    int v = 0;
    while(temp != nullptr){
        if(v == 0 and temp->right != nullptr and temp->right->k == node2->k){
            node2->left_distance = 1;
        }
        else{

            if (temp->right != nullptr) {
                temp->right->left_distance += 1;
            }
        }
        if(temp->up == nullptr and temp->left != nullptr) {
            temp = temp->left;
            v++;
        }
        temp = temp->up;
    }
    return;
}

// Insert Node
template< class T >
void Node_S<T>::insert_node(Node_S<T>* node2, Node_S<T>* lower, int insert_height, int distance){
    if (height < insert_height) {
        node2->left = this;
        node2->right = this->right;
        node2->down = lower;
        if(right != nullptr) {
            right->left = node2;
        }
        right = node2;
        if (lower != nullptr)
            lower->up = node2;
        node2->height = height;
        node2->left_distance = distance;
//        if(node2->right != nullptr) {
//            node2->right->left_distance -= node2->left_distance - 1;
//        }
        Node_S<T>* temp = this;
        while (temp->up == nullptr and temp->left != nullptr) {
            distance += temp->left_distance;
            temp = temp->left;
        }
        if(temp->up != nullptr) {
            temp = temp->up;
            temp->insert_node(new Node_S<T> (node2->k), node2, insert_height, distance);
        }

        //delete temp;
    }
//    else {
//        Node_S<T>* temp = this;
//        if(temp->right != nullptr) {
//            temp->right->left_distance++;
//        }
//        // wyznaczanie odległości na każdej z wysokości od kolejnych elementów
//        while (temp->left != nullptr and temp->up != nullptr ) {
//            while (temp->up == nullptr) {
//                temp = temp->left;
//            }
//            temp = temp->up;
//            if(temp->right != nullptr) {
//                temp->right->left_distance++;
//            }
//        }
//     }


}

// Remove Node
template<class T>
void Node_S<T>::remove_node() {
    //removing node
    Node_S<T>* temp = this;
    while (temp->up != nullptr) {
        if(temp->left != nullptr) {temp->left->right = temp->right; }
        if(temp->right!= nullptr) {
            temp->right->left = temp->left;
            temp->right->left_distance += temp->left_distance - 1;
        }
        temp = temp->up;
    }

    if(temp->left != nullptr) {temp->left->right = temp->right; }
    if(temp->right != nullptr) {
        temp->right->left = temp->left;
        temp->right->left_distance += temp->left_distance - 1;
    }

    //updating distance
    while (temp->left != nullptr and temp->up != nullptr) {
        while (temp->up == nullptr and temp->left != nullptr) {
            temp = temp->left;
        }
        if(temp->right != nullptr)
            temp->right->left_distance--;
        temp = temp->up;

        std::cout<<"remove  0\n";
    }

//    delete node2;
//    delete temp;
}

