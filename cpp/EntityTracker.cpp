#include "../hpp/EntityTracker.hpp"


void tlk::EntityTracker::updatePosition(const Entity* e, uint startingPos)
{
    bool newEntry = positions.emplace(e, startingPos).second;

    if (!newEntry)
        throw std::runtime_error("The Position wasn't initialized because the entity was already found inside the map when calling EntityTracker::updatePosition!");

    Connections moves;
    moves.emplace_back(startingPos, tlk::UNDEFINED);
    entityHistory.emplace(e, moves);
}

void tlk::EntityTracker::updatePosition(const Entity* e, const Connection* move, const Ticket used)
{
    positions.at(e) = move->target;
    entityHistory.at(e).emplace_back(*move);

    if (e->isMrx())
        mrx_publicHistory.emplace_back(used);
}

uint tlk::EntityTracker::getLocationOf(const Entity* e) const
{
    return positions.at(e);
}

uint tlk::EntityTracker::getLocationOfMrx() const
{
    for (const auto& e : positions)
        if (e.first->isMrx())
            return e.second;

    throw std::runtime_error("EntityTracker::getLocationOfMrx No MrX was found!");
}

std::list<uint> tlk::EntityTracker::getEntityLocations(bool hideMrX) const
{
    std::list<uint> location;//TODO use count
    for (const auto& e : positions)
    {
        if (hideMrX && e.first->isMrx())
            continue;

        location.emplace_back(e.second);
    }
    return location;
}