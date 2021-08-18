#include "../hpp/Game.hpp"

tlk::Game::Game():
    gameMap(tlk::Map("../assets/connections.txt"))
    , tracker(tlk::EntityTracker())
    , vMap(gameMap, tracker)
    , mrx(new tlk::Bot_mrx(vMap))
    , sly_units(std::vector<Entity*>())
    , round(0)
    , gameState(tlk::PLAYING)
{ 
    for (int i = 0; i < PLAYER_COUNT; ++i)
        sly_units.emplace_back(new Bot_sly(vMap));

    if (PLAYER_PLAYING)
        sly_units.emplace_back(new Player_sly());
}

tlk::Game::~Game()
{
    delete mrx;
    for (Entity* e : sly_units)
        delete e;
}

tlk::GameLiveInfo tlk::Game::getGameLiveInfo() const
{
    return GameLiveInfo(&tracker, mrx, &sly_units);
}

void tlk::Game::setup()
{    
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    auto rng = std::default_random_engine(rand());
    std::vector<uint> startingOptions = {103, 112, 34, 155, 94, 117, 132, 53, 174, 198, 50, 91, 26, 29, 141, 13, 138, 197};//{58, 34, 14, 29, 52, 94, 78, 66, 86, 105, 100, 137, 154, 157, 135, 144, 180, 199}; 
    std::shuffle(startingOptions.begin(), startingOptions.end(), rng);

    tracker.updatePosition(mrx, *startingOptions.rbegin());
    startingOptions.pop_back();

    tracker.setMrxLocation(100);    //set more intelegently

    for (int i = 0; i < PLAYER_COUNT; ++i)
    {
        tracker.updatePosition(sly_units[i], *startingOptions.rbegin());
        startingOptions.pop_back();
    }

    if (PLAYER_PLAYING)
        tracker.updatePosition(sly_units[PLAYER_COUNT], *startingOptions.rbegin());
}

tlk::Statistics tlk::Game::play()
{
    if (tlk::LOG_LEVEL >= tlk::LOW)
        std::cout << "Das Spiel kann beginnen: " << std::endl;

    auto startG = std::chrono::high_resolution_clock::now();

    do {
        auto startr = std::chrono::high_resolution_clock::now();
        playSingleRound();

        auto finishr = std::chrono::high_resolution_clock::now();
        if (tlk::LOG_LEVEL >= tlk::HIGH)
        {
            std::chrono::duration<double, std::milli> elapsed = finishr - startr;
            std::cout << "Round calculations took: " << elapsed.count() << std::endl;
        }

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

    if (tlk::LOG_LEVEL >= tlk::LOW)
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
        tracker.setMrxLocation(tracker.getLocationOf(mrx));

        if (tlk::LOG_LEVEL == tlk::NORMAL || PLAYER_PLAYING)
            std::cout << "Postion von MRX in Round: " << round << " is " << tracker.getLocationOf(mrx) << " -------------------------------------------" << std::endl;
    }
        
    if (gameState != WON_SLY)
        playSly();

    if (round == 22)
        return WON_MRX;

    return gameState;
}

void tlk::Game::playMrx()
{
    std::pair<const tlk::Connection*, tlk::Ticket> used;
    do {
        const Connections& options =  gameMap.getMovesFor(mrx, &tracker);
        if (options.empty())
        {
            gameState = WON_SLY;
            return;
        }
        used = mrx->move(options);

        if (tlk::LOG_LEVEL >= tlk::HIGH)
            std::cout << "MRX Moved to: " << used.first->target << std::endl;

        if (PLAYER_PLAYING)
            std::cout << "MrX used: " << used.second << std::endl;

        tracker.updatePosition(mrx, used.first, used.second);
    } while (used.second == tlk::DOUBLE_Ti);
}

void tlk::Game::playSly()
{
    std::pair<const tlk::Connection*, tlk::Ticket> used;
    bool noOfficerMoved = true;

    for (Entity* e : sly_units)
    {
        // if (PLAYER_PLAYING)
        //     std::cout << "SLY Unit on: " << tracker.getLocationOf(e) << std::endl;

        const Connections& options =  gameMap.getMovesFor(e, &tracker);
        if (options.empty())
            continue;
        
        used = e->move(options);

        if (tlk::LOG_LEVEL >= tlk::HIGH || PLAYER_PLAYING)
            std::cout << "SLY Unit Moved to: " << used.first->target << std::endl;

        if (tracker.getLocationOfMrx() == used.first->target)
        {
            gameState = WON_SLY;
            return;
        }

        tracker.updatePosition(e, used.first, used.second); 
        mrx->addTicket(used.second);
        noOfficerMoved = false;
    }

    if (noOfficerMoved)
    {
        gameState = WON_MRX;

        if (tlk::LOG_LEVEL >= tlk::NORMAL)
            std::cout << "Officers dind't move!" << std::endl;
    }
}

void tlk::Game::printRoundStart()
{
    std::cout << "Round: " << round << " Positions [MrX, sly0, sly1 ...]: ";
    for (unsigned int ui : tracker.getEntityLocations(false))
        std::cout << ui << " ";
    std::cout << std::endl;
}