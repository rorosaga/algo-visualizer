#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace visualizer {

    template <typename Container>
    class Visualizer {
    public:
        virtual void addState(const Container& array) = 0;
        virtual void visualize() = 0;
        Visualizer(int width, int height, int speed, std::string heading);

    private:
        virtual void renderState(const Container& array) = 0;
    protected:
        sf::RenderWindow window;
        bool showWelcome = true;
        bool isPaused = false;

        std::vector<Container> states;
        int currentStep = 0;

        int rectWidth;
        int spacing;
        int height;
        int speed;
        std::string heading;
        sf::Font font;
    };

    class SearchVisualizer : public Visualizer<std::vector<std::vector<int>>> {
    public:
        // Constructor: Initializes the window with the specified width and height.
        SearchVisualizer(int width, int height, int speed, std::string heading);

        // Adds a new state (array configuration) to be visualized.
        void addState(const std::vector<std::vector<int>>& matrix) override;

        // Runs through all stored states to visualize the search process.
        void visualize() override;

    private:
        // Helper function to render a specific state of the matrix.
        void renderState(const std::vector<std::vector<int>>& matrix) override;
    };

    class SortVisualizer : public Visualizer<std::vector<int>> {
    public:
        // Constructor: Initializes the window with the specified width and height.
        SortVisualizer(int width, int height, int size, int speed, std::string heading);
        SortVisualizer(int width, int height, int size, int speed, std::string heading, std::string timeComplexity);

        // Adds a new state (array configuration) to be visualized.
        virtual void addState(const std::vector<int>& matrix) override;

        // Runs through all stored states to visualize the sort process.
        virtual void visualize() override;

    private:
        // Helper function to render a specific state of the matrix.
        void renderState(const std::vector<int>& matrix) override;

        int size;
        std::string timeComplexity;
    };

} // namespace visualizer
