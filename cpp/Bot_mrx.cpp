#include "../hpp/Bot_mrx.hpp"

double tlk::Bot_mrx::scoreCon(const tlk::Connection& c)
{
    int roundsTillReveal = 4 - (*round + 1) % 5;
    int distanceToClosestSLY = vMap.getDistanceToClosestSly(c.target);
    int outgoingCount = vMap.getPossibleLocationsAfter(c.target, 1, true).size();

    if (roundsTillReveal > 2 || distanceToClosestSLY > 2)
        return 0.5 * distanceToClosestSLY + vMap.getDistanceToMrxReport(c.target);
    
    if (distanceToClosestSLY > 2)
        return 0.5 * distanceToClosestSLY + 0.25 * outgoingCount;


    int slyCount = vMap.countSLYsInRange(c, distanceToClosestSLY);  //check distance to board center to not get stuck in corners?
    return distanceToClosestSLY + 0.1 * slyCount + 0.01 * outgoingCount;
}

tlk::Ticket tlk::Bot_mrx::smartTicket(tlk::ConnectionType usedTransportation)
{
    Ticket used = TicketStack::getTicketFor(usedTransportation);

    if (!tickets.isAdvancedTicketAvailable())
        return used;
    
    if (tickets.ticketCount(used) == 0 
    && tickets.ticketCount(BLACK_Ti) > 0)
        return BLACK_Ti;

    else if (tickets.ticketCount(used) == 0
    && tickets.ticketCount(BLACK_Ti) == 0) //There shouldn't be a case where mrx wasn't able to use the connection
        return DOUBLE_Ti;
    

    int distanceToSLY = vMap.getDistanceToClosestSly();
    if (tickets.ticketCount(DOUBLE_Ti) > 0
    && distanceToSLY <= 2)
        return DOUBLE_Ti;

    int possibleLocAfter = vMap.getMrxPossibleLocationsAfter(2, true).size();
    if (tickets.ticketCount(BLACK_Ti) > 0
    && (possibleLocAfter < 10
    || distanceToSLY <= 2))
        return BLACK_Ti;
    
    return used;
}

tlk::Ticket tlk::Bot_mrx::randomTicket(tlk::ConnectionType usedTransportation)
{
    Ticket used = TicketStack::getTicketFor(usedTransportation);

    if (!tickets.isAdvancedTicketAvailable())
        return used;
    
    if (tickets.ticketCount(used) == 0 
    && tickets.ticketCount(BLACK_Ti) > 0)
        return BLACK_Ti;
    
    int rand = std::rand() % 100;
    if (tickets.ticketCount(BLACK_Ti) > 0
    && rand < 10)
        return BLACK_Ti;
    
    rand = std::rand() % 100;
    if (tickets.ticketCount(DOUBLE_Ti) > 0
    && rand < 10)
        return DOUBLE_Ti;
    
    return used;
}