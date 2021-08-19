#include "../hpp/VirtualMap.hpp"

int tlk::VirtualMap::getDistanceToMrxReport(int pos) const
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

std::unordered_set<int> tlk::VirtualMap::getMrxPossibleLocationsAfter(int roundCount, const bool blockUsed) const
{
    return getPossibleLocationsAfter(tracker.getMrxLastSeenLocation(), roundCount, blockUsed);
}

int tlk::VirtualMap::getDistanceToClosestSly(int pos) const
{
    const std::vector<int>& locations = tracker.getEntityLocations(true);
    int min = 500;

    for (int loc : locations)
    {
        const int dist = getDistanceBetween(pos, loc, false);
        if (min > dist)
            min = dist;
    }
    
    return min;
}

int tlk::VirtualMap::getDistanceBetween(const Entity* e, const int target, const bool blockUsed) const
{
    return getDistanceBetween(tracker.getLocationOf(e), target, blockUsed);
}

int tlk::VirtualMap::getDistanceBetween(const int pos, const int target, const bool blockUsed) const
{
    if (pos == target)
        return 0;

    int distance = 0;
    std::unordered_set<int> locationsInRange;

    do {
        locationsInRange = getPossibleLocationsAfter(pos, distance++, blockUsed);
        
        if (distance == 200)
            throw std::runtime_error("VirtualMap::getDistanceBetween Distance runaway situation!");
    } while (locationsInRange.find(target) == locationsInRange.end());

    return distance;
}

int tlk::VirtualMap::countSLYsInRange(const Connection& con, int dist) const
{
    std::unordered_set<int> unorderedLocs = getPossibleLocationsAfter(con.target, dist, false);
    std::vector<int> unorderedELocs = tracker.getEntityLocations(true);
    std::set<int> checkLocations(unorderedLocs.cbegin(), unorderedLocs.cend());
    std::set<int> slyLocations(unorderedELocs.cbegin(), unorderedELocs.cend());

    std::vector<int> result;
    result.clear();
    std::set_intersection(checkLocations.begin(), checkLocations.end(), slyLocations.begin(), slyLocations.end(), std::back_inserter(result)); 

    return result.size();
}

//TODO Make Boat unusable for SLY
std::unordered_set<int> tlk::VirtualMap::reachableOneRound(const int pos, const bool blockUsed
                                                        , const std::optional<Ticket>& ticket) const
{
    std::unordered_set<int> possibleLocations;
    for (const tlk::Connection& c : originalMap.getOutgoing(pos))
    {
        if (!ticket) 
            possibleLocations.emplace(c.target);

        else if (TicketStack::isAllowedConnection(*ticket, c.type))
            possibleLocations.emplace(c.target);

    }
        
    if (blockUsed)
        for (int i : tracker.getEntityLocations(true))
            possibleLocations.erase(i);


    return possibleLocations;
}

std::unordered_set<int> tlk::VirtualMap::getNewLocations(const std::unordered_set<int>& pos, const bool blockUsed
                                                        , const std::optional<Ticket>& ticket) const
{
    std::unordered_set<int> locations;
    for (int i : pos)
    {
        std::unordered_set<int> newLocations = reachableOneRound(i, blockUsed, ticket);
        std::for_each(newLocations.begin(), newLocations.end(), [&locations](int i) {locations.emplace(i);});
    }
    return locations;
}

//Limited to 200 rounds to keep pc from dying
std::unordered_set<int> tlk::VirtualMap::getPossibleLocationsAfter(const int pos, int roundCount, const bool blockUsed
                                                                , const std::optional<std::vector<Ticket>>& tickets) const
{
    std::unordered_set<int> locations;
    locations.emplace(pos);

    if (roundCount <= 0)
        return locations;

    else if (roundCount > 200)
        roundCount = 200; //Max distance to next info is 5 and max distance between two points should be 200
    
    std::optional<Ticket> ticket;

    int simulatedRounds = 0;
    while (simulatedRounds < roundCount) 
    {
        if (tickets)
            ticket = tickets->at(simulatedRounds);

        locations = getNewLocations(locations, false, ticket);
        simulatedRounds++;
    }

    return locations;
}

//Should tracker be used to simulate Moves? I think so
std::unordered_set<int> tlk::VirtualMap::getMrxPossibleLocationsAfter(const Entity* ent, const Connection& c) const
{
    const int entOriginalLocation = tracker.getLocationOf(ent);
    tracker.simulatePosition(ent, c.target);

    const std::vector<Ticket>& tickets = tracker.getMrxHistory();

    std::unordered_set<int> locations = getPossibleLocationsAfter(c.target, tickets.size(), true, std::make_optional(tickets)); 

    tracker.simulatePosition(ent, entOriginalLocation);

    return locations;
}
