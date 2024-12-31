#include "fusionmenu.hpp"
#include "mainMenu.hpp"

//Button* homeButton = nullptr;

FusionMenu::FusionMenu() {
    // Initialize particles
    hydrogen1 = { {100, 300}, {100, 0}, 20.0f, BLUE, true, 0, 0 };
    hydrogen2 = { {1100, 300}, {-100, 0}, 20.0f, BLUE, true, 0, 0 };
    collisionOccurred = false;
    homeButton = new Button{ "Graphics/home.png", {1150, 550}, 0.1 };
    currentMenu->reset();
}

FusionMenu::~FusionMenu() {
    // Clean up 
    delete homeButton;
}

void FusionMenu::update(Vector2 mousePosition, bool mousePressed) {
    // Update logic for the Fusion Menu
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

void FusionMenu::render() {
    ClearBackground(RAYWHITE);
    // Draw background image
    Vector2 position = { 0.0f, 0.0f };
    Vector2 scale = { (float)GetScreenWidth() / background.width, (float)GetScreenHeight() / background.height };
    DrawTextureEx(background, position, 0.0f, scale.x, WHITE);

    // Display the title
    const char* title = "Fusion Reaction Simulator";
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

void FusionMenu::updateSimulation(float deltaTime) {
    if (!collisionOccurred) {
        // Update hydrogen positions
        hydrogen1.position.x += hydrogen1.velocity.x * deltaTime;
        hydrogen2.position.x += hydrogen2.velocity.x * deltaTime;

        // Check for collision
        float distance = sqrt(pow(hydrogen1.position.x - hydrogen2.position.x, 2) +
            pow(hydrogen1.position.y - hydrogen2.position.y, 2));

        if (distance < (hydrogen1.radius + hydrogen2.radius) && hydrogen1.active && hydrogen2.active) {
            collisionOccurred = true;
            hydrogen1.active = false;
            hydrogen2.active = false;

            // Create fusion product and emitted neutrons
            Particle fusionProduct = { {600, 300}, {0, 0}, 25.0f, ORANGE, true, 0, 0 };
            fusionProducts.push_back(fusionProduct);

            for (int i = 0; i < 1; ++i) {
                Particle neutron = { {600, 300}, {static_cast<float>(rand() % 201 - 100), static_cast<float>(rand() % 201 - 100)}, 5.0f, GRAY, true, 0, 0 };
                emittedNeutrons.push_back(neutron);
            }
        }
    }
    else {
        // Update emitted neutrons
        for (auto& neutron : emittedNeutrons) {
            neutron.position.x += neutron.velocity.x * deltaTime;
            neutron.position.y += neutron.velocity.y * deltaTime;
        }
    }
}

void FusionMenu::draw() {
    if (hydrogen1.active) {
        DrawCircleV(hydrogen1.position, hydrogen1.radius, hydrogen1.color);
    }
    if (hydrogen2.active) {
        DrawCircleV(hydrogen2.position, hydrogen2.radius, hydrogen2.color);
    }
    for (const auto& product : fusionProducts) {
        DrawCircleV(product.position, product.radius, product.color);
    }
    for (const auto& neutron : emittedNeutrons) {
        DrawCircleV(neutron.position, neutron.radius, neutron.color);
    }
}

void FusionMenu::reset() {
    hydrogen1 = { {100, 300}, {100, 0}, 20.0f, BLUE, true, 0, 0 };
    hydrogen2 = { {1100, 300}, {-100, 0}, 20.0f, BLUE, true, 0, 0 };
    fusionProducts.clear();
    emittedNeutrons.clear();
    collisionOccurred = false;
}