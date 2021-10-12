#pragma once

#include "Consts.hpp"
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
    enum State {
        WON_MRX
        , WON_SLY
        , PLAYING
        , ERROR
    };

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
        virtual ~Game();

        void setup();
        Statistics play();
        State playSingleRound();

        GameLiveInfo getGameLiveInfo() const;

    protected: 
        const Map*  gameMap;
        EntityTracker tracker;
        const VirtualMap vMap;

        int round = 0;
        Entity* const mrx;
        std::vector<Entity*> sly_units;

        State gameState;

        void printRoundStart();
        void playMrx();
        void playSly();
    };
}