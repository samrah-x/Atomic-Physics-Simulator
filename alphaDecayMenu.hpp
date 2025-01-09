#pragma once
#ifndef ALPHA_DECAY_MENU_HPP
#define ALPHA_DECAY_MENU_HPP

#include "menu.hpp"  

class AlphaDecayMenu : public Menu {
public:
    AlphaDecayMenu();
    ~AlphaDecayMenu();
    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;
    void updateSimulation(float deltaTime) override;
    void draw() override;
    void reset() override;

private:
    Particle parentNucleus;
    Particle alphaParticle;
    bool decayStarted;
    bool decayOccurred;
    bool isDragging;
    Vector2 dragOffset;
    std::unique_ptr<Button> homeButton;
    std::unique_ptr<Button> startButton;
    bool simulationStarted;
};


#endif // ALPHA_DECAY_MENU_HPP