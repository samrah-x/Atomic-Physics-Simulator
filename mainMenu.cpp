#include "MainMenu.hpp"
#include "fissionMenu.hpp"
#include "fusionMenu.hpp"
#include "chainRxnMenu.hpp"
#include "alphaDecayMenu.hpp"
#include "betaDecayMenu.hpp"
#include "gammaDecayMenu.hpp"
#include <iostream>

// Define the variables here, not just declare them
Button* alphaDecayButton = nullptr;
Button* betaDecayButton = nullptr;
Button* gammaDecayButton = nullptr;
Button* fissionButton = nullptr;
Button* fusionButton = nullptr;
Button* chainRxnButton = nullptr;
Texture2D background = {};  // Initialize as an empty Texture2D

MainMenu::MainMenu() {
    background = LoadTexture("Graphics/b4.jpeg");
    fissionButton = new Button{ "Graphics/fission.png", {775, 70}, 0.25 };
    fusionButton = new Button{ "Graphics/fusion.png", {1025, 70}, 0.25 };
    chainRxnButton = new Button{ "Graphics/chain.png", {775, 265}, 0.25 };
    alphaDecayButton = new Button{ "Graphics/alpha.png", {1025, 265}, 0.25 };
    betaDecayButton = new Button{ "Graphics/beta.png", {775, 460}, 0.25 };
    gammaDecayButton = new Button{ "Graphics/gamma.png", {1025, 460}, 0.25 };

       // Set up the action when each button is pressed
    fissionButton->setOnPressAction([]() {
        std::cout << "Opening Fission Menu..." << std::endl;
        currentMenu = std::make_unique<fissionMenu>();
        });

    fusionButton->setOnPressAction([]() {
        std::cout << "Opening Fusion Menu..." << std::endl;
        currentMenu = std::make_unique<FusionMenu>();
        });

    chainRxnButton->setOnPressAction([]() {
        std::cout << "Opening Chain Reaction Menu..." << std::endl;
        currentMenu = std::make_unique<ChainRxnMenu>();
        });

    alphaDecayButton->setOnPressAction([]() {
        std::cout << "Opening Alpha Decay Menu..." << std::endl;
        currentMenu = std::make_unique<AlphaDecayMenu>();
        });

    betaDecayButton->setOnPressAction([]() {
        std::cout << "Opening Beta Decay Menu..." << std::endl;
        currentMenu = std::make_unique<BetaDecayMenu>();
        });

    gammaDecayButton->setOnPressAction([]() {
        std::cout << "Opening Gamma Decay Menu..." << std::endl;
        currentMenu = std::make_unique<GammaDecayMenu>();
        });

    std::cout << "MainMenu initialized" << std::endl;
}

MainMenu::~MainMenu() {
    // Clean up
    delete fissionButton;
    delete fusionButton;
    delete chainRxnButton;
    delete alphaDecayButton;
    delete betaDecayButton;
    delete gammaDecayButton;
    //delete homeButton;
    std::cout << "MainMenu deconstructed" << std::endl;

}

void MainMenu::update(Vector2 mousePosition, bool mousePressed) {
    bool isHoveringAnyButton = false;
    std::cout << "MainMenu update" << std::endl;

    // Update cursor for each button
    if (fissionButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (fusionButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (chainRxnButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (alphaDecayButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (betaDecayButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (gammaDecayButton->updateCursor(mousePosition)) isHoveringAnyButton = true;

    // Set cursor based on hover state
    if (isHoveringAnyButton) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    // Check if a button is being pressed
    if (fissionButton->isPressed(mousePosition, mousePressed)) fissionButton->press();
    if (fusionButton->isPressed(mousePosition, mousePressed)) fusionButton->press();
    if (chainRxnButton->isPressed(mousePosition, mousePressed)) chainRxnButton->press();
    if (alphaDecayButton->isPressed(mousePosition, mousePressed)) alphaDecayButton->press();
    if (betaDecayButton->isPressed(mousePosition, mousePressed)) betaDecayButton->press();
    if (gammaDecayButton->isPressed(mousePosition, mousePressed)) gammaDecayButton->press();
    //if (homeButton->isPressed(mousePosition, mousePressed)) homeButton->press();
}

void MainMenu::render() {
    std::cout << "MainMenu rendered" << std::endl;

    ClearBackground(BLACK);

    // Draw background image
    Vector2 position = { 0.0f, 0.0f };
    Vector2 scale = { (float)GetScreenWidth() / background.width, (float)GetScreenHeight() / background.height };
    DrawTextureEx(background, position, 0.0f, scale.x, WHITE);

    // Display the title
    const char* title = "Atomic\nPhysics\nSimulator";
    int fontSize = 90;
    int screenWidth = GetScreenWidth();
    int textWidth = MeasureText(title, fontSize);
    int titleX = (screenWidth - textWidth - 500) / 2;
    int titleY = 190;
    DrawText(title, titleX, titleY, fontSize, BLACK);

    // Draw buttons
    fissionButton->Draw();
    fusionButton->Draw();
    chainRxnButton->Draw();
    alphaDecayButton->Draw();
    betaDecayButton->Draw();
    gammaDecayButton->Draw();
}

void MainMenu::updateSimulation(float deltaTime)
{
}

void MainMenu::draw()
{
}

void MainMenu::reset()
{
}
