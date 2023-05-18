//
// Created by antalix on 20.04.23.
//

#ifndef STRUKTURY_DANYCH_AVLTREE_H
#define STRUKTURY_DANYCH_AVLTREE_H

#include <iostream>
#include <memory>


template <typename T>
class Node {
public:
    Node(const T& value_): value(value_){}; //do zrobienia Node jeszcze + compareTo <-Magda update: chyba to zrobiłam, ale warto sprawdzić XD
    ~Node();
    std::unique_ptr<T> left;
    std::unique_ptr<T> right;
    T value;
    int height = 0;
    int bf = 0; // balance factor

    // compare present value to value in node <- nie wiem czy to przypadkiem nie to samo co value hah -- Magda
    T k;
    Node(T key): k(key){};
    int compareTo(std::unique_ptr<Node<T>>& node2);

    // getters - for display
    std::unique_ptr<Node<T>> get_left() const;
    std::unique_ptr<Node<T>> get_right() const;
    T get_value() const;
};

template < typename T>
class AVLtree {
public:

    AVLtree();
    ~AVLtree();
    std::unique_ptr<Node<T>> root;
    int node_count;
    int height() const;
    int size() const;
    bool isEmpty() const;
    bool contains(const T& value);
    bool insert(const T& value);
    bool remove(const T& value);


    void show_tree(std::unique_ptr<Node<T>>& node);
private:
    friend class Node<T>;  // <-nie jestem pewna czy ma być

    bool contains(std::unique_ptr<Node<T>>& node, const T& value);
    auto insert(std::unique_ptr<Node<T>>& node, const T& value);
    auto remove(std::unique_ptr<Node<T>>& node, const T& value);

    void update(std::unique_ptr<Node<T>>& node);
    auto balance(std::unique_ptr<Node<T>>& node);
    auto left_left_case(std::unique_ptr<Node<T>>& node);
    auto left_right_case(std::unique_ptr<Node<T>>& node);
    auto right_left_case(std::unique_ptr<Node<T>>& node);
    auto right_right_case(std::unique_ptr<Node<T>>& node);
    auto left_rotation(std::unique_ptr<Node<T>>& node);
    auto right_rotation(std::unique_ptr<Node<T>>& node);
    T find_min(std::unique_ptr<Node<T>>& node) const;
    T find_max(std::unique_ptr<Node<T>>& node) const;
};


















// TODO: add iterator class
// TODO: add printing function
// TODO: add validation function

#endif //STRUKTURY_DANYCH_AVLTREE_H
