#include "neutron.hpp"


Neutron::Neutron(Vector2 startPos, const char* texturePath) {
    position = startPos;
    texture = LoadTexture(texturePath);
}

Neutron::~Neutron() {
    UnloadTexture(texture);  // Clean up texture when done
}

void Neutron::draw() {
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Neutron::update(Vector2 newPos) {
    position = newPos;  // Move the neutron
}