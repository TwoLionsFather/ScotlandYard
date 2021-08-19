#include "../hpp/EntityTracker.hpp"


void tlk::EntityTracker::simulatePosition(const Entity* e, int newPos)
{
    if (newPos == 0)
        throw std::runtime_error("Location 0 shouldn't be possible");
    positions.at(e) = newPos;
}

void tlk::EntityTracker::updatePosition(const Entity* e, int startingPos)
{
    if (startingPos == 0)
        throw std::runtime_error("Location 0 shouldn't be possible");

    bool newEntry = positions.emplace(e, startingPos).second;

    if (!newEntry)
        throw std::runtime_error("The Position wasn't initialized because the entity was already found inside the map when calling EntityTracker::updatePosition!");

    Connections moves;
    moves.emplace_back(startingPos, tlk::UNDEFINED);
    entityHistory.emplace(e, moves);
}

void tlk::EntityTracker::updatePosition(const Entity* e, const Connection* move, const Ticket used)
{
    if (move->target == 0)
        throw std::runtime_error("Location 0 shouldn't be possible");

    positions.at(e) = move->target;
    entityHistory.at(e).emplace_back(*move);

    if (e->isMrx())
        mrx_publicHistory.emplace_back(used);
}

int tlk::EntityTracker::getLocationOf(const Entity* e) const
{
    return positions.at(e);
}

int tlk::EntityTracker::getLocationOfMrx() const
{
    for (const auto& e : positions)
        if (e.first->isMrx())
            return e.second;

    throw std::runtime_error("EntityTracker::getLocationOfMrx No MrX was found!");
}

std::vector<int> tlk::EntityTracker::getEntityLocations(bool hideMrX) const
{
    std::vector<int> location;
    for (const auto& e : positions)
    {
        if (hideMrX && e.first->isMrx())
            continue;

        if (e.second == 0)
            throw std::runtime_error("Location 0 shouldn't be possible"); 

        location.emplace_back(e.second);
    }
    return location;
}