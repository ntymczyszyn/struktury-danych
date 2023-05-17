//
// Created by Magda on 22.04.2023.
//

#include "../include/SkipList.h"
using namespace std;

// NODE IMPLEMENTATION

template< class T >
Node<T>::Node(Key key){
    k=key;
}

template< class T >
Node<T>::Node(){

}

template< class T >
Node<T>::~Node(){

}

template< class T >
int Node<T>::compare_keys(unique_ptr<Node<T>>& node2){
    return k.compare_key(node2->k);
}

template< class T >
unique_ptr<Node<T>> Node<T>::find(unique_ptr<Node<T>>& found){
    if(found->compare_keys(right) >= 0)
        return right->find(found);
    else if(down != nullptr)
        return down->find(found);
    return this;
}

template< class T >
void Node<T>::insert_node(unique_ptr<Node<T>> &node2, unique_ptr<Node<T>> &lower, int insert_height, int distance){
     if(height <= insert_height){
         node2->left = this;
         node2->right = right;
         node2->down = lower;
         right->left = node2;
         right = node2;
         if(lower != nullptr)
             lower->up = node2;
         node2->height = height;
         node2->left_distance = distance;
         node2->right->left_distance -= node2->left_distance -1;
         unique_ptr<Node<T>> temp = this;
         while(temp->up == nullptr){
             distance += temp->left_distance;
             temp = temp->left;
         }
         temp = temp->up;
         temp->insert_node(new Node<T>(node2->k), node2, insert_height, distance);
     }
     else{
         unique_ptr<Node<T>> temp = this;
         temp->right->left_distance++;
         while(temp->left != nullptr || temp->up != nullptr) {
             while (temp->up == nullptr) {
                 temp = temp->left;
             }
             temp = temp->up;
             temp->right->left_distance++;
         }
     }
}

template< class T >
void Node<T>::remove_node(std::unique_ptr<Node<T>> &node2){
    unique_ptr<Node<T>> temp = this;
    if(temp->compare_keys(node2) != 0){
        return;
    }
    while(temp->up != nullptr){
        temp->left->right = temp->right;
        temp->right->left = temp->left;
        temp->right->left_distance += temp->left_distance - 1;
        temp = temp->up;
    }
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    temp->right->left_distance += temp->left_distance - 1;
    while(temp->left != nullptr || temp->up != nullptr){
        while(temp->up == nullptr) {
            temp = temp->left;
        }
        temp = temp->up;
        temp->right->left_distance--;
    }
}


// SKIP LIST IMPLEMENTATION

template< class T >
SkipList<T>::SkipList(int height_, Key min_key, Key max_key, int h) {
    height = height_;
    head = new Node<T>(min_key);
    tail = new Node<T>(max_key);
    unique_ptr<Node<T>> temp_left = head;
    unique_ptr<Node<T>> temp_right = tail;

    for(int i = 0; i <= h; i++){
        temp_left->right = temp_right;
        temp_right->left = temp_left;
        temp_left->down = new Node<T>(temp_left->k);
        temp_left->down->up =temp_left;
        temp_right->down = new Node<T>(temp_right->k);
        temp_right->down->up =temp_left;
        temp_left->left_distance = 0;
        temp_right->left_distance = 1;
        temp_left->height = height - i;
        temp_right->height = height - i;
        temp_left = temp_left->down;
        temp_right = temp_right->down;
    }
    temp_left->up->down = nullptr;
    temp_right->up->down = nullptr;
}


template< class T >
SkipList<T>::~SkipList(){

}

template< class T >
void SkipList<T>::insert_element(std::unique_ptr<Node<T>>& node2){
    int r = rand();
    if(r < 0)
        r *= -1;
    r %= (1 << (height -1));
    int node_height = __builtin_clz(r) - (32 - (height - 1));
    head->find(node2)->insert_node(node2, nullptr, node_height, 1);
}

template< class T >
void SkipList<T>::remove_element(std::unique_ptr<Node<T>>& node2){
    head->find(node2)->remove_node(node2);
}

template< class T >
int SkipList<T>::get_element_rank(std::unique_ptr<Node<T>>& node2){
    unique_ptr<Node<T>> temp = head->find(node2);
    if(temp->compare_keys(node2) != 0) {
        return -1;
    }
    int distance_sum = 0;
    while(temp->left != nullptr){
        while(temp->up != nullptr){
            temp = temp->up;
        }
        distance_sum += temp->left_distance;
        temp = temp->left;
    }
    return distance_sum;
}