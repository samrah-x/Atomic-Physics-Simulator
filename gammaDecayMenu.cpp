#include "gammaDecayMenu.hpp"
#include "mainMenu.hpp"
#include "raylib.h"

inline Vector2 Vector2Subtract(Vector2 v1, Vector2 v2) {
    return Vector2 { v1.x - v2.x, v1.y - v2.y };
}

Button* homeButton = nullptr;
//Button* startButton = nullptr;

GammaDecayMenu::GammaDecayMenu() {
    parentNucleus = { {600, 300}, {0, 0}, 40.0f, BLUE, true, 0, 0 };
    gammaRay = { {600, 300}, {200, 0}, 5.0f, YELLOW, false, 0, 0 };
    decayOccurred = false;
    homeButton = new Button{ "Graphics/home.png", {1150, 550}, 0.1 };
    currentMenu->reset();
}

GammaDecayMenu::~GammaDecayMenu() {
    // Clean up 
    delete homeButton;
}

void GammaDecayMenu::update(Vector2 mousePosition, bool mousePressed) {
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

    if (dragging) {
        if (mousePressed) {
            parentNucleus.position = mousePosition;
        }
        else {
            dragging = false;
        }
    }
    else if (CheckCollisionPointCircle(mousePosition, parentNucleus.position, parentNucleus.radius)) {
        if (mousePressed) {
            dragging = true;
            offset = Vector2Subtract(parentNucleus.position, mousePosition);
        }
    }

    if (IsKeyPressed(KEY_SPACE)) {
        decayOccurred = true;
    }

}

void GammaDecayMenu::render() {
    ClearBackground(RAYWHITE);
    // Draw background image
    Vector2 position = { 0.0f, 0.0f };
    Vector2 scale = { (float)GetScreenWidth() / background.width, (float)GetScreenHeight() / background.height };
    DrawTextureEx(background, position, 0.0f, scale.x, WHITE);

    // Display the title
    const char* title = "Gamma Decay Simulator";
    int fontSize = 40;
    int screenWidth = GetScreenWidth();
    int textWidth = MeasureText(title, fontSize);
    int titleX = (screenWidth - textWidth) / 2;
    int titleY = 20;
    DrawText(title, titleX, titleY, fontSize, BLACK);

    // draw home button
    homeButton->Draw();

    currentMenu->draw();

    DrawText("Drag the nucleus and press SPACE to start decay", 10, 60, 20, GRAY);

    // Draw the parent nucleus
    DrawCircleV(parentNucleus.position, parentNucleus.radius, parentNucleus.color);

    // Draw the gamma ray if decay occurred
    if (decayOccurred) {
        DrawCircleV(gammaRay.position, gammaRay.radius, gammaRay.color);
    }

    DrawText("Press R to reset simulation", 10, 10, 20, DARKGRAY);

    if (IsKeyPressed(KEY_R)) {
        currentMenu->reset();
    }
}

void GammaDecayMenu::updateSimulation(float deltaTime) {
    if (decayOccurred) {
        gammaRay.position.x += gammaRay.velocity.x * deltaTime;
        gammaRay.position.y += gammaRay.velocity.y * deltaTime;
    }
}

void GammaDecayMenu::draw() {
    if (parentNucleus.active) {
        DrawCircleV(parentNucleus.position, parentNucleus.radius, parentNucleus.color);
    }
    if (gammaRay.active) {
        DrawCircleV(gammaRay.position, gammaRay.radius, gammaRay.color);
    }
}

void GammaDecayMenu::reset() {
    // Initialize parent nucleus
    parentNucleus.position = { 600, 300 };
    parentNucleus.velocity = { 0, 0 };
    parentNucleus.radius = 40.0f;
    parentNucleus.color = BLUE;
    parentNucleus.active = true;

    // Initialize gamma ray
    gammaRay.position = parentNucleus.position;
    gammaRay.velocity = { 200, 0 };
    gammaRay.radius = 5.0f;
    gammaRay.color = YELLOW;
    gammaRay.active = true;

    decayOccurred = false;
    dragging = false;
}