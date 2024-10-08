#include "../hpp/VirtualMap.hpp"


bool tlk::VirtualMap::neighboursContainSLY (const int pos) const
{
    const std::vector<int> slyPos = tracker.getSlyLocations();

    //TODO Maybe opposite required?
    return std::any_of(std::begin(slyPos) +1, std::end(slyPos)
                    , [&](const int sly) { return originalMap.getDistanceBetween(pos, sly, true) == 1; });
}

bool tlk::VirtualMap::neighboursContainMRXSighting (const int pos) const
{
    const int mrxSight = tracker.getMrxLastSeenLocation();
    const Connections& out = originalMap.getOutgoing(pos);

    return std::any_of(std::begin(out), std::end(out)
                    , [&](const Connection loc) { return loc.target == mrxSight; } );
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
    std::vector<int> locations = tracker.getSlyLocations();

    const auto target =  std::min_element(std::begin(locations), std::end(locations)
                        , [&](const auto lA, const auto lB) {
                            return originalMap.getDistanceBetween(pos, lA, true) < originalMap.getDistanceBetween(pos, lB, true);
                        });

    return originalMap.getDistanceBetween(pos, *target, true);
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
    const std::vector<int> slyPos = tracker.getSlyLocations();

    //TODO Maybe opposite required?
    return std::count_if(std::begin(slyPos) +1, std::end(slyPos)
                        , [&](const int sly) { return originalMap.getDistanceBetween(pos, sly, true) <= dist; });
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
        for (int i : tracker.getSlyLocations())
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

tlk::VirtualMap::VirtualMap(const tlk::Map &original, tlk::EntityTracker &tracker)
        : originalMap(original), tracker(tracker) {

}

tlk::VirtualMap::~VirtualMap() {

}
