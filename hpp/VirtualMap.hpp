#pragma once

#include "Map.hpp"
#include "Entity.hpp"
#include <vector>
#include <map>

namespace tlk
{
    class VirtualMap
    {
    public:
        VirtualMap( const Map& originalMap):
            originalMap(originalMap) { };
        ~VirtualMap() { };

        void updatePosition(const Entity* e, unsigned int startingPos);
        void updatePosition(const Entity* e, const Connection* moved);
        std::vector<unsigned int> getEntityLocations(bool forMrX);

        bool gameIsWonBy(const Entity* e);  //TODO Move to Game instead

        std::vector<unsigned int> getAllPossibleLocationsForMrx();
        std::vector<unsigned int> getAllPossibleLocationsForMrxAfter(Connection simulatedMove);


    private:
        const Map& originalMap;

        int roundsTillReveal = 3;   //decrement each time MRX moves and reset on 0 move counter to Game instead
        std::vector<tlk::ConnectionType> mrx_publicHistory;

        std::map<const Entity*, unsigned int> positions; //TODO Add count of players to this 
        std::map<const Entity*, Connections> entityMovementHistory;
    };
    
} // namespace tlk
