#include "../hpp/Game.hpp"

tlk::Game::Game():
    gameMap(new tlk::Map("../assets/connections.txt"))
    , mrx(new tlk::Player_mrx())
    , sly_units(std::vector<Entity*>())
    , gameState(tlk::MOVE_MRX)
{ 
    sly_units.emplace_back(new Sly_bot());
    sly_units.emplace_back(new Sly_bot());
    sly_units.emplace_back(new Sly_bot());
}

tlk::Game::~Game()
{
    delete gameMap;
    delete mrx;
    for (Entity* e : sly_units)
        delete e;
}

std::vector<unsigned int> tlk::Game::getEntityLocations()
{
    std::vector<unsigned int> positions;
    positions.push_back(mrx->getPos());
    for (Entity* e : sly_units)
        positions.push_back(e->getPos());

    return positions;
}

void tlk::Game::setup()
{    
    mrx->setStartingPos(1);
}

void tlk::Game::play()
{
    std::cout << "Das Spiel kann beginnen: " << std::endl;

    do {
        const std::pair<Connection, Ticket>& used = mrx->move(gameMap->getMovesFor(*mrx, getEntityLocations()));

        std::cout << used.first << " using: " << used.second << std::endl;
        std::cout << gameMap;

    } while (true);
    
}

