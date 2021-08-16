#pragma once

#include "Entity.hpp"
#include <algorithm>
#include <vector>
#include <map>

namespace tlk
{
    class EntityTracker
    {
    public:
        EntityTracker() { };
        ~EntityTracker() { };

        void updatePosition(const Entity* e, unsigned int startingPos);
        void updatePosition(const Entity* e, const Connection* moved);

        unsigned int getLocationOf(const Entity* e) const;
        std::vector<unsigned int> getEntityLocations(bool hideMrX) const;

        std::vector<unsigned int> getAllPossibleLocationsForMrx() const;
        std::vector<unsigned int> getAllPossibleLocationsForMrxAfter(Connection simulatedMove) const;


    private:
        std::vector<tlk::ConnectionType> mrx_publicHistory;

        std::map<const Entity*, unsigned int> positions; //TODO Add count of players to this 
        std::map<const Entity*, Connections> entityMovementHistory;
    };
    
} // namespace tlk
