#pragma once

#include "Entity.hpp"
#include <algorithm>
#include <vector>
#include <map>

namespace tlk
{
    class VirtualMap
    {
    public:
        VirtualMap() { };
        ~VirtualMap() { };

        void updatePosition(const Entity* e, unsigned int startingPos);
        void updatePosition(const Entity* e, const Connection* moved);

        unsigned int getLocationOf(const Entity* e) const;
        std::vector<unsigned int> getEntityLocations(bool hideMrX) const;

        bool gameIsWonBy(const Entity* e) const;  //TODO Move to Game instead

        std::vector<unsigned int> getAllPossibleLocationsForMrx() const;
        std::vector<unsigned int> getAllPossibleLocationsForMrxAfter(Connection simulatedMove) const;


    private:
        int roundsTillReveal = 3;   //decrement each time MRX moves and reset on 0 move counter to Game instead
        std::vector<tlk::ConnectionType> mrx_publicHistory;

        std::map<const Entity*, unsigned int> positions; //TODO Add count of players to this 
        std::map<const Entity*, Connections> entityMovementHistory;
    };
    
} // namespace tlk
