#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "button.hpp"

void init();                          // Function to initialize the game
void runGame();                        // Main game loop
void drawHomeScreen();                 // Draw the home screen
void updateButtons(Vector2 mousePos, bool mousePressed);  // Update button logic

// Global variables
extern Button* fissionButton;
extern Button* fusionButton;
extern Button* chainRxnButton;
extern Button* alphaDecayButton;
extern Button* betaDecayButton;
extern Button* gammaDecayButton;
extern Button* homeButton;

#endif // GAME_HPP
