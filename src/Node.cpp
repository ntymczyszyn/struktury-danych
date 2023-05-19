//
// Created by Natalia on 18.05.2023.
//

#include "../include/Node.h"

template< class T >
T Node<T>::compareTo(const T& value_to_comp) {
    return this->value - value_to_comp; // do poprawy dla wartości ujemnych
}

template< class T >
Node<T>* Node<T>::get_left() const {
    return this->left;
}

template< class T >
Node<T>* Node<T>::get_right() const {
    return this->right;
}

// nie wiem co tutaj chciałaś zrobić i sie trochę pogubiłam z getterami w AVL -- Magda
// chce zrobic jakies graficznie wyswietlanie tego drzewa -- Natalia
template< class T >
T Node<T>::get_value() const {
    return this->value;
}
