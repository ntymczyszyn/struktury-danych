#include "include/SkipList.h"
#include "include/AVLtree.h"
#include "src/SkipList.cpp"
#include "src/AVLtree.cpp"
#include <iostream>

// funkcje do sprawdzenia działania kodu
void skip_list(){
    constexpr int test{1};
    SkipList<int> skip_list(test);

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
}

void AVL_tree(){
    AVLtree<int> Tree;
    for (int i = 0; i < 10; i++) {
        if( Tree.insert(i)){
            std::cout<<"okk"<<std::endl;
        }
    }
    Tree.show_tree(Tree.root);

}

int main(){

    skip_list();
    AVL_tree();

    return 0;
}


