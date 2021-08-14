#pragma once

#include "Map.hpp"
#include "Player_mrx.hpp"
#include "Sly_bot.hpp"
#include <iostream>

namespace tlk
{
    enum Status
    {
        WON_MRX,
        WON_SLY,
        MOVE_MRX,
        MOVE_SLY,
        ERROR
    };

    class Game
    {
    public:
        Game();
        ~Game();

        void setup();
        void play();
        std::vector<unsigned int> getEntityLocations();

    private: 
        const Map * const  gameMap;
        Entity* const mrx;
        std::vector<Entity*> sly_units;

        Status gameState;
    };
}