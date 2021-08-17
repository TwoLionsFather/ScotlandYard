#pragma once

#include "Entity.hpp"
#include <algorithm>
#include <vector>
#include <list>
#include <map>

namespace tlk
{
    class EntityTracker
    {
    public:
        EntityTracker() { };
        ~EntityTracker() { };

        void updatePosition(const Entity* e, uint startingPos);
        void updatePosition(const Entity* e, const Connection* moved, const Ticket used);

        uint getLocationOf(const Entity* e) const;
        std::list<uint> getEntityLocations(bool hideMrX) const;

        void setMrxLocation(uint loc)
        {
            mrxLastSeenLocation = loc;
            mrx_publicHistory.clear();
        }

        uint getMrxLastSeenLocation() const
        {
            return mrxLastSeenLocation;
        }

        const std::vector<Ticket>& getMrxHistory() const
        {
            return mrx_publicHistory;
        }

    private:
        uint mrxLastSeenLocation = 0;
        std::vector<tlk::Ticket> mrx_publicHistory;

        std::map<const Entity*, uint> positions; //TODO Add count of players to this 
        std::map<const Entity*, Connections> entityMovementHistory;
    };
    
} // namespace tlk
