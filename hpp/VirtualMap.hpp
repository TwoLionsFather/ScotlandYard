#pragma once

#include "Map.hpp"
#include "TicketStack.hpp"

#include <vector>

namespace tlk
{
    class VirtualMap
    {
    public:
        VirtualMap(const Map& original): originalMap(original) {};
        ~VirtualMap();

        uint getDistanceBetween(uint pos, uint target);

        std::vector<uint> getPossibleLocationsAfter(uint pos, int roundCount);
        std::vector<uint> getPossibleLocationsAfter(uint pos, int roundCount, const TicketStack& tickets);

    private:
        const Map& originalMap;
    };
    
} // namespace tlk
