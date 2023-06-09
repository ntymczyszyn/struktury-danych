#include "../include/AVLNode.h"

template< class T >
AVLNode<T>::AVLNode(const T& value_): value(value_), left(nullptr), right(nullptr), height(0), bf(0){};

template< class T >
AVLNode<T>::~AVLNode(){
};

template< class T >
T AVLNode<T>::compareTo(const T& value_to_comp) {
    if (this->value == value_to_comp) {
        return 0;  // Values are equal
    }
    else if (this->value < value_to_comp) {
        return -1; // this->value is less than value_to_comp
    }
    else {
        return 1;  // this->value is greater than value_to_comp
    }

}
