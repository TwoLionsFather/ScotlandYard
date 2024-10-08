#pragma once

#include "Consts.hpp"
#include "Map.hpp"
#include "VirtualMap.hpp"
#include "Entity.hpp"
#include "EntityTracker.hpp"
#include "Player_mrx.hpp"
#include "Player_sly.hpp"
#include "Bot_sly.hpp"
#include "Bot_mrx.hpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

namespace tlk
{
    enum State {
        WON_MRX
        , WON_SLY
        , PLAYING
        , ERROR
    };

    struct Statistics
    {
        Statistics(State winner, int round);
        const tlk::State endState = ERROR;
        const int finalRound = 0;
        //Possibly More
    };

    struct GameLiveInfo
    {
        GameLiveInfo();
        GameLiveInfo(const EntityTracker *tracker
                    , const Entity* mrx
                    , const std::vector<Entity*> *sly);

        const EntityTracker *tracker = nullptr;
        const Entity* mrx = nullptr;
        const std::vector<Entity*> *sly = nullptr;
    };

    class Game
    {
    public:
        Game() = delete;
        explicit Game(const Map* map);
        virtual ~Game();

        void setup();
        void setup(const std::vector<int>& startLocations);
        Statistics play();
        State playSingleRound();

        GameLiveInfo getGameLiveInfo() const;

    protected: 
        int round;

        const Map*  gameMap;
        const VirtualMap vMap;

        Entity& mrx;
        std::vector<Entity*> sly_units;
        EntityTracker tracker;
        std::vector<int> startLocations;

        State gameState;

        void printRoundStart();
        void playMrx();
        void playSly();
    
    private:
        void initEntities();
    };

}