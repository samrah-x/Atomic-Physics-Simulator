#include "fusionmenu.hpp"
#include "mainMenu.hpp"

//Button* homeButton = nullptr;

constexpr float TEXTURE_NSCALE = 0.1f; // Scale factor for the textures
constexpr float TEXTURE_HeSCALE = 0.3f; // Scale factor for the textures
constexpr float TEXTURE_HSCALE = 0.2f; // Scale factor for the textures

FusionMenu::FusionMenu() {
    // Initialize particles

    deutriumTexture = LoadTexture("Graphics/deutrium.png");
    tritiumTexture = LoadTexture("Graphics/tritium.png");
    heliumTexture = LoadTexture("Graphics/helium.png");
    neutronTexture = LoadTexture("Graphics/neutron.png");


    deutrium = { {100, 200}, {100, 0}, 20.0f, deutriumTexture, true, 0, 0 };
    tritium = { {1100, 200}, {-100, 0}, 20.0f, tritiumTexture, true, 0, 0 };
    /*neutron = { {1100, 300}, {-100, 0}, 20.0f, neutronTexture, true, 0, 0 };
    helium = { {1100, 300}, {-100, 0}, 20.0f, heliumTexture, true, 0, 0 };*/

    collisionOccurred = false;
    // Initialize buttons using smart pointers
    homeButton = std::make_unique<Button>("Graphics/home.png", Vector2{ 1150, 550 }, 0.1f);
    startButton = std::make_unique<Button>("Graphics/start.png", Vector2{ 1150, 450 }, 0.1f);

    simulationStarted = false;

    currentMenu->reset();
}

FusionMenu::~FusionMenu() {
    // no clean up due to smart pointers
    UnloadTexture(deutrium.texture);
    UnloadTexture(tritium.texture);
    for (auto& product : fusionProducts) {
        UnloadTexture(product.texture);
    }
    for (auto& n : emittedNeutrons) {
        UnloadTexture(n.texture);
    }
    //std::cout << "FissionMenu destroyed." << std::endl;
}

void FusionMenu::update(Vector2 mousePosition, bool mousePressed) {
    // Update logic for the Fusion Menu
    bool isHoveringAnyButton = false;
    if (homeButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
    if (startButton->updateCursor(mousePosition)) isHoveringAnyButton = true;
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

    // Legend
    DrawRectangle(320, 460, 650, 130, LIGHTGRAY); // Draw the background rectangle for the legend
    DrawText("Legend", 580, 480, 30, BLACK); // Draw the heading "Legend"

    // Example: Drawing texture names with their atom names
    DrawTextureEx(deutriumTexture, { 350, 525 }, 0.0f, TEXTURE_NSCALE, WHITE);
    DrawText("Deutrium", 410, 540, 20, BLACK);

    DrawTextureEx(tritiumTexture, { 500, 525 }, 0.0f, TEXTURE_NSCALE, WHITE);
    DrawText("Tritium", 560, 540, 20, BLACK);

    DrawTextureEx(neutronTexture, { 650, 525 }, 0.0f, TEXTURE_NSCALE, WHITE);
    DrawText("Neutron", 710, 540, 20, BLACK);

    DrawTextureEx(heliumTexture, { 800, 525 }, 0.0f, TEXTURE_NSCALE, WHITE);
    DrawText("Helium", 860, 540, 20, BLACK);


    // draw home button
    homeButton->Draw();
    startButton->Draw();
    currentMenu->draw();

    DrawText("Press R to reset simulation", 10, 10, 20, DARKGRAY);

    if (IsKeyPressed(KEY_R)) {
        reset();
    }
}

void FusionMenu::updateSimulation(float deltaTime) {
    if (!simulationStarted) return; // Do not update if simulation has not started

    if (!collisionOccurred) {
        // Update hydrogen positions
        deutrium.position.x += deutrium.velocity.x * deltaTime;
        tritium.position.x += tritium.velocity.x * deltaTime;

        // Check for collision
        float distance = sqrt(pow(deutrium.position.x - tritium.position.x, 2) +
            pow(deutrium.position.y - tritium.position.y, 2));

        if (distance < (deutrium.radius + tritium.radius) && deutrium.active && tritium.active) {
            collisionOccurred = true;
            deutrium.active = false;
            tritium.active = false;

            // Create fusion product and emitted neutrons
            Particl fusionProduct = { {570, 170}, {0, 0}, 25.0f, heliumTexture, true, 0, 0 };
            fusionProducts.push_back(fusionProduct);

            for (int i = 0; i < 1; ++i) {
                Particl neutron = { {600, 300}, {static_cast<float>(rand() % 201 - 100), static_cast<float>(rand() % 201 - 100)}, 5.0f, neutronTexture, true, 0, 0 };
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

void FusionMenu::draw() 
{
    if (deutrium.active) {
        // Draw uranium using texture
        DrawTextureEx(deutrium.texture, Vector2{ deutrium.position.x - deutrium.radius * TEXTURE_HSCALE, deutrium.position.y - deutrium.radius * TEXTURE_HSCALE }, 0.0f, TEXTURE_HSCALE, WHITE);
    }

    if (tritium.active) {
        // Draw neutron using texture
        DrawTextureEx(tritium.texture, Vector2{ tritium.position.x - tritium.radius * TEXTURE_HSCALE, tritium.position.y - tritium.radius * TEXTURE_HSCALE }, 0.0f, TEXTURE_HSCALE, WHITE);
    }

    for (const auto& product : fusionProducts) {
        // Draw fission products using texture
        DrawTextureEx(product.texture, Vector2{ product.position.x - product.radius * TEXTURE_HeSCALE, product.position.y - product.radius * TEXTURE_HeSCALE }, 0.0f, TEXTURE_HeSCALE, WHITE);
    }

    for (const auto& n : emittedNeutrons) {
        if (n.active) {
            // Draw neutrons using texture
            DrawTextureEx(n.texture, Vector2{ n.position.x - n.radius * TEXTURE_NSCALE, n.position.y - n.radius * TEXTURE_NSCALE }, 0.0f, TEXTURE_NSCALE, WHITE);
        }
    }
   
}

void FusionMenu::reset() {

    Texture2D deutriumTexture = LoadTexture("Graphics/deutrium.png");
    Texture2D tritiumTexture = LoadTexture("Graphics/tritium.png");

    deutrium = { {100, 200}, {100, 0}, 20.0f, deutriumTexture, true, 0, 0 };
    tritium = { {1100, 200}, {-100, 0}, 20.0f, tritiumTexture, true, 0, 0 };
    
    fusionProducts.clear();
    emittedNeutrons.clear();
    
    collisionOccurred = false;
    simulationStarted = false;
}