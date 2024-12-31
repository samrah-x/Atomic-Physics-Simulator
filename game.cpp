#include "MainMenu.hpp"

std::unique_ptr<Menu> currentMenu;

void init() {
    InitWindow(1250, 650, "Atomic Physics Simulator");
    SetTargetFPS(60);

    // Initialize the main menu as the starting menu
    currentMenu = std::make_unique<MainMenu>();
}

void runGame() {
    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentMenu) {
            //SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            currentMenu->updateSimulation(GetFrameTime());
            currentMenu->render();
            currentMenu->update(mousePosition, mousePressed);
            
        }

        EndDrawing();
    }
}
