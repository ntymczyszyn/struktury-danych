//
// Created by Natalia on 18.05.2023.
//

#ifndef STRUKTURY_DANYCH_NODE_H
#define STRUKTURY_DANYCH_NODE_H

template <typename T>
class Node{
public:
    Node(const T& value_); //do zrobienia Node jeszcze + compareTo <-Magda update: chyba to zrobiłam, ale warto sprawdzić XD
    ~Node();
    Node<T>* left;
    Node<T>* right;
    T value;
    int height = 0;
    int bf = 0; // balance factor

    T compareTo(const T& value_to_comp);

};


#endif//STRUKTURY_DANYCH_NODE_H
