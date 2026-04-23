#include "Game.hpp"

Game::Game(){
}

Game::~Game()
{
}

void Game::draw()
{
    for(auto hexa : hexaList){
        hexa.draw();
    }
}

void Game::update()
{
}

void Game::addHexagon(Vector2 position)
{
    hexaList.insert(Hexagon(position));
}

int Game::getListSize()
{
    if(hexaList.empty()){
        return 0;
    }
    return hexaList.size();
}
