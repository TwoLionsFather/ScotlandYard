#include "../hpp/Bot_sly.hpp"

const tlk::Connection& tlk::Bot_sly::getSelectionForMrx(const Connections& options) 
{
    throw std::runtime_error("getSelectionForMrx is not to be called for sly units!");
}

const tlk::Connection& tlk::Bot_sly::random(const Connections& options) 
{
    const Connection* bestCon = &options[0];
    uint minDistance = vMap.getDistanceToMrxReport(options[0].target);

    for (const Connection& c : options)
    {
        uint distance = vMap.getDistanceToMrxReport(c.target);
        if (minDistance > distance)
        {
            bestCon = &c;
            minDistance = distance;
        }
    }

    return *bestCon;
}

const tlk::Connection& tlk::Bot_sly::minDist(const Connections& options)
{
    const Connection* bestCon = &options[0];
    uint minDistance = vMap.getDistanceToMrxReport(bestCon->target);

    for (const Connection& c : options)
    {
        uint distance = vMap.getDistanceToMrxReport(c.target);
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
    if (vMap.getDistanceToMrxReport(this) > 2)
        return minDist(options);

    const Connection* bestCon = &options[0];
    uint minMrxLocCount = vMap.getMrxPossibleLocationsAfter(this, bestCon).size();

    for (const Connection& c : options)
    {
        uint mrxLocCount = vMap.getMrxPossibleLocationsAfter(this, &c).size();
        if (minMrxLocCount > mrxLocCount)
        {
            bestCon = &c;
            minMrxLocCount = mrxLocCount;
        }
    }

    return *bestCon;
}

tlk::Ticket tlk::Bot_sly::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
    throw std::runtime_error("getTicketForMrx is not to be called on sly unit!");
}