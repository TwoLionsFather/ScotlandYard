#pragma once

#include "Entity.hpp"
#include "VirtualMap.hpp"
#include <random>
#include <chrono>

namespace tlk
{
    class Bot_mrx : public Entity
    {
    public:
        Bot_mrx(const VirtualMap& vMap, const int* round) 
            : Entity(Team::MRX), vMap(vMap), round(round) { };
        virtual ~Bot_mrx() { };

    protected:
        virtual double scoreCon(const Connection& c) override;
        virtual Ticket getTicket(ConnectionType usedTransportation) 
        {
            return randomGetTicketForMrx(usedTransportation);
        };

    private:
        const VirtualMap& vMap; 
        const int* round = 0;

        tlk::Ticket randomGetTicketForMrx(tlk::ConnectionType usedTransportation);
    };
} // namespace tlk
