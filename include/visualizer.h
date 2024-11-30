#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "algorithm.h"

// Visualizer namespace
namespace visualizer {
    
    /**
     * @brief Enum class to represent the different states of the application
     * 
     * WELCOME_SCREEN: The screen that is displayed when the application is started
     * SELECTION_SCREEN: The screen that is displayed when the user selects the sorting algorithm
     * RUNNING: The screen that displays the sorting process
     * COMPLETION: The screen that is displayed when the sorting process is complete
     * EXIT: The state that is reached when the application is closed
     */
    enum AppState {
        WELCOME_SCREEN,
        SELECTION_SCREEN,
        RUNNING,
        COMPLETION,
        EXIT
    };

    /**
     * @brief Abstract class for visualizing algorithms
     * 
     * @tparam Container The type of the data structure to visualize
     */
    template <typename Container>
    class Visualizer {
    public:

        /**
         * @brief Construct a new Visualizer object
         * 
         * @param width The width of the window
         * @param height The height of the window
         * @param speed The speed of the visualization
         * @param heading The heading of the window
         */

        Visualizer(int width, int height, int speed, std::string heading);

        /**
         * @brief Add a new state (array configuration) to be visualized
         * 
         * @param array The array to add
         * @return void
         * @note Pure virtual function
         */
        virtual void addState(const Container& array) = 0;

        /**
         * @brief Visualize the algorithm
         * 
         * @return void
         * @note Pure virtual function
         */
        virtual void visualize() = 0;

    private:
        /**
         * @brief Render the state of the algorithm
         * 
         * @param array The array to render
         * @return void
         * @note Pure virtual function
         */
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

    /**
     * @brief Class for visualizing sorting algorithms
     * 
     * @note Inherits from the Visualizer class
     */
    class SortVisualizer : public Visualizer<std::vector<int>> {
    public:
        /**
         * @brief Construct a new Sort Visualizer object
         * 
         * @param width The width of the window
         * @param height The height of the window
         * @param size The size of the array to sort
         * @param speed The speed of the visualization
         */
        SortVisualizer(int width, int height, int size, int speed);

        /**
         * @brief Construct a new Sort Visualizer object
         * 
         * @param width The width of the window
         * @param height The height of the window
         * @param size The size of the array to sort
         * @param speed The speed of the visualization
         * @param heading The heading of the window
         */
        SortVisualizer(int width, int height, int size, int speed, std::string heading);

        /**
         * @brief Construct a new Sort Visualizer object
         * 
         * @param width The width of the window
         * @param height The height of the window
         * @param size The size of the array to sort
         * @param speed The speed of the visualization
         * @param heading The heading of the window
         * @param timeComplexity The time complexity of the algorithm
         */
        SortVisualizer(int width, int height, int size, int speed, std::string heading, std::string timeComplexity);

        /**
         * @brief Add a new state (array configuration) to be visualized
         * 
         * @param array The array to add
         * @return void
         * 
         * @note Overrides the addState method of the Visualizer class
         */
        void addState(const std::vector<int>& array) override;

        /**
         * @brief Visualize the algorithm
         * 
         * @return void
         * 
         * @note Overrides the visualize method of the Visualizer class
         */
        void visualize() override;

    private:
        /**
         * @brief Render the state of the algorithm (current array configuration)
         * 
         * @param array The array to render
         * @return void
         * 
         * @note Overrides the renderState method of the Visualizer class
         */
        void renderState(const std::vector<int>& array) override;

        /**
         * @brief Show the selection screen
         * 
         * @return void
         */
        void showSelectScreen();

        /**
         * @brief Show the welcome screen
         * 
         * @return void
         */
        void showWelcomeScreen();

        /**
         * @brief Visualize the sorting steps
         * 
         * @return void
         */
        void visualizeSortingSteps();

        /**
         * @brief Show the completion screen
         * 
         * @return void
         */
        void showCompletionScreen();

        /**
         * @brief Prepare the sorting algorithm
         * 
         * @return void
         */
        void prepareSorting();


        int size;
        AppState appState;
        std::string timeComplexity;

        algorithm::SortType sortType = algorithm::SortType::UNINITIALIZED; 
    };

}
