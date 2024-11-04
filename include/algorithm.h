#pragma once
#include <vector>
#include <functional>
#include <stack>

namespace algorithm {
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
     */
    void bogoSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

}