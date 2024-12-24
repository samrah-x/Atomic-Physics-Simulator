// FissionMenu.cpp
#include "fissionMenu.hpp"
#include "mainMenu.hpp"

Button* homeButton = nullptr;


fissionMenu::fissionMenu()
{
    homeButton = new Button{ "Graphics/home.png", {1150, 550}, 0.1 };
    
    /*atoms.push_back(Atom({ 100, 100 }, "Graphics/Uranium236.png"));
    neutrons.push_back(Neutron({ 200, 150 }, "Graphics/neutron.png"));*/
}

fissionMenu::~fissionMenu()
{
    // clean up
    delete homeButton;
}

void fissionMenu::update(Vector2 mousePosition, bool mousePressed) 
{
    // updating if cursor is on home button
    bool isHoveringAnyButton = false;
    if (homeButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    // Set cursor based on hover state
    if (isHoveringAnyButton) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    // going to main menu if home button pressed
    if (homeButton->isPressed(mousePosition, mousePressed)) {
        currentMenu = std::make_unique<MainMenu>();
    }

    //// Update atoms
    //for (auto& atom : atoms) {
    //    atom.update(mousePosition, mousePressed);  // Handle atom dragging
    //}

    //// Update neutrons (for simplicity, we'll just move them around here)
    //for (auto& neutron : neutrons) {
    //    Vector2 neutronMove = { neutron.position.x + 1, neutron.position.y };  // Example of moving the neutron
    //    neutron.update(neutronMove);

    //    // Check for neutron collision with atoms
    //    for (auto& atom : atoms) {
    //        atom.bombardedWithNeutron(neutron.position);  // Check if neutron bombards the atom
    //    }
    //}
}

void fissionMenu::render()
{
    ClearBackground(BLACK);

    // Draw background image
    Vector2 position = { 0.0f, 0.0f };
    Vector2 scale = { (float)GetScreenWidth() / background.width, (float)GetScreenHeight() / background.height };
    DrawTextureEx(background, position, 0.0f, scale.x, WHITE);

    // Display the title
    const char* title = "Fission Reaction Simulator";
    int fontSize = 40;
    int screenWidth = GetScreenWidth();
    int textWidth = MeasureText(title, fontSize);
    int titleX = (screenWidth - textWidth) / 2;
    int titleY = 20;
    DrawText(title, titleX, titleY, fontSize, BLACK);

    // draw home button
    homeButton->Draw();

    //// Render atoms
    //for (auto& atom : atoms) 
    //    atom.draw();

    //// Render neutrons
    //for (auto& neutron : neutrons) 
    //    neutron.draw();        
}
