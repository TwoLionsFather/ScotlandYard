#pragma once
        // void setMrXPos(int pos);
        // void setMrXSighting(int sighting);
        // void setSLYPosition(const Entity *slyUnit, int pos);
        // void setTickets(const Entity *e, TicketStack tickets); //TODO implement assign operator or copy constructor

#include "Game.hpp"

namespace tlk
{
    class GameDebug : protected Game
    {
    public:
        GameDebug(const Map*  gameMap) : Game(gameMap) {
            runTests();
        };
        virtual ~GameDebug();

    private:
        void runTests() 
        {
            
        }
    };

} // namespace tlk
