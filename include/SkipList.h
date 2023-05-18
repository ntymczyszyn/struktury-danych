//
// Created by Magda on 22.04.2023.
//

#ifndef STRUKTURY_DANYCH_SKIPLIST_H
#define STRUKTURY_DANYCH_SKIPLIST_H

#include <memory>
#include <iostream>

// to nadal nie jest do końca dobrze, ale idzie w dobrym kierunku


template< class T >
class Node_S{
public:
    Node_S(const T& key);
    Node_S();
    ~Node_S();

    Node_S<T>* left;
    Node_S<T>* right;
    Node_S<T>* up;
    Node_S<T>* down;

    int height = 0;
    int left_distance = 0;
    T k; // value

    int compare_keys(Node_S<T>* node2);
    Node_S<T>* find(Node_S<T>* f);

    void insert_node(Node_S<T>* node2, Node_S<T>* lower, int insert_height, int distance);
    void remove_node(Node_S<T>* node2);

};

template< class T >
class SkipList {
public:
    explicit SkipList(const T& value);
    //SkipList(int height, const T& min_key, const T& max_key, int h);
    ~SkipList();

    void insert_element(const T& value);
    void remove_element(const T& value);
    int get_element_rank(const T& value);

    void show_list() const;

private:
    Node_S<T>* head;
    Node_S<T>* tail;
    int height;
};


#endif //STRUKTURY_DANYCH_SKIPLIST_H
