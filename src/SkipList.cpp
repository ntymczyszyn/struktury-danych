//
// Created by Magda on 22.04.2023.
//

#include "../include/SkipList.h"
using namespace std;


// SKIP LIST IMPLEMENTATION
template<class T>
SkipList<T>::SkipList() {

}

template< class T >//bez tail bo nie potrzebne tylko problemy powstaja
SkipList<T>::SkipList(int height_): height(height_){
    head = new Node_S<T>();
    Node_S<T>* temp_left{head};
    for( int i = 0; i < height ; i++) {
        auto tmp = new Node_S<T>();
        temp_left->down = tmp;
        temp_left->down->up = temp_left;
        temp_left->left_distance = 0;
        temp_left->height = height - i - 1;
        temp_left = temp_left->down;
    }
    temp_left->up->down = nullptr;
}


template< class T >
SkipList<T>::~SkipList()= default;  //TODO usuwanie wskaznikow

template< class T >
void SkipList<T>::insert_element(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    // node_height -> random values
    std::uniform_int_distribution<int> dis(1, height);
    int node_height = dis(rand);
    //std::cout << "EL: "<<value<<"\tpoziom: " << node_height << std::endl << std::endl;
    Node_S<T>* tmp = head;
    while(tmp->down != nullptr){
        tmp = tmp->down;
    }
    if( tmp->right == nullptr) {
        tmp->insert_node(node2, nullptr, node_height, 1);
    }
    else {
        head->find(node2)->insert_node(node2, nullptr, node_height, 1);
    }
    tmp->update_distance(head->find(node2), node2);
}


template< class T >
void SkipList<T>::remove_element(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    if (head->find(node2)->right != nullptr) {
        head->find(node2)->right->remove_node();
    } else {
        std::cout << "Element not found";
    }
}


// generate position of node in list based on the distance between nodes -> amount of keys with less value
template< class T >
int SkipList<T>::get_element_rank(const T& value){
    Node_S<T>* node2 = new Node_S<T> (value);
    Node_S<T>* temp = head->find(node2);
    if (temp->right == nullptr or temp->right->k != value) {
        return -1;
    }
    int distance_sum = 1;
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
void SkipList<T>::show_list(){
    std::cout<<std::endl<<"SKIP LIST:\n";
    auto node1 = head;
    auto node2 = node1;
    int length = 0;
    int length2 = 0;
    while (node1->down != nullptr) {
        node2 = node1;
        std::cout<<"HEAD  ";
        while (node2->right != nullptr) {
//            length = node2->left_distance;
//            for(int i = 0; i <= length ; i++)
//                std::cout<<"--";
            std::cout<<"-->  ";
            std::cout << node2->right->k <<"  ";
            node2 = node2->right;
        }
        std::cout<<std::endl;
        node1 = node1->down;
    }
    node2 = node1;
    std::cout<<"HEAD  ";
    while (node2->right != nullptr) {
        std::cout<<"-->  ";
        std::cout << node2->right->k <<"  ";
        node2 = node2->right;
    }
    std::cout << std::endl;
}