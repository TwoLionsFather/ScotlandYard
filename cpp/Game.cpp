#include "../hpp/Game.hpp"

tlk::Game::Game():
    gameMap(tlk::Map("../assets/connections.txt"))
    , vMap(tlk::VirtualMap(gameMap))
    , mrx(new tlk::Player_mrx())
    , sly_units(std::vector<Entity*>())
    , round(0)
    , gameState(tlk::MOVE_MRX)
{ 
    sly_units.emplace_back(new Bot_sly());
    sly_units.emplace_back(new Bot_sly());
    sly_units.emplace_back(new Bot_sly());
}

tlk::Game::~Game()
{
    delete mrx;
    for (Entity* e : sly_units)
        delete e;
}

void tlk::Game::setup()
{    
    mrx->setStartingPos(1);
    vMap.updatePosition(mrx, 1);

    sly_units[0]->setStartingPos(8);
    vMap.updatePosition(sly_units[0], 8);

    sly_units[1]->setStartingPos(9);
    vMap.updatePosition(sly_units[1], 9);
}

void tlk::Game::play()
{
    std::cout << "Das Spiel kann beginnen: " << std::endl;

    std::pair<const tlk::Connection*, tlk::Ticket> used;
    do {
        round++;
        printRoundStart();
        do {
            const Connections& options =  gameMap.getMovesFor(mrx, vMap.getEntityLocations(false));
            if (options.empty())
            {
                gameState = WON_SLY;
                break;
            }
            used = mrx->move(options);
            vMap.updatePosition(mrx, used.first);
        } while (used.second == tlk::DOUBLE_Ti);

        if (gameState == WON_SLY)
            break;

        for (Entity* e : sly_units)
        {
            if (e->getPos() == 0) //If unit isn't activated it can be ignored
                continue;

            const Connections& options =  gameMap.getMovesFor(e, vMap.getEntityLocations(false));
            if (options.empty())
                continue;

            used = e->move(options);
            vMap.updatePosition(e, used.first); 
            mrx->addTicket(used.second);
        }

    } while (true);
    
    if (gameState == WON_SLY)
        std::cout << "Game has finished and Scotland Yard won!" << std::endl;

}

void tlk::Game::printRoundStart()
{
    std::cout << "Round: " << round << " Positions [MrX, sly0, sly1 ...]: ";
    for (unsigned int ui : vMap.getEntityLocations(true))
        std::cout << ui << " ";
    std::cout << std::endl;
}