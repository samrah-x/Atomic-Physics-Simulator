#pragma once
#include "raylib.h"

class Neutron {
public:
    Neutron(Vector2 startPos, const char* texturePath);
    ~Neutron();
    void draw();
    void update(Vector2 newPos);

    Vector2 position;
    Texture2D texture;
};
