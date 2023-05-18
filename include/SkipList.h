//
// Created by Magda on 22.04.2023.
//

#ifndef STRUKTURY_DANYCH_SKIPLIST_H
#define STRUKTURY_DANYCH_SKIPLIST_H

#include <memory>
#include <random>
#include <iostream>

// to nadal nie jest do końca dobrze, ale idzie w dobrym kierunku



template< class T >
class Node_S{
public:
    explicit Node_S(const T& key);
    Node_S();
    ~Node_S();

    std::unique_ptr<Node_S<T>> left;
    std::unique_ptr<Node_S<T>> right;
    std::unique_ptr<Node_S<T>> up;
    std::unique_ptr<Node_S<T>> down;

    int height = 0;
    int left_distance = 0;
    T k;

    int compare_keys(std::unique_ptr<Node_S<T>>& node2);
    std::unique_ptr<Node_S<T>> find(std::unique_ptr<Node_S<T>>& f);

    void insert_node(std::unique_ptr <Node_S<T>>& node2, std::unique_ptr <Node_S<T>>& lower, int insert_height, int distance);
    void remove_node(std::unique_ptr<Node_S<T>>& node2);

};

template< class T >
class SkipList {
public:
    explicit SkipList(const T& value);
    SkipList(int height, const T& min_key, const T& max_key, int h);
    ~SkipList();

    void insert_element(const T& value);
    void remove_element(const T& value);
    int get_element_rank(const T& value);

    void show_list() const;

private:
    std::unique_ptr<Node_S<T>> head;
    std::unique_ptr<Node_S<T>> tail;
    std::random_device rd;
    std::mt19937 rand;
    int height;
};


#endif //STRUKTURY_DANYCH_SKIPLIST_H
