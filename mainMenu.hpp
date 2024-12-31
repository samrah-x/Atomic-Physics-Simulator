#pragma once
#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "Menu.hpp"
#include "Button.hpp"
#include "raylib.h"
#include <memory>

class MainMenu : public Menu {

public:
    MainMenu();
    ~MainMenu();

    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;
    void updateSimulation(float deltaTime) override;
    void draw() override;
    void reset() override;
};

extern Button* fissionButton;
extern Button* fusionButton;
extern Button* chainRxnButton;
extern Button* alphaDecayButton;
extern Button* betaDecayButton;
extern Button* gammaDecayButton;

#endif // MAIN_MENU_HPP
