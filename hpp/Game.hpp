#pragma once

#include "ConstsAndEnums.hpp"
#include "Map.hpp"
#include "VirtualMap.hpp"
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

    struct Statistics
    {
        Statistics(State winner, int round) 
            : endState(winner), finalRound(round) { };
        const tlk::State endState = ERROR;
        const int finalRound = 0;
        //Possibly More
    };

    struct GameLiveInfo
    {
        GameLiveInfo() { };
        GameLiveInfo(const EntityTracker *tracker
                    , const Entity *mrx
                    , const std::vector<Entity*> *sly) 
            : tracker(tracker), mrx(mrx), sly(sly) { };

        const EntityTracker *tracker = nullptr;
        const Entity *mrx = nullptr;
        const std::vector<Entity*> *sly = nullptr;
    };

    class Game
    {
    public:
        Game() = delete;
        Game(const Map*  gameMap);
        ~Game();

        void setup();
        Statistics play();
        State playSingleRound();

        GameLiveInfo getGameLiveInfo() const;

    private: 
        const Map*  gameMap;
        EntityTracker tracker;
        const VirtualMap vMap;
        
        std::vector<int> startingOptions = {103, 112, 34, 155, 94, 117, 132, 53, 174, 198, 50, 91, 26, 29, 141, 13, 138, 197};//{58, 34, 14, 29, 52, 94, 78, 66, 86, 105, 100, 137, 154, 157, 135, 144, 180, 199}; 
        int round = 0;
        Entity* const mrx;
        std::vector<Entity*> sly_units;

        State gameState;

        void printRoundStart();
        void playMrx();
        void playSly();
    };
}