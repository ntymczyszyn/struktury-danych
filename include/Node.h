//
// Created by Natalia on 18.05.2023.
//

#ifndef STRUKTURY_DANYCH_NODE_H
#define STRUKTURY_DANYCH_NODE_H

template <typename T>
class Node{
public:
    Node(const T& value_): value(value_), left(nullptr), right(nullptr){}; //do zrobienia Node jeszcze + compareTo <-Magda update: chyba to zrobiłam, ale warto sprawdzić XD
    ~Node();
    Node<T>* left;
    Node<T>* right;
    T value;
    int height = 0;
    int bf = 0; // balance factor

    // compare present value to value in node <- nie wiem czy to przypadkiem nie to samo co value hah -- Magda
    T compareTo(const T& value_to_comp);

    // getters - for display
    Node<T>* get_left() const;
    Node<T>* get_right() const;
    T get_value() const;
};


#endif//STRUKTURY_DANYCH_NODE_H
