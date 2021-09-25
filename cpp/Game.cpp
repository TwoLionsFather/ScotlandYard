#include "../hpp/Game.hpp"

tlk::Game::Game(const Map*  gameMap):
    gameMap(gameMap)
    , tracker(new tlk::EntityTracker())
    , vMap(*gameMap, *tracker)
    , round(0)
    , mrx(new tlk::Bot_mrx(vMap, &round))
    , sly_units(std::vector<Entity*>())
    , gameState(tlk::PLAYING)
{ 
    for (int i = 1; i < PLAYER_COUNT; ++i)
        sly_units.emplace_back(new Bot_sly(vMap, &round));

    if (PLAYER_PLAYING)
        sly_units.emplace_back(new Player_sly());
}

tlk::Game::~Game()
{
    vMap.~VirtualMap();
    delete tracker;
    delete mrx;
    for (Entity* e : sly_units)
        delete e;

    sly_units.clear();
}

tlk::GameLiveInfo tlk::Game::getGameLiveInfo() const
{
    return GameLiveInfo(tracker, mrx, &sly_units);
}

void tlk::Game::setup()
{    
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    auto rng = std::default_random_engine(rand());
    std::vector<int> initPositions(tlk::startingPositions, tlk::startingPositions + tlk::STARTING_OPTIONS_COUNT);


    std::shuffle(initPositions.begin(), initPositions.end(), rng);

    tracker->updatePosition(mrx, *initPositions.rbegin());
    initPositions.pop_back();

    tracker->setMrxLocation(100);    //set more intelegently

    for (const Entity* e : sly_units)
    {
        tracker->updatePosition(e, *initPositions.rbegin());
        initPositions.pop_back();
    }

    if (PLAYER_PLAYING)
        tracker->updatePosition(sly_units[PLAYER_COUNT], *initPositions.rbegin());

    initPositions.emplace_back(tracker->getLocationOf(mrx));
}

tlk::Statistics tlk::Game::play()
{
    if (tlk::LOG_LEVEL >= tlk::LOW)
        std::cout << "Das Spiel kann beginnen: " << std::endl;

    auto startG = std::chrono::high_resolution_clock::now();

    do {
        playSingleRound();

    } while (gameState == tlk::State::PLAYING);
    
    auto finishG = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finishG - startG;

    if (tlk::LOG_LEVEL >= tlk::NORMAL)
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

    if (tlk::CHRONO_LOG_LEVEL >= tlk::LOW)
    {
        std::cout << "Round count was: " << round << " "; 
        std::cout << "Elapsed Time: " << elapsed.count() << " ms" << std::endl;
    }

    return Statistics(gameState, round);
}

tlk::State tlk::Game::playSingleRound()
{
    round++;
    if (tlk::LOG_LEVEL >= tlk::NORMAL || PLAYER_PLAYING)
        printRoundStart();

    playMrx();

    if ((round+2) % 5 == 0)
    {
        tracker->setMrxLocation(tracker->getLocationOf(mrx));

        if (tlk::LOG_LEVEL >= tlk::NORMAL || PLAYER_PLAYING)
            std::cout << "Postion von MRX in Round: " << round << " is " << tracker->getLocationOf(mrx) << " -------------------------------------------" << std::endl;
    }
        
    if (gameState != WON_SLY)
        playSly();

    if (round == 22)
        return WON_MRX;

    return gameState;
}

void tlk::Game::playMrx()
{
    auto start = std::chrono::high_resolution_clock::now();

    do {
        const Connections& options =  gameMap->getMovesFor(mrx, tracker);
        if (options.empty())
        {
            gameState = WON_SLY;
            return;
        }
        const std::pair<const tlk::Connection&, tlk::Ticket> used = mrx->move(options);
        
        if (tlk::LOG_LEVEL >= tlk::HIGH)
            std::cout << "MRX Moved to: " << used.first.target << std::endl;

        if (tlk::LOG_LEVEL >= tlk::NORMAL || PLAYER_PLAYING)
            std::cout << "MrX used: " << used.second << std::endl;

        tracker->updatePosition(mrx, used.first, used.second);
    } while (tracker->getMrxHistory().back() == tlk::DOUBLE_Ti);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;

    if (tlk::CHRONO_LOG_LEVEL >= tlk::NORMAL)
    {
        std::cout << "MRX MOVE Elapsed Time: " << elapsed.count() << " ms" << std::endl;
    }

}

void tlk::Game::playSly()
{
    auto start = std::chrono::high_resolution_clock::now();
    bool noOfficerMoved = true;

    for (Entity* e : sly_units)
    {
        // if (PLAYER_PLAYING)
        //     std::cout << "SLY Unit on: " << tracker->getLocationOf(e) << std::endl;

        const Connections& options =  gameMap->getMovesFor(e, tracker);
        if (options.empty())
            continue;
        
        std::pair<const tlk::Connection&, tlk::Ticket> used = e->move(options);

        if (tlk::LOG_LEVEL >= tlk::HIGH || PLAYER_PLAYING)
            std::cout << "SLY Unit Moved to: " << used.first.target << std::endl;

        tracker->updatePosition(e, used.first, used.second); 
        mrx->addTicket(used.second);
        noOfficerMoved = false;

        if (tracker->getLocationOf(mrx) == used.first.target)
        {
            gameState = WON_SLY;
            return;
        }
    }

    if (noOfficerMoved)
    {
        gameState = WON_MRX;

        if (tlk::LOG_LEVEL >= tlk::NORMAL)
            std::cout << "Officers dind't move!" << std::endl;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;

    if (tlk::CHRONO_LOG_LEVEL >= tlk::NORMAL)
    { 
        std::cout << "SLY MOVE Elapsed Time: " << elapsed.count() << " ms" << std::endl;
    }
}

void tlk::Game::printRoundStart()
{
    std::cout << "Round: " << round << " Positions [MrX, sly0, sly1 ...]: ";
    for (unsigned int ui : tracker->getEntityLocations(false))
        std::cout << ui << " ";
    std::cout << std::endl;
}