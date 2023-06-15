#include "../include/SkipList.h"
#include "../include/AVLtree.h"
#include "../src/SkipList.cpp"
#include "../src/AVLtree.cpp"
#include <memory>
#include <chrono>
#include <fstream>

void AVL_test(int number, std::ofstream& resultsIn, std::ofstream& resultsDel, std::ifstream& data);
void skipList_test(int number, std::ofstream& resultsIn, std::ofstream& resultsDel, std::ifstream& data);

int main(){
    std::ifstream orderedData ("../tests/PN_ordered_numbers.csv");
    std::ifstream reverseOrderedData ("../tests/PN_reversed_numbers.csv");
    std::ifstream randomOrderedData ("../tests/PN_random_numbers.csv");

    std::ofstream resInOrderedAVL ("../tests/results/AVL/resultsPNOrderedIN.csv", std::ios::app);
    std::ofstream resInReverseOrderAVL("../tests/results/AVL/resultsPNReverseOrderIN.csv", std::ios::app);
    std::ofstream resInRandomOrderAVL ("../tests/results/AVL/resultsPNRandomOrderIN.csv", std::ios::app);

    std::ofstream resDelOrderedAVL ("../tests/results/AVL/resultsPNOrderedDEL.csv", std::ios::app);
    std::ofstream resDelReverseOrderAVL("../tests/results/AVL/resultsPNReverseOrderDEL.csv", std::ios::app);
    std::ofstream resDelRandomOrderAVL ("../tests/results/AVL/resultsPNRandomOrderDEL.csv", std::ios::app);

    std::ofstream resInOrderedSL ("../tests/results/SL/resultsPNOrderedIN.csv", std::ios::app);
    std::ofstream resInReverseOrderSL("../tests/results/SL/resultsPNReverseOrderIN.csv", std::ios::app);
    std::ofstream resInRandomOrderSL ("../tests/results/SL/resultsPNRandomOrderIN.csv", std::ios::app);

    std::ofstream resDelOrderedSL ("../tests/results/SL/resultsPNOrderedDEL.csv", std::ios::app);
    std::ofstream resDelReverseOrderSL("../tests/results/SL/resultsPNReverseOrderDEL.csv", std::ios::app);
    std::ofstream resDelRandomOrderSL ("../tests/results/SL/resultsPNRandomOrderDEL.csv", std::ios::app);


    std::vector<int> n {10, 100, 10000, 20000, 50000, 100000, 200000};//, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    std::vector<int> test {10, 20};

    for (const auto& number : n){
        AVL_test(number, resInOrderedAVL, resDelOrderedAVL, orderedData);
        AVL_test(number, resInReverseOrderAVL,resDelReverseOrderAVL, reverseOrderedData);
        AVL_test(number, resInRandomOrderAVL, resDelRandomOrderAVL, randomOrderedData);
//        skipList_test(number, resInOrderedSL, resDelOrderedSL, orderedData);
//        skipList_test(number, resInReverseOrderSL,resDelReverseOrderSL, reverseOrderedData);
//        skipList_test(number, resInRandomOrderSL, resDelRandomOrderSL, randomOrderedData);
    }

    return 0;
}

void AVL_test(int number, std::ofstream& resultsIn, std::ofstream& resultsDel, std::ifstream& data){
    //data.open();
    if(data.is_open() == true) {
        std::unique_ptr<AVLtree<int>> Tree = std::make_unique<AVLtree<int>>();
        int stream{};
        auto duration_start = std::chrono::high_resolution_clock::now();
        for (int i{0}; i < number; ++i) {
            data >> stream;
            Tree->insert(stream);
        }
        auto duration_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
        resultsIn << "AVL, " << "insertion, " << number << ", " << duration << "\n";
// jaka kolejność usuwania??
        duration_start = std::chrono::high_resolution_clock::now();
        for (int i{0}; i < number; ++i) {
            data >> stream;
            Tree->remove(stream);
        }
        duration_end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
        resultsDel << "AVL, " << "deletion, " << number << ", " << duration << "\n";
    }
    //data.close();
}

void skipList_test(int number, std::ofstream& resultsIn, std::ofstream& resultsDel, std::ifstream& data){
    //data.open();
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
    resultsIn << "SL, " << "insertion, " << number << ", " << duration << "\n";

    duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        data >> stream;
        List->remove_element(stream);
    }
    duration_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
    resultsDel << "SL, " << "deletion, " << number << ", " << duration << "\n";
    data.close();
}