#include "../hpp/Bot_sly.hpp"

const tlk::Connection& tlk::Bot_sly::getSelectionForMrx(const Connections& options) 
{
    throw std::runtime_error("getSelectionForMrx is not to be called for sly units!");
}

const tlk::Connection& tlk::Bot_sly::randomGetSelectionForSly(const Connections& options) 
{
    const Connection* bestCon = &options[0];
    uint minDistance = virtualMap.getDistanceToMrx(options[0].target);

    for (const Connection& c : options)
    {
        uint distance = virtualMap.getDistanceToMrx(c.target);
        if (minDistance > distance)
        {
            bestCon = &c;
            minDistance = distance;
        }
    }

    return *bestCon;
}

const tlk::Connection& tlk::Bot_sly::getMinDistanceToMrxCon(const Connections& options)
{
    const Connection* bestCon = &options[0];
    uint minDistance = virtualMap.getDistanceToMrx(bestCon->target);

    for (const Connection& c : options)
    {
        uint distance = virtualMap.getDistanceToMrx(c.target);
        if (minDistance > distance)
        {
            bestCon = &c;
            minDistance = distance;
        }
    }

    return *bestCon;
}

const tlk::Connection& tlk::Bot_sly::getSelectionForSly(const Connections& options) 
{
    // return getMinDistanceToMrxCon(options);

    const Connection* bestCon = &options[0];

    if (virtualMap.getDistanceToMrx(this) > 2)
        return getMinDistanceToMrxCon(options);

    uint minMrxLocationsCount = virtualMap.getMrxPossibleLocationsAfter(this, bestCon).size();

    for (const Connection& c : options)
    {
        uint mrxLocationsCount = virtualMap.getMrxPossibleLocationsAfter(this, &c).size();
        if (minMrxLocationsCount > mrxLocationsCount)
        {
            bestCon = &c;
            minMrxLocationsCount = mrxLocationsCount;
        }
    }

    return *bestCon;
}

tlk::Ticket tlk::Bot_sly::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
    throw std::runtime_error("getTicketForMrx is not to be called on sly unit!");
}