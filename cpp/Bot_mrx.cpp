#include "../hpp/Bot_mrx.hpp"

double tlk::Bot_mrx::scoreCon(const tlk::Connection& c)
{
    int distanceToReveal = 4 - (*round + 1) % 5;
    std::cout << "MrX Round: " << distanceToReveal << std::endl;
    return vMap.getDistanceToClosestSly(c.target);
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