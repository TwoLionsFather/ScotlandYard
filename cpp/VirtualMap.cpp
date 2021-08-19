#include "../hpp/VirtualMap.hpp"

int tlk::VirtualMap::getDistanceToMrxReport(uint pos) const
{
    return getDistanceBetween(pos, tracker.getMrxLastSeenLocation(), false);
}

int tlk::VirtualMap::getDistanceToMrxReport(const Entity* ent) const
{
    return getDistanceToMrxReport(tracker.getLocationOf(ent));
}

int tlk::VirtualMap::getDistanceToClosestSly() const
{
    return getDistanceToClosestSly(tracker.getLocationOfMrx());
}

int tlk::VirtualMap::getDistanceToClosestSly(const Entity* e) const
{
    return getDistanceToClosestSly(tracker.getLocationOf(e));
}

int tlk::VirtualMap::getDistanceToClosestSly(uint pos) const
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

int tlk::VirtualMap::getDistanceBetween(const Entity* e, const uint target, const bool blockUsedPositions) const
{
    return getDistanceBetween(tracker.getLocationOf(e), target, blockUsedPositions);
}

int tlk::VirtualMap::getDistanceBetween(const uint pos, const uint target, const bool blockUsedPositions) const
{
    if (pos == target)
        return 0;
    
    if (originalMap.getGameFields().find(pos) == originalMap.getGameFields().end()
    ||  originalMap.getGameFields().find(target) == originalMap.getGameFields().end())
        throw std::runtime_error("VirtualMap::getDistanceBetween can't do it's job if Location is not part of Map!");

    int distance = 0;
    
    std::unordered_set<uint> locationsInRange;

    do {
        locationsInRange = getPossibleLocationsAfter(pos, distance++, blockUsedPositions);
        
        if (distance == 200)
            throw std::runtime_error("VirtualMap::getDistanceBetween Distance runaway situation!");
    } while (locationsInRange.find(target) == locationsInRange.end());

    return distance;
}

int tlk::VirtualMap::countSLYsInRange(const Connection& con, int dist) const
{
    std::unordered_set<uint> unorderedLocs = getPossibleLocationsAfter(con.target, dist, false);
    std::list<uint> unorderedELocs = tracker.getEntityLocations(true);
    std::set<uint> checkLocations(unorderedLocs.cbegin(), unorderedLocs.cend());
    std::set<uint> slyLocations(unorderedELocs.cbegin(), unorderedELocs.cend());

    std::vector<uint> result;
    result.clear();
    std::set_intersection(checkLocations.begin(), checkLocations.end(), slyLocations.begin(), slyLocations.end(), std::back_inserter(result)); 

    return result.size();
}


//Limited to 5 rounds to keep pc from dying
std::unordered_set<uint> tlk::VirtualMap::getPossibleLocationsAfter(const uint pos, int roundCount, bool blockUsedPositions) const
{
    std::unordered_set<uint> initialLocations;

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

    std::unordered_set<uint> possibleLocations;
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

std::unordered_set<uint> tlk::VirtualMap::getMrxPossibleLocationsAfter(int roundCount, bool blockUsedPositions) const
{
    return getPossibleLocationsAfter(tracker.getMrxLastSeenLocation(), roundCount, blockUsedPositions);
}

std::unordered_set<uint> tlk::VirtualMap::getMrxPossibleLocationsAfter(const Entity* ent, const Connection* con) const
{
    const auto& map = originalMap.getGameFields();
    std::vector<Ticket> history = tracker.getMrxHistory();
    std::unordered_set<uint> initialLocations;

    if (history.empty())
        return  initialLocations;   

    int ticketRound = 0;

    for (const tlk::Connection c : *(map.at(tracker.getMrxLastSeenLocation()).get()))
        if (TicketStack::isAllowedConnection(history[ticketRound], c.type))
            initialLocations.emplace(c.target);

    uint entPos = tracker.getLocationOf(ent);
    std::list<uint> posons = tracker.getEntityLocations(true);
    posons.erase(std::remove_if(posons.begin(), posons.end(), [entPos](uint ui) {return ui == entPos;}), posons.end());
    posons.push_front(con->target);

    for (uint ui : posons)
        initialLocations.erase(ui);

    if (++ticketRound == history.size())
        return initialLocations;

    std::unordered_set<uint> possibleLocations;
    do {
        for (uint ui : initialLocations)
            for (const tlk::Connection& c : *(map.at(ui).get()))
                if (TicketStack::isAllowedConnection(history[ticketRound], c.type))
                    possibleLocations.emplace(c.target);
        
        for (uint ui : posons)
            possibleLocations.erase(ui);

        initialLocations = possibleLocations;
    } while (++ticketRound != history.size() && ticketRound < 5);

    if (ticketRound > 5)
        throw std::runtime_error("VirtualMap::getMrxPossibleLocationsAfter simulated to many rounds!");

    return initialLocations;
}
