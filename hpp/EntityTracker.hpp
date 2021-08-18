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
        ~EntityTracker() 
        {
            mrx_publicHistory.clear();
            positions.clear();
            entityHistory.clear();
        };

        void updatePosition(const Entity* e, uint startingPos);
        void updatePosition(const Entity* e, const Connection* moved, const Ticket used);

        uint getLocationOfMrx() const;
        uint getLocationOf(const Entity* e) const;
        std::list<uint> getEntityLocations(bool hideMrX) const;

        void setMrxLocation(uint loc)
        {
            mrxLastSeenLocation = loc;
            if (!mrx_publicHistory.empty())
                mrx_publicHistory.erase(mrx_publicHistory.cbegin(), --mrx_publicHistory.cend());
        }

        uint getMrxLastSeenLocation() const
        {
            return mrxLastSeenLocation;
        }

        const std::vector<Ticket>& getMrxHistory() const
        {
            return mrx_publicHistory;
        }

        const Connections getEntityHistorie(const Entity* e) const
        {
            return entityHistory.at(e);
        }

    private:
        uint mrxLastSeenLocation = 0;
        std::vector<tlk::Ticket> mrx_publicHistory;

        std::map<const Entity*, uint> positions; //TODO Add count of players to this 
        std::map<const Entity*, Connections> entityHistory;
    };
    
} // namespace tlk
