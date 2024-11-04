#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

namespace visualizer {

    class SortVisualizer {
    public:
        // Constructor: Initializes the window with the specified width and height.
        SortVisualizer(int width, int height);

        // Adds a new state (array configuration) to be visualized.
        void addState(const std::vector<int>& array);

        // Runs through all stored states to visualize the sorting process.
        void visualizeSorting();

        void trackState(const std::vector<int>& array);

    private:
        // Helper function to render a specific state of the array.
        void renderState(const std::vector<int>& array);

        // SFML window for rendering
        sf::RenderWindow window;

        // Collection of array states to visualize each sorting step
        std::vector<std::vector<int>> states;

        // Dimensions for rendering (rectangle width and spacing)
        int rectWidth;
        int spacing;

        // Font for text rendering
        sf::Font font;
    };

} // namespace visualizer