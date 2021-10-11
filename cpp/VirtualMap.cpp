#include "../hpp/VirtualMap.hpp"

bool tlk::VirtualMap::neighboursContainSLY (const int pos) const
{
    std::unordered_set<int> slyPos;
    for (int i : tracker.getEntityLocations(true))
    {
        slyPos.emplace(i);
    }

    for (const Connection& cond1 : originalMap.getOutgoing(pos))
    {
        for (const Connection& cond2 : originalMap.getOutgoing(cond1.target))
        {
            if (slyPos.find(cond2.target) != slyPos.end())
                return true;
        }
    }

    return false;
}

bool tlk::VirtualMap::neighboursContainMRXSighting (const int pos) const
{
    const int mrxSight = tracker.getMrxLastSeenLocation();
    for (const Connection& cond1 : originalMap.getOutgoing(pos))
    {
        for (const Connection& cond2 : originalMap.getOutgoing(cond1.target))
        {
            if (cond2.target == mrxSight)
                return true;
        }
    }

    return false;
}

int tlk::VirtualMap::getDistanceToMrxReport(const Entity* ent) const
{
    return getDistanceToMrxReport(tracker.getLocationOf(ent));
}

int tlk::VirtualMap::getDistanceToMrxReport(int pos) const
{
    return getDistanceBetween(pos, tracker.getMrxLastSeenLocation());
}

int tlk::VirtualMap::getDistanceToClosestSly() const
{
    return getDistanceToClosestSly(tracker.getLocationOfMrx());
}

int tlk::VirtualMap::getDistanceToClosestSly(const Entity* e) const
{
    return getDistanceToClosestSly(tracker.getLocationOf(e));
}

int tlk::VirtualMap::getDistanceToClosestSly(int pos) const
{
    const std::vector<int>& locations = tracker.getEntityLocations(true);
    int min = 500;

    for (int loc : locations)
    {
        const int dist = getDistanceBetween(pos, loc, true);
        if (min > dist)
            min = dist;
    }
    
    return min;
}

int tlk::VirtualMap::getDistanceBetween(const Entity* e, const int target) const
{
    return getDistanceBetween(tracker.getLocationOf(e), target);
}

int tlk::VirtualMap::getDistanceBetween(const int pos, const int target) const
{
    return getDistanceBetween(pos, target, true);
}

int tlk::VirtualMap::getDistanceBetween(const int pos, const int target, bool noBoat) const
{
    if (pos == target)
        return 0;

    int distance = 1;
    bool locationsUsed[201] = { false };
    std::vector<int> locationsQueue, newLocs;

    locationsUsed[pos] = true;
    locationsQueue.emplace_back(pos);

    do {
        for (int i : locationsQueue)
            for (const Connection& con : originalMap.getOutgoing(i))
            {
                if (locationsUsed[con.target])
                    continue;

                else if (noBoat && con.type == tlk::BOAT)
                    continue;

                newLocs.emplace_back(con.target);
                locationsUsed[con.target] = true;
            }

        locationsQueue.swap(newLocs);
        newLocs.clear();

        if (distance++ == 200)
            throw std::runtime_error("VirtualMap::getDistanceBetween Distance runaway situation!");
    } while (!locationsUsed[target]);

    return distance;
}

int tlk::VirtualMap::countSLYsInRange(int pos, int dist) const
{
    std::unordered_set<int> unorderedLocs = getPossibleLocationsAfter(pos, dist, false);
    std::vector<int> unorderedELocs = tracker.getEntityLocations(true);
    std::set<int> checkLocations(unorderedLocs.cbegin(), unorderedLocs.cend());
    std::set<int> slyLocations(unorderedELocs.cbegin(), unorderedELocs.cend());

    std::vector<int> result;
    result.clear();
    std::set_intersection(checkLocations.begin(), checkLocations.end(), slyLocations.begin(), slyLocations.end(), std::back_inserter(result)); 

    return result.size();
}

std::unordered_set<int> tlk::VirtualMap::getMrxPossibleLocationsAfter(int roundCount, const bool blockUsed) const
{
    return getPossibleLocationsAfter(tracker.getMrxLastSeenLocation(), roundCount, blockUsed);
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

        else if (TicketStack::validTicketForType(*ticket, c.type))
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
