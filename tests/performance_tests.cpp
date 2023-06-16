#include "../include/SkipList.h"
#include "../include/AVLtree.h"
#include "../src/SkipList.cpp"
#include "../src/AVLtree.cpp"
#include <memory>
#include <chrono>
#include <fstream>


void AVL_test(int number, std::ofstream& resultsIn, std::ofstream& resultsDel, int type);
void skipList_test(int number, std::ofstream& results, std::ofstream& resultsDel, int type);


int main(){
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

    std::vector<int> nSL {10, 100, 500, 1000, 1500, 2000, 5000, 10000, 15000,  20000, 50000, 100000, 200000, 300000, 400000, 500000};//
    std::vector<int> nSL1 {500000};
    std::vector<int> nAVL {10, 100, 500,  5000, 10000,  20000, 50000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    std::vector<int> test {10, 5};

    for (const auto& number :nSL1){
//        AVL_test(number, resInOrderedAVL, resDelOrderedAVL, 0);
//        AVL_test(number, resInReverseOrderAVL,resDelReverseOrderAVL, 1);
//        AVL_test(number, resInRandomOrderAVL, resDelRandomOrderAVL, 2);
        skipList_test(number, resInOrderedSL, resDelOrderedSL, 0);
        skipList_test(number, resInReverseOrderSL,resDelReverseOrderSL, 1);
        skipList_test(number, resInRandomOrderSL, resDelRandomOrderSL, 2);
    }

    return 0;
}

void AVL_test(int number, std::ofstream& resultsIn, std::ofstream& resultsDel, int type){
    std::ifstream orderedData ("../tests/PN_ordered_numbers.csv");
    std::ifstream reverseOrderedData ("../tests/PN_reversed_numbers.csv");
    std::ifstream randomOrderedData ("../tests/PN_random_numbers.csv");

    std::unique_ptr<AVLtree<int>> Tree = std::make_unique<AVLtree<int>>();
    int stream{};
    auto duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        switch (type){
            case 0:
                orderedData  >> stream;
                break;
            case 1:
                reverseOrderedData  >> stream;
                break;
            case 2:
                randomOrderedData  >> stream;
                break;
        }
        Tree->insert(stream);
    }
    auto duration_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
    resultsIn << "AVL, " << "insertion, " << number << ", " << duration << "\n";
    // wskaźnik na początek pliku
    orderedData.seekg(0, std::ios::beg);
    reverseOrderedData.seekg(0, std::ios::beg);
    randomOrderedData.seekg(0, std::ios::beg);
    duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        switch (type){
            case 0:
                orderedData  >> stream;
                break;
            case 1:
                reverseOrderedData  >> stream;
                break;
            case 2:
                randomOrderedData  >> stream;
                break;
        }
        Tree->remove(stream);
    }
    duration_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
    resultsDel << "AVL, " << "deletion, " << number << ", " << duration << "\n";
}

void skipList_test(int number, std::ofstream& resultsIn, std::ofstream& resultsDel, int type){
    std::ifstream orderedData ("../tests/PN_ordered_numbers.csv");
    std::ifstream reverseOrderedData ("../tests/PN_reversed_numbers.csv");
    std::ifstream randomOrderedData ("../tests/PN_random_numbers.csv");

    constexpr int chosenHeight{20};
    std::unique_ptr<SkipList<int>> List = std::make_unique<SkipList<int>>(chosenHeight);
    int stream{};
    auto duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        switch (type){
            case 0:
                orderedData  >> stream;
                break;
            case 1:
                reverseOrderedData  >> stream;
                break;
            case 2:
                randomOrderedData  >> stream;
                break;
        }
        List->insert_element(stream);
    }
    auto duration_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
// wskaźnik na poczatek pliku
    orderedData.seekg(0, std::ios::beg);
    reverseOrderedData.seekg(0, std::ios::beg);
    randomOrderedData.seekg(0, std::ios::beg);
    resultsIn << "SL, height, "<<chosenHeight<< ", insertion, " << number << ", " << duration << "\n";

//    if(type == 0)
//        List->show_list();

    duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        switch (type){
            case 0:
                orderedData  >> stream;
                break;
            case 1:
                reverseOrderedData  >> stream;
                break;
            case 2:
                randomOrderedData  >> stream;
                break;
        }
        List->remove_element(stream);
    }
    duration_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();

//    if(type == 0)
//        List->show_list();


    resultsDel << "SL, " << "deletion, " << number << ", " << duration << "\n";
}
