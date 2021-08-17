#pragma once

#include "Map.hpp"
#include "Connection.hpp"
#include "EntityTracker.hpp"
#include "TicketStack.hpp"

#include <algorithm>
#include <list>
#include <set>

namespace tlk
{
    class VirtualMap
    {
    public:
        VirtualMap(const Map& original, const EntityTracker& tracker)
            : originalMap(original), tracker(tracker) { };
        ~VirtualMap() { };

        uint getDistanceToMrxReport(uint pos) const;
        uint getDistanceToMrxReport(const Entity* ent) const;
        uint getDistanceToClosestSly(uint pos) const;
        uint getDistanceBetween(uint pos, uint target, bool blockUsedPositions) const;

        std::set<uint> getMrxPossibleLocationsAfter(const Entity* ent, const Connection* con) const;
        std::set<uint> getPossibleLocationsAfter(uint pos, int roundCount, bool blockUsedPositions) const;

    private:
        const Map& originalMap;
        const EntityTracker& tracker;
    };
    
} // namespace tlk
