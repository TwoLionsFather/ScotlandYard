#include "../hpp/Game.hpp"

tlk::Game::Game():
    gameMap(tlk::Map("../assets/connections.txt"))
    , posTrack(tlk::EntityTracker())
    , vMap(gameMap, posTrack)
    , mrx(new tlk::Bot_mrx(vMap))
    , sly_units(std::vector<Entity*>())
    , round(0)
    , gameState(tlk::PLAYING)
{ 
    sly_units.emplace_back(new Bot_sly(vMap));
    sly_units.emplace_back(new Bot_sly(vMap));
}

tlk::Game::~Game()
{
    delete mrx;
    for (Entity* e : sly_units)
        delete e;
}

void tlk::Game::setup()
{    
    auto rng = std::default_random_engine(rand());
    std::vector<uint> startingOptions = {13, 29, 46, 58, 67, 105, 140, 142, 153, 159}; //und weitere aber die haben alle >10 Options
    std::shuffle(startingOptions.begin(), startingOptions.end(), rng);

    posTrack.updatePosition(mrx, *startingOptions.rbegin());
    startingOptions.pop_back();

    posTrack.setMrxLocation(*startingOptions.rbegin());     
    startingOptions.pop_back();

    posTrack.updatePosition(sly_units[0], *startingOptions.rbegin());
    startingOptions.pop_back();

    posTrack.updatePosition(sly_units[1], *startingOptions.rbegin());
    startingOptions.pop_back();
}

tlk::Statistics tlk::Game::play()
{
    if (tlk::Game::loglevel >= tlk::LOW)
        std::cout << "Das Spiel kann beginnen: " << std::endl;

    do {
        round++;

        if (tlk::Game::loglevel >= tlk::NORMAL)
            printRoundStart();

        playMrx();

        if ((round+2) % 5 == 0)
        {
            posTrack.setMrxLocation(posTrack.getLocationOf(mrx));

            if (tlk::Game::loglevel >= tlk::NORMAL)
                std::cout << "Postion von MRX in Round: " << round << " is " << posTrack.getLocationOf(mrx) << " -------------------------------------------" << std::endl;
        }
            
        if (gameState != WON_SLY)
            playSly();

        if (round == 22)
            gameState = WON_MRX;

    } while (gameState == tlk::State::PLAYING);
    
    if (tlk::Game::loglevel >= tlk::NORMAL)
    {
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

    if (tlk::Game::loglevel >= tlk::LOW)
        std::cout << "Round count was: " << round << std::endl;

    return Statistics(gameState, round);
}

void tlk::Game::playMrx()
{
    std::pair<const tlk::Connection*, tlk::Ticket> used;
    do {
        const Connections& options =  gameMap.getMovesFor(mrx, &posTrack);
        if (options.empty())
        {
            gameState = WON_SLY;
            return;
        }
        used = mrx->move(options);

        if (tlk::Game::loglevel >= tlk::NORMAL)
            std::cout << "MRX Moved to: " << used.first->target << std::endl;

        posTrack.updatePosition(mrx, used.first);
    } while (used.second == tlk::DOUBLE_Ti);
}

void tlk::Game::playSly()
{
    std::pair<const tlk::Connection*, tlk::Ticket> used;
    bool noOfficerMoved = true;

    for (Entity* e : sly_units)
    {
        const Connections& options =  gameMap.getMovesFor(e, &posTrack);
        if (options.empty())
            continue;
        
        used = e->move(options);

        if (tlk::Game::loglevel >= tlk::NORMAL)
            std::cout << "SLY Unit Moved to: " << used.first->target << std::endl;

        if (posTrack.getLocationOf(mrx) == used.first->target)
        {
            gameState = WON_SLY;
            return;
        }

        posTrack.updatePosition(e, used.first); 
        mrx->addTicket(used.second);
        noOfficerMoved = false;
    }

    if (noOfficerMoved)
    {
        gameState = WON_MRX;

        if (tlk::Game::loglevel >= tlk::NORMAL)
            std::cout << "Officers dind't move!" << std::endl;
    }
}

void tlk::Game::printRoundStart()
{
    std::cout << "Round: " << round << " Positions [MrX, sly0, sly1 ...]: ";
    for (unsigned int ui : posTrack.getEntityLocations(false))
        std::cout << ui << " ";
    std::cout << std::endl;
}