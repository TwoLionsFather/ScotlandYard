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
        Bot_mrx(const VirtualMap& vMap, const int* round_ptr) 
            : Entity(Team::MRX), vMap(vMap), round_ptr(round_ptr) { };
        virtual ~Bot_mrx() { };

    protected:
        virtual double scoreCon(const Connection& c) override;
        virtual Ticket getTicket(ConnectionType usedTransportation) 
        {
            return smartTicket(usedTransportation);
        };

    private:
        const VirtualMap& vMap; 
        const int* round_ptr = 0;

        tlk::Ticket smartTicket(tlk::ConnectionType usedTransportation);
        tlk::Ticket randomTicket(tlk::ConnectionType usedTransportation);
    };
} // namespace tlk
