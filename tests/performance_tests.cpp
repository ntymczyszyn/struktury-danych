
#include "../include/SkipList.h"
#include "../include/AVLtree.h"
#include "../src/SkipList.cpp"
#include "../src/AVLtree.cpp"

#include <chrono>

int main(){
    std::vector<Movie> movies;
    std::fstream testFile ("../wyniki4.csv", std::ios::app);

    std::vector<int> n {10, 100, 10000, 20000, 50000, 100000, 200000, 300000,
                       400000, 500000, 600000, 700000, 800000, 900000, 1000000, 1010293};
    // inserting
    // deleting

    for (const auto& number : n){
        readData(movies, number);
        auto duration_start = std::chrono::high_resolution_clock::now();
        heapSort(movies);
        auto duration_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(duration_end - duration_start).count();
        testFile << "heapsort, " << number << ", " << duration << "\n";
    }

    return 0;
}
