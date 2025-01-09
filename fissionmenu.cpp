// FissionMenu.cpp
#include "fissionMenu.hpp"
#include "mainMenu.hpp"
#include <iostream>
#include <cmath>

constexpr float SPLIT_VELOCITY = 100.0f; // Define the split velocity
constexpr float NEUTRON_VELOCITY = 200.0f; // Define the neutron velocity
constexpr float VIBRATION_DURATION = 1.0f; // Duration of the vibration phase

constexpr float TEXTURE_NSCALE = 0.1f; // Scale factor for the textures
constexpr float TEXTURE_USCALE = 0.3f; // Scale factor for the textures
constexpr float TEXTURE_FPSCALE = 0.2f; // Scale factor for the textures

fissionMenu::fissionMenu() {
    // Initialize particles
    // particle textures
    uraniumTexture = LoadTexture("Graphics/Uranium236.png");
    neutronTexture = LoadTexture("Graphics/neutron.png");
    fragment1Texture = LoadTexture("Graphics/Krypton.png");
    fragment2Texture = LoadTexture("Graphics/Barium.png");
    
    neutron = { {200, 300}, {200, 0}, 12.0f, neutronTexture, true, 0, 0 };
    uranium = { {600, 250}, {0, 0}, 40.0f, uraniumTexture, true, 0, 0 };


    collisionOccurred = false;
    vibrationTime = 0;

    // Initialize buttons using smart pointers
    homeButton = std::make_unique<Button>("Graphics/home.png", Vector2{ 1150, 550 }, 0.1f);
    startButton = std::make_unique<Button>("Graphics/start.png", Vector2{ 1150, 450 }, 0.1f);

    simulationStarted = false;

    std::cout << "FissionMenu initialized." << std::endl;
}


fissionMenu::~fissionMenu()
{
    // no clean up for smart pointer
    UnloadTexture(uranium.texture);
    UnloadTexture(neutron.texture);
    for (auto& product : fissionProducts) {
        UnloadTexture(product.texture);
    }
    for (auto& n : neutrons) {
        UnloadTexture(n.texture);
    }
    std::cout << "FissionMenu destroyed." << std::endl;
}

void fissionMenu::update(Vector2 mousePosition, bool mousePressed) 
{

    // updating if cursor is on home button
    bool isHoveringAnyButton = false;
    if (homeButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (startButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    // Set cursor based on hover state
    if (isHoveringAnyButton) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    
    if (startButton->isPressed(mousePosition, mousePressed)) {
        simulationStarted = true;
        updateSimulation(GetFrameTime());
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

    // Legend
    DrawRectangle(320, 460, 650, 130, LIGHTGRAY); // Draw the background rectangle for the legend
    DrawText("Legend", 580, 480, 30, BLACK); // Draw the heading "Legend"

    // Example: Drawing texture names with their atom names
    DrawTextureEx(uraniumTexture, {350, 525}, 0.0f ,TEXTURE_NSCALE, WHITE);
    DrawText("Uranium", 410, 540, 20, BLACK);

    DrawTextureEx(neutronTexture, { 500, 525 }, 0.0f, TEXTURE_NSCALE, WHITE);
    DrawText("Neutron", 560, 540, 20, BLACK);

    DrawTextureEx(fragment1Texture, { 650, 525 }, 0.0f, TEXTURE_NSCALE, WHITE);
    DrawText("Krypton", 710, 540, 20, BLACK);

    DrawTextureEx(fragment2Texture, { 800, 525 }, 0.0f, TEXTURE_NSCALE, WHITE);
    DrawText("Barium", 860, 540, 20, BLACK);

    // draw home button
    homeButton->Draw();
    startButton->Draw();
    currentMenu->draw();

    DrawText("Press R to reset simulation", 10, 10, 20, DARKGRAY);

    if (IsKeyPressed(KEY_R)) {
        reset();
    }

    //// Render atoms
    //for (auto& atom : atoms) 
    //    atom.draw();

    //// Render neutrons
    //for (auto& neutron : neutrons) 
    //    neutron.draw();        
}

void fissionMenu::updateSimulation(float deltaTime) {
    if (!simulationStarted) return; // Do not update if simulation has not started

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

            // Calculate velocity vectors for the fission products
            Vector2 velocity1 = { SPLIT_VELOCITY * cos(PI / 5), SPLIT_VELOCITY * sin(PI / 5) }; // 45 degrees
            Vector2 velocity2 = { SPLIT_VELOCITY * cos(-PI / 5), SPLIT_VELOCITY * sin(-PI / 5) }; // -45 degrees

            // Create two fission products
            Particl fragment1 = {
                uranium.position,
                velocity1,
                uranium.radius / 2,
                LoadTexture("Graphics/Krypton.png"),
                true,
                0,
                0
            };

            Particl fragment2 = {
                uranium.position,
                velocity2,
                uranium.radius / 2,
                LoadTexture("Graphics/Barium.png"),
                true,
                0,
                0
            };

            fissionProducts.push_back(fragment1);
            fissionProducts.push_back(fragment2);
            
            // Create three neutrons emitted in different directions
            Vector2 neutronVelocities[3] = {
                { NEUTRON_VELOCITY, 0 }, // Right
                { NEUTRON_VELOCITY * cos(PI / 7), NEUTRON_VELOCITY * sin(PI / 7) }, // 30 degrees
                { NEUTRON_VELOCITY * cos(-PI / 7), NEUTRON_VELOCITY * sin(-PI / 7) } // -30 degrees
            };

            for (int i = 0; i < 3; ++i) {   
                Particl newNeutron = {
                    uranium.position,
                    neutronVelocities[i],
                    neutron.radius,
                    LoadTexture("Graphics/neutron.png"), // Load texture for neutron
                    true,
                    0,
                    0
                };
                neutrons.push_back(newNeutron);
            }
        }

        // Update fission products
        for (auto& product : fissionProducts) {
            product.position.x += product.velocity.x * deltaTime;
            product.position.y += product.velocity.y * deltaTime;
        }

        // Update neutrons
        for (auto& n : neutrons) {
            if (n.active) {
                n.position.x += n.velocity.x * deltaTime;
                n.position.y += n.velocity.y * deltaTime;
            }
        }
    }
}

void fissionMenu::draw()
{
    if (uranium.active) {
        // Draw uranium using texture
        DrawTextureEx(uranium.texture, Vector2{ uranium.position.x - uranium.radius * TEXTURE_USCALE, uranium.position.y - uranium.radius * TEXTURE_USCALE }, 0.0f, TEXTURE_USCALE, WHITE);
    }

    if (neutron.active) {
        // Draw neutron using texture
        DrawTextureEx(neutron.texture, Vector2{ neutron.position.x - neutron.radius * TEXTURE_NSCALE, neutron.position.y - neutron.radius * TEXTURE_NSCALE }, 0.0f, TEXTURE_NSCALE, WHITE);
    }

    for (const auto& product : fissionProducts) {
        // Draw fission products using texture
        DrawTextureEx(product.texture, Vector2{ product.position.x - product.radius * TEXTURE_FPSCALE, product.position.y - product.radius * TEXTURE_FPSCALE }, 0.0f, TEXTURE_FPSCALE, WHITE);
    }

    for (const auto& n : neutrons) {
        if (n.active) {
            // Draw neutrons using texture
            DrawTextureEx(n.texture, Vector2{ n.position.x - n.radius * TEXTURE_NSCALE, n.position.y - n.radius * TEXTURE_NSCALE }, 0.0f, TEXTURE_NSCALE, WHITE);
        }
    }
}

void fissionMenu::reset() 
{
    fissionProducts.clear();
    neutrons.clear();

    Texture2D uraniumTexture = LoadTexture("Graphics/Uranium236.png");
    Texture2D neutronTexture = LoadTexture("Graphics/neutron.png");

    neutron = { {100, 300}, {200, 0}, 12.0f, neutronTexture, true, 0, 0 };
    uranium = { {600, 250}, {0, 0}, 40.0f, uraniumTexture, true, 0, 0 };

    collisionOccurred = false;
    vibrationTime = 0;
    simulationStarted = false; 
}