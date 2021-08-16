#include "../hpp/VirtualMap.hpp"


void tlk::VirtualMap::updatePosition(const Entity* e, unsigned int startingPos)
{
    bool newEntry = positions.emplace(e, startingPos).second;

    if (!newEntry)
        throw std::runtime_error("The Position wasn't initialized because the entity was already found inside the map!");

    Connections cons;
    cons.emplace_back(Connection(startingPos, tlk::UNDEFINED));
    entityMovementHistory.emplace(e, cons);
}

void tlk::VirtualMap::updatePosition(const Entity* e, const Connection* moved)
{
    if (positions.find(e) == positions.end())
        throw std::runtime_error("Can't update the position if entity wasn't initialized!");

    positions.find(e)->second = moved->target;
    entityMovementHistory.find(e)->second.push_back(*moved);
}

std::vector<unsigned int> tlk::VirtualMap::getEntityLocations(bool includeMrX)
{
    std::vector<unsigned int> location;
    std::transform(positions.begin(), positions.end(), std::back_inserter(location)
                    ,  [&](auto entry) {if (entry.first->isMrx() && !includeMrX)     //SLY Officers need to be able to move onto Mrxs location
                                            return (unsigned int) (0);
                        
                                        return entry.second;} );

    return location;
}

bool tlk::VirtualMap::gameIsWonBy(const Entity* e)  //TODO Move to Game instead
{
    return true;
}

std::vector<unsigned int> tlk::VirtualMap::getAllPossibleLocationsForMrx()
{
    return std::vector<unsigned int>();
}

std::vector<unsigned int> tlk::VirtualMap::getAllPossibleLocationsForMrxAfter(Connection simulatedMove)
{
    return std::vector<unsigned int>();
}