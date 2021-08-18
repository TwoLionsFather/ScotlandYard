#include "../hpp/Bot_mrx.hpp"

double tlk::Bot_mrx::scoreCon(const tlk::Connection& c)
{
    int roundsTillReveal = 4 - (*round + 1) % 5;
    int distanceToClosestSLY = vMap.getDistanceToClosestSly(c.target);

    if (roundsTillReveal > 2 && distanceToClosestSLY > 2)
    {
        return 0.5 * distanceToClosestSLY + vMap.getDistanceToMrxReport(c.target);
    }

    return distanceToClosestSLY;
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