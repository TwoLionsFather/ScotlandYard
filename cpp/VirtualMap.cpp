#include "../hpp/VirtualMap.hpp"


bool tlk::VirtualMap::neighboursContainSLY (const int pos) const
{
    const std::vector<int> slyPos = tracker.getEntityLocations(true);

    //TODO implement algo using location of sly units and distance to
    return std::none_of(std::begin(slyPos) +1, std::end(slyPos),
        [&](int sly) { return originalMap.getDistanceBetween(pos, sly, true) == 1; });

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
    return getDistanceToMrxReport(tracker.getLocationOf(*ent));
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
    return getDistanceToClosestSly(tracker.getLocationOf(*e));
}

int tlk::VirtualMap::getDistanceToClosestSly(int pos) const
{
    const std::vector<int>& locations = tracker.getEntityLocations(true);
    const int target =  *std::min(std::begin(locations), std::end(locations)
                        , [&](const auto lA, const auto lB) {
                            return originalMap.getDistanceBetween(pos, *lA, true);
                        });
    return originalMap.getDistanceBetween(pos, target, true);
}

int tlk::VirtualMap::getDistanceBetween(const Entity* e, const int target) const
{
    return getDistanceBetween(tracker.getLocationOf(*e), target);
}

int tlk::VirtualMap::getDistanceBetween(const int pos, const int target) const
{
    return originalMap.getDistanceBetween(pos, target, true);
}

int tlk::VirtualMap::countSLYsInRange(const int pos, const int dist) const
{
    const std::unordered_set<int> locsInRange = getPossibleLocationsAfter(pos, dist, false);
    const std::vector<int> unorderedELocs = tracker.getEntityLocations(true);
    std::set<int> checkLocations(std::begin(locsInRange), std::end(locsInRange));
    std::set<int> slyLocations(std::begin(unorderedELocs), std::end(unorderedELocs));

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


std::unordered_set<int> tlk::VirtualMap::getPossibleLocationsAfter(const int start, int roundCount, const bool futureMode
                                                                , const std::optional<std::vector<Ticket>>& tickets) const
{
    std::unordered_set<int> locations;
    locations.emplace(start);

    if (roundCount <= 0)
        return locations;

    else if (roundCount > 200)
        roundCount = 200; //Max distance to next info is 5 and max distance between two points should be 200
    
    std::optional<Ticket> ticket;
    for (int simulatedRounds = 0; simulatedRounds < roundCount; ++simulatedRounds) 
    {
        if (tickets)
            ticket = tickets->at(simulatedRounds);

        locations = getNewLocations(locations, false, ticket);

    }

    return locations;
}

//Should tracker be used to simulate Moves? I think so
std::unordered_set<int> tlk::VirtualMap::getMrxPossibleLocationsAfter(const Entity* ent, const Connection& c) const
{
    const int entOriginalLocation = tracker.getLocationOf(*ent);
    tracker.simulatePosition(*ent, c.target);

    const std::vector<Ticket>& tickets = tracker.getMrxHistory();

    std::unordered_set<int> locations = getPossibleLocationsAfter(c.target, tickets.size(), true, std::make_optional(tickets)); 

    tracker.simulatePosition(*ent, entOriginalLocation);

    return locations;
}
