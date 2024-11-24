#include "visualizer.h"
#include "algorithm.h"
#include <vector>
#include <thread>


using namespace visualizer;

int main() {
    // create a visualizer object and call .visualize(), this simple 🙏
    SortVisualizer visualizer(1000, 1000, 300, 50);

    visualizer.visualize();

    return 0;
}
