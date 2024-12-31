#pragma once
// FissionMenu.hpp
#ifndef FISSION_MENU_HPP
#define FISSION_MENU_HPP

#include "menu.hpp"  
#include "raylib.h"  
#include <vector>
//#include "atom.hpp"
//#include "neutron.hpp"


class fissionMenu : public Menu {
public:
    fissionMenu();
    ~fissionMenu();
    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;
    void updateSimulation(float deltaTime) override;
    void draw() override;
    void reset() override;

private:
    Particle uranium;
    Particle neutron;
    std::vector<Particle> fissionProducts;
    bool collisionOccurred;
    float vibrationTime;
    const float VIBRATION_DURATION = 1.0f;
    const float SPLIT_VELOCITY = 200.0f;
    Button* homeButton = nullptr;
};

#endif // FISSION_MENU_HPP
