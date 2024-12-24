#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include "raylib.h"
#include <memory>
#include "button.hpp"

class Menu {
public:
    virtual void update(Vector2 mousePosition, bool mousePressed) = 0;
    virtual void render() = 0;
    virtual ~Menu() {}
};

extern std::unique_ptr<Menu> currentMenu;
extern Button* homeButton;
extern Texture2D background;


#endif // MENU_HPP
