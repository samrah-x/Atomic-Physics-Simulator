// game.cpp

#include "game.hpp"
#include "raylib.h"
#include <iostream>

using namespace std;

// Global variables
Texture2D background;
Button* fissionButton;
Button* fusionButton;
Button* chainRxnButton;
Button* alphaDecayButton;
Button* betaDecayButton;
Button* gammaDecayButton;
Button* homeButton;;

void init() {
    InitWindow(1250, 650, "Atomic Physics Simulator");

    SetTargetFPS(60);

    background = LoadTexture("Graphics/b4.jpeg");
    fissionButton = new Button{ "Graphics/fission.png", { 775, 70 }, 0.25 };
    fusionButton = new Button{ "Graphics/fusion.png", { 1025, 70 }, 0.25 };
    chainRxnButton = new Button{ "Graphics/chain.png", { 775, 265 }, 0.25 };
    alphaDecayButton = new Button{ "Graphics/alpha.png", { 1025, 265 }, 0.25 };
    betaDecayButton = new Button{ "Graphics/beta.png", { 775, 460 }, 0.25 };
    gammaDecayButton = new Button{ "Graphics/gamma.png", { 1025, 460 }, 0.25 };
    homeButton = new Button{ "Graphics/home.png", { 1025, 70 }, 0.25 };

    // Set up the action when each button is pressed
    fissionButton->setOnPressAction([]() {
        // Action for fission button (e.g., open a menu or perform an operation)
        cout << "Opening Fission Menu..." << endl;
        });

    fusionButton->setOnPressAction([]() {
        // Action for fusion button
        cout << "Opening Fusion Menu..." << endl;
        });

    chainRxnButton->setOnPressAction([]() {
        // Action for fusion button
        cout << "Opening Chain Rxn Menu..." << endl;
        });

    alphaDecayButton->setOnPressAction([]() {
        // Action for fusion button
        cout << "Opening Alpha Decay Menu..." << endl;
        });

    betaDecayButton->setOnPressAction([]() {
        // Action for fusion button
        cout << "Opening Beta Decay Menu..." << endl;
        });

    gammaDecayButton->setOnPressAction([]() {
        // Action for fusion button
        cout << "Opening Gamma Decay Menu..." << endl;
        });

    homeButton->setOnPressAction([]() {
        cout << "Opening Home Menu..." << endl;
        });
}

void runGame() 
{
    while (!WindowShouldClose()) 
    {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Update buttons
        updateButtons(mousePosition, mousePressed);

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);
        drawHomeScreen();
        EndDrawing();
    }
}

void updateButtons(Vector2 mousePosition, bool mousePressed) 
{
    bool isHoveringAnyButton = false;

    // update cursor for each button
    // if it iis colliding, change flag to true
    if (fissionButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (fusionButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (chainRxnButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (alphaDecayButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (betaDecayButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (gammaDecayButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (homeButton->updateCursor(mousePosition)) isHoveringAnyButton = true;

    // set cursor based on hover state
    if (isHoveringAnyButton)
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    // check if a button is being pressed 
    if (fissionButton->isPressed(mousePosition, mousePressed)) fissionButton->press();
    if (fusionButton->isPressed(mousePosition, mousePressed)) fusionButton->press();
    if (chainRxnButton->isPressed(mousePosition, mousePressed)) chainRxnButton->press();
    if (alphaDecayButton->isPressed(mousePosition, mousePressed)) alphaDecayButton->press();
    if (betaDecayButton->isPressed(mousePosition, mousePressed)) betaDecayButton->press();
    if (gammaDecayButton->isPressed(mousePosition, mousePressed)) gammaDecayButton->press();
    if (homeButton->isPressed(mousePosition, mousePressed)) homeButton->press();
}

void drawHomeScreen() 
{
    Vector2 position = { 0.0f, 0.0f };
    Vector2 scale = { (float)GetScreenWidth() / background.width, (float)GetScreenHeight() / background.height };
    DrawTextureEx(background, position, 0.0f, scale.x, WHITE);

    // display the title
    const char* title = "Atomic\nPhysics\nSimulator";
    int fontSize = 90;
    int screenWidth = GetScreenWidth();
    int textWidth = MeasureText(title, fontSize);
    int titleX = (screenWidth - textWidth - 500) / 2;
    int titleY = 190;
    DrawText(title, titleX, titleY, fontSize, BLACK);

    // draw all the buttons
    fissionButton->Draw();
    fusionButton->Draw();
    chainRxnButton->Draw();
    alphaDecayButton->Draw();
    betaDecayButton->Draw();
    gammaDecayButton->Draw();
}
