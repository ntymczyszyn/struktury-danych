#include "../include/SkipList.h"
#include "../include/AVLtree.h"
#include "../src/SkipList.cpp"
#include "../src/AVLtree.cpp"
#include <memory>
#include <chrono>
#include <fstream>

void AVL_test(int number, int type, std::ifstream& data);
void skipList_test(int number, int type, std::ifstream& data);

int main(){
    std::ifstream orderedData ("../tests/PN_ordered_numbers.csv");
    std::ifstream reverseOrderedData ("../tests/PN_reversed_numbers.csv");
    std::ifstream randomOrderedData ("../tests/PN_random_numbers.csv");

    std::vector<int> n {10, 100, 10000, 20000, 50000, 100000, 200000, 300000};
                       //400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    std::vector<int> test {10, 20};

    for (const auto& number : test){
//        AVL_test(number, 0, orderedData);
//        AVL_test(number, 1, reverseOrderedData);
//        AVL_test(number, 2, randomOrderedData );
        skipList_test(number, 0, orderedData);
        skipList_test(number, 1, reverseOrderedData);
        skipList_test(number, 2, randomOrderedData );
    }

    return 0;
}

void AVL_test(int number, int type, std::ifstream& data){
    std::ofstream resInOrderedAVL ("../tests/results/AVL/resultsPNOrderedIN.csv", std::ios::app);
    std::ofstream resInReverseOrderAVL("../tests/results/AVL/resultsPNReverseOrderIN.csv", std::ios::app);
    std::ofstream resInRandomOrderAVL ("../tests/results/AVL/resultsPNRandomOrderIN.csv", std::ios::app);
    std::ofstream resDelOrderedAVL ("../tests/results/AVL/resultsPNOrderedDEL.csv", std::ios::app);
    std::ofstream resDelReverseOrderAVL("../tests/results/AVL/resultsPNReverseOrderDEL.csv", std::ios::app);
    std::ofstream resDelRandomOrderAVL ("../tests/results/AVL/resultsPNRandomOrderDEL.csv", std::ios::app);

    std::unique_ptr<AVLtree<int>> Tree = std::make_unique<AVLtree<int>>();
    int stream{};
    auto duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        data >> stream;
        Tree->insert(stream);
    }
    auto duration_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
    switch (type){
        case 0:
            resInOrderedAVL  << "AVL, " << "insertion, " << number << ", " << duration << "\n";
            break;
        case 1:
            resInReverseOrderAVL  << "AVL, " << "insertion, " << number << ", " << duration << "\n";
            break;
        case 2:
            resInRandomOrderAVL << "AVL, " << "insertion, " << number << ", " << duration << "\n";
            break;
        }
// jaka kolejność usuwania??
    duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        data >> stream;
        Tree->remove(stream);
    }
    duration_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
    switch (type){
        case 0:
            resDelOrderedAVL  << "AVL, " << "deletion, " << number << ", " << duration << "\n";
            break;
        case 1:
            resDelReverseOrderAVL  << "AVL, " << "deletion, " << number << ", " << duration << "\n";
            break;
        case 2:
            resDelRandomOrderAVL << "AVL, " << "deletion, " << number << ", " << duration << "\n";
            break;
    }
}

void skipList_test(int number, int type, std::ifstream& data){
    std::ofstream resInOrderedSL ("../tests/results/SL/resultsPNOrderedIN.csv", std::ios::app);
    std::ofstream resInReverseOrderSL("../tests/results/SL/resultsPNReverseOrderIN.csv", std::ios::app);
    std::ofstream resInRandomOrderSL ("../tests/results/SL/resultsPNRandomOrderIN.csv", std::ios::app);

    std::ofstream resDelOrderedSL ("../tests/results/SL/resultsPNOrderedDEL.csv", std::ios::app);
    std::ofstream resDelReverseOrderSL("../tests/results/SL/resultsPNReverseOrderDEL.csv", std::ios::app);
    std::ofstream resDelRandomOrderSL ("../tests/results/SL/resultsPNRandomOrderDEL.csv", std::ios::app);

    constexpr int chosenHeight{5};
    std::unique_ptr<SkipList<int>> List = std::make_unique<SkipList<int>>(chosenHeight);
    int stream{};
    auto duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        data >> stream;
        List->insert_element(stream);
    }
    auto duration_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();

    switch (type) {
        case 0:
            resInOrderedSL << "SL, "
                           << "insertion, " << number << ", " << duration << "\n";
            break;
        case 1:
            resInReverseOrderSL << "SL, "
                                << "insertion, " << number << ", " << duration << "\n";
            break;
        case 2:
            resInRandomOrderSL << "SL, "
                               << "insertion, " << number << ", " << duration << "\n";
            break;
    }
    duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        data >> stream;
        List->remove_element(stream);
    }
    duration_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();

    switch (type){
        case 0:
            resDelOrderedSL  << "SL, " << "deletion, " << number << ", " << duration << "\n";
            break;
        case 1:
            resDelReverseOrderSL  << "SL, " << "deletion, " << number << ", " << duration << "\n";
            break;
        case 2:
            resDelRandomOrderSL << "SL, " << "deletion, " << number << ", " << duration << "\n";
            break;
    }
}
