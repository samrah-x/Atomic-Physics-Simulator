#pragma once
// FissionMenu.hpp
#ifndef FISSION_MENU_HPP
#define FISSION_MENU_HPP

#include "menu.hpp"  
#include "raylib.h"  
#include <vector>
#include "atom.hpp"
#include "neutron.hpp"

class fissionMenu : public Menu {
public:
    fissionMenu();
    ~fissionMenu();
    void update(Vector2 mousePosition, bool mousePressed) override;
    void render() override;

//private:
//    std::vector<Atom> atoms;  
//    std::vector<Neutron> neutrons;
};

#endif // FISSION_MENU_HPP
