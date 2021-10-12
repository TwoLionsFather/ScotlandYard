#include "../hpp/Bot_sly.hpp"

double tlk::Bot_sly::scoreCon(const Connection& c) 
{
    if (*round < 3)
        return -minDistStart(c);

    double score = minDist(c) - ticketFactor(c.type);
    
    if (tlk::LOG_LEVEL >= HIGH)
        std::cout << "Bot_sly::scoreCon " << score << " Score for " << c << std::endl;

    // if (score >= 2)       
        return -score;

    // return -minOptionsCount(c);
}

double tlk::Bot_sly::ticketFactor(ConnectionType type)
{
    return 0.1 * *round /22 * tickets.ticketCount(TicketStack::getTicketFor(type));
}

double tlk::Bot_sly::minOptionsCount(const Connection& c)
{
    return vMap.getMrxPossibleLocationsAfter(this, c).size();
}

double tlk::Bot_sly::minDist(const Connection& c)
{
    return vMap.getDistanceToMrxReport(c.target);
}

double tlk::Bot_sly::minDistStart(const Connection& c)
{
    return vMap.getDistanceBetween(c.target, 100);
}
