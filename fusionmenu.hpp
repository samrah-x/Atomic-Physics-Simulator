
#pragma once
#ifndef FUSION_MENU_HPP
#define FUSION_MENU_HPP

#include "menu.hpp"  
#include <vector>

class FusionMenu : public Menu {
public:
    FusionMenu();
    ~FusionMenu();
    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;
    void updateSimulation(float deltaTime) override;
    void draw() override;
    void reset() override;

private:
    Particle hydrogen1;
    Particle hydrogen2;
    std::vector<Particle> fusionProducts;
    std::vector<Particle> emittedNeutrons;
    bool collisionOccurred;
    Button* homeButton = nullptr;
};

#endif // FUSION_MENU_HPP