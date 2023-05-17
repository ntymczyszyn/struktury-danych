//
// Created by Magda on 22.04.2023.
//

#ifndef STRUKTURY_DANYCH_SKIPLIST_H
#define STRUKTURY_DANYCH_SKIPLIST_H

#include <memory>
#include <random>
// compare values of element in the list/nodes

class Key{
public:
    int key;
    explicit Key(int k) : key(k) {};
    int compare_key(Key key2) const{
        return key - key2.key;
    }
};

template< class T >
class Node_S{
public:
    explicit Node_S(Key key);
    Node_S();
    ~Node_S();
    std::unique_ptr<Node_S<T>> left;
    std::unique_ptr<Node_S<T>> right;
    std::unique_ptr<Node_S<T>> up;
    std::unique_ptr<Node_S<T>> down;


    int height = 0;
    int left_distance = 0;
    Key k;

    int compare_keys(std::unique_ptr<Node_S<T>>& node2);
    std::unique_ptr<Node_S<T>> find(std::unique_ptr<Node_S<T>>& f);
    void insert_node(std::unique_ptr <Node_S<T>> &node2, std::unique_ptr <Node_S<T>> &lower, int insert_height, int distance);
    void remove_node(std::unique_ptr<Node_S<T>>& node2);

};

template< class T >
class SkipList {
public:
    SkipList();
    SkipList(int height, Key min_key, Key max_key, int h);
    ~SkipList();
    void insert_element(std::unique_ptr<Node_S<T>>& node2);
    void remove_element(std::unique_ptr<Node_S<T>>& node2);
    int get_element_rank(std::unique_ptr<Node_S<T>>& node2);

private:
    std::unique_ptr<Node_S<T>> head;
    std::unique_ptr<Node_S<T>> tail;
    std::random_device rd;
    std::mt19937 rand;
    int height;
};


#endif //STRUKTURY_DANYCH_SKIPLIST_H
