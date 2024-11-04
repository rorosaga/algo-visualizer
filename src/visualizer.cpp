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