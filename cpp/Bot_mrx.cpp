#include "../hpp/Bot_mrx.hpp"

const tlk::Connection& tlk::Bot_mrx::random(const Connections& options) 
{
    return options[rand()%options.size()];
}

const tlk::Connection& tlk::Bot_mrx::maxDistToSLY(const Connections& options) 
{
    const Connection* best = &options[0];
    uint maxDistance = vMap.getDistanceToClosestSly(best->target);

    for (const Connection& con : options)
    {
        uint distance = vMap.getDistanceToClosestSly(con.target);
        if (maxDistance < distance)
        {
            best = &con;
            maxDistance = distance;
        }
    }

    return *best;
}

const tlk::Connection& tlk::Bot_mrx::getSelectionForMrx(const Connections& options) 
{
    return maxDistToSLY(options);
}

const tlk::Connection& tlk::Bot_mrx::getSelectionForSly(const Connections& options) 
{
    throw std::runtime_error("getSelectionForSly is not to be called for mrx units!");
}

tlk::Ticket tlk::Bot_mrx::randomGetTicketForMrx(tlk::ConnectionType usedTransportation)
{
    Ticket used = TicketStack::getTicketFor(usedTransportation);

    if (!tickets.isAdvancedTicketAvailable())
        return used;
    
    if (tickets.ticketCount(used) == 0 
    && tickets.ticketCount(BLACK_Ti) > 0)
        return BLACK_Ti;
    
    uint rand = std::rand() % 100;
    if (tickets.ticketCount(BLACK_Ti) > 0
    && rand < 10)
        return BLACK_Ti;
    
    rand = std::rand() % 100;
    if (tickets.ticketCount(DOUBLE_Ti) > 0
    && rand < 10)
        return DOUBLE_Ti;
    
    return used;
}

tlk::Ticket tlk::Bot_mrx::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
   return randomGetTicketForMrx(usedTransportation);
}