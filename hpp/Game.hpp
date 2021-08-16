#pragma once

#include "Map.hpp"
#include "EntityTracker.hpp"
#include "Player_mrx.hpp"
#include "Player_sly.hpp"
#include "Bot_sly.hpp"
#include "Bot_mrx.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

namespace tlk
{
    enum State {WON_MRX
                , WON_SLY
                , PLAYING
                , ERROR};

    class Game
    {
    public:
        Game();
        ~Game();

        void setup();
        void play();

    private: 
        const Map  gameMap;
        EntityTracker vMap;

        Entity* const mrx;
        std::vector<Entity*> sly_units;

        unsigned int round = 0;
        State gameState;

        void printRoundStart();
        void playMrx();
        void playSly();
    };
}