//
// Created by Natalia on 18.05.2023.
//

#include "../include/Node.h"

template< class T >
Node<T>::Node(const T& value_): value(value_), left(nullptr), right(nullptr){};

template< class T >
Node<T>::~Node(){
};

template< class T >
T Node<T>::compareTo(const T& value_to_comp) {  // nie wyszukuje poprawnie duplikatow wartosci ujemych
    if (this->value == value_to_comp) {
        return this->value - value_to_comp;
    }
    else if (this->value < 0) {
        return (-this->value) - value_to_comp;
    }
    else {
        return this->value - value_to_comp;
    }
}

