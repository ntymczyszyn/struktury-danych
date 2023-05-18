//
// Created by Magda on 22.04.2023.
//

#include "../include/SkipList.h"
using namespace std;

// NODE IMPLEMENTATION

template< class T >
Node_S<T>::Node_S(const T& keeey){
    k = keeey;
}

template< class T >
Node_S<T>::Node_S()= default;

template< class T >
Node_S<T>::~Node_S()= default;

// compare values of element in the list/nodes
template< class T >
int Node_S<T>::compare_keys(unique_ptr<Node_S<T>>& node2){
    return k - node2->k;
}

// Find node of specified key in List -> searching for the key value in List
template< class T >
unique_ptr<Node_S<T>> Node_S<T>::find(unique_ptr<Node_S<T>>& found){
    if(found->compare_keys(right) >= 0)
        return right->find(found);
    else if(down != nullptr)
        return down->find(found);
    return this;
}


// Insert Node
template< class T >
void Node_S<T>::insert_node(std::unique_ptr <Node_S<T>>& node2, std::unique_ptr <Node_S<T>>& lower, int insert_height, int distance){
    if (height <= insert_height) {
        node2->left = std::move(std::unique_ptr<Node_S<T>>(this));
        node2->right = right;
        node2->down = std::move(std::unique_ptr<Node_S<T>>(lower));
        right->left = node2.get();
        right = node2.get();
        if (lower != nullptr)
            lower->up = node2.get();
        node2->height = height;
        node2->left_distance = distance;
        node2->right->left_distance -= node2->left_distance - 1;
        std::unique_ptr<Node_S<T>> temp = std::unique_ptr<Node_S<T>>(this);
        while (temp->up == nullptr) {
            distance += temp->left_distance;
            temp = temp->left;
        }
        temp = temp->up;
        temp->insert_node(std::make_unique<Node_S<T>>(node2->k), node2, insert_height, distance);
    }
    else {
        std::unique_ptr<Node_S<T>> temp = this;
        temp->right->left_distance++;
        while (temp->left != nullptr || temp->up != nullptr) {
            while (temp->up == nullptr) {
                temp = temp->left;
            }
            temp = temp->up;
            temp->right->left_distance++;
        }
    }
}

// Remove Node
template< class T >
void Node_S<T>::remove_node(std::unique_ptr<Node_S<T>>& node2){
    std::unique_ptr<Node_S<T>> temp = std::unique_ptr<Node_S<T>>(this);
    while (temp->up != nullptr) {
        temp->left->right = temp->right;
        temp->right->left = temp->left;
        temp->right->left_distance += temp->left_distance - 1;
        temp = temp->up;
    }
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    temp->right->left_distance += temp->left_distance - 1;
    while (temp->left != nullptr || temp->up != nullptr) {
        while (temp->up == nullptr) {
            temp = temp->left;
        }
        temp = temp->up;
        temp->right->left_distance--;
    }
}



// SKIP LIST IMPLEMENTATION

template< class T >
SkipList<T>::SkipList(const T& value): height(0){
    head = make_unique<Node_S<T>>(value);
    tail = make_unique<Node_S<T>>(value);
    unique_ptr<Node_S<T>> temp_left = head;
    unique_ptr<Node_S<T>> temp_right = tail;
    temp_left->right = temp_right.get();
    temp_right->left = temp_left.get();
    temp_left->down = make_unique<Node_S<T>>(value);
    temp_left->down->up = temp_left.get();
    temp_right->down = make_unique<Node_S<T>>(value);
    temp_right->down->up = temp_left.get();
    temp_left->left_distance = 0;
    temp_right->left_distance = 1;
    temp_left = move(temp_left->down);
    temp_right = move(temp_right->down);

    rand.seed(rd());
}

// key max and min tell us min and max values stored in the list
template< class T >
SkipList<T>::SkipList(int height_, const T& min_key, const T& max_key, int h) {
    height = height_;
    head = make_unique<Node_S<T>>(min_key);
    tail = make_unique<Node_S<T>>(max_key);
    unique_ptr<Node_S<T>> temp_left = move(head);
    unique_ptr<Node_S<T>> temp_right = move(tail);

    for(int i = 0; i <= h; i++){
        temp_left->right = move(temp_right);
        temp_right->left = move(temp_left);
        temp_left->down = make_unique<Node_S<T>>(temp_left->k);
        temp_left->down->up =temp_left.get();
        temp_right->down = make_unique<Node_S<T>>(temp_right->k);
        temp_right->down->up =temp_left.get();
        temp_left->left_distance = 0;
        temp_right->left_distance = 1;
        temp_left->height = height - i;
        temp_right->height = height - i;
        temp_left = move(temp_left->down);
        temp_right = move(temp_right->down);
    }
    temp_left->up->down = nullptr;
    temp_right->up->down = nullptr;
}


template< class T >
SkipList<T>::~SkipList()= default;

template< class T >
void SkipList<T>::insert_element(const T& value){
    std::unique_ptr<Node_S<T>> node2 = std::make_unique<Node_S<T>>(value);
    head->find(node2)->insert_node(node2, nullptr, height, 1);

}


template< class T >
void SkipList<T>::remove_element(const T& value){
    std::unique_ptr<Node_S<T>> node2 = std::make_unique<Node_S<T>>(value);
    head->find(node2)->remove_node(node2);
}


// generate position of node in list based on the distance between nodes -> amount of keys with less value
template< class T >
int SkipList<T>::get_element_rank(const T& value){
    std::unique_ptr<Node_S<T>> node2 = std::make_unique<Node_S<T>>(value);
    std::unique_ptr<Node_S<T>> temp = head->find(node2);
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
    auto node = head.get();
    while (node->down) {
        node = node->down.get();
    }
    node = node->right.get();
    while (node->right) {
        std::cout << node->k << " ";
        node = node->right.get();
    }
    std::cout << std::endl;
}