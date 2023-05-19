//
// Created by Magda on 22.04.2023.
//

#include "../include/SkipList.h"
using namespace std;



// SKIP LIST IMPLEMENTATION

template< class T >
SkipList<T>::SkipList(const T& value): height(0){
    head = new Node_S<T> (value);
    tail = new Node_S<T> (value);
    Node_S<T>* temp_left = head;
    Node_S<T>* temp_right = tail;
    temp_left->right = temp_right;
    temp_right->left = temp_left;
    temp_left->down = new Node_S<T> (value);
    temp_left->down->up = temp_left;
    temp_right->down = new Node_S<T> (value);
    temp_right->down->up = temp_left;
    temp_left->left_distance = 0;
    temp_right->left_distance = 1;
    temp_left = temp_left->down;
    temp_right = temp_right->down;

}

template< class T >
SkipList<T>::SkipList(): height(0), head(nullptr), tail(nullptr){

}


template< class T >
SkipList<T>::~SkipList()= default;  //TODO usuwanie wskaznikow

template< class T >
void SkipList<T>::insert_element(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    head->find(node2)->insert_node(node2, nullptr, height, 1);

}


template< class T >
void SkipList<T>::remove_element(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    head->find(node2)->remove_node(node2);
}


// generate position of node in list based on the distance between nodes -> amount of keys with less value
template< class T >
int SkipList<T>::get_element_rank(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    Node_S<T>* temp = head->find(node2);
    if (temp->compare_keys(node2) != 0) {
        return -1;
    }
    int distance_sum = 0;
    while (temp->left != nullptr) {
        while (temp->up != nullptr) {
            temp = temp->up;
        }
        distance_sum += temp->left_distance;
        temp = temp->left;
    }
    return distance_sum;

}

template<class T>
void SkipList<T>::show_list() const {
    auto node = head;
    while (node->down) {
        node = node->down;
    }
    node = node->right;
    while (node->right) {
        std::cout << node->k << " ";
        node = node->right;
    }
    std::cout << std::endl;
}