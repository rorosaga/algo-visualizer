#pragma once
#include <vector>
#include <functional>
#include <stack>
#include <random>

namespace algorithm {
    void randomNumberGen(std::vector<int>& arr, int size, int min, int max);

    void selectionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void bubbleSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void insertionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void iterMergeSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback);

    void iterQuickSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback);

    void mergeSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void quickSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void bogoSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

}