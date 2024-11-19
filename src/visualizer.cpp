#include "visualizer.h"
#include "resources.h"
#include "algorithm.h"

namespace visualizer {

    template <typename Container>
    Visualizer<Container>::Visualizer(int width, int height, int speed, std::string heading) :
        window(sf::VideoMode(width, height), "Visualizer"),
        rectWidth(width / 10),
        spacing(width / 10),
        height(height),
        speed(speed),
        heading(heading) {
            window.setFramerateLimit(60);
        }

    SortVisualizer::SortVisualizer(int width, int height, int size, int speed, std::string heading)
        : Visualizer<std::vector<int>>(width, height, speed, heading),
        size(size)
        { // Initialize derived class member
        this->timeComplexity = "null";
        this->rectWidth=width/(size+10);
        this->spacing=width/(size+10);

        // Load the font after initializing the window
        auto fs = algos_resources::getResourceFile("resources/Pixellettersfull-BnJ5.ttf");
        if (!this->font.loadFromMemory(fs.begin(), fs.size())) {
            std::cerr << "Failed to load font." << std::endl;
        }
    }

    SortVisualizer::SortVisualizer(int width, int height, int size, int speed, std::string heading, std::string timeComplexity)
        : Visualizer<std::vector<int>>(width, height, speed, heading),
        size(size), timeComplexity(timeComplexity)
        { // Initialize derived class member

        this->rectWidth=width/(size+10);
        this->spacing=width/(size+10);

        // Load the font after initializing the window
        auto fs = algos_resources::getResourceFile("resources/Pixellettersfull-BnJ5.ttf");
        if (!this->font.loadFromMemory(fs.begin(), fs.size())) {
            std::cerr << "Failed to load font." << std::endl;
        }
    }

    void SortVisualizer::addState(const std::vector<int>& array) {
        this->states.push_back(array);
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



    void SortVisualizer::visualize() {
        sf::Event event;
        sf::Text heading(this->heading, font, 40); // Create the heading with a font size of 40
        heading.setFillColor(sf::Color::Yellow); // Choose your color
        heading.setPosition(
            (window.getSize().x - heading.getLocalBounds().width) / 2, // Center horizontally
            10 // Position 10 pixels from the top
        );


        // Stop button
        sf::RectangleShape stopButton(sf::Vector2f(50, 50));
        stopButton.setPosition(50, 20);
        stopButton.setFillColor(sf::Color::Red);

        // Text for the stop button
        sf::Text stopText("Stop", font, 20);
        stopText.setFillColor(sf::Color::White);
        stopText.setPosition(57, 30);

        // Play button
        sf::RectangleShape playButton(sf::Vector2f(50, 50));
        playButton.setPosition(110, 20);
        playButton.setFillColor(sf::Color::Green);

        // Play button text
        sf::Text playText("Play", font, 20);
        playText.setFillColor(sf::Color::Black);
        playText.setPosition(117, 30);

        // Undo button
        sf::RectangleShape undoButton(sf::Vector2f(50, 50));
        undoButton.setPosition(160, 20);
        undoButton.setFillColor(sf::Color::Yellow);

        // Undo button text
        sf::Text undoText("Undo", font, 20);
        undoText.setFillColor(sf::Color::Black);
        undoText.setPosition(167, 30);

        sf::Text timeComplexityText;
        if (this->timeComplexity != "null") {
            timeComplexityText.setFont(font);
            timeComplexityText.setString(this->timeComplexity);
            timeComplexityText.setCharacterSize(40);
            timeComplexityText.setFillColor(sf::Color::White);

            // Position timeComplexityText in the top-right corner of the border box
            float topRightX = window.getSize().x - 70 - timeComplexityText.getLocalBounds().width;
            float topRightY = 25; // Align it with the top border line
            timeComplexityText.setPosition(topRightX, topRightY);
        }

        // Define a VertexArray for a custom border with four corners
        sf::VertexArray border(sf::LinesStrip, 5); // 5 points for a closed rectangle (back to the first point)

        // Set each corner's position manually (adjust to your desired coordinates)
        border[0].position = sf::Vector2f(40, 15); // Top-left corner
        border[1].position = sf::Vector2f(window.getSize().x - 40, 15); // Top-right corner
        border[2].position = sf::Vector2f(window.getSize().x - 40, window.getSize().y - 20); // Bottom-right corner
        border[3].position = sf::Vector2f(40, window.getSize().y - 20); // Bottom-left corner
        border[4].position = border[0].position; // Connect back to the first point to close the shape

        // Set color for each vertex if desired (optional)
        for (size_t i = 0; i < border.getVertexCount(); ++i) {
            border[i].color = sf::Color::Yellow;
        }

        while (window.isOpen()) {
            std::cout << "Window open" << std::endl;
            // This allows the window to not close automatically
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }

            std::cout << "Show welcome message" << std::endl;
            // Display the welcome message
            window.clear();
            sf::Text welcome("Welcome to the Sorting Visualizer!", font, 40);
            welcome.setFillColor(sf::Color::Yellow);
            welcome.setPosition((window.getSize().x - welcome.getLocalBounds().width) / 2, (window.getSize().y - welcome.getLocalBounds().height) / 2);
            window.draw(welcome);

            sf::Text instructions("Press any key to start the visualization.", font, 20);
            instructions.setFillColor(sf::Color::White);
            instructions.setPosition((window.getSize().x - instructions.getLocalBounds().width) / 2, ((window.getSize().y - welcome.getLocalBounds().height) / 2) + 50 );
            window.draw(instructions);

            window.display();

            while (this->showWelcome) {
                // Wait for any key press to start the visualization
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::KeyPressed) {
                        std::cout << "Key pressed" << std::endl;
                        this->showWelcome = false;
                        break;
                    }
                }
            }

            // While the visualization is paused, render the current state and the buttons to control the visualization
            // if the play button is pressed, it will render the next state iteratively
            while (currentStep < states.size()) {
                if (this->isPaused) {
                    std::cout << "Paused at step " << currentStep << std::endl;
                    // Draw the headers and basic ui stuff
                    window.clear();
                    if (this->timeComplexity != "null") {window.draw(timeComplexityText);}
                    window.draw(border);
                    window.draw(heading);

                    window.draw(playButton);
                    window.draw(playText);

                    window.draw(undoButton);
                    window.draw(undoText);

                    renderState(states[currentStep]);

                    window.display();

                    while (this->isPaused) {
                        // to prevent the window from refreshing everytime, it simply waits for the user to click play or undo button
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                    std::cout << "Play button clicked" << std::endl;
                                    this->isPaused = false;
                                    break;
                                }
                        }

                        // check if undo button is clicked
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            if (undoButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Undo button clicked" << std::endl;
                                if (currentStep > 0) {
                                    currentStep--;
                                }
                                break;
                            }
                        }
                    }

                } else {
                    std::cout << "Run simulation" << std::endl;

                    window.clear();
                    if (this->timeComplexity != "null") {window.draw(timeComplexityText);}
                    window.draw(border);
                    window.draw(heading);

                    window.draw(stopButton);
                    window.draw(stopText);


                    // check if stop button is clicked
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        if (stopButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            std::cout << "Stop button clicked" << std::endl;
                            this->isPaused = true;
                        }
                    }
                    // std::cout << "current state: " << states[currentStep] << std::endl;

                    renderState(states[currentStep]);

                    window.display();
                    sf::sleep(sf::milliseconds(this->speed)); // Adjust for speed
                    currentStep++;
                };
            };


            // Show the ending ui when the sorting is done
            std::cout << "Sorting complete" << std::endl;
            this->isPaused = true;

            // Display the final sorted state with the "Sorting complete!" message
            window.clear();
            if (this->timeComplexity != "null") {window.draw(timeComplexityText);}
            // Set color for each vertex if desired (optional)
            for (size_t i = 0; i < border.getVertexCount(); ++i) {
                border[i].color = sf::Color::Green;
            }

            window.draw(border);
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

    SearchVisualizer::SearchVisualizer(int width, int height, int speed, std::string heading)
        : Visualizer<std::vector<std::vector<int>>>(width, height, speed, heading) { // Call base class constructor
        window.setFramerateLimit(60);
    }

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

} // namespace visualizer
