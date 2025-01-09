
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
    Particl deutrium;
    Particl tritium;
    //Particl neutron;
    //Particl helium;
    Texture2D deutriumTexture;
    Texture2D tritiumTexture;
    Texture2D heliumTexture;
    Texture2D neutronTexture;
    std::vector<Particl> fusionProducts;
    std::vector<Particl> emittedNeutrons;
    bool collisionOccurred;
    std::unique_ptr<Button> homeButton;
    std::unique_ptr<Button> startButton;
    bool simulationStarted;
};

#endif // FUSION_MENU_HPP