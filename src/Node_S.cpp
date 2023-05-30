//
// Created by Natalia on 18.05.2023.
//

#include "../include/Node_S.h"


// NODE IMPLEMENTATION

template< class T >
Node_S<T>::Node_S(const T& keeey): k(keeey){
    left = nullptr;
    right = nullptr;
    up = nullptr;
    down = nullptr;
}

template< class T > //TODO usuwanie wskaznikow
Node_S<T>::~Node_S(){
    // delete node;
}

// compare values of element in the list/nodes
template< class T >
int Node_S<T>::compare_keys(Node_S<T>* node2){
    return this->k - node2->k;
}

// Find node of specified key in List -> searching for the key value in List
template< class T >  // trzeba zrobić dodawanie na ostatnim miejscu
Node_S<T>* Node_S<T>::find(Node_S<T>* found){
    if(right!=nullptr and found->compare_keys(right) > 0 ) {
        // tylko > ponieważ do usuwania chcemy mieć element przed
        return right->find(found);
    }
    else if(down != nullptr) {
        return down->find(found);
    }
    return this;
}

// Update distance between nodes
template<class T>
void Node_S<T>::update_distance(Node_S<T>* temp, Node_S<T>* node2, int insert_height) {
    while(temp != nullptr){
        if(temp->right == node2){
            node2->left_distance = 1;
        }
        else{
            if (temp->right != nullptr) {
                //temp->right->left_distance++;
                std::cout << "\n odleglosc 1: " << temp->right->left_distance << std::endl;
            }
        }
        if(temp->up == nullptr and temp->left != nullptr)
            temp = temp->left;

        temp = temp->up;
    }
//    Node_S<T> *temp = this;
//    while (temp->up != nullptr) {
//        if(temp->left != nullptr and temp->left->up != nullptr){
//            temp = temp->left;
//
//            if(temp->left != nullptr)
//                std::cout << "Element: " << temp->k<<" do "<<temp->left->k << "   odleglosc: " << temp->left_distance << std::endl;
//            else
//                std::cout << "Element: " << temp->k<< "   odleglosc: " << temp->left_distance << std::endl;
//
//                std::cout << "t - height: " << temp->height<< "   i_h: " << insert_height << std::endl;
//            // czy tylko > ?
//            if (temp->height >= insert_height ){ //and node2->height == insert_height - 1) {
//                if (temp->right != nullptr) {
//                    temp->right->left_distance++;
//                    std::cout << "\nodleglosc 1: " << temp->right->left_distance << std::endl;
//                }
//                while (temp->left != nullptr) {
//                    while (temp->up == nullptr) {
//                        temp = temp->left;
//                    }
//                    temp = temp->up;
//                    if (temp->right != nullptr) {
//                        temp->right->left_distance++;
//                        std::cout << "\n odleglosc 2: " << temp->right->left_distance << std::endl;
//                    }
//                }
//
//            }
//        }
//        temp = temp->up;
//
//    }
    return;
}

// Insert Node
template< class T >
void Node_S<T>::insert_node(Node_S<T>* node2, Node_S<T>* lower, int insert_height, int distance){
    if (height < insert_height) {
        node2->left = this;
        node2->right = this->right;
        node2->down = lower;
        if(right != nullptr) {
            right->left = node2;
        }
        right = node2;
        if (lower != nullptr)
            lower->up = node2;
        node2->height = height;
        node2->left_distance = distance;
        if(node2->right != nullptr) {
            node2->right->left_distance -= node2->left_distance - 1;
        }
        Node_S<T>* temp = this;
        while (temp->up == nullptr and temp->left != nullptr) {
            distance += temp->left_distance;
            temp = temp->left;
        }
        if(temp->up != nullptr) {
            temp = temp->up;
            temp->insert_node(new Node_S<T> (node2->k), node2, insert_height, distance);
        }

        //delete temp;
    }
//    else {
//        Node_S<T>* temp = this;
//        if(temp->right != nullptr) {
//            temp->right->left_distance++;
//        }
//        // wyznaczanie odległości na każdej z wysokości od kolejnych elementów
//        while (temp->left != nullptr and temp->up != nullptr ) {
//            while (temp->up == nullptr) {
//                temp = temp->left;
//            }
//            temp = temp->up;
//            if(temp->right != nullptr) {
//                temp->right->left_distance++;
//            }
//        }
//     }

        //tworzenie fukncji zamiast elsa zeby wchodziło gdy wysokosc jest za duzoo
        //delete temp; //można tak?

}

// Remove Node
template< class T >
void Node_S<T>::remove_node(Node_S<T>* node2){
    Node_S<T>* temp = this;
    while (temp->up != nullptr) {
        temp->left->right = temp->right;
        temp->right->left = temp->left;
        temp->right->left_distance += temp->left_distance - 1;
        temp = temp->up;
    }
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    temp->right->left_distance += temp->left_distance - 1;
    while (temp->left != nullptr or temp->up != nullptr) {
        while (temp->up == nullptr and temp->left != nullptr) {
            temp = temp->left;
        }
        if(temp->right != nullptr)
            temp->right->left_distance--;
        //możliwe że najpierw bedzie trzeba dac up a potem zmieniac right, ale to jeszcze do sprawdzenia
        temp = temp->up;

        std::cout<<"remove  0\n";
    }

    std::cout<<"remove  1\n";
    delete node2; //chyba tak bedzie giit
    std::cout<<"remove  2\n";
    delete temp; //giit??
}
