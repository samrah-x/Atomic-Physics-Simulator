#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include "raylib.h"
#include <memory>
#include "button.hpp"

// Structure for particles
struct Particle {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    bool active;
    float vibrationPhase;
    float vibrationAmplitude;
};
// Structure for particles
struct Particl {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Texture2D texture;
    bool active;
    float vibrationPhase;
    float vibrationAmplitude;
};
class Menu {
public:
    virtual void update(Vector2 mousePosition, bool mousePressed) = 0;
    virtual void render() = 0;
    virtual void updateSimulation(float deltaTime) = 0;
    virtual void draw() = 0;
    virtual void reset() = 0;
    virtual ~Menu() {}
};

extern std::unique_ptr<Menu> currentMenu;
extern Button* homeButton;
extern Texture2D background;


#endif // MENU_HPP
