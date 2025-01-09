#pragma once
#ifndef BETA_DECAY_MENU_HPP
#define BETA_DECAY_MENU_HPP

#include "menu.hpp"  

class BetaDecayMenu : public Menu {
public:
    BetaDecayMenu();
    ~BetaDecayMenu();
    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;
    void updateSimulation(float deltaTime) override;
    void draw() override;
    void reset() override;

private:
    Particle parentNucleus;
    Particle betaParticle;
    bool decayStarted;
    bool decayOccurred;
    bool isDragging;
    Vector2 dragOffset;
    std::unique_ptr<Button> homeButton;
    std::unique_ptr<Button> startButton;
    bool simulationStarted;
};

#endif // BETA_DECAY_MENU_HPP