# algo-visualizer 📊👀

<p>
    <img alt="C++" src="https://img.shields.io/badge/-C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
    <img alt="CMake" src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white">
    <img alt="Conda" src="https://img.shields.io/badge/SFML-8CC445?style=for-the-badge&logo=sfml&logoColor=white">
    <img alt="Conda" src="https://img.shields.io/badge/conda-342B029.svg?&style=for-the-badge&logo=anaconda&logoColor=white">
</p>

The **algo-visualizer** is a C++ library designed to bring sorting algorithms to life by visually representing their step-by-step execution. Built using SFML for real-time graphical rendering, it includes two main components: a comprehensive user interface for algorithm visualization and a generic visualizer to support custom algorithms. The project also explores the workings of the C++ Standard Library's `sort` function.

📄 For more information on this project, check out the documentation [here](https://algo-visualizer.readthedocs.io/en/latest/docu.html#).

## 📚 **Index**
1. [Description](#description)
2. [Project Structure](#project-structure)
3. [How to Run](#how-to-run)
4. [Sorting Algorithms](#sorting-algorithms)
5. [STDLib Sort Function Findings](#stdlib-sort-function-findings)
6. [SFML Visualization](#using-sfml-for-ui-)

## 🐧 **Description**

The **algo-visualizer** serves both as a tool for learning and a platform for experimenting with sorting algorithms. It allows users to:
- Visualize classic sorting algorithms and their execution steps.
- Understand the algorithms’ complexities and behaviors.
- Utilize an generic visualizer to adapt the visualization for custom algorithms.

## 📁 **Project Structure**
The project is organized into the following directories:
```
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── cmake
│   ├── CMakeRC.cmake
│   └── CMakeRC.make
├── docs
│   ├── CMakeLists.txt
│   ├── Doxyfile.in
│   └── source
│       ├── conf.py
│       ├── docu.rst
│       ├── index.rst
│       └── screenshot.png
├── environment.yml
├── include
│   ├── algorithm.h
│   ├── resources.h
│   └── visualizer.h
├── resources
│   ├── Pixelletters-RLm3.ttf
│   └── Pixellettersfull-BnJ5.ttf
├── src
│   ├── CMakeLists.txt
│   ├── generic_visualizer.cpp
│   ├── algorithm.cpp
│   ├── main_generic.cpp
│   ├── main_visualizer.cpp
│   └── visualizer.cpp
└── tests
    ├── CMakeLists.txt
    └── test_sortalgos.cpp
```
- **`src/`**: Source code files.
- **`include/`**: Header files.
- **`resources/`**: Fonts for UI.
- **`docs/`**: Documentation written using Sphinx/Doxygen.
- **`tests/`**: Unit tests for algorithms.


**Executables**:  
- **`main_visualizer`**: Complete visualizer UI with sorting algorithm options.  
- **`main_generic`**: Generic visualizer for any algorithm.

## 🚀 **How to Run**
### **Prerequisites**
- [C++ Compiler (GCC/Clang)](https://gcc.gnu.org/) 🖥️
- [Conda](https://docs.conda.io/en/latest/miniconda.html) 🐍
- [CMake](https://cmake.org/) ⚙️

### **Installation**

1. Clone the repository:
```bash
git clone https://github.com/rorosaga/algo-visualizer.git
cd algo-visualizer
```

2. Create the conda environment:
```bash
conda env create -f environment.yml
conda activate visualizer
```

3. Build the project:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### **Running the Visualizer**
- To run the visualizer:
```bash
./bin/main_visualizer
```

- To run the generic visualizer:
```bash
./bin/main_generic
```

## 📊 Sorting Algorithms

### 1. **Selection Sort**
- **Complexity**: `O(N^2)`
- **Description**: Selects the smallest or largest element in the array and swaps it into its correct position. This process is repeated until the entire array is sorted.

![selection_sort](/img/selection_sort.gif)

### 2. **Bubble Sort**
- **Complexity**: `O(N^2)`
- **Description**: Repeatedly traverses the array, swapping adjacent elements if they are in the wrong order. The algorithm is optimized with an early exit flag that stops execution when no swaps are performed in a pass.

![bubble_sort](/img/bubble_sort.gif)

### 3. **Insertion Sort**
- **Complexity**: `O(N^2)`
- **Description**: Iteratively builds a sorted portion of the array by inserting each element from the unsorted portion into its correct position in the sorted portion.

![insertion_sort](/img/insertion_sort.gif)

### 4. **Merge Sort**
- **Complexity**: `O(N log(N))`
- **Description**: Employs a divide-and-conquer strategy to recursively divide the array into smaller subarrays, sorts each, and merges them back together. Both iterative and recursive implementations are provided.

![merge_sort](/img/merge_sort.gif)

### 5. **Quick Sort**
- **Complexity**: `O(N log(N))`
- **Description**: Another divide-and-conquer algorithm that partitions the array around a pivot. Elements smaller than the pivot are placed to its left, and elements larger to its right. Implemented iteratively using a stack to simulate recursive behavior.

![quick_sort](/img/quick_sort.gif)

### 6. **STDLib Sort Function**
- **Complexity**: `O(N log(N))`
- **Description**: Visualizes the inner workings of the C++ Standard Library’s `sort` function, which combines multiple sorting algorithms for efficiency.

![stdlib_sort](/img/stdlib_sort.gif)

## 📸 **Using Lambda Functions to Capture Snapshots Per Step**

To efficiently visualize sorting algorithms, a **lambda function** is used to capture snapshots of the array at each step without duplicating the entire array. This approach significantly reduces memory overhead, as only references to the current state are passed to the callback, avoiding costly array copies.

### Example: Selection Sort with a Lambda Callback
Below is the implementation of `selectionSort`, which uses a lambda function to capture snapshots of the arrya after each iteration:

`/algorithm.cpp`:
```cpp
void selectionSort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> stepCallback){
    for (int i = 0; i < arr.size(); i++){
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++){
            if (arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
        stepCallback(arr); // Capture snapshot after each iteration
    }
}
```

`visualizer.cpp`:
```cpp
...
case algorithm::SortType::SELECTION:
    algorithm::selectionSort(input_array, [&sortingSteps](const std::vector<int>& step){
        sortingSteps.push_back(step);
    });
...
```

## 🔍 **STDLib Sort Function Findings**
The **C++ Standard Library's `sort` function** uses a hybrid algorithm depending on the context:

- **Before C++11**: Based on **Quicksort**.
- **After C++11**: Implements **Introsort**, a combination of Quicksort, Heapsort, and Insertion Sort.

### Key Observations 🔑
1. **Pivot Selection**: The hybrid nature of Introsort modifies how pivots are chosen compared to standard Quicksort.
2. **Switch to Heapsort**: When the recursive depth exceeds a threshold, the algorithm switches to Heapsort for better worst-case performance.
3. **Insertion Sort**: For small subarrays (fewer than 20 elements), Insertion Sort is used due to its efficiency for small data sizes.

## Using SFML for UI 👀

The **Simple and Fast Multimedia Library (SFML)** is used to create the visualizer's user interface. SFML provides a simple interface to the various components of your PC, such as the graphics, audio, and network. It is a cross-platform library that can be used on Windows, Linux, and macOS.

**Why SFML?**

- Simple and easy-to-use graphics library.
- Based on components where you create and render them on the main screen.
- Large and active community support.

**How we use SFML ?**

- *AppState enum:* Used to define the different states of the application, such as the main menu, sorting, and visualization. This prevents infinite refreshing of the screen and ensures that the correct screen is displayed at all times.
- *visualize function:* Used to control the visualized state. It leverages the AppState enum to determine the current state and display the appropriate screen.
- *show functions:* Used to display different screens: showWelcomeScreen, showSelectScreen and showCompletionScreen.
- *prepareSorting function:* Used to prepare the sorting algorithm and set up the visualization. This includes sorting the array and capturing snapshots of the array at each step.
- *visualizeSortingStep function:* Used to visualize the sorting steps after prepation.


The main parent class Visualizer initializes the variables necessary for the simulation and creates the SFML window with its own size, simulation speed and framerate.

```C++
template <typename Container>
    Visualizer<Container>::Visualizer(int width, int height, int speed, std::string heading) :
        window(sf::VideoMode(width, height), heading),
        rectWidth(width / 10),
        spacing(width / 10),
        height(height),
        speed(speed),
        heading(heading) {
            window.setFramerateLimit(60);
    }
```

The derived child class SortVisualizer inherits from Visualizer and implements the pure virtual methods. This class is in charge of handling all the logic for displaying the main display loop, including the following methods:



Where `void visualize() override;` is the entry point to the visualization process that renders the different states. Defined in visualizer.cpp.

```C++
void SortVisualizer::visualize() {
        while (window.isOpen()) {
            switch (appState) {
                case AppState::WELCOME_SCREEN:
                    showWelcomeScreen();
                    break;
                case AppState::SELECTION_SCREEN:
                    showSelectScreen();
                    prepareSorting();
                    break;
                case AppState::RUNNING:
                    visualizeSortingSteps();
                    break;

                case AppState::COMPLETION:
                    showCompletionScreen();
                    break;
                case AppState::EXIT:
                    window.close();
                    return;
            }
        }
    }
```

The sorting steps are shown by our `renderState(const std::vector<int>& array)` called inside our main sorting visualization method `visualizeSortingSteps()`.

By passing a custom lambda function as the comparator (one of the parameters), we captured snapshots of the array after each sorting step. This provided insights into the transitions between Quicksort, Heapsort, and Insertion Sort, revealing how the hybrid algorithm adapts dynamically based on the data and conditions.




## License ⚖️
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
