// FissionMenu.cpp
#include "fissionMenu.hpp"
#include "mainMenu.hpp"



fissionMenu::fissionMenu()
{
    // Initialize buttons using smart pointers
    homeButton = std::make_unique<Button>("Graphics/home.png", Vector2{ 1150, 550 }, 0.1f);
    startButton = std::make_unique<Button>("Graphics/start.png", Vector2{ 1150, 450 }, 0.1f);
    currentMenu->reset();
    
}

fissionMenu::~fissionMenu()
{
    // no clean up for smart pointer
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
    //currentMenu->updateSimulation(GetFrameTime());

    ClearBackground(RAYWHITE);

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
    startButton->Draw();
    currentMenu->draw();

    DrawText("Press R to reset simulation", 10, 10, 20, DARKGRAY);

    if (IsKeyPressed(KEY_R)) {
        currentMenu->reset();
    }

    //// Render atoms
    //for (auto& atom : atoms) 
    //    atom.draw();

    //// Render neutrons
    //for (auto& neutron : neutrons) 
    //    neutron.draw();        
}

void fissionMenu::updateSimulation(float deltaTime)
{
    if (!collisionOccurred) {
        // Update neutron position
        neutron.position.x += neutron.velocity.x * deltaTime;
        neutron.position.y += neutron.velocity.y * deltaTime;

        // Check for collision
        float distance = sqrt(pow(neutron.position.x - uranium.position.x, 2) +
            pow(neutron.position.y - uranium.position.y, 2));

        if (distance < (uranium.radius + neutron.radius) && neutron.active) {
            collisionOccurred = true;
            neutron.active = false;
            vibrationTime = 0;
        }
    }
    else {
        vibrationTime += deltaTime;

        if (vibrationTime < VIBRATION_DURATION) {
            // Vibration phase
            uranium.vibrationPhase += 10.0f * deltaTime;
            uranium.vibrationAmplitude = 10.0f * (1.0f - vibrationTime / VIBRATION_DURATION);
        }
        else if (uranium.active) {
            // Split the uranium
            uranium.active = false;

            // Create two fission products
            Particle fragment1 = {
                uranium.position,
                {-SPLIT_VELOCITY, 0},
                uranium.radius / 2,
                ORANGE,
                true,
                0,
                0
            };

            Particle fragment2 = {
                uranium.position,
                {SPLIT_VELOCITY, 0},
                uranium.radius / 2,
                ORANGE,
                true,
                0,
                0
            };

            fissionProducts.push_back(fragment1);
            fissionProducts.push_back(fragment2);
        }

        // Update fission products
        for (auto& product : fissionProducts) {
            product.position.x += product.velocity.x * deltaTime;
            product.position.y += product.velocity.y * deltaTime;
        }
    }
}

void fissionMenu::draw()
{
    if (neutron.active) {
        DrawCircleV(neutron.position, neutron.radius, neutron.color);
    }

    if (uranium.active) {
        Vector2 vibPos = uranium.position;
        if (collisionOccurred) {
            vibPos.x += sin(uranium.vibrationPhase) * uranium.vibrationAmplitude;
        }
        DrawCircleV(vibPos, uranium.radius, uranium.color);
    }

    for (const auto& product : fissionProducts) {
        DrawCircleV(product.position, product.radius, product.color);
    }
}

void fissionMenu::reset() 
{
    // Initialize uranium atom
    uranium.position = { 600, 300 };
    uranium.velocity = { 0, 0 };
    uranium.radius = 40.0f;
    uranium.color = BLUE;
    uranium.active = true;
    uranium.vibrationPhase = 0;
    uranium.vibrationAmplitude = 0;

    // Initialize neutron
    neutron.position = { 100, 300 };
    neutron.velocity = { 200, 0 };
    neutron.radius = 9.0f;
    neutron.color = RED;
    neutron.active = true;

    fissionProducts.clear();
    collisionOccurred = false;
    vibrationTime = 0;
}