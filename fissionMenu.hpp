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
    Particl uranium;
    Particl neutron;
    std::vector<Particl> fissionProducts;
    std::vector<Particl> neutrons; 
    bool collisionOccurred;
    float vibrationTime;
    const float VIBRATION_DURATION = 1.0f;
    const float SPLIT_VELOCITY = 200.0f;
    std::unique_ptr<Button> homeButton;
    std::unique_ptr<Button> startButton;
    bool simulationStarted;
    Texture2D uraniumTexture;
    Texture2D neutronTexture;
    Texture2D fragment1Texture;
    Texture2D fragment2Texture;
};

#endif // FISSION_MENU_HPP
    