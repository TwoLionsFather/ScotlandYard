#include "../hpp/Game.hpp"

tlk::Game::Game():
    gameMap(tlk::Map("../assets/connections.txt"))
    , vMap(tlk::VirtualMap())
    , mrx(new tlk::Player_mrx())
    , sly_units(std::vector<Entity*>())
    , round(0)
    , gameState(tlk::PLAYING)
{ 
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
    vMap.updatePosition(mrx, 1);
    vMap.updatePosition(sly_units[0], 2);
}

void tlk::Game::play()
{
    std::cout << "Das Spiel kann beginnen: " << std::endl;

    do {
        round++;
        printRoundStart();
        playMrx();

        if (round-3 % 5 == 0)
            std::cout << "Postion von MRX in : "<< round << " is " << vMap.getLocationOf(mrx) << " -------------------------------------------";

        if (gameState != WON_SLY)
            playSly();

    } while (gameState == tlk::State::PLAYING);
    
    if (gameState == WON_SLY)
        std::cout << "Game has finished and Scotland Yard won!" << std::endl;
}

void tlk::Game::playMrx()
{
    std::pair<const tlk::Connection*, tlk::Ticket> used;
    do {
        const Connections& options =  gameMap.getMovesFor(mrx, &vMap);
        if (options.empty())
        {
            gameState = WON_SLY;
            return;
        }
        used = mrx->move(options);
        vMap.updatePosition(mrx, used.first);
    } while (used.second == tlk::DOUBLE_Ti);
}

void tlk::Game::playSly()
{
    std::pair<const tlk::Connection*, tlk::Ticket> used;
    bool noOfficerMoved = true;

    for (Entity* e : sly_units)
    {
        const Connections& options =  gameMap.getMovesFor(e, &vMap);
        if (options.empty())
            continue;
        
        used = e->move(options);

        if (vMap.getLocationOf(mrx) == used.first->target)
        {
            gameState = WON_SLY;
            return;
        }

        vMap.updatePosition(e, used.first); 
        mrx->addTicket(used.second);
        noOfficerMoved = false;
    }

    if (noOfficerMoved)
        gameState = WON_MRX;
}

void tlk::Game::printRoundStart()
{
    std::cout << "Round: " << round << " Positions [MrX, sly0, sly1 ...]: ";
    for (unsigned int ui : vMap.getEntityLocations(false))
        std::cout << ui << " ";
    std::cout << std::endl;
}