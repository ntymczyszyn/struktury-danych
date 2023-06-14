#include "../include/SkipList.h"
#include "../include/AVLtree.h"
#include "../src/SkipList.cpp"
#include "../src/AVLtree.cpp"
#include <memory>
#include <chrono>
#include <fstream>

void AVL_test(int number, std::ofstream& results, std::ifstream& data);
void skipList_test(int number, std::ofstream& results, std::ifstream& data);

int main(){
    std::ofstream resultsOrdered ("../resultsPNOrdered.csv", std::ios::app);
    std::ofstream resultsReverseOrder ("../resultsPNReverseOrder.csv", std::ios::app);
    std::ofstream resultsRandomOrder ("../resultsPNRandomOrder.csv", std::ios::app);

    std::ifstream orderedData ("../tests/PN_ordered_numbers.csv");
    std::ifstream reverseOrderedData ("../tests/PN_reversed_numbers.csv");
    std::ifstream randomOrderedData ("../tests/PN_random_numbers.csv");

    // można podokładać jakbyśmy chciały więcej/ mnie zależy jakie to wydajne wyjdzie
    std::vector<int> n {10, 100, 10000, 20000, 50000, 100000, 200000, 300000};
                       //400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    std::vector<int> test {10, 20};
    for (const auto& number : test){
        AVL_test(number, resultsOrdered, orderedData);
        AVL_test(number, resultsReverseOrder, orderedData);
        AVL_test(number, resultsRandomOrder, orderedData);
    }

    return 0;
}

void AVL_test(int number, std::ofstream& results, std::ifstream& data){
    // on się sam ogarnie po wyjściu ze scopu
    std::unique_ptr<AVLtree<int>> Tree = std::make_unique<AVLtree<int>>();
    int stream{};
    auto duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        data >> stream;
        Tree->insert(stream);
    }
    auto duration_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
    results << "AVL, " << "insertion, " << number << ", " << duration << "\n";
// jaka kolejność usuwania??
    duration_start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < number; ++i) {
        data >> stream;
        Tree->insert(stream);
    }
    duration_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
    results << "AVL, " << "deletion, " << number << ", " << duration << "\n";
}