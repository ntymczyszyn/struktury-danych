//
// Created by Magda on 22.04.2023.
//

#ifndef STRUKTURY_DANYCH_SKIPLIST_H
#define STRUKTURY_DANYCH_SKIPLIST_H

#include <memory>
#include <random>

class Key{
public:
    int key;
    Key(int k) : key(k) {};
    int compare_key(Key key2){
        return key - key2.key;
    }
};

template< class T >
class Node{
public:
    Node(Key key);
    Node();
    ~Node();
    std::unique_ptr<Node<T>>& left;
    std::unique_ptr<Node<T>>& right;
    std::unique_ptr<Node<T>>& up;
    std::unique_ptr<Node<T>>& down;


    int height;
    int left_distance;
    Key k;

    int compare_keys(std::unique_ptr<Node<T>>& node2);
    std::unique_ptr<Node<T>> find(std::unique_ptr<Node<T>>& f);
    void insert_node( std::unique_ptr <Node<T>> &node2, std::unique_ptr <Node<T>> &lower, int insert_height, int distance);
    void remove_node(std::unique_ptr<Node<T>>& node2);

};

template< class T >
class SkipList {
public:
    SkipList();
    SkipList(int height, Key min_key, Key max_key, int h);
    ~SkipList();
    void insert_element(std::unique_ptr<Node<T>>& node2);
    void remove_element(std::unique_ptr<Node<T>>& node2);
    int get_element_rank(std::unique_ptr<Node<T>>& node2);

private:
    std::unique_ptr<Node<T>>& head;
    std::unique_ptr<Node<T>>& tail;
    std::random_device rd;
    std::mt19937 rand;
    int height;
};


#endif //STRUKTURY_DANYCH_SKIPLIST_H
