#include "../hpp/Game.hpp"

tlk::Game::Game():
    gameMap(tlk::Map("../assets/connections.txt"))
    , vMap(tlk::EntityTracker())
    , mrx(new tlk::Bot_mrx())
    , sly_units(std::vector<Entity*>())
    , round(0)
    , gameState(tlk::PLAYING)
{ 
    sly_units.emplace_back(new Bot_sly());
    sly_units.emplace_back(new Player_sly());
}

tlk::Game::~Game()
{
    delete mrx;
    for (Entity* e : sly_units)
        delete e;
}

void tlk::Game::setup()
{    
    auto rng = std::default_random_engine(std::time(0));
    std::vector<uint> startingOptions = {13, 29, 46, 58, 67, 105, 140, 142, 153, 159}; //und weitere aber die haben alle >10 Options
    std::shuffle(startingOptions.begin(), startingOptions.end(), rng);

    vMap.updatePosition(mrx, *startingOptions.rbegin());
    startingOptions.pop_back();

    vMap.updatePosition(sly_units[0], *startingOptions.rbegin());
    startingOptions.pop_back();

    vMap.updatePosition(sly_units[1], *startingOptions.rbegin());
    startingOptions.pop_back();
}

void tlk::Game::play()
{
    std::cout << "Das Spiel kann beginnen: " << std::endl;

    do {
        round++;
        printRoundStart();
        playMrx();

        if ((round+2) % 5 == 0)
            std::cout << "Postion von MRX in Round: " << round << " is " << vMap.getLocationOf(mrx) << " -------------------------------------------" << std::endl;

        if (gameState != WON_SLY)
            playSly();

    } while (gameState == tlk::State::PLAYING);
    
    switch (gameState) {
    case tlk::WON_SLY:
        std::cout << "Game has finished and Scotland Yard won!" << std::endl;
        break;

    case tlk::WON_MRX:
        std::cout << "Game has finished and MrX won!" << std::endl;
        break;

    default:
        std::cout << "Looks like there might be an issue... no clue what though :/" << std::endl;

    }
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
    {
        std::cout << "Officers dind't move!" << std::endl;
        gameState = WON_MRX;
    }
}

void tlk::Game::printRoundStart()
{
    std::cout << "Round: " << round << " Positions [MrX, sly0, sly1 ...]: ";
    for (unsigned int ui : vMap.getEntityLocations(false))
        std::cout << ui << " ";
    std::cout << std::endl;
}