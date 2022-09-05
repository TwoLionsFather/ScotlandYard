#pragma once
        // void setMrXPos(int pos);
        // void setMrXSighting(int sighting);
        // void setSLYPosition(const Entity *slyUnit, int pos);
        // void setTickets(const Entity *e, TicketStack tickets); //TODO implement assign operator or copy constructor

#include "Game.hpp"
#include <iostream>

namespace tlk
{
    class GameDebug : protected Game
    {
    public:
        GameDebug(const Map*  gameMap) : Game(gameMap) { };
        virtual ~GameDebug() { };

        bool runTests() 
        {
            // tracker.setStartingPos(mrx, 45);
            // tracker.setMrxLocation(45);
            // tracker.setStartingPos(sly_units[0], 32);
            // tracker.setStartingPos(sly_units[1], 60);
            // sly_units.pop_back();
            // sly_units.pop_back();

            tracker.setStartingPos(mrx, 37);
            tracker.setMrxLocation(23);
            tracker.setStartingPos(*sly_units[0], 22);
            tracker.setStartingPos(*sly_units[1], 67);
            tracker.setStartingPos(*sly_units[2], 38);
            sly_units.pop_back();

            round = 3;
            playSingleRound();
            
            // checkMrXLocation(46);
            checkMrXLocation(36);
            std::cout << "Tests are done" << std::endl;

            return false;
        };

    private: 

        void checkMrXLocation(int expected)
        {
            if (tracker.getLocationOfMrx() != expected)
                std::cout << "GameDebug::checkMrXLocation MrX Location: " << tracker.getLocationOfMrx() << " is not " << expected << std::endl;
        };
    
    };

} // namespace tlk
