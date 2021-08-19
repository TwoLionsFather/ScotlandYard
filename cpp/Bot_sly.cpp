#include "../hpp/Bot_sly.hpp"

double tlk::Bot_sly::scoreCon(const Connection& c) 
{
    if (*round < 3)
        return -minDistStart(c);

    double score = minDist(c) - ticketFactor(c.type);
    
    if (tlk::LOG_LEVEL >= HIGH)
        std::cout << score << " Score for " << c << std::endl;

    // if (score >= 2)       
        return -score;

    // return -minOptionsCount(c);
}

double tlk::Bot_sly::minOptionsCount(const Connection& c)
{
    return vMap.getMrxPossibleLocationsAfter(this, &c).size();
}

double tlk::Bot_sly::minDist(const Connection& c)
{
    return vMap.getDistanceToMrxReport(c.target);
}

double tlk::Bot_sly::minDistStart(const Connection& c)
{
    uint startingTarget = (*startingOptions)[0];

    double minDist = vMap.getDistanceBetween(this, startingTarget, false);
    for (int pos : *startingOptions)
    {
        double dist = vMap.getDistanceBetween(this, pos, false);
        if (minDist > dist)
        {
            startingTarget = pos;
            minDist = dist;
        }
    }

    return vMap.getDistanceBetween(c.target, startingTarget, false);
}
