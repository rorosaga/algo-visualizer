#include "gtest/gtest.h"
#include "algorithm.h"

using namespace algorithm;

TEST(SortAlgos, SelectionSort) {
    std::vector<int> arr = {2, 7, 1, 4, 9, 6, 3, 5, 8};
    selectionSort(arr);
    ASSERT_EQ(arr, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(SortAlgos, BubbleSort) {
    std::vector<int> arr = {2, 7, 1, 4, 9, 6, 3, 5, 8};
    bubbleSort(arr);
    ASSERT_EQ(arr, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(SortAlgos, InsertionSort) {
    std::vector<int> arr = {2, 7, 1, 4, 9, 6, 3, 5, 8};
    insertionSort(arr);
    ASSERT_EQ(arr, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(SortAlgos, MergeSort) {
    std::vector<int> arr = {2, 7, 1, 4, 9, 6, 3, 5, 8};
    mergeSort(arr);
    ASSERT_EQ(arr, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(SortAlgos, QuickSort) {
    std::vector<int> arr = {2, 7, 1, 4, 9, 6, 3, 5, 8};
    quickSort(arr);
    ASSERT_EQ(arr, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(SortAlgos, BogoSort) {
    std::vector<int> arr = {2, 3, 1};
    bogoSort(arr);
    ASSERT_EQ(arr, std::vector<int>({1, 2, 3}));
}