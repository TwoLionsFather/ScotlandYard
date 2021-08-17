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

    class Game
    {
    public:
        Game();
        ~Game();

        void setup();
        Statistics play();

    private: 
        const Map  gameMap;
        EntityTracker posTrack;
        const VirtualMap vMap;

        Entity* const mrx;
        std::vector<Entity*> sly_units;

        unsigned int round = 0;
        State gameState;

        void printRoundStart();
        void playMrx();
        void playSly();
    };
}