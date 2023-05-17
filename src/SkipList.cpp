//
// Created by Magda on 22.04.2023.
//

#include "../include/SkipList.h"
using namespace std;

// NODE IMPLEMENTATION

template< class T >
Node_S<T>::Node_S(Key keeey){
    k = keeey;
}

template< class T >
Node_S<T>::Node_S()= default;

template< class T >
Node_S<T>::~Node_S()= default;

template< class T >
int Node_S<T>::compare_keys(unique_ptr<Node_S<T>>& node2){
    return k.compare_key(node2->k);
}

template< class T >
unique_ptr<Node_S<T>> Node_S<T>::find(unique_ptr<Node_S<T>>& found){
    if(found->compare_keys(right) >= 0)
        return right->find(found);
    else if(down != nullptr)
        return down->find(found);
    return this;
}

template< class T >
void Node_S<T>::insert_node(unique_ptr<Node_S<T>> &node2, unique_ptr<Node_S<T>> &lower, int insert_height, int distance){
     if(height <= insert_height){
         node2->left = move(unique_ptr<Node_S>(this));
         node2->right = right;
         node2->down = move(unique_ptr<Node_S>(lower));
         right->left = node2;
         right = node2;
         if(lower != nullptr)
             lower->up = node2;
         node2->height = height;
         node2->left_distance = distance;
         node2->right->left_distance -= node2->left_distance - 1;
         unique_ptr<Node_S<T>> temp = unique_ptr<Node_S>(this);
         while(temp->up == nullptr){
             distance += temp->left_distance;
             temp = temp->left;
         }
         temp = temp->up;
         temp->insert_node(make_unique<Node_S<T>>(node2->k), node2, insert_height, distance);
     }
     else{
         unique_ptr<Node_S<T>> temp = this;
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
void Node_S<T>::remove_node(std::unique_ptr<Node_S<T>> &node2){
    unique_ptr<Node_S<T>> temp = unique_ptr<Node_S>(this);
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
    head = make_unique<Node_S<T>>(min_key);
    tail = make_unique<Node_S<T>>(max_key);
    unique_ptr<Node_S<T>> temp_left = head;
    unique_ptr<Node_S<T>> temp_right = tail;

    for(int i = 0; i <= h; i++){
        temp_left->right = temp_right;
        temp_right->left = temp_left;
        temp_left->down = make_unique<Node_S<T>>(temp_left->k);
        temp_left->down->up =temp_left;
        temp_right->down = make_unique<Node_S<T>>(temp_right->k);
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
SkipList<T>::~SkipList()= default;

template< class T >
void SkipList<T>::insert_element(std::unique_ptr<Node_S<T>>& node2){
    // choosing level
    int r = rand();
    if(r < 0)
        r *= -1;

    // shifting bits to the left : 1 << 2 = '0000 0100'
    r %= (1 << (height -1));

    // clz -> count leading zeros before one
    int node_height = __builtin_clz(r) - (32 - (height - 1));
    head->find(node2)->insert_node(node2, nullptr, node_height, 1);
}

template< class T >
void SkipList<T>::remove_element(std::unique_ptr<Node_S<T>>& node2){
    head->find(node2)->remove_node(node2);
}

template< class T >
int SkipList<T>::get_element_rank(std::unique_ptr<Node_S<T>>& node2){
    unique_ptr<Node_S<T>> temp = head->find(node2);
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