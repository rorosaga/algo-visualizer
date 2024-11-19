#include "visualizer.h"
#include "resources.h"
#include "algorithm.h"


// for simplicity we created another file to have visualizer2 class methods
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

    SortVisualizer2::SortVisualizer2(int width, int height, int size, int speed)
        : Visualizer<std::vector<int>>(width, height, speed, "Visualizer 2")
        {
            // Initialize derived class member
            this->timeComplexity = "null";
            this->rectWidth=width/(size+10);
            this->spacing=width/(size+10);

            // Load the font after initializing the window
            auto fs = algos_resources::getResourceFile("resources/Pixellettersfull-BnJ5.ttf");
            if (!this->font.loadFromMemory(fs.begin(), fs.size())) {
                std::cerr << "Failed to load font." << std::endl;
            }
        }



    void SortVisualizer2::addState(const std::vector<int>& matrix) {
        this->states.push_back(matrix);
    }

    void SortVisualizer2::renderState(const std::vector<int>& array) {
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

    void SortVisualizer2::showSelectScreen() {
        std::vector<int> input_array;
        algorithm::randomNumberGen(input_array, 300, 1, 100);
        std::vector<std::vector<int>> sortingSteps;


        // Button selections for algos
        sf::RectangleShape mergeButton(sf::Vector2f(100, 50));
        mergeButton.setPosition(50, 50);
        mergeButton.setFillColor(sf::Color::Green);

        sf::Text mergeText("Merge Sort", font, 20);
        mergeText.setFillColor(sf::Color::Black);
        mergeText.setPosition(57, 60);

        sf::RectangleShape quickButton(sf::Vector2f(100, 50));
        quickButton.setPosition(50, 120);
        quickButton.setFillColor(sf::Color::Green);

        sf::Text quickText("Quick Sort", font, 20);
        quickText.setFillColor(sf::Color::Black);
        quickText.setPosition(57, 130);

        sf::RectangleShape bubbleButton(sf::Vector2f(100, 50));
        bubbleButton.setPosition(50, 190);
        bubbleButton.setFillColor(sf::Color::Green);

        sf::Text bubbleText("Bubble Sort", font, 20);
        bubbleText.setFillColor(sf::Color::Black);
        bubbleText.setPosition(57, 200);

        sf::RectangleShape selectionButton(sf::Vector2f(100, 50));
        selectionButton.setPosition(50, 260);
        selectionButton.setFillColor(sf::Color::Green);

        sf::Text selectionText("Selection Sort", font, 20);
        selectionText.setFillColor(sf::Color::Black);
        selectionText.setPosition(57, 270);

        sf::RectangleShape insertionButton(sf::Vector2f(100, 50));
        insertionButton.setPosition(50, 330);
        insertionButton.setFillColor(sf::Color::Green);

        sf::Text insertionText("Insertion Sort", font, 20);
        insertionText.setFillColor(sf::Color::Black);
        insertionText.setPosition(57, 340);

        sf::RectangleShape bogoButton(sf::Vector2f(100, 50));
        bogoButton.setPosition(50, 400);
        bogoButton.setFillColor(sf::Color::Green);

        sf::Text bogoText("Bogo Sort", font, 20);
        bogoText.setFillColor(sf::Color::Black);
        bogoText.setPosition(57, 410);


        window.clear();
        sf::Text selectText("Select a sorting algorithm", font, 40);
        selectText.setFillColor(sf::Color::White);
        selectText.setPosition((window.getSize().x - selectText.getLocalBounds().width) / 2, 10);
        window.draw(selectText);


        // draw all the buttons and their
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
        window.draw(bogoButton);
        window.draw(bogoText);

        window.display();

        // wait for the user to select a sorting algorithm
        sf::Event event;
        while (sortType == algorithm::SortType::UNINITIALIZED) {
            if (window.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (mergeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::MERGE;
                    } else if (quickButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::QUICK;
                    } else if (bubbleButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::BUBBLE;
                    } else if (selectionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::SELECTION;
                    } else if (insertionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::INSERTION;
                    } else if (bogoButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::BOGO;
                    }
                    std::cout << "Sort type selected" << std::endl;
                }
            }
        }

        // Run the selected sorting algorithm
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
            case algorithm::SortType::UNINITIALIZED:
                break;
        }

    }

    void SortVisualizer2::visualize() {
        std::vector<int> input_array;
        algorithm::randomNumberGen(input_array, 300, 1, 100);
        std::vector<std::vector<int>> sortingSteps;

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

        // Buttons and text fot the selection screen
        sf::RectangleShape mergeButton(sf::Vector2f(100, 50));
        mergeButton.setPosition(50, 50);
        mergeButton.setFillColor(sf::Color::Green);

        sf::Text mergeText("Merge Sort", font, 20);
        mergeText.setFillColor(sf::Color::Black);
        mergeText.setPosition(57, 60);

        sf::RectangleShape quickButton(sf::Vector2f(100, 50));
        quickButton.setPosition(50, 120);
        quickButton.setFillColor(sf::Color::Green);

        sf::Text quickText("Quick Sort", font, 20);
        quickText.setFillColor(sf::Color::Black);
        quickText.setPosition(57, 130);

        sf::RectangleShape bubbleButton(sf::Vector2f(100, 50));
        bubbleButton.setPosition(50, 190);
        bubbleButton.setFillColor(sf::Color::Green);

        sf::Text bubbleText("Bubble Sort", font, 20);
        bubbleText.setFillColor(sf::Color::Black);
        bubbleText.setPosition(57, 200);

        sf::RectangleShape selectionButton(sf::Vector2f(100, 50));
        selectionButton.setPosition(50, 260);
        selectionButton.setFillColor(sf::Color::Green);

        sf::Text selectionText("Selection Sort", font, 20);
        selectionText.setFillColor(sf::Color::Black);
        selectionText.setPosition(57, 270);

        sf::RectangleShape insertionButton(sf::Vector2f(100, 50));
        insertionButton.setPosition(50, 330);
        insertionButton.setFillColor(sf::Color::Green);

        sf::Text insertionText("Insertion Sort", font, 20);
        insertionText.setFillColor(sf::Color::Black);
        insertionText.setPosition(57, 340);

        sf::RectangleShape bogoButton(sf::Vector2f(100, 50));
        bogoButton.setPosition(50, 400);
        bogoButton.setFillColor(sf::Color::Green);

        sf::Text bogoText("Bogo Sort", font, 20);
        bogoText.setFillColor(sf::Color::Black);
        bogoText.setPosition(57, 410);

        while (window.isOpen()) {
            std::cout << "Window open" << std::endl;
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

            sf::Text instructions("Press any key to start", font, 20);
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


            // select sorting algorithm
            std::cout << "Select algo screen" << std::endl;
            window.clear();
            sf::Text selectText("Select a sorting algorithm", font, 40);
            selectText.setFillColor(sf::Color::White);
            selectText.setPosition((window.getSize().x - selectText.getLocalBounds().width) / 2, 10);
            window.draw(selectText);


            // draw all the buttons and their
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
            window.draw(bogoButton);
            window.draw(bogoText);

            window.display();

            // wait for the user to select a sorting algorithm
            std::cout << "waiting for selection" << std::endl;
            while (this->sortType == algorithm::SortType::UNINITIALIZED) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (mergeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::MERGE;
                        break;
                    } else if (quickButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::QUICK;
                        break;
                    } else if (bubbleButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::BUBBLE;
                        break;
                    } else if (selectionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::SELECTION;
                        break;
                    } else if (insertionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::INSERTION;
                        break;
                    } else if (bogoButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->sortType = algorithm::SortType::BOGO;
                        break;
                    }
                }
            }

            std::cout << "Sort type selected" << std::endl;

            // Run the selected sorting algorithm
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
            }

            for (const auto& step : sortingSteps) {
                this->addState(step);
            }
            std::cout << "steps added" << std::endl;

            // Show the sorting visualization
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

} // namespace visualizer
