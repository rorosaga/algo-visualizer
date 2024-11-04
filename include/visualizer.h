#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace visualizer {

    class SortVisualizer {
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

        /**
         * @brief Adds a state of the array to the collection of states to visualize.
         * 
         * @param array Array to add to the collection of states
         * 
         * @note SortVisualizer recquires a collection of states to visualize the sorting process.
         * Each state is a snapshot of the array at a specific point in time.
         */
        void addState(const std::vector<int>& array);

        /**
         * @brief Visualizes the sorting process.
         * 
         * @note This function should be called after adding all the states to visualize.
         */
        void visualizeSorting();

    private:
        /**
         * @brief Renders the current state of the array.
         * 
         * @param array Array to render
         * 
         * @note This function is called by visualizeSorting() to render each state of the array.
         */
        void renderState(const std::vector<int>& array);

        // SFML window for rendering
        sf::RenderWindow window;

        // Collection of array states to visualize each sorting step
        std::vector<std::vector<int>> states;

        // Dimensions for rendering (rectangle width and spacing)
        int rectWidth;
        int spacing;
        int height;
        int speed;
        std::string heading;

        // Font for text rendering
        sf::Font font;
    };

} // namespace visualizer