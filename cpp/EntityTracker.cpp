#include "../hpp/EntityTracker.hpp"

void tlk::EntityTracker::track(const Entity& e)
{
    if (positions.count(&e) == 1)
        throw std::runtime_error("EntityTracker::track could not track, Entity is tracked already!");

    positions.emplace(&e, -1); //init position before game
    entityHistory.emplace(&e, Moves{});
}

void tlk::EntityTracker::simulatePosition(const Entity& e, int newPos)
{
    if (newPos == 0)
        throw std::runtime_error("EntityTracker::simulatePosition Location 0 shouldn't be possible");
    
    positions.at(&e) = newPos;
}

void tlk::EntityTracker::setStartingPos(const Entity& e, int startingPos)
{
    if (startingPos == 0 || startingPos == 108)
        throw std::runtime_error("EntityTracker::setStartingPos Location 0 | 108 shouldn't be possible");

    if (positions.at(&e) != -1)
        throw std::runtime_error("The Position wasn't initialized because the entity was already moved inside the map when calling EntityTracker::setStartingPos!");

    positions.at(&e)= startingPos;
    entityHistory.at(&e).emplace_back(Connection{startingPos, tlk::UNDEFINED}, tlk::Ticket::NO_TICKET);
}

tlk::Connections tlk::EntityTracker::getMovesFor(const Entity& e) const
{
    if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "Getting Moves for Entity: " << std::endl;
    const int loc = positions.at(&e);

    if (tlk::LOG_LEVEL >= tlk::HIGH)
    {
        std::cout << "at loc " << loc << std::endl;
        std::cout << "using map: " << &map << std::endl;
    }

    Connections options = map.getOutgoing(loc);

     if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "with options " << options  << std::endl;

    options.erase(std::remove_if(std::begin(options)
                                , std::end(options) 
                                , [&](const Connection& c) {
                                    return !e.hasTicketFor(c.type);
                                }), std::end(options)
    );  //remove if makes sure only valid elements are infront of returened iterator



    if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "legal options " << options  << std::endl;

    return options;
}


void tlk::EntityTracker::updatePosition(const Entity& e, const Move used)
{
    if (used.first.target == 0)
        throw std::runtime_error("EntityTracker::updatePosition Location 0 shouldn't be possible");

    positions.at(&e) = used.first.target;
    entityHistory.at(&e).emplace_back(used);

    if (e.isMrx())
        mrx_ticketHistory.emplace_back(used.second);
}

int tlk::EntityTracker::getLocationOf(const Entity& e) const
{
    return positions.at(&e);
}

int tlk::EntityTracker::getLocationOfMrx() const
{
    for (const auto& e : positions)
        if (e.first->isMrx())
            return e.second;

    throw std::runtime_error("EntityTracker::getLocationOfMrx No MrX was found!");
}

const std::vector<int> tlk::EntityTracker::getEntityLocations(bool hideMrX) const
{
    std::vector<int> locations;
    for (const auto& e : positions)
    {
        if (e.first->isMrx())
        {
            if (!hideMrX)
                locations.emplace(std::begin(locations), e.second);
            else
                locations.emplace(std::begin(locations), 0);

            continue;
        }

        if (e.second == 0 || e.second == 108)
            throw std::runtime_error("EntityTracker::getEntityLocations Location 0 shouldn't be possible"); 

        locations.emplace_back(e.second);
    }

    return locations;
}

const std::vector<int> tlk::EntityTracker::getSlyLocations() const
{
    std::vector<int> slyLocs = getEntityLocations(true);
    slyLocs.erase(std::begin(slyLocs));
    return slyLocs;
}

const std::vector<int> tlk::EntityTracker::getSlyLocations(const int roundOffset) const
{
    std::vector<int> locations;
    for (const auto pair : entityHistory)
    {
        if (pair.first->isMrx())
            continue;

        const Connection used = (pair.second.crbegin() + std::abs(roundOffset))->first; 

        locations.emplace_back(used.target);
        std::cout << "location of sly was: " << locations.back() << std::endl;
    }

    return locations;
}

tlk::EntityTracker::~EntityTracker()
{
    mrx_ticketHistory.clear();
    entityHistory.clear();
    positions.clear();
}

tlk::EntityTracker::EntityTracker(const tlk::Map &map)
        : map(map), mrxLastSeenLocation(0) {

}

void tlk::EntityTracker::setMrxLocation(int loc)
{
    mrxLastSeenLocation = loc;
    if (!mrx_ticketHistory.empty())
        mrx_ticketHistory.erase(mrx_ticketHistory.cbegin(), --mrx_ticketHistory.cend());
}

int tlk::EntityTracker::getMrxLastSeenLocation() const
{
    return mrxLastSeenLocation;
}

const std::vector<tlk::Ticket> &tlk::EntityTracker::getMrxHistory() const
{
    return mrx_ticketHistory;
}

const tlk::Connections tlk::EntityTracker::getEntityMovesHistory(const tlk::Entity &e) const
{
    Connections conns;
    for (auto move : entityHistory.at(&e))
    {
        conns.push_back(move.first);
    }

    return conns;
}
