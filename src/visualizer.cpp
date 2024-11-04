#include "visualizer.h"
#include "resources.h"

namespace visualizer {

    SortVisualizer::SortVisualizer(int width, int height)
        : window(sf::VideoMode(width, height), "Sort Visualizer"), rectWidth(30), spacing(40) {
        window.setFramerateLimit(60);
        auto fs = algos_resources::getResourceFile("resources/Pixellettersfull-BnJ5.ttf");
        if (!this->font.loadFromMemory(fs.begin(), fs.size())) {
            std::cerr << "Failed to load font." << std::endl;
        }
    }
    

    void SortVisualizer::addState(const std::vector<int>& array) {
        this->states.push_back(array);
    }

    void SortVisualizer::visualizeSorting() {
        sf::Event event;

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }

            // Render each state of the sorting process
            for (const auto& state : this->states) {
                window.clear();
                renderState(state);
                window.display();
                sf::sleep(sf::milliseconds(100)); // Adjust for speed
            }

            // Display the final sorted state with the "Sorting complete!" message
            window.clear();
            renderState(this->states.back()); // Render the final sorted state
            sf::Text endText("Sorting complete!", font, 40);
            endText.setPosition((window.getSize().x - endText.getLocalBounds().width) / 2, 10);
            window.draw(endText);
            window.display();

            // Keep the window open until the user closes it
            while (window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }
            }
        }
    }  


    void SortVisualizer::renderState(const std::vector<int>& array) {
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