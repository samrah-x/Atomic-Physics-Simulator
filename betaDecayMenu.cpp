#include "betaDecayMenu.hpp"
#include "mainMenu.hpp"

//Button* homeButton = nullptr;

BetaDecayMenu::BetaDecayMenu() {
    parentNucleus = { {500, 300}, {0, 0}, 40.0f, BLUE, true, 0, 0 };
    betaParticle = { {500, 300}, {100, 0}, 20.0f, GREEN, false, 0, 0 };
    decayStarted = false;
    decayOccurred = false;
    isDragging = false;
    startDecayButton = new Button("Graphics/start.png", { 1000, 600 }, 0.5f);
    homeButton = new Button{ "Graphics/home.png", {1150, 550}, 0.1 };
    currentMenu->reset();
}

BetaDecayMenu::~BetaDecayMenu() {
    // Clean up 
    delete homeButton;
    delete startDecayButton;
}

void BetaDecayMenu::update(Vector2 mousePosition, bool mousePressed) {
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

    if (mousePressed && CheckCollisionPointCircle(mousePosition, parentNucleus.position, parentNucleus.radius)) {
        isDragging = true;
        dragOffset = { mousePosition.x - parentNucleus.position.x, mousePosition.y - parentNucleus.position.y };
    }

    if (isDragging) {
        parentNucleus.position = { mousePosition.x - dragOffset.x, mousePosition.y - dragOffset.y };
        if (!mousePressed) isDragging = false;
    }

    if (startDecayButton->isPressed(mousePosition, mousePressed)) {
        decayStarted = true;
    }
}

void BetaDecayMenu::render() {
    ClearBackground(RAYWHITE);
    // Draw background image
    Vector2 position = { 0.0f, 0.0f };
    Vector2 scale = { (float)GetScreenWidth() / background.width, (float)GetScreenHeight() / background.height };
    DrawTextureEx(background, position, 0.0f, scale.x, WHITE);

    // Display the title
    const char* title = "Beta Decay Simulator";
    int fontSize = 40;
    int screenWidth = GetScreenWidth();
    int textWidth = MeasureText(title, fontSize);
    int titleX = (screenWidth - textWidth) / 2;
    int titleY = 20;
    DrawText(title, titleX, titleY, fontSize, BLACK);

    // draw home button
    homeButton->Draw();

    currentMenu->draw();

    if (parentNucleus.active) {
        DrawCircleV(parentNucleus.position, parentNucleus.radius, parentNucleus.color);
    }
    if (betaParticle.active) {
        DrawCircleV(betaParticle.position, betaParticle.radius, betaParticle.color);
    }
    startDecayButton->Draw();

    DrawText("Press R to reset simulation", 10, 10, 20, DARKGRAY);

    if (IsKeyPressed(KEY_R)) {
        currentMenu->reset();
    }
}

void BetaDecayMenu::updateSimulation(float deltaTime) {
    if (decayStarted && !decayOccurred) {
        betaParticle.active = true;
        betaParticle.position.x += betaParticle.velocity.x * deltaTime;
        if (betaParticle.position.x > GetScreenWidth()) {
            decayOccurred = true;
        }
    }
}

void BetaDecayMenu::draw() {
    if (parentNucleus.active) {
        DrawCircleV(parentNucleus.position, parentNucleus.radius, parentNucleus.color);
    }
    if (betaParticle.active) {
        DrawCircleV(betaParticle.position, betaParticle.radius, betaParticle.color);
    }
}

void BetaDecayMenu::reset() {
    parentNucleus = { {500, 300}, {0, 0}, 40.0f, BLUE, true, 0, 0 };
    betaParticle = { {500, 300}, {100, 0}, 20.0f, GREEN, false, 0, 0 };
    decayStarted = false;
    decayOccurred = false;
    isDragging = false;
}