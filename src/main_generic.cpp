#include "visualizer.h"
#include "algorithm.h" // Assuming this contains your sorting algorithms
#include <vector>
#include <iostream>

using namespace visualizer;

int main() {
    std::vector<int> arr;
    algorithm::randomNumberGen(arr, 500, 1, 100);

    int width = 800;
    int height = 600;
    int size = arr.size();
    int speed = 50;

    std::string heading = "Quick Sort Visualization";
    std::string timeComplexity = "O(n log n)";

    SortVisualizer sorter(width, height, size, speed, heading, timeComplexity);

    // Perform the iterative QuickSort and capture each step
    algorithm::iterQuickSort(arr, [&](const std::vector<int>& step) {
        sorter.addState(step);
    });

    sorter.visualize();

    return 0;
}
