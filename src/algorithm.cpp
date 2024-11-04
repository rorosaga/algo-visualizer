#include "algorithm.h"

namespace algorithm {

    void selectionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback){
        for (int i = 0; i < arr.size(); i++){
            int minIndex = i;
            for (int j = i + 1; j < arr.size(); j++){
                if (arr[j] < arr[minIndex]){
                    minIndex = j;
                }
            }
            std::swap(arr[i], arr[minIndex]);
            stepCallback(arr);
        }
    }

    void bubbleSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback){
        bool swapped;
        for (int i = 0; i < arr.size(); i++){
            swapped = false;
            for (int j = 0; j < arr.size() - i - 1; j++){
                if (arr[j] > arr[j + 1]){
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;

                    stepCallback(arr);
                }
            }
            if (!swapped){
                break;
            }
        }
    }

    void insertionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback){
        for (int i = 1; i < arr.size() + 1; i++){
            auto key = arr[i];
            int j = i - 1;

            while (j >=0 && arr[j] > key){
                arr[j+1] = arr[j];
                j = j - 1;
            }

            arr[j + 1] = key;

            stepCallback(arr);
        }
    }

    // can be improved for easier callback readability
    void mergeSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback){
        if (arr.size() <= 1){
            return;
        }

        int mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        mergeSort(left, stepCallback);
        mergeSort(right, stepCallback);

        int i = 0;
        int j = 0;
        int k = 0;

        while (i < left.size() && j < right.size()){
            if (left[i] < right[j]){
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < left.size()){
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < right.size()){
            arr[k] = right[j];
            j++;
            k++;
        }

        stepCallback(arr);
    }

    void quickSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback){
        if (arr.size() <= 1){
            return;
        }

        std::stack<int> stack;
        stack.push(0);
        stack.push(arr.size() - 1);

        while (!stack.empty()){
            int high = stack.top();
            stack.pop();
            int low = stack.top();
            stack.pop();

            int pivot = arr[high];
            int i = low - 1;

            for (int j = low; j <= high - 1; j++){
                if (arr[j] < pivot){
                    i++;
                    std::swap(arr[i], arr[j]);
                }
            }

            std::swap(arr[i + 1], arr[high]);
            int partition = i + 1;

            if (partition - 1 > low){
                stack.push(low);
                stack.push(partition - 1);
            }

            if (partition + 1 < high){
                stack.push(partition + 1);
                stack.push(high);
            }

            stepCallback(arr);
        }
    }

    void bogoSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback){
        while (!std::is_sorted(arr.begin(), arr.end())){
            std::random_shuffle(arr.begin(), arr.end());
            stepCallback(arr);
        }
    }


}