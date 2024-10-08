#include "../hpp/Bot_mrx.hpp"

double tlk::Bot_mrx::scoreCon(const tlk::Connection& c)
{
    if (tlk::LOG_LEVEL >= HIGH)
    {
        std::cout << "Bot_mrx::scoreCon Scoring " << std::endl;
        std::cout << "Connection: " << c << std::endl;
    }
    // int round_ptrsTillReveal = 4 - (*round_ptr + 1) % 5;

    double distanceToClosestSLY = vMap.getDistanceToClosestSly(c.target);
    double distanceToMrxReport = vMap.getDistanceToMrxReport(c.target);
    double outgoingCount = vMap.getPossibleLocationsAfter(c.target, 1, true).size(); // max is 12
    // int slyCount = vMap.countSLYsInRange(c.target, distanceToClosestSLY); // max is 4

    double score = distanceToClosestSLY 
            + distanceToMrxReport * 0.5
            + outgoingCount / 12;

    if (distanceToClosestSLY <= 1)
        score =  0;

    if (tlk::LOG_LEVEL >= HIGH)
        std::cout << " Score: " << score << " d: "<< distanceToClosestSLY << std::endl;

    //use underground in Late game?
    return score;
}

tlk::Ticket tlk::Bot_mrx::smartTicket(tlk::ConnectionType usedTransportation)
{
    Ticket used = TicketStack::getTicketFor(usedTransportation);

    if (!tickets.isAdvancedTicketAvailable())
        return used;
    
    if (tickets.ticketCount(used) == 0)
        return (tickets.ticketCount(BLACK_Ti) > 0)? BLACK_Ti:DOUBLE_Ti;
    

    int distanceToSLY = vMap.getDistanceToClosestSly();
    if ((tickets.ticketCount(DOUBLE_Ti) > 0)
    && distanceToSLY < 2) //about equal performance of < and <=
        return DOUBLE_Ti;

    int possibleLocAfter = vMap.getMrxPossibleLocationsAfter(2, true).size();
    if ((tickets.ticketCount(BLACK_Ti) > 0)
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

tlk::Ticket tlk::Bot_mrx::getTicket(tlk::ConnectionType usedTransportation) {
        return smartTicket(usedTransportation);
}

tlk::Bot_mrx::Bot_mrx(const tlk::VirtualMap &vMap, const int *round_ptr)
        : Entity(Team::MRX), vMap(vMap), round_ptr(round_ptr) {

}

tlk::Bot_mrx::~Bot_mrx() {

};
