#include "../hpp/Bot_sly.hpp"

const tlk::Connection& tlk::Bot_sly::getSelectionForMrx(const Connections& options) 
{
    throw std::runtime_error("getSelectionForMrx is not to be called for sly units!");
}

const tlk::Connection& tlk::Bot_sly::getSelectionForSly(const Connections& options) 
{
    const Connection* bestCon = &options[0];
    uint minDistance = virtualMap.getDistanceToMrx(options[0].target);

    for (const Connection& c : options)
        if (minDistance > virtualMap.getDistanceToMrx(c.target))
        {
            bestCon = &c;
            minDistance = virtualMap.getDistanceToMrx(c.target);
        }

    return *bestCon;
}

tlk::Ticket tlk::Bot_sly::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
    throw std::runtime_error("getTicketForMrx is not to be called on sly unit!");
}