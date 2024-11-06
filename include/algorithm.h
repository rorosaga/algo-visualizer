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
    
    /**
     * @brief BFS algorithm that finds the shortest path from the start node to the end node
     * @param graph The graph to search
     * @param start The starting node
     * @param end The ending node
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the graph
     */

    void bfs(std::vector<std::vector<int>>& graph, int start, int end, std::function<void(const std::vector<std::vector<int>>&)> stepCallback = [](const std::vector<std::vector<int>>&) {});

    /**
     * @brief DFS algorithm that finds the shortest path from the start node to the end node
     * @param graph The graph to search
     * @param start The starting node
     * @param end The ending node
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the graph
     */

    void dfs(std::vector<std::vector<int>>& graph, int start, int end, std::function<void(const std::vector<std::vector<int>>&)> stepCallback = [](const std::vector<std::vector<int>>&) {});

    /**
     * @brief A* algorithm that finds the shortest path from the start node to the end node using the manhattan distance heuristic
     * @param graph The graph to search
     * @param start The starting node
     * @param end The ending node
     * @param stepCallback lambda function to call after each step letting the caller know the current state of the graph
     */

    void aStar(std::vector<std::vector<int>>& graph, int start, int end, std::function<void(const std::vector<std::vector<int>>&)> stepCallback = [](const std::vector<std::vector<int>>&) {});

}
