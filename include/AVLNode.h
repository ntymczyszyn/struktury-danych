#ifndef STRUKTURY_DANYCH_AVLNODE_H
#define STRUKTURY_DANYCH_AVLNODE_H

template <typename T>
class AVLNode {
public:
    AVLNode(const T& value_);
    ~AVLNode();
    AVLNode<T>* left;
    AVLNode<T>* right;
    T value;
    int height;
    int bf; // balance factor

    T compareTo(const T& value_to_comp);
};


#endif//STRUKTURY_DANYCH_AVLNODE_H
