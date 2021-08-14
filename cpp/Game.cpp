#include "../hpp/Game.hpp"

tlk::Game::Game():
    gameMap(new tlk::Map("../assets/connections.txt"))
    , mrx(new tlk::Player_mrx())
    , sly_units(std::vector<Entity*>())
    , gameState(tlk::MOVE_MRX)
{ 
    sly_units.emplace_back(new Bot_sly());
    sly_units.emplace_back(new Bot_sly());
    sly_units.emplace_back(new Bot_sly());
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
    sly_units[0]->setStartingPos(2);
    sly_units[1]->setStartingPos(3);
}

void tlk::Game::play()
{
    std::cout << "Das Spiel kann beginnen: " << std::endl;

    do {
        const Connections& options =  gameMap->getMovesFor(mrx, getEntityLocations());
        if (options.empty())
        {
            gameState = WON_SLY;
            break;
        }
        const std::pair<Connection, Ticket>& used = mrx->move(options);
            
        for (Entity* e : sly_units)
        {
            if (e->getPos() == 0) //If unit isn't activated it can be ignored
                continue;

            const Connections& options =  gameMap->getMovesFor(e, getEntityLocations());
            if (options.empty())
                continue;

            const std::pair<Connection, Ticket>& used = e->move(options); 
        }

    } while (true);
    
    if (gameState == WON_SLY)
        std::cout << "Game has finished and Scotland Yard won!" << std::endl;

}

