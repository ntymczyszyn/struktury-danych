//
// Created by Magda on 22.04.2023.
//

#ifndef STRUKTURY_DANYCH_SKIPLIST_H
#define STRUKTURY_DANYCH_SKIPLIST_H

#include <memory>
#include <random>
#include <iostream>
#include "Node_S.h"
#include "../src/Node_S.cpp"
// to nadal nie jest do końca dobrze, ale idzie w dobrym kierunku


template< class T >
class SkipList {
public:
    SkipList();
    SkipList(int height_);
    ~SkipList();

    void insert_element(const T& value);
    void remove_element(const T& value);
    int get_element_rank(const T& value);

    void show_list();

private:
    Node_S<T>* head;
    int height;
    std::random_device rd;
    std::mt19937 rand{ rd() };
};



#endif //STRUKTURY_DANYCH_SKIPLIST_H
