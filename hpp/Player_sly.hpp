#pragma once

#include "PlayerInput.hpp"
#include "Connection.hpp"
#include "Entity.hpp"
#include <iostream>
#include <string>

namespace tlk
{
    class Player_sly : public Entity
    {
    public:
        Player_sly() : Entity(Team::SLY) { };
        virtual ~Player_sly() { };

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options)
        {
            throw std::runtime_error("A Player in SLYs Role shouldn't select moves like MrX! wrong Method called for move selection on Player_sly");
        }

        virtual const Connection& getSelectionForSly(const Connections& options)
        {
            return tlk::PlayerInput::consoleSelectMoveFromOptions(options, tickets);
        }

        virtual Ticket getTicketForMrx(ConnectionType usedTransportation)
        {
            throw std::runtime_error("getTicketForMrx is not to be called on sly unit!");
        }
    };
}