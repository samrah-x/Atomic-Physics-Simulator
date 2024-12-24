#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include <memory>  // For std::unique_ptr
#include "Menu.hpp"  // The base class for all menus
#include "MainMenu.hpp"  // Include the header for MainMenu

// Global pointer to the current menu
extern std::unique_ptr<Menu> currentMenu;

// Function declarations
void init();
void runGame();

#endif // GAME_HPP
