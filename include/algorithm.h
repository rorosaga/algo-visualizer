#pragma once
#include <vector>
#include <functional>
#include <stack>

namespace algorithm {

    void selectionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void bubbleSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void insertionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void mergeSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void quickSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

    void bogoSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback = [](const std::vector<int>&) {});

}