#include "../include/SkipList.h"

template<class T>
SkipList<T>::SkipList(): rand(rd()){ // czy my wgl z tego korzystamy????
}

template<class T> //bez tail bo nie potrzebne tylko problemy powstaja
SkipList<T>::SkipList(int height_): head(new SNode<T>()), height(height_), rand(rd()){
    head->height = height;
    SNode<T>* temp_left{head};

    for (int i{1}; i <= height ; i++) {
        auto newLevel = new SNode<T>();
        newLevel->height = height - i;
        newLevel->up = temp_left;

        temp_left->down = newLevel;
        temp_left = newLevel;
    }
}

template<class T>
SkipList<T>::~SkipList(){

};

template<class T>
void SkipList<T>::insert_element(const T& valueToAdd){

    // checking if exists !!!!!

    SNode<T>* newNode{new SNode<T> (valueToAdd)};

    std::uniform_int_distribution<int> dis(1, height+1);
    int node_height{dis(rand)};

    //std::cout << "EL: "<<value<<"\tpoziom: " << node_height << std::endl << std::endl;
    SNode<T>* currentNode{head};

    while (currentNode->down != nullptr) {
        currentNode = currentNode->down;
    }

    if (currentNode->right == nullptr) { // end of the list
        insert_node(currentNode, newNode, nullptr, node_height, 1);
    }
    else {
        insert_node(find(currentNode, newNode), newNode, nullptr, node_height, 1);
    }

}

template<class T>
void SkipList<T>::remove_element(const T& value){
    SNode<T>* node2{new SNode<T> (value)};

    if (find(head, node2)->right != nullptr) {
        remove_node(find(head, node2)->right);
    }
    else {
        std::cout << "Element not found";
    }
}

// generate position of node in list based on the distance between nodes -> amount of keys with less value
template<class T>
int SkipList<T>::get_element_rank(const T& value){
    SNode<T>* node2{new SNode<T> (value)};
    SNode<T>* temp{find(head, node2)};

    if (temp->right == nullptr or temp->right->value != value) {
        return -1;
    }
    int distance_sum = 1;

    while (temp->left != nullptr) {
        while (temp->up != nullptr) {
            temp = temp->up;
        }

        distance_sum += temp->left_distance;
        temp = temp->left;
    }

    return distance_sum;
}

template<class T>
void SkipList<T>::show_list(){
    std::cout<<std::endl<<"SKIP LIST:\n";
    auto node1 = head;
    auto node2 = node1;
    int length = 0;
    int length2 = 0;
    while (node1->down != nullptr) {
        node2 = node1->right;
        std::cout<<"HEAD ";

        while (node2 != nullptr) {
            length = node2->left_distance;
            for (int i = 0; i < length - 1 ; i++)
                std::cout<<"-- ";
            std::cout<<"-->  ";
            std::cout << node2->value <<"("<<node2->left_distance<<") ";
            node2 = node2->right;
        }
        std::cout<<std::endl;
        node1 = node1->down;
    }
    node2 = node1;
    std::cout<<"HEAD ";

    while (node2->right != nullptr) {
        std::cout<<"-->  ";
        std::cout << node2->right->value <<"  ";
        node2 = node2->right;
    }
    std::cout << std::endl;
}

template< class T >
SNode<T>* SkipList<T>::find(SNode<T>* node, SNode<T>* nodeToFind){
    if (node->right != nullptr and nodeToFind->compare_keys(node->right) > 0 ) {
        return find(node->right, nodeToFind);
    }
    else if (node->down != nullptr) {
        return find(node->down, nodeToFind);
    }
    std::cout << "nodeToFind" << std::endl;
    return node;
}

template< class T >
void SkipList<T>::insert_node(SNode<T>* node, SNode<T>* nodeToAdd, SNode<T>* lower, int insert_height, int distance){
    std::cout << "insert_node" << std::endl;
    if (node->height < insert_height) {
        nodeToAdd->left = node;
        nodeToAdd->right = node->right;
        nodeToAdd->down = lower;
        if(node->right != nullptr) {
            node->right->left = nodeToAdd;
        }
        node->right = nodeToAdd;
        if (lower != nullptr)
            lower->up = nodeToAdd;

        nodeToAdd->height = node->height;
// updating distance
        nodeToAdd->left_distance = distance;
        if(nodeToAdd->right != nullptr and nodeToAdd->right->left_distance != 1) {
            nodeToAdd->right->left_distance -= nodeToAdd->left_distance - 1;
        }
        SNode<T>* temp{node};
        while (temp->up == nullptr and temp->left != nullptr) {
            distance += temp->left_distance;
            temp = temp->left;
        }
        if (temp->up != nullptr) {
            temp = temp->up;
            insert_node(temp, new SNode<T> (nodeToAdd->value), nodeToAdd, insert_height, distance);
        }
    }
    else {
        update_distance(nodeToAdd->right);
    }

}
template<class T>
void SkipList<T>::update_distance(SNode<T>* node) {
    SNode<T>* temp{node};
    if (temp == nullptr)
        return;

    if (temp->up == nullptr)
        update_distance(temp->right);
    else {
        temp = temp->up;
        temp->left_distance++;
        update_distance(temp->right);
    }
}

template<class T>
void SkipList<T>::remove_node(SNode<T>* node) {
    //removing node
    SNode<T>* temp = node;
    while (temp->up != nullptr) {
        if(temp->left != nullptr) {temp->left->right = temp->right; }
        if(temp->right!= nullptr) {
            temp->right->left = temp->left;
            temp->right->left_distance += temp->left_distance - 1;
        }
        temp = temp->up;
    }

    if(temp->left != nullptr) {temp->left->right = temp->right; }
    if(temp->right != nullptr) {
        temp->right->left = temp->left;
        temp->right->left_distance += temp->left_distance - 1;
    }

    //updating distance
    while (temp->left != nullptr and temp->up != nullptr) {
        while (temp->up == nullptr and temp->left != nullptr) {
            temp = temp->left;
        }
        if(temp->right != nullptr)
            temp->right->left_distance--;
        temp = temp->up;

        std::cout<<"remove  0\n";
    }

    //    delete node2;
    //    delete temp;
}