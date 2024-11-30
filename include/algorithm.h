#pragma once
#include <vector>
#include <functional>
#include <stack>
#include <random>

namespace algorithm {

    /**
     * @brief Enum class to represent the different sorting algorithms
     */
    enum class SortType {
        UNINITIALIZED, // default value
        SELECTION,
        BUBBLE,
        INSERTION,
        MERGE,
        QUICK,
        BOGO,
        STD
    };

    void randomNumberGen(std::vector<int>& arr, int size, int min, int max);

    /**
     * @brief Sorts the given array using the selection sort algorithm
     * @param arr The array to sort
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the array
     */
    void selectionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    /**
     * @brief Sorts the given array using the bubble sort algorithm
     * @param arr The array to sort
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the array
     */
    void bubbleSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    /**
     * @brief Sorts the given array using the insertion sort algorithm
     * @param arr The array to sort
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the array
     */
    void insertionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void iterMergeSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback);

    void iterQuickSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback);

    /**
     * @brief Sorts the given array using the merge sort algorithm
     * @param arr The array to sort
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the array
     */
    void mergeSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    /**
     * @brief Sorts the given array using the quick sort algorithm
     * @param arr The array to sort
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the array
     */
    void quickSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    /**
     * @brief Sorts the given array using the bogo sort algorithm
     * @param arr The array to sort
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the array
     * @note This algorithm won't work for large arrays as the time complexity is infinity in the worst case.
     *      For the application of this visualizer, it will not work as the sorting is recquired to be finished
     *     before visualizing the steps.
     */
    void bogoSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});
}
