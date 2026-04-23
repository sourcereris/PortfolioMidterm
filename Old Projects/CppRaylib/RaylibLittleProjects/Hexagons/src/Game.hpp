#pragma once
#include "Hexagon.hpp"
#include <vector>
#include <set>

class Game{
    public:
        Game();
        ~Game();
        void draw();
        void update();
        void addHexagon(Vector2);
        int  getListSize();
    private:
        std::set<Hexagon> hexaList;
};