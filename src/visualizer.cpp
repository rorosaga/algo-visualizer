#include "visualizer.h"
#include "resources.h"

namespace visualizer {

    SortVisualizer::SortVisualizer(int width, int height, int size, int speed, std::string heading)
        : window(sf::VideoMode(width, height), "Sort Visualizer")
        , rectWidth(width / (size + 10))
        , spacing(width/(size+10))
        , height(height)
        , speed(speed)
        , heading(heading) {

        // Set the framerate limit to 60 FPS
        window.setFramerateLimit(60);

        // Load the font after initializing the window
        auto fs = algos_resources::getResourceFile("resources/Pixellettersfull-BnJ5.ttf");
        if (!this->font.loadFromMemory(fs.begin(), fs.size())) {
            std::cerr << "Failed to load font." << std::endl;
        }
    }
    

    void SortVisualizer::addState(const std::vector<int>& array) {
        this->states.push_back(array);
    Visualizer::Visualizer(int width, int height)
        : window(sf::VideoMode(width, height), "Visualizer"), rectWidth(10), spacing(15) {
        // Load font
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
        }
    }

    SearchVisualizer::SearchVisualizer(int width, int height)
        : Visualizer(width, height) {}

    void SearchVisualizer::addState(const std::vector<std::vector<int>>& matrix) {
        states.push_back(matrix);
    }

    void SortVisualizer::visualizeSorting() {
        sf::Event event;
        sf::Text heading(this->heading, font, 40); // Create the heading with a font size of 40
        heading.setFillColor(sf::Color::Yellow); // Choose your color
        heading.setPosition(
            (window.getSize().x - heading.getLocalBounds().width) / 2, // Center horizontally
            10 // Position 10 pixels from the top
        );

        while (window.isOpen()) {

            // This allows the window to not close automatically
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }

            // Render each state of the sorting process
            // Each state is rendered for a short period of time
            // Then, it gets cleared and the next state is rendered
            for (const auto& state : this->states) {
                window.clear();
                window.draw(heading);
                renderState(state);
                window.display();
                sf::sleep(sf::milliseconds(this->speed)); // Adjust for speed
            }

            // Display the final sorted state with the "Sorting complete!" message
            window.clear();
            renderState(this->states.back()); // Render the final sorted state
            sf::Text endText("Sorting complete!", font, 40);
            endText.setFillColor(sf::Color::Green);
            endText.setPosition((window.getSize().x - endText.getLocalBounds().width) / 2, 10);
            window.draw(endText);
    void SearchVisualizer::visualize() {
        for (const auto& state : states) {
            renderState(state);
            window.display();
            sf::sleep(sf::seconds(1)); // Pause for a second between states
        }
    }

    void SearchVisualizer::renderState(const std::vector<std::vector<int>>& matrix) {
        window.clear();
        // Render the matrix state (implementation depends on your visualization needs)
        // Example: Draw rectangles for each element in the matrix
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                sf::RectangleShape rect(sf::Vector2f(rectWidth, matrix[i][j]));
                rect.setPosition(j * spacing, i * spacing);
                rect.setFillColor(sf::Color::White);
                window.draw(rect);
            }
        }
    }

    SortVisualizer::SortVisualizer(int width, int height)
        : Visualizer(width, height) {}

    void SortVisualizer::addState(const std::vector<std::vector<int>>& matrix) {
        states.push_back(matrix);
    }

    void SortVisualizer::visualize() {
        for (const auto& state : states) {
            renderState(state);
            window.display();
            sf::sleep(sf::seconds(1)); // Pause for a second between states
        }
    }

    void SortVisualizer::renderState(const std::vector<int>& array) {

    void SortVisualizer::renderState(const std::vector<std::vector<int>>& matrix) {
        window.clear();
        // Assuming matrix has only one row for sorting visualization
        const auto& array = matrix[0];
        // Calculate the total width of the visualized array
        float totalWidth = array.size() * spacing - (spacing - rectWidth);
        float startX = (window.getSize().x - totalWidth) / 2; // Start position for centering

        int max = *std::max_element(array.begin(), array.end());

        for (size_t i = 0; i < array.size(); ++i) {

            // Create and position the rectangle
            float barHeight = (array[i] / static_cast<float>(max)) * (0.3f * height);
            sf::RectangleShape rect(sf::Vector2f(rectWidth, barHeight));
            
            rect.setPosition(startX + i * spacing, window.getSize().y - barHeight - 30);
            rect.setFillColor(sf::Color::White);

            // Create and position the text
            sf::Text text(std::to_string(array[i]), font, 12);
            text.setFillColor(sf::Color::Red);
            text.setPosition(startX + i * spacing + (rectWidth - text.getLocalBounds().width) / 2, window.getSize().y - array[i] - 20);

            window.draw(rect);
            //window.draw(text);
        }
    }

} // namespace visualizer