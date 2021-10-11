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

        void setStartingPos(const Entity* e, int startingPos);
        void simulatePosition(const Entity* e, int newPos); //TODO make reverting an option also
        void updatePosition(const Entity* e, const Connection& moved, const Ticket used);

        int getLocationOfMrx() const;
        int getLocationOf(const Entity* e) const;
        std::vector<int> getEntityLocations(bool hideMrX) const;

        void setMrxLocation(int loc)
        {
            mrxLastSeenLocation = loc;
            if (!mrx_publicHistory.empty())
                mrx_publicHistory.erase(mrx_publicHistory.cbegin(), --mrx_publicHistory.cend());
        }

        int getMrxLastSeenLocation() const
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
        int mrxLastSeenLocation = 0;
        std::vector<tlk::Ticket> mrx_publicHistory;

        std::map<const Entity*, int> positions; 
        std::map<const Entity*, Connections> entityHistory;
    };
    
} // namespace tlk
