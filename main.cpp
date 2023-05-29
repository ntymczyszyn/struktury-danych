#include "include/SkipList.h"
#include "include/AVLtree.h"
#include "src/SkipList.cpp"
#include "src/AVLtree.cpp"
#include <iostream>

// funkcje do sprawdzenia działania kodu
void skip_list(){
    constexpr int test{1};
    SkipList<int> skip_list(test);

    //std::cout<<std::endl;
    skip_list.show_list();// nie działa :((
    std::cout<<std::endl;

    skip_list.insert_element(5);
    std::cout<<std::endl<<" okkkk 1"<<std::endl<<std::endl;

    skip_list.show_list();
    std::cout<<std::endl;

    skip_list.insert_element(10);
    std::cout<<std::endl<<" okkkk 2"<<std::endl<<std::endl;

/*
    skip_list.insert_element(5);
    skip_list.insert_element(10);
    skip_list.insert_element(3);
    skip_list.insert_element(7);
    skip_list.insert_element(1);

    std::cout << "Rank of 5: " << skip_list.get_element_rank(5) << std::endl;
    std::cout << "Rank of 10: " << skip_list.get_element_rank(10) << std::endl;
    std::cout << "Rank of 3: " << skip_list.get_element_rank(3) << std::endl;
    std::cout << "Rank of 7: " << skip_list.get_element_rank(7) << std::endl;
    std::cout << "Rank of 1: " << skip_list.get_element_rank(1) << std::endl;

    skip_list.remove_element(3);

    std::cout << "Rank of 3 after removal: " << skip_list.get_element_rank(3) << std::endl;

    skip_list.show_list();
    */
}

void AVL_tree(){
    AVLtree<int> Tree;
    Tree.insert(5);
    Tree.insert(5);
    Tree.insert(7);
    Tree.insert(1);
    Tree.insert(6);
    Tree.insert(3);

    for (int i = 0; i < 20; i++) {
        Tree.insert(5 - i);
    }
    Tree.insert(-5);
    Tree.displayBinaryTree(Tree.root, "", true);
}

int main(){

    skip_list();
    //AVL_tree();
    return 0;
}


