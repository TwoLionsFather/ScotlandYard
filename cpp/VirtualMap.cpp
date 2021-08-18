#include "../hpp/VirtualMap.hpp"

uint tlk::VirtualMap::getDistanceToMrxReport(uint pos) const
{
    return getDistanceBetween(pos, tracker.getMrxLastSeenLocation(), false);
}

uint tlk::VirtualMap::getDistanceToMrxReport(const Entity* ent) const
{
    return getDistanceToMrxReport(tracker.getLocationOf(ent));
}

uint tlk::VirtualMap::getDistanceToClosestSly(uint pos) const
{
    const std::list<uint>& locations = tracker.getEntityLocations(true);
    uint min = 500;

    for (uint loc : locations)
    {
        if (loc == 0)
            continue;

        const uint dist = getDistanceBetween(pos, loc, false);
        if (min > dist)
            min = dist;
    }
    
    return min;
}

uint tlk::VirtualMap::getDistanceBetween(const Entity* e, const uint target, const bool blockUsedPositions) const
{
    return getDistanceBetween(tracker.getLocationOf(e), target, blockUsedPositions);
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
    
    for (const Connection c : *(map.find(pos)->second.get()))
        initialLocations.emplace(c.target);
    
    const std::list<uint>& posons = tracker.getEntityLocations(false); //TODO check if correct and fix so that only future moves are effected
    if (blockUsedPositions)
        for (uint ui : posons)
            initialLocations.erase(ui);
    
    if (--roundCount == 0)
        return initialLocations;

    std::set<uint> possibleLocations;
    //TODO make more efficent
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

std::set<uint> tlk::VirtualMap::getMrxPossibleLocationsAfter(const Entity* ent, const Connection* con) const
{
    const auto& map = originalMap.getGameFields();
    const std::vector<Ticket>& history = tracker.getMrxHistory();

    std::set<uint> initialLocations;
    
    if (history.empty())
        return initialLocations;

    auto histIterator = history.begin();
    Ticket used = *histIterator++;
    for (const tlk::Connection c : *(map.find(tracker.getMrxLastSeenLocation())->second.get()))
        if (TicketStack::isAllowedConnection(used, c.type))
            initialLocations.emplace(c.target);
    
    uint entPos = tracker.getLocationOf(ent);
    std::list<uint> posons = tracker.getEntityLocations(true);
    posons.erase(std::remove_if(posons.begin(), posons.end(), [entPos](uint ui) {return ui == entPos;}), posons.end());
    posons.push_front(con->target);

    for (uint ui : posons)
        initialLocations.erase(ui);

    if (histIterator == history.end())
        return initialLocations;

    std::set<uint> possibleLocations;
    do {
        used = *histIterator++;
        for (uint ui : initialLocations)
            for (const tlk::Connection c : *(map.find(ui)->second.get()))
                if (TicketStack::isAllowedConnection(used, c.type))
                    possibleLocations.emplace(c.target);
        
        for (uint ui : posons)
            possibleLocations.erase(ui);

        initialLocations = possibleLocations;
    } while (histIterator != history.end());

    return initialLocations;
}
