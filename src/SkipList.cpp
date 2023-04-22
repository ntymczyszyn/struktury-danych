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
int Node<T>::compare_to(unique_ptr<Node<T>> node2){
    return k.compare_to(node2->k);
}

template< class T >
unique_ptr<Node<T>> Node<T>::find(unique_ptr<Node<T>> f){
    if(f->compare_to(right) >= 0)
        return right->find(f);
    else if(down != nullptr)
        return down->find(f);
    return this;
}

template< class T >
void Node<T>::insert(unique_ptr<Node<T>> node2, unique_ptr<Node<T>> lower, int insert_height, int distance){
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
         unique_ptr<Node<T>> curr = this;
         while(curr->up == nullptr){
             distance += curr->left_distance;
             curr = curr->left;
         }
         curr = curr->up;
         curr->insert(new Node<T>(node2->k), node2, insert_height, distance);
     }
     else{
         unique_ptr<Node<T>> curr = this;
         curr->right->left_distance++;
         while( curr->left != nullptr || curr->up != nullptr) {
             while (curr->up == nullptr) {
                 curr = curr->left;
             }
             curr = curr->up;
             curr->right->left_distance++;
         }
     }
}

template< class T >
void Node<T>::remove(unique_ptr<Node<T>> node2){
    unique_ptr<Node<T>> curr = this;
    if(curr->compare_to(node2) != 0){
        return;
    }
    while(curr->up != nullptr){
        curr->left->right = curr->right;
        curr->right->left = curr->left;
        curr->right->left_distance += curr->left_distance - 1;
        curr = curr->up;
    }
    curr->left->right = curr->right;
    curr->right->left = curr->left;
    curr->right->left_distance += curr->left_distance - 1;
    while(curr->left != nullptr || curr->up != nullptr){
        while(curr->up == nullptr) {
            curr = curr->left;
        }
        curr = curr->up;
        curr->right->left_distance--;
    }
}


// SKIP LIST IMPLEMENTATION

template< class T >
SkipList<T>::SkipList(int height_, Key min_key, Key max_key, int h) {
    height = height_;
    head = new Node<T>(min_key);
    tail = new Node<T>(max_key);
    unique_ptr<Node<T>> curr_left = head;
    unique_ptr<Node<T>> curr_right = tail;

    for(int i = 0; i <= h; i++){
        curr_left->right = curr_right;
        curr_right->left = curr_left;
        curr_left->down = new Node<T>(curr_left->k);
        curr_left->down->up =curr_left;
        curr_right->down = new Node<T>(curr_right->k);
        curr_right->down->up =curr_left;
        curr_left->left_distance = 0;
        curr_right->left_distance = 1;
        curr_left->height = height - i;
        curr_right->height = height - i;
        curr_left = curr_left->down;
        curr_right = curr_right->down;
    }
    curr_left->up->down = nullptr;
    curr_right->up->down = nullptr;
}


template< class T >
SkipList<T>::~SkipList(){

}

template< class T >
void SkipList<T>::insert(std::unique_ptr<Node<T>> node2){
    int r = rand();
    if(r < 0)
        r *= -1;
    r %= (1 << (height -1));
    int node_height = __builtin_clz(r) - (32 - (height - 1));
    head->find(node2)->insert(node2, nullptr, node_height, 1);
}

template< class T >
void SkipList<T>::remove(std::unique_ptr<Node<T>> node2){
    head->find(node2)->remove(node2)
}

template< class T >
int SkipList<T>::get_rank(std::unique_ptr<Node<T>> node2){
    unique_ptr<Node<T>> curr = head->find(node2);
    if(curr->compare_to(node2) != 0) {
        return -1;
    }
    int distance_sum = 0;
    while(curr->left != nullptr){
        while(curr->up != nullptr){
            curr = curr->up;
        }
        distance_sum += curr->left_distance;
        curr = curr->left;
    }
    return distance_sum;
}