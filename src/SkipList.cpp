#include "../include/SkipList.h"


template<class T> //bez tail bo nie potrzebne tylko problemy powstaja
SkipList<T>::SkipList(int height_): head(new SNode<T>()), height(height_), rand(rd()), numberOfElements(0){
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
    while (head->right != nullptr){
        remove_node(head->right);
    }
    // usuwanie head
};

template<class T>
void SkipList<T>::insert_element(const T& valueToAdd){

    SNode<T>* newNode{new SNode<T> (valueToAdd)};
    if(find(head, newNode)->right != nullptr and find(head, newNode)->right->value == valueToAdd) {
        std::cout << "Value exists!\n";
    }
    else {
        numberOfElements++;
        std::uniform_int_distribution<int> dis(1, height + 1);
        int node_height{dis(rand)};

        //std::cout << "EL: "<<value<<"\tpoziom: " << node_height << std::endl << std::endl;
        SNode<T>* currentNode{head};

        while (currentNode->down != nullptr) {
            currentNode = currentNode->down;
        }

        if (currentNode->right == nullptr) { // end of the list
            insert_node(currentNode, newNode, nullptr, node_height, 1);
        } else {
            insert_node(find(currentNode, newNode), newNode, nullptr, node_height, 1);
        }
    }
}

template<class T>
void SkipList<T>::remove_element(const T& value){
    SNode<T>* node2{new SNode<T> (value)};

    // auto = find(head, node2)->right ??
    if (find(head, node2)->right != nullptr) {
        numberOfElements--;
        remove_node(find(head, node2)->right);
    }
    else {
        std::cout << "Element not found";
    }
    delete node2;
}

// generate position of node in list based on the distance between nodes -> amount of keys with less value
template<class T>
int SkipList<T>::get_element_rank(const T& value){
    SNode<T>* node2{new SNode<T> (value)};
    // czy da się inaczej?? bez tej alokacji zasobów
    SNode<T>* temp{find(head, node2)};

    if (temp->right == nullptr or temp->right->value != value) {
        delete node2;
        return -1; // when element not found
    }
    int distance_sum = 1;

    while (temp->left != nullptr) {
        while (temp->up != nullptr) {
            temp = temp->up;
        }
        distance_sum += temp->left_distance;
        temp = temp->left;
    }
    delete node2;

    return distance_sum;
}

template<class T>
void SkipList<T>::show_list(){
    std::cout<<std::endl<<"SKIP LIST:\n";
    auto node1 = head;
    auto node2 = node1;
    int length;
    while (node1->down != nullptr) {
        node2 = node1->right;
        std::cout<<"HEAD ";

        while (node2 != nullptr) {
            length = node2->left_distance;
            for (int i = 0; i < length - 1 ; i++)
                std::cout<<" -----";
            std::cout<<" --> ";
            std::cout << node2->value <<"("<<node2->left_distance<<") ";
            node2 = node2->right;
        }

        std::cout<<std::endl;
        node1 = node1->down;
    }
    node2 = node1;
    std::cout<<"HEAD ";

    while (node2->right != nullptr) {
        std::cout<<" --> ";
        std::cout << node2->right->value;
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
    //std::cout << "nodeToFind" << std::endl;
    return node;
}

template< class T >
void SkipList<T>::insert_node(SNode<T>* node, SNode<T>* nodeToAdd, SNode<T>* lower, int insert_height, int distance){
    //std::cout << "insert_node" << std::endl;
    int h = 0, k = 0;
    while(h <= height) {
        if (node->height < insert_height) {
            nodeToAdd->left = node;
            nodeToAdd->right = node->right;
            nodeToAdd->down = lower;
            if (node->right != nullptr) {
                node->right->left = nodeToAdd;
            }
            node->right = nodeToAdd;
            if (lower != nullptr)
                lower->up = nodeToAdd;

            nodeToAdd->height = node->height;
            // updating distance
            nodeToAdd->left_distance = distance;
            if (nodeToAdd->right != nullptr and nodeToAdd->right->left_distance != 1) {
                nodeToAdd->right->left_distance -= nodeToAdd->left_distance - 1;
            }
            SNode<T> *temp{node};
            while (temp->up == nullptr and temp->left != nullptr) {
                distance += temp->left_distance;
                temp = temp->left;
            }
            if (temp->up != nullptr) {
                node = temp->up;
                lower = nodeToAdd;
                nodeToAdd = new SNode<T>(lower->value);
                // czemu to jest wykomentowane??
                //insert_node(temp, new SNode<T>(nodeToAdd->value), nodeToAdd, insert_height, distance);
            }
        } else {
            if(k == 0 and lower->right != nullptr) {
                k = 1;
                update_distance(lower->right);
            }
        }
        ++h;
    }
}

template<class T>
void SkipList<T>::update_distance(SNode<T>* node) {
    SNode<T>* temp{node};

    if (temp->up == nullptr) {
        if (temp->right != nullptr) {
            update_distance(temp->right);
        }
    }
    else {
        temp = temp->up;
        temp->left_distance++;
        if(temp->up != nullptr){
            update_distance(temp);
        }else if (temp->right != nullptr) {
            update_distance(temp->right);
        }
    }
}

template<class T>
void SkipList<T>::remove_node(SNode<T>* node) {
    //removing node
    SNode<T>* temp = node;
    while (temp->up != nullptr) {
        if(temp->left != nullptr) {
            temp->left->right = temp->right;
        }
        if(temp->right!= nullptr) {
            temp->right->left = temp->left;
            temp->right->left_distance += temp->left_distance - 1;
        }
        delete temp;
        temp = temp->up;
    }

    if(temp->left != nullptr) {
        temp->left->right = temp->right;
    }
    if(temp->right != nullptr) {
        temp->right->left = temp->left;
        temp->right->left_distance += temp->left_distance - 1;
    }
    delete temp;
    //updating distance
    while (temp->left != nullptr and temp->up != nullptr) {
        while (temp->up == nullptr and temp->left != nullptr) {
            temp = temp->left;
        }
        if(temp->right != nullptr)
            temp->right->left_distance--;
        temp = temp->up;

        //std::cout<<"remove  0\n";
    }

}