#include "include/SkipList.h"
#include "include/AVLtree.h"

int main(){
    Key min_key(2);
    Key max_key(3);
    Key keey(6);
    std::unique_ptr<Node_S<int>> node = std::make_unique<Node_S<int>>(keey);
    SkipList<int>A(2, min_key, max_key, 2);

    A.insert_element(node);

    return 0;
}


