#include "visualizer.h"
#include "resources.h"

namespace visualizer {

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

    void SortVisualizer::renderState(const std::vector<std::vector<int>>& matrix) {
        window.clear();
        // Assuming matrix has only one row for sorting visualization
        const auto& array = matrix[0];
        // Calculate the total width of the visualized array
        float totalWidth = array.size() * spacing - (spacing - rectWidth);
        float startX = (window.getSize().x - totalWidth) / 2; // Start position for centering

        for (size_t i = 0; i < array.size(); ++i) {
            // Create and position the rectangle
            sf::RectangleShape rect(sf::Vector2f(rectWidth, array[i]));
            rect.setPosition(startX + i * spacing, window.getSize().y - array[i] - 30);
            rect.setFillColor(sf::Color::White);

            // Create and position the text
            sf::Text text(std::to_string(array[i]), font, 12);
            text.setFillColor(sf::Color::Red);
            text.setPosition(startX + i * spacing + (rectWidth - text.getLocalBounds().width) / 2, window.getSize().y - array[i] - 20);

            window.draw(rect);
            window.draw(text);
        }
    }

} // namespace visualizer