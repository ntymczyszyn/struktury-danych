//
// Created by Natalia on 18.05.2023.
//

#include "../include/SNode.h"
#include <limits>

// NODE IMPLEMENTATION
template<class T>
SNode<T>::SNode():k(std::numeric_limits<int>::min()), left(nullptr), right(nullptr), up(nullptr), down(nullptr){
}

template< class T >
SNode<T>::SNode(const T& keeey): k(keeey), left(nullptr), right(nullptr), up(nullptr), down(nullptr){
}

template< class T > //TODO usuwanie wskaznikow
SNode<T>::~SNode(){
    // delete node;
}

// compare values of element in the list/nodes
template< class T >
int SNode<T>::compare_keys(SNode<T>* node2){
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
SNode<T>*SNode<T>::find(SNode<T>* found){
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
void SNode<T>::update_distance(SNode<T>* temp, SNode<T>* node2) {
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

// Insert AVLNode
template< class T >
void SNode<T>::insert_node(SNode<T>* node2, SNode<T>* lower, int insert_height, int distance){
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
        SNode<T>* temp = this;
        while (temp->up == nullptr and temp->left != nullptr) {
            distance += temp->left_distance;
            temp = temp->left;
        }
        if(temp->up != nullptr) {
            temp = temp->up;
            temp->insert_node(new SNode<T> (node2->k), node2, insert_height, distance);
        }

        //delete temp;
    }
//    else {
//        SNode<T>* temp = this;
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

// Remove AVLNode
template<class T>
void SNode<T>::remove_node() {
    //removing node
    SNode<T>* temp = this;
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

