#include "../hpp/VirtualMap.hpp"


void tlk::VirtualMap::updatePosition(const Entity* e, unsigned int startingPos)
{
    bool newEntry = positions.emplace(e, startingPos).second;

    if (!newEntry)
        throw std::runtime_error("The Position wasn't initialized because the entity was already found inside the map when calling VirtualMap::updatePosition!");

    Connections cons;
    cons.emplace_back(Connection(startingPos, tlk::UNDEFINED));
    entityMovementHistory.emplace(e, cons);
}

void tlk::VirtualMap::updatePosition(const Entity* e, const Connection* moved)
{
    if (positions.find(e) == positions.end())
        throw std::runtime_error("Can't update the position if entity wasn't initialized inside of VirtualMap::updatePosition!");

    positions.find(e)->second = moved->target;
    entityMovementHistory.find(e)->second.push_back(*moved);
}

unsigned int tlk::VirtualMap::getLocationOf(const Entity* e) const
{
    if (positions.find(e) == positions.end())
        throw std::runtime_error("Can't get the position of entity that wasn't initialized inside of VirtualMap::getLocationOf!");

    return positions.find(e)->second;
}

std::vector<unsigned int> tlk::VirtualMap::getEntityLocations(bool hideMrX) const
{
    std::vector<unsigned int> location;
    std::transform(positions.begin(), positions.end(), std::back_inserter(location)
                    ,  [&](auto entry) {if (hideMrX && entry.first->isMrx())     //SLY Officers need to be able to move onto Mrxs location
                                            return (unsigned int) (0);
                                        else
                                            return entry.second;} );

    return location;
}

bool tlk::VirtualMap::gameIsWonBy(const Entity* e) const
{
    return true;
}

std::vector<unsigned int> tlk::VirtualMap::getAllPossibleLocationsForMrx() const
{
    return std::vector<unsigned int>();
}

std::vector<unsigned int> tlk::VirtualMap::getAllPossibleLocationsForMrxAfter(Connection simulatedMove) const
{
    return std::vector<unsigned int>();
}