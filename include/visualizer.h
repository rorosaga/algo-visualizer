#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "algorithm.h"
namespace visualizer {
    /**
     * @brief Constructor for the Visualizer class
     * @param width The width of the window
     * @param height The height of the window
     * @param speed The speed at which the visualization should run
     * @param heading The heading to display at the top of the window
     * @tparam Container The type of the container to visualize
     * @return A new instance of the Visualizer class
     * @note This is the base class constructor
     */
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

    // Visualizer without the select screen, needs to be used implemented with the main function code
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

    // Visualizer with the select screen, simply create an instance of this object and call visualize to access everything
    // This could be seen as an out of the box alternative to the SortVisualizer class
    // It keeps all the functionalities, but adds a select screen to choose the sorting algorithm
    class SortVisualizer2 : public Visualizer<std::vector<int>> {
    public:
        SortVisualizer2(int width, int height, int size, int speed);

        virtual void addState(const std::vector<int>& matrix) override;
        virtual void visualize() override;

    private:
        algorithm::SortType sortType = algorithm::SortType::UNINITIALIZED; // Default value;
        std::string timeComplexity;
        void renderState(const std::vector<int>& matrix) override;
        void showSelectScreen();
    };
} // namespace visualizer
