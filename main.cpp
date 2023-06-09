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

    for (int i = 0; i <= 10; i +=2) {
        skip_list.insert_element( i);
    }
    for (int i = 1; i < 10; i+=2) {
        skip_list.insert_element( i);
    }
    skip_list.show_list();
    std::cout<<"\n Rank 1:  "<<skip_list.get_element_rank(1)<<std::endl;
    std::cout<<"\n Rank 4: "<<skip_list.get_element_rank(4)<<std::endl;
    std::cout<<"\n Rank 14: "<<skip_list.get_element_rank(14)<<std::endl;
    std::cout<<"\n Rank 19: "<<skip_list.get_element_rank(19)<<std::endl;


    //skip_list.remove_element(20);

    //skip_list.show_list();
    //std::cout<<"OK"<<std::endl;

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

    skip_list();
    //AVL_tree();
    return 0;
}


