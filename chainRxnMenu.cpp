#include "chainRxnMenu.hpp"
#include "mainMenu.hpp"

//Button* homeButton = nullptr;

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
    homeButton = new Button{ "Graphics/home.png", {1150, 550}, 0.1 };
    currentMenu->reset();
}

ChainRxnMenu::~ChainRxnMenu() {
    // Clean up 
    delete homeButton;
}

void ChainRxnMenu::update(Vector2 mousePosition, bool mousePressed) {
    bool isHoveringAnyButton = false;
    if (homeButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (isHoveringAnyButton) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (homeButton->isPressed(mousePosition, mousePressed)) {
        currentMenu = std::make_unique<MainMenu>();
    }
}

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

    // draw home button
    homeButton->Draw();

    currentMenu->draw();

    DrawText("Press R to reset simulation", 10, 10, 20, DARKGRAY);

    if (IsKeyPressed(KEY_R)) {
        currentMenu->reset();
    }
}

void ChainRxnMenu::updateSimulation(float deltaTime) {
    if (chainCount < 2) {
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
    }
    else {
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
}

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
}