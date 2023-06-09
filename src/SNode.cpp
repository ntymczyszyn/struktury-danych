#include "../include/SNode.h"
#include <limits>


template<class T>
SNode<T>::SNode(): value(std::numeric_limits<int>::min()), height(0), left_distance(0), left(nullptr), right(nullptr), up(nullptr), down(nullptr){
} // limit nue

template< class T >
SNode<T>::SNode(const T&key_): value(key_), height(0), left_distance(0), left(nullptr), right(nullptr), up(nullptr), down(nullptr){
}

template< class T >
SNode<T>::~SNode(){
}

// compare values of element in the list/nodes
template< class T >
int SNode<T>::compare_keys(SNode<T>* node2){
    if(this->value >= 0 and node2->value >= 0) {
        return this->value - node2->value;
    }
    else if(this->value < 0 and node2->value >= 0) {
        return -1;
    }
    else if(this->value >= 0 and node2->value < 0) {
        return 1;
    }
    else {
        return this->value - node2->value;
    }
}



