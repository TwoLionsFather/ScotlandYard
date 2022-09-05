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

const tlk::Connections tlk::EntityTracker::getMovesFor(const Entity& e) const
{
    const int loc = positions.at(&e);
    Connections options = map.getOutgoing(loc);

    options.erase(std::remove_if(std::begin(options)
                                , std::end(options) 
                                , [&](const Connection& c) {
                                    return e.hasTicketFor(c.type);
                                }), std::end(options)
    );  //remove if makes sure only valid elements are infront of returened iterator

    return options;
}


void tlk::EntityTracker::updatePosition(const Entity& e, const Move used)
{
    if (used.first.target == 0)
        throw std::runtime_error("EntityTracker::updatePosition Location 0 shouldn't be possible");

    positions.at(&e) = used.first.target;
    entityHistory.at(&e).emplace_back(used);

    if (e.isMrx())
        mrx_publicHistory.emplace_back(used.second);
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
    std::vector<int> location;
    for (const auto& e : positions)
    {
        if (hideMrX && e.first->isMrx())
            continue;

        if (e.second == 0)
            throw std::runtime_error("EntityTracker::getEntityLocations Location 0 shouldn't be possible"); 

        location.emplace_back(e.second);
    }
    return location;
}