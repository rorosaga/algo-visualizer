#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

namespace visualizer {

    class Visualizer {
    public:
        // Constructor: Initializes the window with the specified width and height.
        Visualizer(int width, int height);

        // Adds a new state (array configuration) to be visualized.
        virtual void addState(const std::vector<std::vector<int>>& matrix) = 0;

        // Runs through all stored states to visualize the process.
        virtual void visualize() = 0;

    protected:
        // Helper function to render a specific state of the matrix.
        virtual void renderState(const std::vector<std::vector<int>>& matrix) = 0;

        // SFML window for rendering
        sf::RenderWindow window;

        // Collection of matrix states to visualize each step
        std::vector<std::vector<std::vector<int>>> states;

        // Dimensions for rendering (rectangle width and spacing)
        int rectWidth;
        int spacing;

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
