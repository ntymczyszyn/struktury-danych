#ifndef STRUKTURY_DANYCH_SNODE_H
#define STRUKTURY_DANYCH_SNODE_H

template< class T >
class SNode {
public:
    SNode();
    SNode(const T&key_);
    ~SNode();

    SNode<T>* left;
    SNode<T>* right;
    SNode<T>* up;
    SNode<T>* down;

    int height;
    int left_distance;
    T value;

    int compare_keys(SNode<T>* node2);
};



#endif//STRUKTURY_DANYCH_SNODE_H
