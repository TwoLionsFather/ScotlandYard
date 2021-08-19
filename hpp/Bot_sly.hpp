#pragma once

#include "Entity.hpp"
#include "VirtualMap.hpp"
#include <random>
#include <chrono>

namespace tlk
{
    class Bot_sly : public Entity
    {
    public:
        Bot_sly(const VirtualMap& map, const int* round) 
            : Entity(Team::SLY), vMap(map), round(round) { };
        virtual ~Bot_sly() { };
        
    protected:
        virtual double scoreCon(const Connection& c) override;

    private:
        const VirtualMap& vMap; 
        const int* round = 0;
        int initialTarget = -1;
        
        //give slight edge if more tickets are available
        inline double ticketFactor(ConnectionType type)
        {
            return (*round / 22) *  0.01 * tickets.ticketCount(TicketStack::getTicketFor(type));
        }

        //Connection with highest score is selected!
        double minDist(const Connection& options);
        double minDistStart(const Connection& options);
        double minOptionsCount(const Connection& options);
    };
} // namespace tlk
