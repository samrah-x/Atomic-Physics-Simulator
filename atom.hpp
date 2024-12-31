// atom.hpp
#pragma once
#include "raylib.h"
#include <vector>

class Atom {
private:
    Vector2 position;
    Texture2D texture;
    bool isBeingDragged;
    bool isSplit;
    bool active;
    float scale;
    float radius;
    std::vector<Atom> fragments;

public:
    // Constructors & Destructor
    Atom(Vector2 initPosition, const char* texturePath);
    ~Atom();

    // Original functionality
    void draw();
    void update(Vector2 mousePos, bool mousePressed);
    void split();
    void bombardedWithNeutron(Vector2 neutronPosition);

    // New functionality for fission simulation
    bool isActive() const { return active; }
    void setActive(bool isActive) { active = isActive; }
    float getRadius() const { return radius; }
    Vector2 getPosition() const { return position; }
    void setPosition(Vector2 pos) { position = pos; }
    float getScale() const { return scale; }
    void setScale(float newScale) { scale = newScale; }
    bool isSplitState() const { return isSplit; }
    void setSplitState(bool state) { isSplit = state; }
};
