#include "include/SkipList.h"
#include "include/AVLtree.h"
#include "src/SkipList.cpp"
#include "src/AVLtree.cpp"
#include <iostream>

// funkcje do sprawdzenia działania kodu
void skip_list(){
    constexpr int chosenHeight{5};
    SkipList<int> skip_list(chosenHeight);


    std::cout<<std::endl;

    for (int i = 0; i < 100; i++) {
        skip_list.insert_element(10 - i);
    }

    skip_list.show_list();

    //skip_list.remove_element(20);

    //skip_list.show_list();
    std::cout<<"OK"<<std::endl;

    //skip_list.remove_element(3);

    //skip_list.show_list();
    //std::cout<<std::endl;

}

void AVL_tree(){
    AVLtree<int> Tree;
    Tree.insert(5);
    Tree.insert(5);
    Tree.insert(7);
    Tree.insert(1);
    Tree.insert(6);
    Tree.insert(0);
    Tree.insert(4);
    Tree.insert(0);
//    for (int i = 0; i < 10; i++) {
//        if (5 - i != 0)
//            Tree.insert(5 - i);
//    }
    //Tree.insert(-5);
    Tree.displayBinaryTree(Tree.root, "", true);
    Tree.remove(6);
    Tree.displayBinaryTree(Tree.root, "", true);

}

int main(){

    //skip_list();
    AVL_tree();
    return 0;
}


