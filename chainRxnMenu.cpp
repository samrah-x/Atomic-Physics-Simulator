#include "chainRxnMenu.hpp"
#include "mainMenu.hpp"
#include <iostream>

// Constructor for ChainRxnMenu
ChainRxnMenu::ChainRxnMenu() {
    // Initialize atoms and neutrons
    for (int i = 0; i < 2; ++i) {
        Particle uranium = { {300 + i * 300, 300}, {0, 0}, 40.0f, BLUE, true, 0, 0 };
        uraniumAtoms.push_back(uranium);
    }
    Particle neutron = { {100, 300}, {200, 0}, 9.0f, RED, true, 0, 0 };
    neutrons.push_back(neutron);

    collisionOccurred = false;
    chainCount = 0;

    // Initialize buttons using smart pointers
    homeButton = std::make_unique<Button>("Graphics/home.png", Vector2{ 1150, 550 }, 0.1f);
    startButton = std::make_unique<Button>("Graphics/start.png", Vector2{ 1150, 450 }, 0.1f);

    simulationStarted = false;

    currentMenu->reset();

    std::cout << "ChainRxnMenu initialized." << std::endl;
}

// Destructor for ChainRxnMenu
ChainRxnMenu::~ChainRxnMenu() {
    std::cout << "ChainRxnMenu destroyed." << std::endl;
}

// Update function for ChainRxnMenu
void ChainRxnMenu::update(Vector2 mousePosition, bool mousePressed) {
    bool isHoveringAnyButton = false;
    if (homeButton && homeButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (startButton && startButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (isHoveringAnyButton) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (startButton && startButton->isPressed(mousePosition, mousePressed)) {
        std::cout << "Start button pressed, starting simulation." << std::endl;
        simulationStarted = true;
    }

    if (homeButton && homeButton->isPressed(mousePosition, mousePressed)) {
        std::cout << "Home button pressed, switching to main menu." << std::endl;
        // Transition to the main menu
        currentMenu = std::make_unique<MainMenu>();
        //currentMenu->reset();
    }

}

// Render function for ChainRxnMenu
void ChainRxnMenu::render() {
    ClearBackground(RAYWHITE);

    // Draw background image
    Vector2 position = { 0.0f, 0.0f };
    Vector2 scale = { (float)GetScreenWidth() / background.width, (float)GetScreenHeight() / background.height };
    DrawTextureEx(background, position, 0.0f, scale.x, WHITE);

    // Display the title
    const char* title = "Chain Reaction Simulator";
    int fontSize = 40;
    int screenWidth = GetScreenWidth();
    int textWidth = MeasureText(title, fontSize);
    int titleX = (screenWidth - textWidth) / 2;
    int titleY = 20;
    DrawText(title, titleX, titleY, fontSize, BLACK);

    // Draw buttons
    homeButton->Draw();
    startButton->Draw();
    currentMenu->draw();
    

    DrawText("Press R to reset simulation", 10, 10, 20, DARKGRAY);

    if (IsKeyPressed(KEY_R)) {
        std::cout << "Resetting simulation." << std::endl;
        reset();
    }
}

// UpdateSimulation function for ChainRxnMenu
void ChainRxnMenu::updateSimulation(float deltaTime) {
    if (!simulationStarted) return; // Do not update if simulation has not started

    for (auto& neutron : neutrons) {
        if (neutron.active) {
            neutron.position.x += neutron.velocity.x * deltaTime;
            neutron.position.y += neutron.velocity.y * deltaTime;

            for (auto& uranium : uraniumAtoms) {
                float distance = sqrt(pow(neutron.position.x - uranium.position.x, 2) +
                    pow(neutron.position.y - uranium.position.y, 2));

                if (distance < (uranium.radius + neutron.radius) && uranium.active) {
                    neutron.active = false;
                    uranium.active = false;
                    chainCount++;

                    // Create fission products
                    for (int i = 0; i < 2; ++i) {
                        Particle fragment = { uranium.position, {0, 0}, 20.0f, ORANGE, true, 0, 0 };
                        fissionProducts.push_back(fragment);
                    }

                    // Create equally spaced new neutrons heading right
                    for (int i = 0; i < 3; ++i) {
                        Particle newNeutron = { uranium.position, {200, (i - 1) * 50}, 9.0f, RED, true, 0, 0 };
                        neutrons.push_back(newNeutron);
                    }
                }
            }
        }
    }

    // Update fission products and neutrons
    for (auto& product : fissionProducts) {
        product.position.x += product.velocity.x * deltaTime;
        product.position.y += product.velocity.y * deltaTime;
    }
    for (auto& neutron : neutrons) {
        if (neutron.active) {
            neutron.position.x += neutron.velocity.x * deltaTime;
            neutron.position.y += neutron.velocity.y * deltaTime;
        }
    }
}

// Draw function for ChainRxnMenu
void ChainRxnMenu::draw() {
    for (const auto& uranium : uraniumAtoms) {
        if (uranium.active) {
            DrawCircleV(uranium.position, uranium.radius, uranium.color);
        }
    }
    for (const auto& neutron : neutrons) {
        if (neutron.active) {
            DrawCircleV(neutron.position, neutron.radius, neutron.color);
        }
    }
    for (const auto& product : fissionProducts) {
        DrawCircleV(product.position, product.radius, product.color);
    }
}

// Reset function for ChainRxnMenu
void ChainRxnMenu::reset() {
    uraniumAtoms.clear();
    neutrons.clear();
    fissionProducts.clear();

    for (int i = 0; i < 2; ++i) {
        Particle uranium = { {300 + i * 300, 300}, {0, 0}, 40.0f, BLUE, true, 0, 0 };
        uraniumAtoms.push_back(uranium);
    }

    Particle neutron = { {100, 300}, {200, 0}, 9.0f, RED, true, 0, 0 };
    neutrons.push_back(neutron);

    collisionOccurred = false;
    chainCount = 0;
    simulationStarted = false; // Reset the flag for simulation
}