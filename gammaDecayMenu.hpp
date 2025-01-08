#pragma once
#ifndef GAMMA_DECAY_MENU_HPP
#define GAMMA_DECAY_MENU_HPP

#include "menu.hpp"  
#include "raylib.h"

class GammaDecayMenu : public Menu {
public:
    GammaDecayMenu();
    ~GammaDecayMenu();
    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;
    void updateSimulation(float deltaTime) override;
    void draw() override;
    void reset() override;

private:
    Particle parentNucleus;
    Particle gammaRay;
    bool decayOccurred;
    bool dragging;
    Vector2 offset;
    Button* startDecayButton = nullptr;
    Button* homeButton = nullptr;
};


#endif // GAMMA_DECAY_MENU_HPP