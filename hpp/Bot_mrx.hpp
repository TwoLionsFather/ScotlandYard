#pragma once

#include "Entity.hpp"
#include <random>
#include <ctime>

namespace tlk
{
    class Bot_mrx : public Entity
    {
    public:
        Bot_mrx() : Entity(Team::MRX) { };
        virtual ~Bot_mrx() { };

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options) override;
        virtual const Connection& getSelectionForSly(const Connections& options) override;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) override;
    };
} // namespace tlk
