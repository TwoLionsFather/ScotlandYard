#pragma once

#include "Entity.hpp"
#include "Connection.hpp"
#include <iostream>
#include <string>

namespace tlk
{
    class Player_mrx : public Entity
    {
    public:
        Player_mrx() : Entity(Team::MRX) { };
        virtual ~Player_mrx() { };

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options) override;
        virtual const Connection& getSelectionForSly(const Connections& options) override;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) override;
    };
}