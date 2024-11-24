#include "visualizer.h"
#include "resources.h"
#include "algorithm.h"

namespace visualizer {

    // Base Visualizer class constructor
    template <typename Container>
    Visualizer<Container>::Visualizer(int width, int height, int speed, std::string heading) :
        window(sf::VideoMode(width, height), heading),
        rectWidth(width / 10),
        spacing(width / 10),
        height(height),
        speed(speed),
        heading(heading) {
            window.setFramerateLimit(60);
    }

    // SortVisualizer class implementation
    SortVisualizer::SortVisualizer(int width, int height, int size, int speed)
        : Visualizer<std::vector<int>>(width, height, speed, "Sorting Visualizer"),
          size(size),
          timeComplexity("null"),
          appState(AppState::WELCOME_SCREEN) {

        this->rectWidth = width / (size + 10);
        this->spacing = width / (size + 10);

        // Load the font after initializing the window
        auto fs = algos_resources::getResourceFile("resources/Pixellettersfull-BnJ5.ttf");
        if (!this->font.loadFromMemory(fs.begin(), fs.size())) {
            std::cerr << "Failed to load font." << std::endl;
        }
    }

    // Add state
    void SortVisualizer::addState(const std::vector<int>& array) {
        this->states.push_back(array);
    }

    void SortVisualizer::renderState(const std::vector<int>& array) {
        float totalWidth = array.size() * spacing - (spacing - rectWidth);
        float startX = (window.getSize().x - totalWidth) / 2; // Centering

        int max = *std::max_element(array.begin(), array.end());

        for (size_t i = 0; i < array.size(); ++i) {
            float barHeight = (array[i] / static_cast<float>(max)) * (0.3f * height);
            sf::RectangleShape rect(sf::Vector2f(rectWidth, barHeight));

            rect.setPosition(startX + i * spacing, window.getSize().y - barHeight - 30);
            rect.setFillColor(sf::Color::White);

            // Optional: display the value on the bar
            // sf::Text text(std::to_string(array[i]), font, 12);
            // text.setFillColor(sf::Color::Red);
            // text.setPosition(startX + i * spacing + (rectWidth - text.getLocalBounds().width) / 2, window.getSize().y - barHeight - 20);

            window.draw(rect);
            // window.draw(text); // Uncomment to display the values
        }
    }

    void SortVisualizer::showWelcomeScreen() {
        sf::Event event;

        // Display the welcome message
        window.clear();
        sf::Text welcome("Welcome to the Sorting Visualizer!", font, 40);
        welcome.setFillColor(sf::Color::Yellow);
        welcome.setPosition((window.getSize().x - welcome.getLocalBounds().width) / 2, (window.getSize().y - welcome.getLocalBounds().height) / 2);
        window.draw(welcome);

        sf::Text instructions("Press any key to start", font, 20);
        instructions.setFillColor(sf::Color::White);
        instructions.setPosition((window.getSize().x - instructions.getLocalBounds().width) / 2, ((window.getSize().y - welcome.getLocalBounds().height) / 2) + 50 );
        window.draw(instructions);

        window.display();

        // Wait for any key press to start the visualization
        bool waiting = true;
        while (waiting) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    waiting = false;
                    break;
                }
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }
        }
        appState = AppState::SELECTION_SCREEN;
    }

    void SortVisualizer::showSelectScreen() {
        // Buttons and texts for sorting algorithms
        sf::RectangleShape mergeButton(sf::Vector2f(150, 50));
        mergeButton.setPosition(440, 100);
        mergeButton.setFillColor(sf::Color::Green);

        sf::Text mergeText("Merge Sort", font, 20);
        mergeText.setFillColor(sf::Color::Black);
        mergeText.setPosition(477, 110);

        sf::RectangleShape quickButton(sf::Vector2f(150, 50));
        quickButton.setPosition(440, 170);
        quickButton.setFillColor(sf::Color::Green);

        sf::Text quickText("Quick Sort", font, 20);
        quickText.setFillColor(sf::Color::Black);
        quickText.setPosition(477, 185);

        sf::RectangleShape bubbleButton(sf::Vector2f(150, 50));
        bubbleButton.setPosition(440, 240);
        bubbleButton.setFillColor(sf::Color::Green);

        sf::Text bubbleText("Bubble Sort", font, 20);
        bubbleText.setFillColor(sf::Color::Black);
        bubbleText.setPosition(477, 255);

        sf::RectangleShape selectionButton(sf::Vector2f(150, 50));
        selectionButton.setPosition(440, 310);
        selectionButton.setFillColor(sf::Color::Green);

        sf::Text selectionText("Selection Sort", font, 20);
        selectionText.setFillColor(sf::Color::Black);
        selectionText.setPosition(477, 325);

        sf::RectangleShape insertionButton(sf::Vector2f(150, 50));
        insertionButton.setPosition(440, 380);
        insertionButton.setFillColor(sf::Color::Green);

        sf::Text insertionText("Insertion Sort", font, 20);
        insertionText.setFillColor(sf::Color::Black);
        insertionText.setPosition(477, 395);

        sf::RectangleShape stdButton(sf::Vector2f(150, 50));
        stdButton.setPosition(440, 450);
        stdButton.setFillColor(sf::Color::Green);

        sf::Text stdText("STDlib Sort", font, 20);
        stdText.setFillColor(sf::Color::Black);
        stdText.setPosition(477, 465);

        // sf::RectangleShape bogoButton(sf::Vector2f(150, 50));
        // bogoButton.setPosition(50, 450);
        // bogoButton.setFillColor(sf::Color::Green);

        // sf::Text bogoText("Bogo Sort", font, 20);
        // bogoText.setFillColor(sf::Color::Black);
        // bogoText.setPosition(57, 465);

        // Display the selection screen
        window.clear();
        sf::Text selectText("Select a sorting algorithm", font, 40);
        selectText.setFillColor(sf::Color::White);
        selectText.setPosition((window.getSize().x - selectText.getLocalBounds().width) / 2, 20);
        window.draw(selectText);

        // Draw all buttons and texts
        window.draw(mergeButton);
        window.draw(mergeText);
        window.draw(quickButton);
        window.draw(quickText);
        window.draw(bubbleButton);
        window.draw(bubbleText);
        window.draw(selectionButton);
        window.draw(selectionText);
        window.draw(insertionButton);
        window.draw(insertionText);
        window.draw(stdButton);
        window.draw(stdText);

        // window.draw(bogoButton);
        // window.draw(bogoText);

        window.display();

        // Wait for the user to select an algorithm
        sf::Event event;
        sortType = algorithm::SortType::UNINITIALIZED; // Reset sortType
        while (sortType == algorithm::SortType::UNINITIALIZED) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (mergeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        sortType = algorithm::SortType::MERGE;
                        timeComplexity = "O(n log n)";
                    } else if (quickButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        sortType = algorithm::SortType::QUICK;
                        timeComplexity = "O(n log n)";
                    } else if (bubbleButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        sortType = algorithm::SortType::BUBBLE;
                        timeComplexity = "O(n^2)";
                    } else if (selectionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        sortType = algorithm::SortType::SELECTION;
                        timeComplexity = "O(n^2)";
                    } else if (insertionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        sortType = algorithm::SortType::INSERTION;
                        timeComplexity = "O(n^2)";
                    } else if (stdButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        sortType = algorithm::SortType::STD;
                        timeComplexity = "O(n log n)";
                    }

                    if (sortType != algorithm::SortType::UNINITIALIZED) {
                        break;
                    }
                }
            }
        }
        appState = AppState::RUNNING;
    }

    void SortVisualizer::visualize() {
        while (window.isOpen()) {
            switch (appState) {
                case AppState::WELCOME_SCREEN:
                    showWelcomeScreen();
                    break;
                case AppState::SELECTION_SCREEN:
                    showSelectScreen();
                    prepareSorting();
                    break;
                case AppState::RUNNING:
                    visualizeSortingSteps();
                    break;

                case AppState::COMPLETION:
                    showCompletionScreen();
                    break;
                case AppState::EXIT:
                    window.close();
                    return;
            }
        }
    }

    void SortVisualizer::showCompletionScreen() {
        sf::Event event;

        // Quit button
        sf::RectangleShape quitButton(sf::Vector2f(80, 40));
        quitButton.setPosition(180, 20);
        quitButton.setFillColor(sf::Color::Blue);

        sf::Text quitText("Home", font, 20);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(187, 25);

        // Time complexity text
        sf::Text timeComplexityText;
        if (this->timeComplexity != "null") {
            timeComplexityText.setFont(font);
            timeComplexityText.setString(this->timeComplexity);
            timeComplexityText.setCharacterSize(40);
            timeComplexityText.setFillColor(sf::Color::White);

            float topRightX = window.getSize().x - 70 - timeComplexityText.getLocalBounds().width;
            float topRightY = 25;
            timeComplexityText.setPosition(topRightX, topRightY);
        }

        // Define a border
        sf::VertexArray border(sf::LinesStrip, 5);
        border[0].position = sf::Vector2f(40, 15);
        border[1].position = sf::Vector2f(window.getSize().x - 40, 15);
        border[2].position = sf::Vector2f(window.getSize().x - 40, window.getSize().y - 20);
        border[3].position = sf::Vector2f(40, window.getSize().y - 20);
        border[4].position = border[0].position;

        for (size_t i = 0; i < border.getVertexCount(); ++i) {
            border[i].color = sf::Color::Green;
        }

        // Main loop for the completion screen
        while (window.isOpen() && appState == AppState::COMPLETION) {
            // Event handling
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Return to home screen
                        appState = AppState::SELECTION_SCREEN;
                        return;
                    }
                }
            }

            // Drawing code
            window.clear();

            if (this->timeComplexity != "null") {
                window.draw(timeComplexityText);
            }

            window.draw(border);

            // Render the final sorted state
            renderState(this->states.back());

            // Display the completion message with green text
            sf::Text completionText("Sorting complete!", font, 40);
            completionText.setFillColor(sf::Color::Green); // Set text color to green
            completionText.setPosition(
                (window.getSize().x - completionText.getLocalBounds().width) / 2,
                10
            );
            window.draw(completionText);

            // Draw only the "Home" button
            window.draw(quitButton);
            window.draw(quitText);

            window.display();

            // Add a small delay
            sf::sleep(sf::milliseconds(this->speed));
        }
    }

    void SortVisualizer::prepareSorting() {
        // Generate input array
        std::vector<int> input_array;
        algorithm::randomNumberGen(input_array, this->size, 1, 100);

        // Run the selected sorting algorithm and collect steps
        std::vector<std::vector<int>> sortingSteps;
        switch (sortType) {
            case algorithm::SortType::MERGE:
                algorithm::iterMergeSort(input_array, [&sortingSteps](const std::vector<int>& step){
                    sortingSteps.push_back(step);
                });
                break;
            case algorithm::SortType::QUICK:
                algorithm::iterQuickSort(input_array, [&sortingSteps](const std::vector<int>& step){
                    sortingSteps.push_back(step);
                });
                break;
            case algorithm::SortType::BUBBLE:
                algorithm::bubbleSort(input_array, [&sortingSteps](const std::vector<int>& step){
                    sortingSteps.push_back(step);
                });
                break;
            case algorithm::SortType::SELECTION:
                algorithm::selectionSort(input_array, [&sortingSteps](const std::vector<int>& step){
                    sortingSteps.push_back(step);
                });
                break;
            case algorithm::SortType::INSERTION:
                algorithm::insertionSort(input_array, [&sortingSteps](const std::vector<int>& step){
                    sortingSteps.push_back(step);
                });
                break;
            case algorithm::SortType::BOGO:
                algorithm::bogoSort(input_array, [&sortingSteps](const std::vector<int>& step){
                    sortingSteps.push_back(step);
                });
                break;
            case algorithm::SortType::STD:
                std::sort(input_array.begin(), input_array.end(), [&sortingSteps, &input_array](int a, int b) {
                    sortingSteps.push_back(input_array);
                    return a < b;
                });
                break;
            case algorithm::SortType::UNINITIALIZED:
                break;
        }

        // Clear previous states and steps
        this->states.clear();
        this->currentStep = 0;
        this->isPaused = false;

        // Add the steps to the visualizer
        for (const auto& step : sortingSteps) {
            this->addState(step);
        }
    }

    void SortVisualizer::visualizeSortingSteps() {
        sf::Event event;

        sf::Text heading(this->heading, font, 40);
        heading.setFillColor(sf::Color::Yellow);
        heading.setPosition(
            (window.getSize().x - heading.getLocalBounds().width) / 2,
            10
        );

        // Stop button
        sf::RectangleShape stopButton(sf::Vector2f(80, 40));
        stopButton.setPosition(50, 20);
        stopButton.setFillColor(sf::Color::Red);

        sf::Text stopText("Stop", font, 20);
        stopText.setFillColor(sf::Color::White);
        stopText.setPosition(57, 25);

        // Play button
        sf::RectangleShape playButton(sf::Vector2f(80, 40));
        playButton.setPosition(50, 20);
        playButton.setFillColor(sf::Color::Green);

        sf::Text playText("Play", font, 20);
        playText.setFillColor(sf::Color::Black);
        playText.setPosition(57, 25);

        // Undo button
        sf::RectangleShape undoButton(sf::Vector2f(80, 40));
        undoButton.setPosition(130, 20);
        undoButton.setFillColor(sf::Color::Yellow);

        sf::Text undoText("Undo", font, 20);
        undoText.setFillColor(sf::Color::Black);
        undoText.setPosition(137, 25);

        // Quit button
        sf::RectangleShape quitButton(sf::Vector2f(80, 40));
        quitButton.setPosition(180, 20);
        quitButton.setFillColor(sf::Color::Blue);

        sf::Text quitText("Home", font, 20);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(187, 25);

        // Time complexity text
        sf::Text timeComplexityText;
        if (this->timeComplexity != "null") {
            timeComplexityText.setFont(font);
            timeComplexityText.setString(this->timeComplexity);
            timeComplexityText.setCharacterSize(40);
            timeComplexityText.setFillColor(sf::Color::White);

            float topRightX = window.getSize().x - 70 - timeComplexityText.getLocalBounds().width;
            float topRightY = 25;
            timeComplexityText.setPosition(topRightX, topRightY);
        }

        // Define a border
        sf::VertexArray border(sf::LinesStrip, 5);
        border[0].position = sf::Vector2f(40, 15);
        border[1].position = sf::Vector2f(window.getSize().x - 40, 15);
        border[2].position = sf::Vector2f(window.getSize().x - 40, window.getSize().y - 20);
        border[3].position = sf::Vector2f(40, window.getSize().y - 20);
        border[4].position = border[0].position;

        for (size_t i = 0; i < border.getVertexCount(); ++i) {
            border[i].color = sf::Color::Yellow;
        }

        while (window.isOpen() && appState == RUNNING) {
            // **Event Handling**
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // **Handle Quit Button Click**
                    if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        appState = SELECTION_SCREEN;
                        return;
                    }

                    // **Handle Based on State**
                    if (this->isPaused) {
                        if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            this->isPaused = false;
                        } else if (undoButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            if (currentStep > 0) {
                                currentStep--;
                            }
                        }
                    } else {
                        if (stopButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            this->isPaused = true;
                        }
                    }
                }
            }

            window.clear();

            if (this->timeComplexity != "null") {
                window.draw(timeComplexityText);
            }
            window.draw(border);
            window.draw(heading);

            // **Draw UI Elements Based on State**
            if (this->isPaused) {
                window.draw(playButton);
                window.draw(playText);
                window.draw(undoButton);
                window.draw(undoText);
            } else {
                window.draw(stopButton);
                window.draw(stopText);
            }
            window.draw(quitButton);
            window.draw(quitText);

            // **Render the Current State**
            renderState(states[currentStep]);

            window.display();

            // **Update Simulation Only if Not Paused**
            if (!this->isPaused) {
                sf::sleep(sf::milliseconds(this->speed));
                currentStep++;
                if (currentStep >= states.size()) {
                    appState = COMPLETION;
                }
            }
        }
    }


} // namespace visualizer
