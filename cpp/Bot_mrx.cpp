#include "../hpp/Bot_mrx.hpp"

double tlk::Bot_mrx::scoreCon(const tlk::Connection& c)
{
    // int roundsTillReveal = 4 - (*round + 1) % 5;

    int distanceToClosestSLY = vMap.getDistanceToClosestSly(c.target);
    int distanceToMrxReport = vMap.getDistanceToMrxReport(c.target);
    int outgoingCount = vMap.getPossibleLocationsAfter(c.target, 1, true).size(); // max is 12
    // int slyCount = vMap.countSLYsInRange(c.target, distanceToClosestSLY); // max is 4

    //use underground in Late game?
    return distanceToClosestSLY 
            + distanceToMrxReport * 0.5
            + outgoingCount / 12 ;
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
    && distanceToSLY < 2) //about equal performance of < and <=
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