#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace visualizer {

    class Visualizer {
    public:
        /**
         * @brief Construct a new Sort Visualizer object
         * 
         * @param width Width of the window
         * @param height Height of the window
         * @param size Size of the array
         * @param speed Speed of the visualization in milliseconds
         * 
         * @note The size of the array is used to calculate the width of each rectangle representation
         * of an element in the array for rendering.
         */
        SortVisualizer(int width, int height, int size, int speed, std::string heading);

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

        // Collection of matrix states to visualize each step
        std::vector<std::vector<std::vector<int>>> states;

        // Dimensions for rendering (rectangle width and spacing)
        int rectWidth;
        int spacing;
        int height;
        int speed;
        std::string heading;

        // Font for text rendering
        sf::Font font;
    };

    class SearchVisualizer : public Visualizer {
    public:
        // Constructor: Initializes the window with the specified width and height.
        SearchVisualizer(int width, int height);

        // Adds a new state (array configuration) to be visualized.
        void addState(const std::vector<std::vector<int>>& matrix) override;

        // Runs through all stored states to visualize the search process.
        void visualize() override;

    private:
        // Helper function to render a specific state of the matrix.
        void renderState(const std::vector<std::vector<int>>& matrix) override;
    };

    class SortVisualizer : public Visualizer {
    public:
        // Constructor: Initializes the window with the specified width and height.
        SortVisualizer(int width, int height);

        // Adds a new state (array configuration) to be visualized.
        void addState(const std::vector<std::vector<int>>& matrix) override;

        // Runs through all stored states to visualize the sort process.
        void visualize() override;

    private:
        // Helper function to render a specific state of the matrix.
        void renderState(const std::vector<std::vector<int>>& matrix) override;
    };

} // namespace visualizer
