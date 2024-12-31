#pragma once
#ifndef CHAIN_RXN_MENU_HPP
#define CHAIN_RXN_MENU_HPP

#include "menu.hpp"  
#include <vector>

class ChainRxnMenu : public Menu {
public:
    ChainRxnMenu();
    ~ChainRxnMenu();
    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;
    void updateSimulation(float deltaTime) override;
    void draw() override;
    void reset() override;

private:
    std::vector<Particle> uraniumAtoms;
    std::vector<Particle> neutrons;
    std::vector<Particle> fissionProducts;
    bool collisionOccurred;
    int chainCount;
    Button* homeButton = nullptr;
};

#endif // CHAIN_RXN_MENU_HPP