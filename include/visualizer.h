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
    
    enum AppState {
        WELCOME_SCREEN,
        SELECTION_SCREEN,
        RUNNING,
        COMPLETION,
        EXIT
    };

    template <typename Container>
    class Visualizer {
    public:
        Visualizer(int width, int height, int speed, std::string heading);

        virtual void addState(const Container& array) = 0;
        virtual void visualize() = 0;

    private:
        virtual void renderState(const Container& array) = 0;

    protected:
        sf::RenderWindow window;
        bool showWelcome = true;
        bool isPaused = false;
        bool isInHome = false;

        std::vector<Container> states;
        int currentStep = 0;

        int rectWidth;
        int spacing;
        int height;
        int speed;
        std::string heading;
        sf::Font font;
    };

    // Updated SortVisualizer class with methods merged from SortVisualizer2
    class SortVisualizer : public Visualizer<std::vector<int>> {
    public:
        // Constructors: Initializes the window with the specified width and height.
        SortVisualizer(int width, int height, int size, int speed);
        SortVisualizer(int width, int height, int size, int speed, std::string heading);
        SortVisualizer(int width, int height, int size, int speed, std::string heading, std::string timeComplexity);

        // Adds a new state (array configuration) to be visualized.
        void addState(const std::vector<int>& array) override;

        // Runs through all stored states to visualize the sort process.
        void visualize() override;

    private:
        // Helper functions to render specific states and screens.
        void renderState(const std::vector<int>& array) override;
        void showSelectScreen();
        void showWelcomeScreen();
        void visualizeSortingSteps();
        void showCompletionScreen();
        void prepareSorting();

        int size;
        AppState appState;
        std::string timeComplexity;

        // Added from SortVisualizer2
        algorithm::SortType sortType = algorithm::SortType::UNINITIALIZED; // Default value
    };

} // namespace visualizer
