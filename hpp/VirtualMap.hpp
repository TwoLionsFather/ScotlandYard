#pragma once

#include "Map.hpp"
#include "Connection.hpp"
#include "EntityTracker.hpp"
#include "TicketStack.hpp"

#include <algorithm>
#include <list>
#include <set>
#include <unordered_set>

namespace tlk
{
    class VirtualMap
    {
    public:
        VirtualMap(const Map& original, EntityTracker& tracker)
            : originalMap(original), tracker(tracker) { };
        ~VirtualMap() { };
        

        bool neighboursContainSLY (const int pos) const;
        bool neighboursContainMRXSighting (const int pos) const;
        
        int getDistanceToMrxReport(const int pos) const;
        int getDistanceToMrxReport(const Entity* e) const;

        int getDistanceToClosestSly() const;
        int getDistanceToClosestSly(const int pos) const;
        int getDistanceToClosestSly(const Entity* e) const;

        int getDistanceBetween(const int pos, const int target) const;
        int getDistanceBetween(const Entity* e, const int target) const;

        int countSLYsInRange(const Connection& con, const int dist) const;

        std::unordered_set<int> getMrxPossibleLocationsAfter (const int roundCount, const bool blockUsed = true) const;
        std::unordered_set<int> getMrxPossibleLocationsAfter (const Entity* ent, const Connection& con) const;
        std::unordered_set<int> getPossibleLocationsAfter (const int pos, const int roundCount, const bool blockUsed = true
                                                            , const std::optional<std::vector<Ticket>>& tickets = std::nullopt) const;

    private:
        const Map& originalMap;
        EntityTracker& tracker; //TODO Evaluate better option?

        //Per default every Location except MrXs get blocked for first iteration if multiple rounds are calculated
        std::unordered_set<int> reachableOneRound(const int pos, const bool blockUsed = true, const std::optional<Ticket>& ticket = std::nullopt) const;
        std::unordered_set<int> getNewLocations(const std::unordered_set<int>& pos, const bool blockUsed = true, const std::optional<Ticket>& ticket = std::nullopt) const;
    };
    
} // namespace tlk
