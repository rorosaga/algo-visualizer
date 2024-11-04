#include "algorithm.h"
#include <iostream>

int main() {

    std::vector<int> arr = {2, 1, 4, 3};
    algorithm::bogoSort(arr, [](const std::vector<int>& step){
        for (int num : step) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    });

    // works without lambda too
    // std::vector<int> arr2 = {5, 3, 1, 4, 2};
    // algorithm::bubbleSort(arr2);

    // for (int num : arr2) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    // return 0;
}