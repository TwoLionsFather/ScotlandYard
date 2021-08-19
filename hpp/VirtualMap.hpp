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
        VirtualMap(const Map& original, const EntityTracker& tracker)
            : originalMap(original), tracker(tracker) { };
        ~VirtualMap() { };

        int getDistanceToMrxReport (uint pos) const;
        int getDistanceToMrxReport (const Entity* e) const;
        int getDistanceToClosestSly () const;
        int getDistanceToClosestSly (uint pos) const;
        int getDistanceToClosestSly (const Entity* e) const;
        int getDistanceBetween (uint pos, uint target, bool blockUsedPositions) const;
        int getDistanceBetween( const Entity* e, const uint target, const bool blockUsedPositions) const;

        int countSLYsInRange(const Connection& con, int dist) const;

        std::unordered_set<uint> getMrxPossibleLocationsAfter (int roundCount, bool blockUsedPositions) const;
        std::unordered_set<uint> getMrxPossibleLocationsAfter (const Entity* ent, const Connection* con) const;
        std::unordered_set<uint> getPossibleLocationsAfter (uint pos, int roundCount, bool blockUsedPositions) const;

    private:
        const Map& originalMap;
        const EntityTracker& tracker;
    };
    
} // namespace tlk
