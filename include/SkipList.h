//
// Created by Magda on 22.04.2023.
//

#ifndef STRUKTURY_DANYCH_SKIPLIST_H
#define STRUKTURY_DANYCH_SKIPLIST_H

#include <memory>
#include <iostream>
#include "Node_S.h"
#include "../src/Node_S.cpp"
// to nadal nie jest do końca dobrze, ale idzie w dobrym kierunku


template< class T >
class SkipList {
public:
    explicit SkipList(const T& value);
    SkipList();
    ~SkipList();

    void insert_element(const T& value);
    void remove_element(const T& value);
    int get_element_rank(const T& value);

    void show_list() const;

private:
    Node_S<T>* head;
    int height;
};


#endif //STRUKTURY_DANYCH_SKIPLIST_H
