#include "atom.hpp"

Atom::Atom(Vector2 initPosition, const char* texturePath) {
    position = initPosition;
    texture = LoadTexture(texturePath);
    isBeingDragged = false;
    isSplit = false;
    active = true;
    scale = 1.0f;
    // Set radius based on texture size
    radius = (texture.width + texture.height) / 4.0f;
}

Atom::~Atom() {
    UnloadTexture(texture);
}

void Atom::draw() {
    if (!active) return;

    if (isSplit) {
        for (auto& fragment : fragments) {
            fragment.draw();
        }
    }
    else {
        Rectangle destRec = {
            position.x,
            position.y,
            texture.width * scale,
            texture.height * scale
        };
        DrawTexturePro(
            texture,
            { 0, 0, (float)texture.width, (float)texture.height },
            destRec,
            { 0, 0 },
            0.0f,
            WHITE
        );
    }
}

void Atom::update(Vector2 mousePos, bool mousePressed) {
    if (!active) return;

    if (isBeingDragged) {
        position = mousePos;
        if (!mousePressed) {
            isBeingDragged = false;
        }
    }
    else {
        Rectangle bounds = {
            position.x,
            position.y,
            texture.width * scale,
            texture.height * scale
        };
        if (CheckCollisionPointRec(mousePos, bounds) && mousePressed) {
            isBeingDragged = true;
        }
    }
}

void Atom::split() {
    if (!isSplit && active) {
        isSplit = true;
        active = false;

        // Create fragments with adjusted scale
        float fragmentScale = scale * 0.5f;
        Vector2 offsetLeft = { position.x - (texture.width * scale * 0.5f), position.y };
        Vector2 offsetRight = { position.x + (texture.width * scale * 0.5f), position.y };

        fragments.push_back(Atom(offsetLeft, "Graphics/Krypton.png"));
        fragments.back().setScale(fragmentScale);

        fragments.push_back(Atom(offsetRight, "Graphics/Barium.png"));
        fragments.back().setScale(fragmentScale);

        // Set initial state for fragments
        for (auto& fragment : fragments) {
            fragment.setActive(true);
        }
    }
}

void Atom::bombardedWithNeutron(Vector2 neutronPosition) {
    if (!isSplit && active) {
        Rectangle bounds = {
            position.x,
            position.y,
            texture.width * scale,
            texture.height * scale
        };
        if (CheckCollisionPointRec(neutronPosition, bounds)) {
            split();
        }
    }
}