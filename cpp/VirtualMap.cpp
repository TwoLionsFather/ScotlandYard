#include "../hpp/VirtualMap.hpp"

uint tlk::VirtualMap::getDistanceToMrx(uint pos) const
{
    return getDistanceBetween(pos, tracker.getMrxLastSeenLocation(), false);
}

uint tlk::VirtualMap::getDistanceBetween(const uint pos, const uint target, const bool blockUsedPositions) const
{
    if (pos == target)
        return 0;
    
    if (originalMap.getGameFields().find(pos) == originalMap.getGameFields().end()
    ||  originalMap.getGameFields().find(target) == originalMap.getGameFields().end())
        throw std::runtime_error("VirtualMap::getDistanceBetween can't do it's job if Location is not part of Map!");

    int distance = 0;
    
    std::set<uint> locationsInRange;

    do {
        locationsInRange = getPossibleLocationsAfter(pos, distance++, blockUsedPositions);
        
        if (distance == 200)
            throw std::runtime_error("VirtualMap::getDistanceBetween Distance runaway situation!");
    } while (locationsInRange.find(target) == locationsInRange.end());

    return distance;
}

//Limited to 5 rounds to keep pc from dying
std::set<uint> tlk::VirtualMap::getPossibleLocationsAfter(const uint pos, int roundCount, bool blockUsedPositions) const
{
    std::set<uint> initialLocations;

    const auto& map = originalMap.getGameFields();

    if (map.find(pos) == map.end())
        throw std::runtime_error("VirtualMap::getPossibleLocationsAfter can't do it's job if Location is not part of Map!");

    if (roundCount <= 0)
        return initialLocations;

    if (roundCount > 200)
        roundCount = 200; //Max distance to next info is 5
    
    for (const tlk::Connection c : *(map.find(pos)->second.get()))
        initialLocations.emplace(c.target);
    
    std::vector<uint> posons = tracker.getEntityLocations(false);
    if (blockUsedPositions)
        for (uint ui : posons)
            initialLocations.erase(ui);
    
        
    if (roundCount-- == 1)
        return initialLocations;


    std::set<uint> possibleLocations;
    do {
        for (uint ui : initialLocations)
            for (const tlk::Connection c : *(map.find(ui)->second.get()))
                possibleLocations.emplace(c.target);
        
        if (blockUsedPositions)
            for (uint ui : posons)
                possibleLocations.erase(ui);

        initialLocations = possibleLocations;
    } while (--roundCount > 0);

    return initialLocations;
}

std::set<uint> tlk::VirtualMap::getPossibleLocationsAfter(uint pos, int roundCount, const TicketStack& tickets) const
{
    return getPossibleLocationsAfter(pos, roundCount, true);
}
