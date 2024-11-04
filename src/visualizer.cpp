#include "visualizer.h"
#include "resources.h"

namespace visualizer {

    SortVisualizer::SortVisualizer(int width, int height)
        : window(sf::VideoMode(width, height), "Sort Visualizer"), rectWidth(10), spacing(2) {
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

            for (const auto& state : this->states) {
                window.clear();
                renderState(state);
                window.display();
                sf::sleep(sf::milliseconds(100)); // Adjust for speed
            }
            sf::sleep(sf::seconds(5));

            sf::Text endText("Sorting complete!", font, 40);
            endText.setPosition((window.getSize().x - endText.getLocalBounds().width) / 2, 10);
            window.draw(endText);
            window.display();

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
        for (size_t i = 0; i < array.size(); ++i) {
            sf::RectangleShape rect(sf::Vector2f(10, array[i]));
            rect.setPosition(i * 40, window.getSize().y - array[i]);
            rect.setFillColor(sf::Color::White);
            window.draw(rect);
        }
    }

} // namespace visualizer