#include "../hpp/Bot_sly.hpp"

double tlk::Bot_sly::minDistStart(const Connection& c)
{
    uint startingTarget = (*startingOptions)[0];

    double minDist = vMap.getDistanceBetween(this, startingTarget, true);
    for (int pos : *startingOptions)
    {
        double dist = vMap.getDistanceBetween(this, pos, false);
        if (minDist > dist)
        {
            startingTarget = pos;
            minDist = dist;
        }
    }

    return -vMap.getDistanceBetween(c.target, startingTarget, false);
}

double tlk::Bot_sly::minDist(const Connection& c)
{
    return -vMap.getDistanceToMrxReport(c.target);
}