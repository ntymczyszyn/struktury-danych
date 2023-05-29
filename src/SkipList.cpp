//
// Created by Magda on 22.04.2023.
//

#include "../include/SkipList.h"
using namespace std;



// SKIP LIST IMPLEMENTATION

template< class T >//bez tail bo nie potrzebne tylko problemy powstaja
SkipList<T>::SkipList(const T& value): height(2){
    head = new Node_S<T> (value);
    //tail = new Node_S<T> (value);
    Node_S<T>* temp_left = head;
   // Node_S<T>* temp_right = tail;
    for( int i = 0; i < height ; i++) {
        //temp_left->right = temp_right;
        //temp_right->left = temp_left;
        temp_left->down = new Node_S<T>(value);
        temp_left->down->up = temp_left;
        //temp_right->down = new Node_S<T>(value);
        //temp_right->down->up = temp_left;
        temp_left->left_distance = 0;
        //tail->left_distance = 1;
        temp_left = temp_left->down;
        //temp_right = temp_right->down;
    }
    temp_left->up->down = nullptr;
    //temp_right->up->down = nullptr;
}

template< class T > // aby tworzyć listę bez elementów;
SkipList<T>::SkipList(): height(2), head(nullptr){ //}, tail(nullptr){

}


template< class T >
SkipList<T>::~SkipList()= default;  //TODO usuwanie wskaznikow

template< class T >
void SkipList<T>::insert_element(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    // height -> random values

    if(head->right == nullptr) {
        std::cout<<"pierwszy insert \n";
        head->insert_node(node2, nullptr, 2, 1);
    }
    else {
        std::cout<<"kolejny insert \n";
        head->find(node2)->insert_node(node2, nullptr, height, 1);
    }
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
    std::cout<<std::endl<<"SKIP LIST:\n";
    auto node = head;
    while (node->down != nullptr) {
        node = node->down;
    }
    //node = node->right; <- raczej nie potrzebnee
    while (node->right != nullptr) {
        std::cout << node->k << "  ";
        node = node->right;
    }
    std::cout << node->k << "  ";
    std::cout << std::endl;
}