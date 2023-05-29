//
// Created by Magda on 22.04.2023.
//

#include "../include/SkipList.h"
using namespace std;



// SKIP LIST IMPLEMENTATION

template< class T >//bez tail bo nie potrzebne tylko problemy powstaja
SkipList<T>::SkipList(const T& value): height(3){
    head = new Node_S<T> (value);
    Node_S<T>* temp_left = head;
    for( int i = 0; i < height ; i++) {
        auto tmp = new Node_S<T>(value);
        temp_left->down = tmp;
        temp_left->down->up = temp_left;
        temp_left->left_distance = 0;
        temp_left = temp_left->down;
    }
    temp_left->up->down = nullptr;
}

template< class T > // aby tworzyć listę bez elementów;
SkipList<T>::SkipList(): height(3), head(nullptr){ //}, tail(nullptr){

}


template< class T >
SkipList<T>::~SkipList()= default;  //TODO usuwanie wskaznikow

template< class T >
void SkipList<T>::insert_element(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    // node_height -> random values
    std::uniform_int_distribution<int> dis(1, 3);
    int node_height = dis(rand);
    std::cout << "poziom: " << node_height << std::endl;

    if( head->right == nullptr ) {
        Node_S<T>* tmp = head;
        while(tmp->down != nullptr) { tmp = tmp->down; }
        tmp->insert_node(node2, nullptr, node_height, 1);

    }
    else {
        head->find(node2)->insert_node(node2, nullptr, node_height, 1);
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
    auto node1 = head;
    auto node2 = head;
    while (node1->down != nullptr) {
        node2 = node1;
        while (node2->right != nullptr) {
            std::cout << node2->k << "   ->   ";
            node2 = node2->right;
        }
        std::cout << node2->k<<std::endl;
        node1 = node1->down;
    }
    node2 = node1;
    while (node2->right != nullptr) {
        std::cout << node2->k << "   ->   ";
        node2 = node2->right;
    }
    std::cout << node2->k<<std::endl;
    std::cout << std::endl;
}