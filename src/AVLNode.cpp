#include "../include/AVLNode.h"

template< class T >
AVLNode<T>::AVLNode(const T& value_): value(value_), left(nullptr), right(nullptr), height(0), bf(0){};

template< class T >
AVLNode<T>::~AVLNode(){
};

template< class T >
T AVLNode<T>::compareTo(const T& value_to_comp) {  // nie wyszukuje poprawnie duplikatow wartosci ujemych
//    if (this->value >= 0 and value_to_comp >= 0) {
//        return this->value - value_to_comp;
//    }
//    else if (this->value > 0 and value_to_comp < 0){ //this jest wieksze
//        return 1;
//    }
//    else if (this->value < 0 and value_to_comp > 0) { //value jest wieksze
//        return -1;
//    }
//    else if (this->value < 0 and value_to_comp < 0) {
//        return this->value - value_to_comp;
//    }
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
