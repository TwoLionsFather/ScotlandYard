#pragma once

#include "Entity.hpp"
#include "Connection.hpp"
#include "PlayerInput.hpp"
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
        virtual const Connection& getSelection(const Connections& options) override
        {
            return tlk::PlayerInput::consoleSelectMoveFromOptions(options, tickets);
        }

        virtual Ticket getTicket(ConnectionType usedTransportation) override
        {
            return tlk::PlayerInput::consoleSelectTicket(usedTransportation, tickets);
        };
    };
}