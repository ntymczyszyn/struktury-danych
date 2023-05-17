#include "include/SkipList.h"
#include "include/AVLtree.h"
#include <iostream>

void skip_list(){
    // max and min value stored in variable type int
    Key min_key(INT_MIN);
    Key max_key(INT_MAX);

    Key keey(6);
    std::unique_ptr<Node_S<int>> node = std::make_unique<Node_S<int>>(keey);
    SkipList<int>A(2, min_key, max_key, 2);

    A.insert_element(node);
    std::cout << A.get_element_rank(node) << std::endl;

}
void AVL_tree(){
    AVLtree<int> Tree;
    Tree.insert(6);
    Tree.insert(2);
    Tree.show_tree(Tree.root);

}

int main(){

    skip_list();
    AVL_tree();

    return 0;
}


